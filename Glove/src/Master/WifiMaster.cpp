#include "WifiMaster.h"

#ifdef TEST_ENV
    MockLittleFS LittleFS;
    MockFile file;
    MockWifiEspNow WifiEspNow;
    MockWiFi WiFi;
    MockESP ESP;
    
#else
    LittleFS LittleFS;
    File file;
    WifiEspNow WifiEspNow;
    WiFi WiFi;
    ESP ESP;
#endif



// WifiMaster::WifiMaster(GloveModel gloveModel): server(80), view(&server), gloveModel(gloveModel) {} // Initialize tcpServer with port 80
WifiMaster::WifiMaster(GloveModel gloveModel): server(80), gloveModel(gloveModel) {} // Initialize tcpServer with port 80


void WifiMaster::setFrontend(){
    if (LittleFS.exists("/switch.html")) {
        // Open the file for reading
        file = LittleFS.open("/switch.html", "r");
        if (file) {
            // Read the file content into a string
            String content = file.readString();
            // Send the content as a response
            server.send(200, "text/html", content);
            file.close(); // Don't forget to close the file
        } else {
            Serial.println("Failed to open switch.html");
            server.send(500, "text/plain", "Server error: Unable to read file");
        }
    } else {
        Serial.println("switch.html does not exist");
        server.send(404, "text/plain", "File not found");
    }
    Serial.println("homePage");
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
    Serial.println("repeat");
    Serial.println(repeat);
    sendVectorToSlave(shortPattern, status, repeat);     //send the pattern to the other glove
    
    idx = 99999;                       //prevent ajax
    setFrontend();
}


void WifiMaster::frontendAjaxCall(){
    Serial.println("====================\n");
    //todo read a character, pause, vibrate
    if (idx < (int)gloveModel.getPatternLength()) {
        

        String charToSend = String(pattern[idx]);
        int asciNumber = (int)pattern[idx];

        Serial.println("\nCurrent Character [" + charToSend + "] ascii: [" + asciNumber + "]");
        server.send(200, "text/plain", charToSend);

        if(asciNumber == 32){
            //space
            // Serial.println("PAUSE: " + String(SingeltonGloveSettings::getInstance().PAUSE) + " (SPACE - PAUSE)");
            // customDelay(SingeltonGloveSettings::getInstance().PAUSE);
        }else{
            //next character
            Serial.println("PAUSE: " + String(SingeltonGloveSettings::getInstance().AUDIO_VIBRATION_OFFSET)+ " (AUDIO_VIBRATION_OFFSET)");
            customDelay(SingeltonGloveSettings::getInstance().AUDIO_VIBRATION_OFFSET);
        }
        
        sendIntegerToSlave(idx);
        this->gloveModel.executePatternAt(idx);
        
        idx++;
    } else {
        server.send(200, "text/plain", "");  //otherwise the whole website gets resent
        idx = 0;
        //pattern = "";//added so that it is not played 2 times in a row
    }
}


std::vector<int> WifiMaster::computePatternFromText(String text){
    std::vector<int> values = brailleMapper.stringToIntegerList(text);           //character to the braille integer
    return queue.reorderVectorBySensitivity(values);                             //braille integer according to sensitivity 
}


