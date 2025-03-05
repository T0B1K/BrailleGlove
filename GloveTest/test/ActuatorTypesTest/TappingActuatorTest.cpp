#include <Arduino.h>
#include <unity.h>
#include "../src/ActuatorTypes/TabbingActuator.h"

class MockServo {
public:
    static int lastAngle;
    static int lastPin;
    static bool attached;

    static void reset() {
        lastAngle = -1;
        lastPin = -1;
        attached = false;
    }

    void attach(int pin) {
        lastPin = pin;
        attached = true;
    }
    void write(int angle) {
        lastAngle = angle;
    }
};

int MockServo::lastAngle = -1;
bool MockServo::attached = false;
int MockServo::lastPin = -1;

// Mock TabbingActuator class using the mock servo
class TestTabbingActuator : public TabbingActuator {
public:
    TestTabbingActuator(int pin) : TabbingActuator(pin) {}
    void setMockServo(MockServo* mockServo) {
        this->servo = mockServo;
    }
    MockServo* getMockServo() {
        return servo;
    }
private:
    MockServo* servo;
};

TestTabbingActuator* tabbingActuator;

void setUp() {
    tabbingActuator = new TestTabbingActuator(5);
    MockServo::reset();
}

void tearDown() {
    delete tabbingActuator;
}

void test_activate_tabbing() {
    tabbingActuator->activate();
    TEST_ASSERT_EQUAL(90, MockServo::lastAngle);
}

void test_deactivate_tabbing() {
    tabbingActuator->deactivate();
    TEST_ASSERT_EQUAL(180, MockServo::lastAngle);
}

void test_multiple_activate_calls() {
    tabbingActuator->activate();
    MockServo::reset();
    tabbingActuator->activate();
    TEST_ASSERT_EQUAL(-1, MockServo::lastAngle); // No change expected
}

void test_multiple_deactivate_calls() {
    tabbingActuator->deactivate();
    MockServo::reset();
    tabbingActuator->deactivate();
    TEST_ASSERT_EQUAL(-1, MockServo::lastAngle); // No change expected
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_activate_tabbing);
    RUN_TEST(test_deactivate_tabbing);
    RUN_TEST(test_multiple_activate_calls);
    RUN_TEST(test_multiple_deactivate_calls);

    UNITY_END();
}

void loop() {
    // Empty as this is a unit test
}
