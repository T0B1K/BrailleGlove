#include "Controller/Controller.h"

// Define whether the device is a slave or a master.
// Set to true for slave, false for master.
const bool IS_SLAVE = false; ///< Flag indicating whether the device is a slave (true) or master (false).
Controller controller(IS_SLAVE); ///< Initializes the controller with the appropriate role (master or slave).

/**
 * @brief Setup function for the device.
 * 
 * Initializes serial communication and sets up the controller.
 * Only initializes serial if the code is not running in unit test mode.
 */
void setup() {
    #ifndef UNIT_TEST
        Serial.begin(115200);  ///< Starts serial communication at 115200 baud if not running in unit test mode.
    #endif
    controller.setup();
}

/**
 * @brief Main loop function for the device.
 * 
 * Continuously calls the loop function of the controller.
 */
void loop() {
    controller.loop(); ///< Calls the loop function of the controller.
}
