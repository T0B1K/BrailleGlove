#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    Serial.println("Hello, PlatformIO!");
}

void loop() {
    // Your main code here
}
