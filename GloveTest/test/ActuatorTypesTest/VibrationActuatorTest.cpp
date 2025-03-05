#include <Arduino.h>
#include <unity.h>
#include "../src/ActuatorTypes/VibrationActuator.h"

class MockDigitalWrite {
public:
    static bool pinHighCalled;
    static bool pinLowCalled;
    static int lastPin;
    
    static void reset() {
        pinHighCalled = false;
        pinLowCalled = false;
        lastPin = -1;
    }

    static void digitalWrite(int pin, int value) {
        lastPin = pin;
        if (value == HIGH) {
            pinHighCalled = true;
        } else {
            pinLowCalled = true;
        }
    }
};

bool MockDigitalWrite::pinHighCalled = false;
bool MockDigitalWrite::pinLowCalled = false;
int MockDigitalWrite::lastPin = -1;

// Mock pinMode as well
void pinMode(int pin, int mode) {
    // Mock implementation, no action needed for tests
}

VibrationActuator *vibrationActuator;

void setUp() {
    // Create new actuator for each test
    vibrationActuator = new VibrationActuator(12); // Pin 12 for example
    MockDigitalWrite::reset(); // Reset mock state
}

void tearDown() {
    delete vibrationActuator; // Clean up
}

void test_activate_vibration() {
    vibrationActuator->activate();
    TEST_ASSERT_TRUE(MockDigitalWrite::pinHighCalled);
    TEST_ASSERT_EQUAL(12, MockDigitalWrite::lastPin);
}

void test_deactivate_vibration() {
    vibrationActuator->deactivate();
    TEST_ASSERT_TRUE(MockDigitalWrite::pinLowCalled);
    TEST_ASSERT_EQUAL(12, MockDigitalWrite::lastPin);
}

void test_multiple_activate_calls() {
    // Test activating multiple times, should only turn on once
    vibrationActuator->activate();
    MockDigitalWrite::reset(); // Reset state
    vibrationActuator->activate();
    TEST_ASSERT_FALSE(MockDigitalWrite::pinHighCalled);
}

void test_multiple_deactivate_calls() {
    // Test deactivating multiple times, should only turn off once
    vibrationActuator->deactivate();
    MockDigitalWrite::reset(); // Reset state
    vibrationActuator->deactivate();
    TEST_ASSERT_FALSE(MockDigitalWrite::pinLowCalled);
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_activate_vibration);
    RUN_TEST(test_deactivate_vibration);
    RUN_TEST(test_multiple_activate_calls);
    RUN_TEST(test_multiple_deactivate_calls);

    UNITY_END();
}

void loop() {
    // Empty as this is a unit test
}
