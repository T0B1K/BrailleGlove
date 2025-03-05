#ifndef GLOVE_MODEL_TEST_H
#define GLOVE_MODEL_TEST_H

#include "GloveModel.h"
#include "../Mocks/MockActuator.h"
#include "new_Arduino_Mock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Test class for GloveModel
class GloveModelTest : public ::testing::Test {
protected:
    MockActuator actuator1{1, ActuatorType::TYPE_A};
    MockActuator actuator2{2, ActuatorType::TYPE_B};
    MockActuator actuator3{3, ActuatorType::TYPE_C};
    GloveModel gloveModel{Left, actuator1, actuator2, actuator3};  // Left hand

    void SetUp() override {
        // Set up any necessary preconditions for the tests
    }

    void TearDown() override {
        // Clean up after the test
    }
};

// Test for resetAllActuators
TEST_F(GloveModelTest, ResetAllActuatorsTest) {
    // Expect all actuators to be deactivated
    EXPECT_CALL(actuator1, deactivate()).Times(1);
    EXPECT_CALL(actuator2, deactivate()).Times(1);
    EXPECT_CALL(actuator3, deactivate()).Times(1);

    gloveModel.resetAllActuators();
}

// Test for executePatternAt
TEST_F(GloveModelTest, ExecutePatternAtTest) {
    std::vector<int> pattern = {1, 2, 3};
    gloveModel.setPattern(pattern);

    // Mock the resetAllActuators and vibrateOnNumber methods to track calls
    EXPECT_CALL(actuator1, deactivate()).Times(3);  // Expect 3 deactivations for actuators
    EXPECT_CALL(actuator2, deactivate()).Times(3);
    EXPECT_CALL(actuator3, deactivate()).Times(3);

    // Mock the vibrateOnNumber method call
    EXPECT_CALL(gloveModel, vibrateOnNumber(1)).Times(1);
    EXPECT_CALL(gloveModel, vibrateOnNumber(2)).Times(1);
    EXPECT_CALL(gloveModel, vibrateOnNumber(3)).Times(1);

    gloveModel.executePatternAt(0);  // Should call vibrateOnNumber(1)
    gloveModel.executePatternAt(1);  // Should call vibrateOnNumber(2)
    gloveModel.executePatternAt(2);  // Should call vibrateOnNumber(3)
}

// Test for vibrateOnNumber
TEST_F(GloveModelTest, VibrateOnNumberTest) {
    gloveModel.setPattern({1, 2});

    // Mock the SequentialEncoding and OSTEncoding methods to track calls
    EXPECT_CALL(actuator1, activate()).Times(1);  // Expect activation for actuator1
    EXPECT_CALL(actuator1, deactivate()).Times(1);  // Expect deactivation for actuator1

    EXPECT_CALL(actuator2, activate()).Times(1);  // Expect activation for actuator2
    EXPECT_CALL(actuator2, deactivate()).Times(1);  // Expect deactivation for actuator2

    // Test when playMode is SEQUENTIAL_ENCODING
    gloveModel.setChordMode(SEQUENTIAL_ENCODING);
    gloveModel.vibrateOnNumber(1);  // Activate actuator1
    gloveModel.vibrateOnNumber(2);  // Activate actuator2
}

// Test for setPattern and getPattern
TEST_F(GloveModelTest, SetGetPatternTest) {
    std::vector<int> pattern = {5, 10, 15};
    gloveModel.setPattern(pattern);

    std::vector<int> result = gloveModel.getPattern();
    EXPECT_EQ(result, pattern);  // Ensure the pattern is set correctly
}

// Test for setChordMode
TEST_F(GloveModelTest, SetChordModeTest) {
    gloveModel.setChordMode(SEQUENTIAL_ENCODING);
    EXPECT_EQ(gloveModel.getChordMode(), SEQUENTIAL_ENCODING);

    gloveModel.setChordMode(OST_ENCODING);
    EXPECT_EQ(gloveModel.getChordMode(), OST_ENCODING);
}

#endif // GLOVE_MODEL_TEST_H
