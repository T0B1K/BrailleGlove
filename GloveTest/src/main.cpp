#include <Arduino.h>

void setup() {
    // Initialize serial communication at 115200 baud
    Serial.begin(115200);
    // Wait for serial port to connect (needed for native USB)
    while (!Serial) {
        delay(10);
    }
    Serial.println("Hello, PlatformIO!");
}

void loop() {
    // Your main code here
}
