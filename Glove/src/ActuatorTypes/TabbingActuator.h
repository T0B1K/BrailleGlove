#ifndef TABBING_ACTUATOR_H
#define TABBING_ACTUATOR_H

#include <Servo.h>
#include "Actuator.h"

class TabbingActuator : public Actuator {
  private:
    Servo servo;  // Servo object to control the DS208
  public:
    TabbingActuator(int pin) : Actuator(pin, Stroking) {
        // Initialize the servo and set to 180 degrees
        servo.attach(pin);  // Attach the servo to the specified pin
        servo.write(180);
        turnedOn = false;
    }

    void activate() override {
        turnedOn = true;
        servo.write(90);
    }

    void deactivate() override {
        turnedOn = false;
        servo.write(180);
    }
};

#endif
