#include "Controller/Controller.h"

const bool IS_SLAVE = false; // Set to true for slave, false for master
Controller controller(IS_SLAVE); //inits the controller

void setup() {
    #ifndef UNIT_TEST
        Serial.begin(115200);  // Serial communication, if it's not the test class
    #endif
    controller.setup();
}

void loop() {
    controller.loop();
}
