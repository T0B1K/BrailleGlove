// #include "WifiMaster.h"
// #include <WiFiClient.h>

// WifiMaster::WifiMaster(GloveModel gloveModel)
//     : server(80), tcpServer(80), view(&server), gloveModel(gloveModel) {} // Initialize tcpServer with port 80

// int i = 0;
// void WifiMaster::setup() {
//     WiFi.softAP(ssid, password);
//     Serial.println("Access Point Started:");
//     Serial.print("IP Address: ");
//     Serial.println(WiFi.softAPIP());

//     server.on("/", [this]() {
//         view.renderHomePage();
//         Serial.println("Rendering home page");
//     });
    
//     server.on("/setpattern", [this]() { setPatternFunction(); });

//     server.on("/start", [this]() {
//         idx = 0;  // Reset index when starting
//         view.renderHomePage();
//     });

//     server.on("/ajax", HTTP_GET, [this]() {
//         if (idx < pattern.length()) {
//             Serial.println("Received AJAX request");
//             Serial.println("Pattern length: " + String(pattern.length()));
//             Serial.println("Sending pattern " + String(pattern[idx]));

//             String charToSend = String(pattern[idx]);
//             server.send(200, "text/plain", charToSend);

//             delay(1000);

//             Serial.println("Starting pattern");
//             this->gloveModel.executePatternAt(idx);
//             idx++;
//         } else {
//             server.send(200, "text/plain", "");  
//             idx = 0;
//         }
//     });

//     server.begin();
    
//     // Setup TCP server
//     tcpServer.begin(); // Start the TCP server
// }

// void WifiMaster::loop() {
//     server.handleClient();
//     i++;

//     // Check for TCP client connections
//     WiFiClient client = tcpServer.available();  // Use available() instead of accept()
    
//     if (client) {
//         Serial.println("New client connected");

//         // Send a message periodically for observation
//         String messageToSend = "Hello World"; // or send your pattern here
//         Serial.println("Sending message: " + messageToSend);
//         client.println(messageToSend); // Send the message
//         Serial.println("Message sent to client");
        
//         client.stop();  // Close the connection
//     }
    
//     // Regularly print connected devices every 20 seconds
//     if(i == 20000) {
//         printConnectedDevices();
//         i = 0;
//     }

//     // Optionally, add a delay to avoid rapid firing
//     delay(100);  // Adjust delay as necessary
// }

// // Remaining methods...

// void WifiMaster::printConnectedDevices() {
//     // Get the list of connected devices
//     struct station_info *station_list = wifi_softap_get_station_info();
    
//     Serial.println("Connected devices:");
//     while (station_list != NULL) {
//         IPAddress ip = IPAddress((&station_list->ip)->addr);
//         Serial.print("IP Address: ");
//         Serial.println(ip);
        
//         Serial.print("MAC Address: ");
//         for (int i = 0; i < 6; ++i) {
//             Serial.printf("%02X", station_list->bssid[i]);
//             if (i < 5) Serial.print(":");
//         }
//         Serial.println();
        
//         // Move to the next connected device
//         station_list = STAILQ_NEXT(station_list, next);
//     }
    
//     // Free the list to avoid memory leaks
//     wifi_softap_free_station_info();
// }

// void WifiMaster::setPatternFunction() {
//     String pattern = server.arg("pattern") + " ";
//     this->pattern = pattern;  // Store the pattern
//     Serial.println("Setting pattern: " + pattern);
//     patternModel.setPattern(pattern);

//     std::vector<int> values = brailleMapper.stringToIntegerList(patternModel.getPattern());
//     std::vector<int> reorderedValues = queue.reorderVectorBySensitivity(values);
//     gloveModel.setPattern(reorderedValues);

//     view.renderPatternSetPage();
// }
