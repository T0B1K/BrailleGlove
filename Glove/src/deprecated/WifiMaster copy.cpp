// #include "WifiMaster.h"
// #include <ESP8266WiFi.h>
// #include <WifiEspNow.h>
// #include <ESP8266WebServer.h>
// #include <vector>
// #include <cstring>
// #include "../Settings/SingeltonWifiSettings.h"
// #include <LittleFS.h>


// WifiMaster::WifiMaster(GloveModel gloveModel)
//     : server(80), view(&server), gloveModel(gloveModel) {} // Initialize tcpServer with port 80


// void WifiMaster::sendVectorToSlave(std::vector<int> reorderedValues) {
//     std::vector<int> vectorToSend;

//     for (int value : reorderedValues) {
//         if (value == 0) {
//             vectorToSend.push_back(-1);  // Replace 0 with -1   //otherwise can't be sent
//         } else {
//             vectorToSend.push_back(value);  // Keep the original value
//         }
//     }

//     size_t vectorSize = vectorToSend.size();
//     size_t totalSize = sizeof(uint8_t) + sizeof(size_t) + vectorSize * sizeof(int);
//     uint8_t* dataToSend = new uint8_t[totalSize];

//     dataToSend[0] = 0; // 0 for vector
//     memcpy(dataToSend + 1, &vectorSize, sizeof(size_t));
//     memcpy(dataToSend + sizeof(uint8_t) + sizeof(size_t), vectorToSend.data(), vectorSize * sizeof(int));

//     WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, totalSize);
//     Serial.printf("Sent vector of size %zu to slave\n", vectorSize);
//     delete[] dataToSend;
//     // Respond to web client
//     //server.send(200, "text/plain", "");
// }

// void WifiMaster::sendIntegerToSlave(int singleValueToSend) {
//     uint8_t dataToSend[sizeof(uint8_t) + sizeof(int)];
//     dataToSend[0] = 1; // 1 for integer
//     memcpy(dataToSend + 1, &singleValueToSend, sizeof(int));

//     WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, sizeof(dataToSend));
//     Serial.printf("Sent integer %d to slave\n", singleValueToSend);

//     // Respond to web client
//     //server.send(200, "text/plain", "");
// }

// void WifiMaster::setFrontend(){
//     Serial.println("show frontend");
//     if (LittleFS.exists("/switch.html")) {
//         Serial.println("switch.html exists, serving file");
        
//         // Open the file for reading
//         File file = LittleFS.open("/switch.html", "r");
//         if (file) {
//             // Read the file content into a string
//             String content = file.readString();
//             // Send the content as a response
//             server.send(200, "text/html", content);
//             file.close(); // Don't forget to close the file
//         } else {
//             Serial.println("Failed to open switch.html");
//             server.send(500, "text/plain", "Server error: Unable to read file");
//         }
//     } else {
//         Serial.println("switch.html does not exist");
//         server.send(404, "text/plain", "File not found");
//     }
//     Serial.println("homePage");
// }

// void WifiMaster::frontendSetPattern(String pattern) {
//     this->pattern = pattern;                //save it for the ajax call
//     computePatternAndDistribute(pattern);
    
//     idx = 99999;                       //prevent ajax
//     setFrontend();
// }


// void WifiMaster::frontendAjaxCall(){
//     Serial.println("receiving ajax");
//     //todo read a character, pause, vibrate
//     if (idx < (int)gloveModel.getPatternLength()) {
//         Serial.println(">AJAX: Pattern length: " + String(gloveModel.getPatternLength()) + "Sending pattern " + String(pattern[idx]));

//         String charToSend = String(pattern[idx]);
//         server.send(200, "text/plain", charToSend);

//         if((char)pattern[idx] == ' '){
//             Serial.println("pause");
//             customDelay(SingeltonGloveSettings::getInstance().PAUSE);
//         }else{
//             customDelay(SingeltonGloveSettings::getInstance().AUDIO_VIBRATION_OFFSET);
//         }
        
//         Serial.println("Starting pattern");
//         sendIntegerToSlave(idx);
//         this->gloveModel.executePatternAt(idx);

        
//         idx++;
//     } else {
//         server.send(200, "text/plain", "");  //otherwise the whole website gets resent
//         idx = 0;
//         //pattern = "";//added so that it is not played 2 times in a row
//     }
// }

// void WifiMaster::computePatternAndDistribute(String text){
//     std::vector<int> glovePattern = computePatternFromText(text);
//     distributePatternToGloves(glovePattern);
// }

// std::vector<int> WifiMaster::computePatternFromText(String text){
//     std::vector<int> values = brailleMapper.stringToIntegerList(text);           //character to the braille integer
//     return queue.reorderVectorBySensitivity(values);                             //braille integer according to sensitivity 
// }

// void WifiMaster::distributePatternToGloves(std::vector<int> sensitivityPattern){
//     gloveModel.setPattern(sensitivityPattern); //save the pattern for oneself
//     sendVectorToSlave(sensitivityPattern);     //send the pattern to the other glove
// }


// void WifiMaster::setup() {
//     Serial.println();

//     WiFi.persistent(false);
//     WiFi.mode(WIFI_STA); // Set to Station mode
//     WiFi.disconnect();
//     WiFi.softAP("ESP-Master");

//     delay(200);
    
//     if (!LittleFS.begin()) {  // Initialize LittleFS
//     Serial.println("LittleFS Mount Failed");
//     return;
//     } else {
//         Serial.println("LittleFS mounted successfully");
//     }

//     Dir dir = LittleFS.openDir("/");
//     while (dir.next()) {
//         Serial.print("File: ");
//         Serial.println(dir.fileName());
//     }

//     // Initialize ESP-NOW
//     if (!WifiEspNow.begin()) {
//         Serial.println("Error initializing ESP-NOW");
//         ESP.restart(); // Restart if initialization fails
//     }

//     // Print the MAC address of this node
//     Serial.print("MAC address of this master is: ");
//     Serial.println(WiFi.macAddress());
  
//     // Add the slave as a peer
//     if (!WifiEspNow.addPeer(SingeltonWifiConnector::getInstance().SLAVE_MAC)) {
//         Serial.println("Failed to add peer");
//         ESP.restart(); // Restart if adding peer fails
//     }


//     server.on("/start", [this]() {
//         idx = 0;  // Reset index when starting
//         setFrontend();
//     });
//     server.on("/setpattern", HTTP_POST,  [this]() { 
//         Serial.println("setting pattern");
//         if (server.hasArg("pattern")) {
//         String pattern = server.arg("pattern");  // Get the value of the "pattern" field
//         Serial.println("Received pattern: " + pattern);  // Print it to the serial monitor (for debugging)
        
//         // Now you can process the pattern, e.g., pass it to your function
//         frontendSetPattern(pattern);
        
//         server.send(200, "text/plain", "Pattern received: " + pattern);  // Send a response back
//     } else {
//         server.send(400, "text/plain", "No pattern received");  // Error response if no pattern was provided
//     }
//     });
//     server.on("/ajax", HTTP_GET, [this]() {frontendAjaxCall();});

//     server.on("/", HTTP_GET, [this]() {setFrontend();});


//     server.begin();
//     Serial.println("Web server started");
// }

// void WifiMaster::loop() {
//     server.handleClient();
// }
