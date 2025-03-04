#ifndef VIBRATION_ACTUATOR_H
#define VIBRATION_ACTUATOR_H

#include "Actuator.h"

class VibrationActuator : public Actuator {
  public:
    VibrationActuator(int pin) : Actuator(pin, Vibration) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        turnedOn = false;
        Serial.println("Vibration Actuator initialized and set to low at pin: " + String(pin));
    }

    void activate() override {
        if(!turnedOn){
            turnedOn = true;
            digitalWrite(pin, HIGH); // Turn on vibration
            Serial.println("A: Vibration Actuator at pin: " + String(pin));
        }
    }

    void deactivate() override {
        if(turnedOn){
            turnedOn = false;
            digitalWrite(pin, LOW); // Turn off vibration
            Serial.println("O: Vibration Actuator at pin: " + String(pin));
        }
    }
};

#endif
