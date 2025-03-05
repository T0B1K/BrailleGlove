#ifndef OST_ENCODING_TEST_H
#define OST_ENCODING_TEST_H

#include "../src/Models/EncodingScheme/OSTEncoding.h"
#include "MockActuator.h"
#include "new_Arduino_Mock.h"  // Include your existing mock class
#include <gtest/gtest.h>
#include <gmock/gmock.h>  // For mocking

// Mock SingeltonGloveSettings to return specific values
class SingeltonGloveSettings {
public:
    static SingeltonGloveSettings& getInstance() {
        static SingeltonGloveSettings instance;
        return instance;
    }
    int NUM_ACTUATORS = 3;  // 3 actuators per hand
    int OST_OFFSET = 100;    // Mock OST offset for the delay
};

// Test class for OSTEncoding
class OSTEncodingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any necessary preconditions for the tests
    }

    void TearDown() override {
        // Clean up after the test
    }
};

// Test for the handle function when the index is valid
TEST_F(OSTEncodingTest, HandleTest_ValidIndex) {
    MockActuator actuator1(1, ActuatorType::TYPE_A), actuator2(2, ActuatorType::TYPE_B), actuator3(3, ActuatorType::TYPE_C);
    Actuator* actuators[] = { &actuator1, &actuator2, &actuator3 };  // Actuators array

    // Mock the validIndex to return true
    EXPECT_CALL(*this, validIndex(1, Left)).WillOnce(testing::Return(true));  // Assume Left hand

    // Mock the activate function to track its call
    EXPECT_CALL(actuator1, activate()).Times(1);  // Expect actuator1 to be activated

    // Call the handle function with a valid index for the Left hand
    OSTEncoding::handle(1, actuators, Left);

    // Check that the delay method is called
    EXPECT_EQ(millis() % SingeltonGloveSettings::getInstance().OST_OFFSET, 0);  // Check that millis is incremented by OST_OFFSET
}

// Test for the handle function when the index is invalid
TEST_F(OSTEncodingTest, HandleTest_InvalidIndex) {
    MockActuator actuator1(1, ActuatorType::TYPE_A), actuator2(2, ActuatorType::TYPE_B), actuator3(3, ActuatorType::TYPE_C);
    Actuator* actuators[] = { &actuator1, &actuator2, &actuator3 };

    // Mock the validIndex to return false for invalid index
    EXPECT_CALL(*this, validIndex(5, Left)).WillOnce(testing::Return(false));  // Invalid index for Left hand

    // Call the handle function with an invalid index
    OSTEncoding::handle(5, actuators, Left);

    // Verify that no actuator is activated because of invalid index
    EXPECT_CALL(actuator1, activate()).Times(0);
    EXPECT_CALL(actuator2, activate()).Times(0);
    EXPECT_CALL(actuator3, activate()).Times(0);

    // Check that no actuator is activated due to invalid index
}

#endif // OST_ENCODING_TEST_H
