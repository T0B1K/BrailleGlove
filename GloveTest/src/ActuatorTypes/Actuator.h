#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "ActuatorType.h"

#ifdef UNIT_TEST
    #include "../test/Mocks/Servo_Mock.h"
#else
    #include <Servo.h>
#endif

#ifdef UNIT_TEST
#else
    #include <Arduino.h>
#endif

class Actuator {
  protected:
    int pin;
    ActuatorType actuatorType;
    bool turnedOn = false;

  public:
    Actuator(int pin, ActuatorType type) : pin(pin), actuatorType(type) {
    }

    virtual void activate() = 0;   // Pure virtual function
    virtual void deactivate() = 0; // Pure virtual function

    ActuatorType getType() {
        return actuatorType;
    }
};

#endif
