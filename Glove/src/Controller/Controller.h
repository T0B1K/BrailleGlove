#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef TEST_ENV
    #include "MockClasses/MockWifiEspNow.h"
    #include "MockClasses/MockESP8266WebServer.h"
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

// Include master and slave headers conditionally
#ifdef MASTER_DEVICE
    #include "../Master/WifiMaster.h"
#else
    #include "../Slave/WifiSlave.h"
#endif

class Controller {
public:
    Controller(bool isSlave);
    void setup();
    void loop();

private:
    bool isSlave;

    #ifdef MASTER_DEVICE
        WifiMaster* master;
        void initializeMaster();
    #else
        WifiSlave* slave;
        void initializeSlave();
    #endif


    // Unified function to handle master and slave device initialization
    void initializeDevice(bool isSlave);
};

#endif // CONTROLLER_H
