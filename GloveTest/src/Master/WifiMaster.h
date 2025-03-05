#ifndef WIFI_MASTER_H
#define WIFI_MASTER_H

#ifdef UNIT_TEST
    #ifndef ARDUINO_MOCK_H
        #pragma once
        #include "../test/Mocks/new_Arduino_Mock.h"
    #endif

    #include "../test/Mocks/ESP8266WiFi_Mock.h"
    #include "../test/Mocks/MockWiFiUDP.h"
    #include "../test/Mocks/LittleFS_Mock.h"
    #include "../test/Mocks/ESPNOW_Mock.h"
    #include "../test/Mocks/ESP_Mock.h"

    extern LittleFSMock LittleFS;
    #define File MockFile
    extern MockWiFi WiFi;
    extern MockWifiEspNow WifiEspNow;
    
#else
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <WiFiUdp.h>
    #include <WiFiServer.h>  // Include for TCP server
    #include <LittleFS.h>
    #include <WifiEspNow.h>

#endif

#include <vector>

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
    void setup();
    void loop();

    void sendVectorToSlave(const std::vector<int> &reorderedValues, const ChordingScheme status, int repeat);

    void sendVectorToSlave(const std::vector<int> &reorderedValues, const ChordingScheme status);

private:
    int idx;
    String pattern;
    ESP8266WebServer server;

    // View view;
    BrailleMapper brailleMapper = BrailleMapper();
    ActuatorProcessingOrderMapper queue = ActuatorProcessingOrderMapper();
    GloveModel gloveModel;
    // DataSender dataSender;

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
