// #ifndef WIFI_MASTER_H
// #define WIFI_MASTER_H

// #include <ESP8266WebServer.h>
// #include <WiFiUdp.h>
// #include <vector>
// #include <WiFiServer.h>  // Include for TCP server
// #include "View/View.h"
// #include "Models/PatternModel.h"
// #include "Mapper/BrailleMapper.h"
// #include "Mapper/ActuatorProcessingOrderMapper.h"
// #include "Models/GloveModel.h"
// #include "Models/HandEnum.h"

// class WifiMaster {
// public:
//     WifiMaster(GloveModel gloveModel);
//     void setup();
//     void loop();
//     void receiveSlaveIP();  // Function to receive the slave's IP address

// private:
//     const char* ssid = "ESP-Master";
//     const char* password = "masterpassword";
//     int idx;
//     String pattern;

//     ESP8266WebServer server;
//     WiFiServer tcpServer;  // TCP server instance
//     View view;
//     PatternModel patternModel = PatternModel();
//     BrailleMapper brailleMapper = BrailleMapper();
//     ActuatorProcessingOrderMapper queue = ActuatorProcessingOrderMapper();
//     GloveModel gloveModel;

//     void printConnectedDevices();
//     void setPatternFunction();
//     void startFunction();
//     void sendPatternToSlave(const std::vector<int>& pattern);
// };

// #endif // WIFI_MASTER_H
