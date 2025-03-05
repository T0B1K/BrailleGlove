#include "new_Arduino_Mock.h"

void digitalWrite(int pin, int value) {
    // Mock behavior, e.g., print to console
}

void pinMode(int pin, int mode) {
    // Mock behavior
}

unsigned long millis() {
    static unsigned long fakeMillis = 0;
    return fakeMillis += 100;  // Simulate time passing
}

void delay(int ms) {
    // Mock behavior
}

void yield() {
    // Mock behavior
}
