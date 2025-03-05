#ifndef ARDUINO_MOCK_H
#define ARDUINO_MOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OUTPUT
    #define OUTPUT 0
#endif

#ifndef LOW
    #define LOW 1
#endif

#ifndef HIGH
    #define HIGH 2
#endif

#include <stdint.h>  // Ensure uint8_t is defined

void digitalWrite(uint8_t pin, uint8_t value);
void pinMode(uint8_t pin, uint8_t mode);
unsigned long millis();
void delay(unsigned long);
void yield();

#ifdef __cplusplus
}
#endif

#endif // ARDUINO_MOCK_H
