#ifndef STROKING_ACTUATOR_H
#define STROKING_ACTUATOR_H

#include <Servo.h>
#include "Actuator.h"

class StrokingActuator : public Actuator {
  private:
    Servo servo;  // Servo object to control the DS208
  public:
    StrokingActuator(int pin) : Actuator(pin, Stroking) {
        // Initialize the servo and set to 0 degrees
        servo.attach(pin);  // Attach the servo to the specified pin
        servo.write(0);     // Set servo to 0 degrees initially
        turnedOn = false;
    }

    void activate() override {
        turnedOn = true;
        // Turn 45 degrees
        Serial.println("Turing ON Actuator at Pin [" + String(pin) + "]");
        servo.write(180);  // Move the servo to 45 degrees
    }

    void deactivate() override {
        turnedOn = false;
        Serial.println("Turing OFF Actuator at Pin [" + String(pin) + "]");
        // Turn back to 0 degrees
        servo.write(0);   // Move the servo back to 0 degrees
    }
};

#endif
