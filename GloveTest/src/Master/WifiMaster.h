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
    #include <WiFiServer.h>
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

/**
 * @class WifiMaster
 * @brief This class handles the communication and Wi-Fi functionality for the master device,
 * including website setup, response handling, and communication between the master and slave devices.
 */
class WifiMaster {
public:
    /**
     * @brief Constructs a WifiMaster object with a given glove model.
     * 
     * @param gloveModel The glove model to be used for actuator control and pattern execution.
     */
    WifiMaster(GloveModel gloveModel);

    /**
     * @brief Standard setup function for the Wi-Fi master.
     * 
     * Sets up Wi-Fi, ESP-NOW, and the web server.
     */
    void setup();

    /**
     * @brief Standard loop function for the Wi-Fi master.
     * 
     * Continuously handles communication and controls actuators.
     */
    void loop();

    /**
     * @brief Sends a vector to the slave device, including a repeat count for longer patterns.
     * 
     * @param reorderedValues The vector of reordered values representing the pattern.
     * @param status The current chording scheme status.
     * @param repeat The number of times to repeat the pattern if it is long.
     */
    void sendVectorToSlave(const std::vector<int> &reorderedValues, const ChordingScheme status, int repeat);

    /**
     * @brief Sends a vector to the slave device for a short pattern (no repeat).
     * 
     * @param reorderedValues The vector of reordered values representing the pattern.
     * @param status The current chording scheme status.
     */
    void sendVectorToSlave(const std::vector<int> &reorderedValues, const ChordingScheme status);

private:
    int idx; ///< Current character index for pattern execution.
    String pattern; ///< The pattern string to be played.
    ESP8266WebServer server; ///< Web server for the Wi-Fi master.

    BrailleMapper brailleMapper = BrailleMapper(); ///< Decodes Braille messages.
    ActuatorProcessingOrderMapper queue = ActuatorProcessingOrderMapper(); ///< Decodes processing order from Wi-Fi.
    GloveModel gloveModel; ///< Glove model that handles actuator control.

    /**
     * @brief Sets up the Wi-Fi connection for the master.
     */
    void setupWifi();

    /**
     * @brief Sets up ESP-NOW communication for the master.
     */
    void setupESPNow();

    /**
     * @brief Sends a vector of reordered values to the slave device.
     * 
     * @param reorderedValues The vector of reordered values representing the pattern.
     */
    void sendVectorToSlave(std::vector<int> reorderedValues);

    /**
     * @brief Sends a single integer value to the slave device.
     * 
     * @param singleValueToSend The integer value to be sent.
     */
    void sendIntegerToSlave(int singleValueToSend);

    /**
     * @brief Sets up the frontend for the web interface.
     */
    void setFrontend();

    /**
     * @brief Sets the pattern on the frontend for playback as audio.
     * 
     * @param pattern The pattern to be played.
     * @param status The current chording scheme status.
     * @param longPattern A flag indicating if the pattern is long.
     */
    void frontendSetPattern(String pattern, ChordingScheme status, bool longPattern);

    /**
     * @brief Sets the pattern on the frontend for playback as audio.
     * 
     * @param pattern The pattern to be played.
     * @param status The current chording scheme status.
     */
    void frontendSetPattern(String pattern, ChordingScheme status);

    /**
     * @brief Computes the pattern based on text input and distributes it to the gloves.
     * 
     * @param text The text input to compute the pattern from.
     * @param status The current chording scheme status.
     * @param longPattern A flag indicating if the pattern is long.
     */
    void computePatternAndDistribute(String text, ChordingScheme status, bool longPattern);

    /**
     * @brief Computes the pattern from a text input.
     * 
     * @param text The text input to compute the pattern from.
     * @return A vector representing the computed pattern.
     */
    std::vector<int> computePatternFromText(String text);

    /**
     * @brief Distributes the computed pattern to the gloves.
     * 
     * @param pattern The pattern to be distributed.
     */
    void distributePatternToGloves(std::vector<int> pattern);

    /**
     * @brief Defines the frontend AJAX call to update the website.
     */
    void frontendAjaxCall();
};

#endif // WIFI_MASTER_H
