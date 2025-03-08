#ifndef VIBRATION_ACTUATOR_H
#define VIBRATION_ACTUATOR_H

#include "Actuator.h"

/**
 * @class VibrationActuator
 * @brief A class representing a vibration actuator.
 * 
 * This actuator uses a digital output pin to control a vibration motor.
 */
class VibrationActuator : public Actuator {
  public:
    /**
     * @brief Constructor for VibrationActuator.
     * 
     * Initializes the vibration actuator by setting the specified pin as an output
     * and turning off the vibration motor initially.
     * 
     * @param pin The GPIO pin to which the actuator is connected.
     */
    VibrationActuator(int pin) : Actuator(pin, Vibration) {
        pinMode(pin, OUTPUT);      ///< Set the pin as an output.
        digitalWrite(pin, LOW);    ///< Ensure the actuator is off initially.
        turnedOn = false;
    }

    /**
     * @brief Activates the vibration actuator.
     * 
     * Turns on the vibration motor if it is not already on.
     */
    void activate() override {
        if (!turnedOn) {
            turnedOn = true;
            digitalWrite(pin, HIGH); ///< Turn on vibration.
        }
    }

    /**
     * @brief Deactivates the vibration actuator.
     * 
     * Turns off the vibration motor if it is currently on.
     */
    void deactivate() override {
        if (turnedOn) {
            turnedOn = false;
            digitalWrite(pin, LOW); ///< Turn off vibration.
        }
    }
};

#endif // VIBRATION_ACTUATOR_H