void WifiMaster::setup() {
    Serial.println();

    WiFi.persistent(false);
    WiFi.mode(WIFI_AP); // Set to Station mode
    WiFi.disconnect();
    WiFi.softAP(SingeltonWifiConnector::getInstance().MASTER_SSID);

    delay(200);
    Serial.println("\nStarting Master Glove " + String(SingeltonWifiConnector::getInstance().MASTER_SSID));
    if (!LittleFS.begin()) {  // Initialize LittleFS
    Serial.println("File System Mount Fail");
    return;
    } else {
        Serial.println("File System Mounted");
    }

    if (!WifiEspNow.begin()) {
        Serial.println("Error initializing ESP-NOW");
        ESP.restart(); // Restart if initialization fails
    }

    // Print the MAC address of this node
    Serial.print("MAC address of this master is: ");
    Serial.println(WiFi.macAddress());
    
    const int maxRetries = 5; // Set the number of retries
    int attempts = 0;

    // Add the slave as a peer
    while (attempts < maxRetries) {
        if (WifiEspNow.addPeer(SingeltonWifiConnector::getInstance().SLAVE_MAC)) {
            Serial.println("Successfully added peer");
            break; // Exit loop if successful
        } else {
            Serial.println("Failed to add peer, retrying...");
            attempts++;
            delay(1000); // Delay before retrying
        }
    }

    if (attempts == maxRetries) {
        Serial.println("Failed to add peer after multiple attempts, restarting...");
        ESP.restart();
    }


    server.on("/start", [this]() {
        idx = 0;  // Reset index when starting
        setFrontend();
    });
    server.on("/setpattern", HTTP_POST,  [this]() { 
        Serial.println("\n---- Setting pattern ----");
        
        ChordingScheme status = OST_ENCODING;
        if(server.hasArg("ostStatus")){
            String ostStatus = server.arg("ostStatus");
            status = (ostStatus == "false")? SEQUENTIAL_ENCODING : OST_ENCODING;
            Serial.println("Encoding Scheme: " + String(ostStatus));
        }

        if (server.hasArg("pattern")) {
            String pattern = server.arg("pattern");  // Get the value of the "pattern" field
            Serial.println("Received pattern: " + pattern);  // Print it to the serial monitor (for debugging)
            
            // Now you can process the pattern, e.g., pass it to your function
            frontendSetPattern(pattern, status, false);
            Serial.println("-----------------------------------\n\n");
            server.send(200, "text/plain", "Pattern received: " + pattern);  // Send a response back
        } else {
            server.send(400, "text/plain", "No pattern received");  // Error response if no pattern was provided
        }
    });
    server.on("/setstartpattern", HTTP_POST,  [this](){
        Serial.println("\n---- Setting pattern and start ----");
        
        ChordingScheme status = OST_ENCODING;
        if(server.hasArg("ostStatus")){
            String ostStatus = server.arg("ostStatus");
            status = (ostStatus == "false")? SEQUENTIAL_ENCODING : OST_ENCODING;
            Serial.println("Encoding Scheme: " + String(ostStatus));
        }

        if (server.hasArg("pattern")) {
            String pattern = server.arg("pattern");  // Get the value of the "pattern" field
            Serial.println("Received pattern: " + pattern);  // Print it to the serial monitor (for debugging)
            
            // Now you can process the pattern, e.g., pass it to your function
            frontendSetPattern(pattern, status, true);
            Serial.println("-----------------------------------\n\n");
        }
        
        server.send(200, "text/plain", "Pattern received: ");
        // idx = 0;  // Reset index when starting
        // setFrontend();
    });

    server.on("/ajax", HTTP_GET, [this]() {frontendAjaxCall();});

    server.on("/", HTTP_GET, [this]() {setFrontend();});


    server.begin();
    Serial.println("Web server started");
}

void WifiMaster::loop() {
    server.handleClient();
}


void WifiMaster::sendVectorToSlave(const std::vector<int>& reorderedValues, const ChordingScheme status, int repeat) {
    std::vector<int> vectorToSend;

    // If repeat is specified (non-zero), make it the first character and convert to negative
    if (repeat != 0) {
        vectorToSend.push_back(repeat);
    }else{
        vectorToSend.push_back(1);
    }

    // Transform the reordered values, replacing 0 with -1
    for (int value : reorderedValues) {
        vectorToSend.push_back(value == 0 ? -1 : value);
    }

    // Size of the vector data
    size_t vectorSize = vectorToSend.size();

    // Calculate the total size, excluding repeat from the separate field and incorporating it in the vector
    size_t totalSize = sizeof(uint8_t) * 2 + sizeof(size_t) + vectorSize * sizeof(int);
    uint8_t* dataToSend = new uint8_t[totalSize];

    // First byte: 0 indicates a vector
    dataToSend[0] = 0;

    // Second byte: encoding status (0 for OST, 1 for SEQ)
    dataToSend[1] = (status == OST_ENCODING) ? 0 : 1;

    // Copy the vector size after the first two characters
    memcpy(dataToSend + 2, &vectorSize, sizeof(size_t));

    // Copy the vector data after the size
    memcpy(dataToSend + 2 + sizeof(size_t), vectorToSend.data(), vectorSize * sizeof(int));

    // Send the data to the slave
    WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, totalSize);
    // Serial.printf("==> Sent vector of size %zu to slave (repeat as negative if present)\n\n", vectorSize);

    // Clean up dynamically allocated memory
    delete[] dataToSend;
}

  


void WifiMaster::sendIntegerToSlave(int singleValueToSend){
    uint8_t dataToSend[sizeof(uint8_t) + sizeof(int)];
    dataToSend[0] = 1; // 1 for integer
    memcpy(dataToSend + 1, &singleValueToSend, sizeof(int));

    WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, sizeof(dataToSend));
    // Serial.printf("==> Sent integer %d to slave\n\n", singleValueToSend);
}