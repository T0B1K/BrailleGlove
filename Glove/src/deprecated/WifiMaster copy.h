// #ifndef WIFI_MASTER_H
// #define WIFI_MASTER_H

// #include <ESP8266WebServer.h>
// #include <WiFiUdp.h>
// #include <vector>
// #include <WiFiServer.h>  // Include for TCP server
// #include "View/View.h"
// #include "Mapper/BrailleMapper.h"
// #include "Mapper/ActuatorProcessingOrderMapper.h"
// #include "Models/GloveModel.h"
// #include "Models/HandEnum.h"
// #include <ESP8266WiFi.h>
// #include <WifiEspNow.h>
// #include <ESP8266WebServer.h>
// #include <vector>
// #include <cstring>

// class WifiMaster {
// public:
//     WifiMaster(GloveModel gloveModel);
//     void setup();
//     void loop();

// private:
//     int idx;
//     String pattern;
//     ESP8266WebServer server;

//     View view;
//     BrailleMapper brailleMapper = BrailleMapper();
//     ActuatorProcessingOrderMapper queue = ActuatorProcessingOrderMapper();
//     GloveModel gloveModel;

//     void sendVectorToSlave(std::vector<int> reorderedValues);
//     void sendIntegerToSlave(int singleValueToSend);
//     void setFrontend();
//     void printConnectedDevices();
//     void frontendSetPattern(String pattern);
//     void computePatternAndDistribute(String text);
//     std::vector<int> computePatternFromText(String text);
//     void distributePatternToGloves(std::vector<int> pattern);
//     void startFunction();
//     void frontendAjaxCall();

//     void customDelay(unsigned long timeInMs){ //this is needed for wifi compatability
//       unsigned long startMillis = millis();  // Get the current time
//       while (millis() - startMillis < timeInMs) { 
//           yield();  //the programm doesn't stop
//       }
//     }
// };
// #endif // WIFI_MASTER_H
