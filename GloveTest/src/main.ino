#include "Controller/Controller.h"

const bool IS_SLAVE = false; // Set to true for slave, false for master
Controller controller(IS_SLAVE);

void setup() {
    // Serial.begin(115200);
    Serial.begin(115200);
    controller.setup();
}

void loop() {
    controller.loop();
}
