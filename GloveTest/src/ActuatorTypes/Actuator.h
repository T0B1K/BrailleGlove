#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "ActuatorType.h"

#ifdef UNIT_TEST
    // Define HIGH and LOW only if they are not already defined
    #ifndef HIGH
        #define HIGH 1
    #endif
    #ifndef LOW
        #define LOW 0
    #endif

    // Define pin_t only if it's not already defined
    #ifndef pin_t
        typedef int pin_t;
    #endif

    // Provide empty implementations of digitalWrite and pinMode
    // only if they are not already defined
    #ifndef digitalWrite
        void digitalWrite(pin_t pin, int value) {
            // Empty implementation
        }
    #endif

    #ifndef pinMode
        void pinMode(pin_t pin, int mode) {
            // Empty implementation
        }
    #endif
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
