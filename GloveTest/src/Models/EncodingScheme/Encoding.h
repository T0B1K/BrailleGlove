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

/**
 * @class Encoding
 * @brief Base class for encoding operations.
 * 
 * This class provides the basic functions for encoding used by its child classes.
 */
class Encoding {
public:
    /**
     * @brief Custom delay function to provide a non-blocking delay.
     * 
     * This function allows for a non-blocking delay (unlike the blocking `delay()` function in Arduino),
     * so the program can continue execution while waiting.
     * 
     * @param timeInMs The delay duration in milliseconds.
     */
    static void customDelay(unsigned long timeInMs) {
        unsigned long startMillis = millis();
        while (millis() - startMillis < timeInMs) {
            yield();
        }
    }

    /**
     * @brief Checks whether the given pin number is valid for the specified hand.
     * 
     * This function validates whether the pin number belongs to the correct hand (left or right)
     * based on the actuator configuration.
     * 
     * @param number The pin number to be validated.
     * @param hand The hand (left or right) for which the validation is being done.
     * @return True if the pin is valid for the hand; false otherwise.
     */
    static bool validIndex(int number, Hand hand){
        if ((hand == Left && number > SingeltonGloveSettings::getInstance().NUM_ACTUATORS) ||
            (hand == Right && number < SingeltonGloveSettings::getInstance().NUM_ACTUATORS + 1)) {
            return false;
        } else {
            return true;
        }
    }
};

#endif
