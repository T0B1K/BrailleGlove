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
        servo.attach(pin);  ///< Attach the servo to the specified pin.
        servo.write(0);     ///< Set servo to 0 degrees initially.
        turnedOn = false;
    }

    /**
     * @brief Activates the stroking actuator.
     * 
     * Moves the servo to 180 degrees to simulate a stroking motion.
     */
    void activate() override {
        turnedOn = true;
        servo.write(180);  ///< Move the servo to 180 degrees.
    }

    /**
     * @brief Deactivates the stroking actuator.
     * 
     * Moves the servo back to 0 degrees.
     */
    void deactivate() override {
        turnedOn = false;
        servo.write(0);   ///< Move the servo back to 0 degrees.
    }
};

#endif // STROKING_ACTUATOR_H
