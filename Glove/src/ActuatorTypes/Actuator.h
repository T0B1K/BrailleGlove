#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "ActuatorType.h"


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
