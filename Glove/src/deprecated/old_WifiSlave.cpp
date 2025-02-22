// #include "WifiSlave.h"

// WifiSlave::WifiSlave(GloveModel gloveModel)
//     : gloveModel(gloveModel) {}

// void WifiSlave::setup() {
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(1000);
//         Serial.println("Connecting to WiFi...");
//     }

//     Serial.println("Connected to WiFi");
//     Serial.println("WiFi Information:");
//     Serial.print("IP Address: ");
//     Serial.println(WiFi.localIP());
//     Serial.print("Subnet Mask: ");
//     Serial.println(WiFi.subnetMask());
//     Serial.print("Gateway: ");
//     Serial.println(WiFi.gatewayIP());
//     Serial.print("Signal Strength (RSSI): ");
//     Serial.print(WiFi.RSSI());
//     Serial.println(" dBm");

//     delay(1000);
// }

// void WifiSlave::loop() {
//     // Create a WiFi client and connect to the master
//     WiFiClient client;
    
//     // Connect to the master's IP address and TCP port (make sure to use the correct IP)
//     if (client.connect("192.168.4.1", 80)) {  // Master IP is usually the access point IP
//         Serial.println("Connected to master!");

//         // Wait for the message from the master
//         String message = client.readStringUntil('\n');  // Read the message until newline
//         Serial.println("Received message: " + message);
        
//         client.stop();  // Close the connection
//     } else {
//         Serial.println("Connection to master failed");
//     }

//     delay(2000);  // Delay to avoid rapid connection attempts
// }

