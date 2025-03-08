#ifndef TABBING_ACTUATOR_H
#define TABBING_ACTUATOR_H

#include "Actuator.h"

/**
 * @class TabbingActuator
 * @brief A class representing a tabbing actuator.
 * 
 * This actuator is designed to create a tapping or tabbing sensation using a servo motor.
 */
class TabbingActuator : public Actuator {
  private:
    Servo servo;  ///< Servo object to control the DS208.

  public:
    /**
     * @brief Constructor for TabbingActuator.
     * 
     * Initializes the tabbing actuator by attaching the servo to the specified pin
     * and setting it to the initial position (180 degrees).
     * 
     * @param pin The GPIO pin to which the actuator is connected.
     */
    TabbingActuator(int pin) : Actuator(pin, Stroking) {
        servo.attach(pin);
        servo.write(180);
        turnedOn = false;
    }

    /**
     * @brief Activates the tabbing actuator.
     * 
     * Moves the servo to 90 degrees to simulate a tabbing motion.
     */
    void activate() override {
        turnedOn = true;
        servo.write(90);
    }

    /**
     * @brief Deactivates the tabbing actuator.
     * 
     * Moves the servo back to 180 degrees.
     */
    void deactivate() override {
        turnedOn = false;
        servo.write(180);
    }
};

#endif // TABBING_ACTUATOR_H
