#ifndef ENCODING_H
#define ENCODING_H


#ifdef UNIT_TEST
    #ifndef ARDUINO_MOCK_H
        #pragma once
        #include "../test/Mocks/new_Arduino_Mock.h"
    #endif
#else
    #include <Arduino.h>
#endif

class Encoding {
public:
    static void customDelay(unsigned long timeInMs) {
        unsigned long startMillis = millis();  // Get the current time
        while (millis() - startMillis < timeInMs) {
            yield();  // the program doesn't stop
        }
    }

    static bool validIndex(int number, Hand hand){
        if ((hand == Left && number > SingeltonGloveSettings::getInstance().NUM_ACTUATORS) ||
            (hand == Right && number < SingeltonGloveSettings::getInstance().NUM_ACTUATORS + 1)) {
            return false;
        }else{
            return true;
        }

    }
};
#endif
