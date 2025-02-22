#ifndef ENCODING_H
#define ENCODING_H

#include <Arduino.h>

class Encoding {
public:
    static void customDelay(unsigned long timeInMs) {
        unsigned long startMillis = millis();  // Get the current time
        while (millis() - startMillis < timeInMs) {
            yield();  // the program doesn't stop
        }
    }

    static boolean validIndex(int number, Hand hand){
        if ((hand == Left && number > SingeltonGloveSettings::getInstance().NUM_ACTUATORS) ||
            (hand == Right && number < SingeltonGloveSettings::getInstance().NUM_ACTUATORS + 1)) {
            return false;
        }else{
            return true;
        }

    }
};
#endif
