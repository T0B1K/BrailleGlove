#ifdef MASTER_DEVICE

#ifndef WIFI_MASTER_H
#define WIFI_MASTER_H

#ifdef TEST_ENV
    #include "MockClasses/MockLittleFS.h"
    #include "MockClasses/MockWifiEspNow.h"
    #include "MockClasses/MockWiFi.h"
    #include "MockClasses/MockESP8266WebServer.h"
#else
    #include <LittleFS.h>
    #include <WifiEspNow.h>

    #include <ESP8266WebServer.h>
    #include <WiFiServer.h> 
    #include <ESP8266WiFi.h>
#endif


#include <vector>
 // Include for TCP server
#include <cstring>
#include "Mapper/BrailleMapper.h"
#include "Mapper/ActuatorProcessingOrderMapper.h"
#include "Models/GloveModel.h"
#include "Models/EncodingScheme/ChordingScheme.h"
#include "Models/HandEnum.h"
#include "../Settings/SingeltonWifiSettings.h"



class WifiMaster {
public:
    WifiMaster(GloveModel gloveModel);
    ESP8266WebServer server;
    void setup();
    void loop();
    void sendVectorToSlave(const std::vector<int> &reorderedValues, const ChordingScheme status, int repeat);

    void sendVectorToSlave(const std::vector<int> &reorderedValues, const ChordingScheme status);

private:
    int idx;
    String pattern;

    // View view;
    BrailleMapper brailleMapper = BrailleMapper();
    ActuatorProcessingOrderMapper queue = ActuatorProcessingOrderMapper();
    GloveModel gloveModel;

    void sendVectorToSlave(std::vector<int> reorderedValues);
    void sendIntegerToSlave(int singleValueToSend);
    void setFrontend();
    void frontendSetPattern(String pattern, ChordingScheme status, bool longPattern);
    void printConnectedDevices();
    void frontendSetPattern(String pattern, ChordingScheme status);
    void computePatternAndDistribute(String text, ChordingScheme status, bool longPattern);
    std::vector<int> computePatternFromText(String text);
    void distributePatternToGloves(std::vector<int> pattern);
    void startFunction();
    void frontendAjaxCall();

    void customDelay(unsigned long timeInMs){ //this is needed for wifi compatability
      unsigned long startMillis = millis();  // Get the current time
      while (millis() - startMillis < timeInMs) { 
          yield();  //the programm doesn't stop
      }
    }
};
#endif // WIFI_MASTER_H
#endif