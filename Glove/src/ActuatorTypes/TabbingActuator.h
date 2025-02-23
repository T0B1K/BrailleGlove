#ifndef TABBING_ACTUATOR_H
#define TABBING_ACTUATOR_H

#ifdef TEST_ENV
    #include "MockClasses/MockServo.h"
#else
    #include <Servo.h>
#endif

#include "Actuator.h"


class TabbingActuator : public Actuator {
  private:
    #ifdef TEST_ENV
      MockServo servo;
    #else
      Servo servo;
    #endif
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
