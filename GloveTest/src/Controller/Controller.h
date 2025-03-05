#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <vector>

#include "../Models/GloveModel.h"
#include "../ActuatorTypes/VibrationActuator.h"
#include "../Mapper/ActuatorProcessingOrderMapper.h"
#include "../Mapper/BrailleMapper.h"
#include "../Models/HandEnum.h"

#include "../Master/WifiMaster.h"
#include "../Slave/WifiSlave.h"

#ifdef UNIT_TEST
    #include "../test/Mocks/ESP8266WiFi_Mock.h"
    #include "../test/Mocks/MockWiFiUDP.h"
#else
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <WiFiUdp.h>
#endif

class Controller {
public:
    Controller(bool isSlave);
    void setup();
    void loop();

private:
    bool isSlave;
    WifiMaster* master;
    WifiSlave* slave;

    void initializeMaster();
    void initializeSlave();
};

#endif // CONTROLLER_H
