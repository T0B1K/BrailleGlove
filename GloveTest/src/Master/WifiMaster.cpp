#include "WifiMaster.h"

#ifdef UNIT_TEST
    extern MockESPClass ESP;
    #ifndef HTTP_GET
        #define HTTP_GET 1
    #endif
    #ifndef HTTP_POST
        #define HTTP_POST 0
    #endif
#endif

WifiMaster::WifiMaster(GloveModel gloveModel): server(80), gloveModel(gloveModel) {} // Initialize tcpServer with port 80

void WifiMaster::setFrontend(){
    if (LittleFS.exists("/switch.html")) {
        File file = LittleFS.open("/switch.html", "r"); // Open the file for reading
        if (file) {
            String content = file.readString(); // Read the file content into a string
            server.send(200, "text/html", content); // Send the content as a response
            file.close(); // Don't forget to close the file
        } else {
            server.send(500, "text/plain", "Server error: Unable to read file");
        }
    } else {
        server.send(404, "text/plain", "File not found");
    }
}

String concatenateString(String string, int amount){
    String concatenatedPattern = "";
    for (int i = 0; i < amount; ++i) {
        concatenatedPattern += string;
    }
    return concatenatedPattern;
}

void WifiMaster::frontendSetPattern(String pattern, ChordingScheme status, bool longPattern) {    
    String usedPattern = pattern;
    std::vector<int> shortPattern = computePatternFromText(pattern);
    int repeat = 0;
    if(longPattern){//save it for the ajax call
        repeat = (status == OST_ENCODING)? SingeltonGloveSettings::getInstance().studyOstRepititions: SingeltonGloveSettings::getInstance().studySeqRepititions; 
        usedPattern = concatenateString(pattern, repeat);
        this->pattern = usedPattern;
    }else{
        this->pattern = pattern;
    }
    std::vector<int> glovePattern = computePatternFromText(usedPattern);
    gloveModel.setPattern(glovePattern); //save the pattern for oneself
    gloveModel.setChordMode(status);
    sendVectorToSlave(shortPattern, status, repeat);     //send the pattern to the other glove
    idx = 99999;                       //prevent ajax
    setFrontend();
}

void WifiMaster::frontendAjaxCall(){
    if (idx < (int)gloveModel.getPatternLength()) {
        String charToSend = String(pattern[idx]);
        int asciNumber = (int)pattern[idx];
        server.send(200, "text/plain", charToSend);
        if(asciNumber == 32){
            Encoding::customDelay(SingeltonGloveSettings::getInstance().PAUSE);
        }else{
            Encoding::customDelay(SingeltonGloveSettings::getInstance().AUDIO_STIMULI_OFFSET);
        }
        sendIntegerToSlave(idx);
        this->gloveModel.executePatternAt(idx);
        idx++;
    } else {
        server.send(200, "text/plain", "");  //otherwise the whole website gets resent
        idx = 0;
    }
}

std::vector<int> WifiMaster::computePatternFromText(String text){
    std::vector<int> values = brailleMapper.stringToIntegerList(text);           //character to the braille integer
    return queue.reorderVectorBySensitivity(values);                             //braille integer according to sensitivity 
}

void WifiMaster::setupWifi(){
    WiFi.persistent(false);
    WiFi.mode(WIFI_AP); // Set to Station mode
    WiFi.disconnect();
    WiFi.softAP(SingeltonWifiConnector::getInstance().MASTER_SSID);
}

void WifiMaster::setupESPNow() {
 if (!LittleFS.begin()) {
        return;
    }
    if (!WifiEspNow.begin()) {
        ESP.restart(); // Restart if initialization fails
    }
    const int maxRetries = 5; // Number of retries
    int attempts = 0;
    while (attempts < maxRetries) {// Add the slave as a peer
        if (WifiEspNow.addPeer(SingeltonWifiConnector::getInstance().SLAVE_MAC)) {
            break; // Exit loop if successful
        } else {
            attempts++;
            delay(1000); // Delay before retrying
        }
    }

    if (attempts == maxRetries) {
        ESP.restart();
    }
}

void WifiMaster::setup() {
    setupWifi();
    delay(200);
    setupESPNow();
   
    server.on("/start", [this]() {
        idx = 0;  // Reset index when starting
        setFrontend();
    });
    server.on("/setpattern", HTTP_POST,  [this]() { 
        ChordingScheme status = OST_ENCODING;
        if(server.hasArg("ostStatus")){
            String ostStatus = server.arg("ostStatus");
            status = (ostStatus == "false")? SEQUENTIAL_ENCODING : OST_ENCODING;
        }
        if (server.hasArg("pattern")) {
            String pattern = server.arg("pattern");
            frontendSetPattern(pattern, status, false);
            server.send(200, "text/plain", "Pattern received: " + pattern);  // Send a response back
        } else {
            server.send(400, "text/plain", "No pattern received");  // Error response if no pattern was provided
        }
    });
    server.on("/setstartpattern", HTTP_POST,  [this](){
        ChordingScheme status = OST_ENCODING;
        if(server.hasArg("ostStatus")){
            String ostStatus = server.arg("ostStatus");
            status = (ostStatus == "false")? SEQUENTIAL_ENCODING : OST_ENCODING;
        }
        if (server.hasArg("pattern")) {
            String pattern = server.arg("pattern");
            frontendSetPattern(pattern, status, true);
        }
        server.send(200, "text/plain", "Pattern received: ");
    });
    server.on("/ajax", HTTP_GET, [this]() {frontendAjaxCall();});
    server.on("/", HTTP_GET, [this]() {setFrontend();});
    server.begin();
}

void WifiMaster::loop() {
    server.handleClient();
}

void WifiMaster::sendVectorToSlave(const std::vector<int>& reorderedValues, const ChordingScheme status, int repeat) {
    std::vector<int> vectorToSend;
    if (repeat != 0) { // If repeat is specified (non-zero), make it the first character and convert to negative
        vectorToSend.push_back(repeat);
    }else{
        vectorToSend.push_back(1);
    }
    for (int value : reorderedValues) { // Transform the reordered values, replacing 0 with -1
        vectorToSend.push_back(value == 0 ? -1 : value);
    }
    size_t vectorSize = vectorToSend.size(); // Size of the vector data
    // Calculate the total size, excluding repeat from the separate field and incorporating it in the vector
    size_t totalSize = sizeof(uint8_t) * 2 + sizeof(size_t) + vectorSize * sizeof(int);
    uint8_t* dataToSend = new uint8_t[totalSize];
    dataToSend[0] = 0; // First byte: 0 indicates a vector
    dataToSend[1] = (status == OST_ENCODING) ? 0 : 1; // Second byte: encoding status (0 for OST, 1 for SEQ)
    memcpy(dataToSend + 2, &vectorSize, sizeof(size_t)); // Copy the vector size after the first two characters
    memcpy(dataToSend + 2 + sizeof(size_t), vectorToSend.data(), vectorSize * sizeof(int)); // Copy the vector data after the size
    WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, totalSize);// Send the data to the slave
    delete[] dataToSend; // Clean up dynamically allocated memory
}

void WifiMaster::sendIntegerToSlave(int singleValueToSend){
    uint8_t dataToSend[sizeof(uint8_t) + sizeof(int)];
    dataToSend[0] = 1; // 1 for integer
    memcpy(dataToSend + 1, &singleValueToSend, sizeof(int));
    WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, sizeof(dataToSend));
}