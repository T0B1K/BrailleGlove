 #ifndef Arduino_Mock
 #define Arduino_Mock

 #ifndef HIGH
        #define HIGH 1
    #endif
    #ifndef LOW
        #define LOW 0
    #endif
    #ifndef OUTPUT
        #define OUTPUT -1
    #endif

    // Provide empty implementations of digitalWrite and pinMode
    // only if they are not already defined
    #ifndef digitalWrite
        void digitalWrite(int pin, int value) {
            // Empty implementation
        }
    #endif

    #ifndef pinMode
        void pinMode(int pin, int mode) {
            // Empty implementation
        }
    #endif

#endif

#ifndef MOCK_UTILS
#define MOCK_UTILS

#include <iostream>
#include <chrono>

// Mock for millis()
unsigned long millis() {
    static unsigned long startTime = 0;
    if (startTime == 0) {
        startTime = static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count());
    }
    // Return elapsed time in milliseconds since the start
    return static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()) - startTime;
}

// Mock for yield()
void yield() {
    // This is a no-op for now; implement any background task logic you need here
    // For testing purposes, you can leave it empty
    // If needed, this could simulate a delay or background processing.
    // std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Example if you want to simulate a small delay
}

#endif
