#include <Arduino.h>
#include <unity.h>
#include "../src/ActuatorTypes/StrokingActuator.h"

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

// Mock StrokingActuator class using the mock servo
class TestStrokingActuator : public StrokingActuator {
public:
    TestStrokingActuator(int pin) : StrokingActuator(pin) {}
    void setMockServo(MockServo* mockServo) {
        this->servo = mockServo;
    }
    MockServo* getMockServo() {
        return servo;
    }
private:
    MockServo* servo;
};

TestStrokingActuator* strokingActuator;

void setUp() {
    strokingActuator = new TestStrokingActuator(5);
    MockServo::reset();
}

void tearDown() {
    delete strokingActuator;
}

void test_activate_stroking() {
    strokingActuator->activate();
    TEST_ASSERT_EQUAL(180, MockServo::lastAngle);
}

void test_deactivate_stroking() {
    strokingActuator->deactivate();
    TEST_ASSERT_EQUAL(0, MockServo::lastAngle);
}

void test_multiple_activate_calls() {
    strokingActuator->activate();
    MockServo::reset();
    strokingActuator->activate();
    TEST_ASSERT_EQUAL(-1, MockServo::lastAngle); // No change expected
}

void test_multiple_deactivate_calls() {
    strokingActuator->deactivate();
    MockServo::reset();
    strokingActuator->deactivate();
    TEST_ASSERT_EQUAL(-1, MockServo::lastAngle); // No change expected
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_activate_stroking);
    RUN_TEST(test_deactivate_stroking);
    RUN_TEST(test_multiple_activate_calls);
    RUN_TEST(test_multiple_deactivate_calls);

    UNITY_END();
}

void loop() {
    // Empty as this is a unit test
}
