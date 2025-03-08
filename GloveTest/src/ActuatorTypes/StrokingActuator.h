#ifndef STROKING_ACTUATOR_H
#define STROKING_ACTUATOR_H

#include "Actuator.h"

/**
 * @class StrokingActuator
 * @brief A class representing a stroking actuator.
 * 
 * This actuator is designed to create a stroking sensation using a servo motor.
 */
class StrokingActuator : public Actuator {
  private:
    Servo servo;  ///< Servo object to control the DS208.

  public:
    /**
     * @brief Constructor for StrokingActuator.
     * 
     * Initializes the stroking actuator by attaching the servo to the specified pin
     * and setting it to the initial position (0 degrees).
     * 
     * @param pin The GPIO pin to which the actuator is connected.
     */
    StrokingActuator(int pin) : Actuator(pin, Stroking) {
        servo.attach(pin);
        servo.write(0);  
        turnedOn = false;
    }

    /**
     * @brief Activates the stroking actuator.
     * 
     * Moves the servo to 180 degrees to simulate a stroking motion.
     */
    void activate() override {
        turnedOn = true;
        servo.write(180);
    }

    /**
     * @brief Deactivates the stroking actuator.
     * 
     * Moves the servo back to 0 degrees.
     */
    void deactivate() override {
        turnedOn = false;
        servo.write(0);
    }
};

#endif // STROKING_ACTUATOR_H
