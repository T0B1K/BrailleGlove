#ifndef SEQUENTIAL_ENCODING_TEST_H
#define SEQUENTIAL_ENCODING_TEST_H

#include "SequentialEncoding.h"
#include "MockActuator.h"
#include "new_Arduino_Mock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock SingeltonGloveSettings to return specific values
class SingeltonGloveSettings {
public:
    static SingeltonGloveSettings& getInstance() {
        static SingeltonGloveSettings instance;
        return instance;
    }
    int NUM_ACTUATORS = 3;  // 3 actuators per hand
    int DURATION = 100;      // Mock duration for the delay
    int SEQ_OFFSET = 50;     // Mock sequence offset for the delay
};

// Test class for SequentialEncoding
class SequentialEncodingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any necessary preconditions for the tests
    }

    void TearDown() override {
        // Clean up after the test
    }
};

// Test for the handle function when the index is valid
TEST_F(SequentialEncodingTest, HandleTest_ValidIndex) {
    MockActuator actuator1(1, ActuatorType::TYPE_A), actuator2(2, ActuatorType::TYPE_B), actuator3(3, ActuatorType::TYPE_C);
    Actuator* actuators[] = { &actuator1, &actuator2, &actuator3 };

    // Mock the validIndex to return true
    EXPECT_CALL(*this, validIndex(1, Left)).WillOnce(testing::Return(true));  // Assume Left hand

    // Mock the activate and deactivate functions to track their calls
    EXPECT_CALL(actuator1, activate()).Times(1);   // Expect actuator1 to be activated
    EXPECT_CALL(actuator1, deactivate()).Times(1); // Expect actuator1 to be deactivated

    // Mock the customDelay function to ensure it's called with the correct durations
    EXPECT_CALL(*this, customDelay(SingeltonGloveSettings::getInstance().DURATION)).Times(1);
    EXPECT_CALL(*this, customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET)).Times(1);

    // Call the handle function with a valid index for the Left hand
    SequentialEncoding::handle(1, actuators, Left);
}

// Test for the handle function when the index is invalid
TEST_F(SequentialEncodingTest, HandleTest_InvalidIndex) {
    MockActuator actuator1(1, ActuatorType::TYPE_A), actuator2(2, ActuatorType::TYPE_B), actuator3(3, ActuatorType::TYPE_C);
    Actuator* actuators[] = { &actuator1, &actuator2, &actuator3 };

    // Mock the validIndex to return false for an invalid index
    EXPECT_CALL(*this, validIndex(5, Left)).WillOnce(testing::Return(false));  // Invalid index for Left hand

    // Mock the customDelay function to ensure it's called with the correct durations
    EXPECT_CALL(*this, customDelay(SingeltonGloveSettings::getInstance().DURATION)).Times(1);
    EXPECT_CALL(*this, customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET)).Times(1);

    // Call the handle function with an invalid index
    SequentialEncoding::handle(5, actuators, Left);

    // Verify that no actuator is activated or deactivated because of the invalid index
    EXPECT_CALL(actuator1, activate()).Times(0);
    EXPECT_CALL(actuator1, deactivate()).Times(0);
    EXPECT_CALL(actuator2, activate()).Times(0);
    EXPECT_CALL(actuator2, deactivate()).Times(0);
    EXPECT_CALL(actuator3, activate()).Times(0);
    EXPECT_CALL(actuator3, deactivate()).Times(0);
}

#endif // SEQUENTIAL_ENCODING_TEST_H
