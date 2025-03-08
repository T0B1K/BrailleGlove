#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef UNIT_TEST
    #include "../test/Mocks/ESP8266WiFi_Mock.h"
    #include "../test/Mocks/MockWiFiUDP.h"
    #include "../test/Mocks/new_Arduino_Mock.h"
    #include "../test/Mocks/ESPNOW_Mock.h"
    #include "../test/Mocks/ESP_Mock.h"
#else
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <WiFiUdp.h>
#endif

#include <vector>
#include "../Models/GloveModel.h"
#include "../ActuatorTypes/VibrationActuator.h"
#include "../Mapper/ActuatorProcessingOrderMapper.h"
#include "../Mapper/BrailleMapper.h"
#include "../Models/HandEnum.h"
#include "../Master/WifiMaster.h"
#include "../Slave/WifiSlave.h"

/**
 * @class Controller
 * @brief Handles the initialization and execution of either the master or slave mode.
 * 
 * This class determines whether the system should operate as a master or a slave 
 * and initializes the appropriate class accordingly.
 */
class Controller {
public:
    /**
     * @brief Constructor for the Controller class.
     * 
     * Determines whether the device should act as a master or a slave.
     * 
     * @param isSlave A boolean flag indicating whether the device should run in slave mode.
     */
    Controller(bool isSlave);

    /**
     * @brief Sets up the master or slave mode based on the given conditions.
     * 
     * This function initializes the appropriate components depending on whether 
     * the device is in master or slave mode.
     */
    void setup();

    /**
     * @brief Runs the main execution loop for either the master or slave mode.
     * 
     * This function should be called continuously in the main program loop.
     */
    void loop();

private:
    bool isSlave;   ///< Flag to determine whether the device is a slave.
    WifiMaster* master; ///< Pointer to the master class for Wi-Fi communication.
    WifiSlave* slave; ///< Pointer to the slave class for Wi-Fi communication.

    /**
     * @brief Initializes the master mode.
     * 
     * Sets up and configures the device as a master.
     */
    void initializeMaster();

    /**
     * @brief Initializes the slave mode.
     * 
     * Sets up and configures the device as a slave.
     */
    void initializeSlave();
};


#endif // CONTROLLER_H
