#include "Controller/Controller.h"

const bool IS_SLAVE = false; // Set to true for slave, false for master
Controller controller(IS_SLAVE);

void setup() {
    #ifndef UNIT_TEST
        Serial.begin(115200);  // Serial communication, using either MockSerial or HardwareSerial
    #endif
    controller.setup();
}

void loop() {
    controller.loop();
}
