#ifndef MOCK_ACTUATOR_H
#define MOCK_ACTUATOR_H

#include "Actuator.h"
#include <gmock/gmock.h>

// Mock Actuator class for testing
class MockActuator : public Actuator {
public:
    MockActuator(int pin, ActuatorType type) : Actuator(pin, type) {}

    MOCK_METHOD(void, activate, (), (override));  // Mock the activate function
    MOCK_METHOD(void, deactivate, (), (override));  // Mock the deactivate function
};

#endif
