#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <vector>

#include "../Models/GloveModel.h"
// #include "../View/View.h"
#include "../ActuatorTypes/VibrationActuator.h"
#include "../Mapper/ActuatorProcessingOrderMapper.h"
#include "../Mapper/BrailleMapper.h"
#include "../Models/HandEnum.h"

#include "../Master/WifiMaster.h"
#include "../Slave/WifiSlave.h"

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
