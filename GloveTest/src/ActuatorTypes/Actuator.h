#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "ActuatorType.h"

#ifdef UNIT_TEST
    #include "../test/Mocks/Servo_Mock.h"
#else
    #include <Servo.h>
    #include <Arduino.h>
#endif



/**
 * @class Actuator
 * @brief Abstract class for implementing different types of actuators.
 * 
 * This class provides a base for all actuator types, defining common properties and methods.
 */
class Actuator {
  protected:
    int pin; ///< GPIO pin number the actuator is connected to.
    ActuatorType actuatorType; ///< Type of actuator (e.g., vibration, stroking, tabbing).
    bool turnedOn = false; ///< Flag to check if the actuator is currently active.

  public:
    /**
     * @brief Constructor for the Actuator class.
     * @param pin The GPIO pin to which the actuator is connected.
     * @param type The type of actuator.
     */
    Actuator(int pin, ActuatorType type) : pin(pin), actuatorType(type) {}

    /**
     * @brief Pure virtual function to activate the actuator.
     * 
     * This function must be implemented by derived classes to define 
     * how the actuator should be activated.
     */
    virtual void activate() = 0;

    /**
     * @brief Pure virtual function to deactivate the actuator.
     * 
     * This function must be implemented by derived classes to define 
     * how the actuator should be deactivated.
     */
    virtual void deactivate() = 0;
};

#endif // ACTUATOR_H
