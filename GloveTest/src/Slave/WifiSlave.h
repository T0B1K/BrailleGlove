#ifndef WIFI_SLAVE_H
#define WIFI_SLAVE_H

#ifdef UNIT_TEST
    #include "../test/Mocks/ESP8266WiFi_Mock.h"
    #include "../test/Mocks/MockWiFiUDP.h"
    #include "../test/Mocks/ESPNOW_Mock.h"
    #include "../test/Mocks/ESP_Mock.h"
#else
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <WiFiUdp.h>
    #include <WiFiServer.h>  ///< Include for TCP server
    #include <LittleFS.h>
    #include <WifiEspNow.h>
#endif

#include <vector>
#include "Models/GloveModel.h"

/**
 * @class WifiSlave
 * @brief This class defines the behavior of a WiFi slave device, including receiving
 * data via Wi-Fi and processing it to control actuators.
 */
class WifiSlave {
public:
    /**
     * @brief Constructs a WifiSlave object with a given glove model.
     * 
     * @param gloveModel The glove model to be used for actuator control and pattern execution.
     */
    WifiSlave(GloveModel gloveModel);

    /**
     * @brief Standard setup function for the Wi-Fi slave.
     * 
     * Initializes necessary components for Wi-Fi communication and the glove model.
     */
    void setup();

    /**
     * @brief Standard loop function for the Wi-Fi slave.
     * 
     * Continuously handles incoming data and controls the actuators accordingly.
     */
    void loop();

    /**
     * @brief Callback function for handling received data.
     * 
     * This function is called when data is received via Wi-Fi. It identifies the type
     * of data and processes it accordingly.
     * 
     * @param mac The MAC address of the sender.
     * @param buf The received data buffer.
     * @param count The number of bytes received.
     * @param arg Additional argument passed to the callback (not used here).
     */
    static void onReceiveCallback(const uint8_t* mac, const uint8_t* buf, size_t count, void* arg);

    /**
     * @brief Processes the received message.
     * 
     * This function processes the message and takes the appropriate actions based
     * on the content of the message.
     * 
     * @param mac The MAC address of the sender.
     * @param buf The received data buffer.
     * @param count The number of bytes received.
     */
    void processMessage(const uint8_t* mac, const uint8_t* buf, size_t count);

private:
    GloveModel gloveModel; ///< The glove model for actuators, hand location, and pattern handling.
    bool hasPatternFlag = false; ///< Flag to indicate if a pattern is currently running.
    bool nextCharacterFlag = false; ///< Flag to indicate if the next character in the pattern is ready.
    int characterIndex = 0; ///< Index of the character currently being executed.

    /**
     * @brief Runs the program logic during each loop cycle.
     * 
     * This function handles executing the appropriate actions for controlling actuators.
     */
    void runProgram();

    /**
     * @brief Handles the next index when it is received in a new message.
     * 
     * @param index The index of the next character in the pattern.
     */
    void receivedIndex(int index);

    /**
     * @brief Handles the received pattern when it is received in a new message.
     * 
     * @param sensitivityPattern A vector containing the pattern data.
     */
    void receivedPatten(std::vector<int> sensitivityPattern);
};

#endif // WIFI_SLAVE_H
