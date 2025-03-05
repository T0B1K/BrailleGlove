#ifndef ENCODING_TEST_H
#define ENCODING_TEST_H

#include "Encoding.h"
#include <gtest/gtest.h>

// Mock classes for Hand and SingeltonGloveSettings
enum Hand { Left, Right };

class SingeltonGloveSettings {
public:
    static SingeltonGloveSettings& getInstance() {
        static SingeltonGloveSettings instance;
        return instance;
    }
    int NUM_ACTUATORS = 10;  // Example setting
};

class EncodingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup before each test
    }

    void TearDown() override {
        // Cleanup after each test
    }
};

// Test for the customDelay function
TEST_F(EncodingTest, CustomDelayTest) {
    unsigned long delayTime = 1000;  // Simulated delay of 1000ms

    // Use the mock millis to simulate time passing
    unsigned long startMillis = millis();  // Get the current mock millis time
    Encoding::customDelay(delayTime);      // Run custom delay

    // After calling customDelay, we should have the millis() incremented
    unsigned long elapsedTime = millis() - startMillis;

    // Check if elapsed time is greater than or equal to the delay time
    EXPECT_GE(elapsedTime, delayTime);
}

// Test for the validIndex function
TEST_F(EncodingTest, ValidIndexTest) {
    Hand leftHand = Left;
    Hand rightHand = Right;

    SingeltonGloveSettings::getInstance().NUM_ACTUATORS = 10;

    // Valid index for Left hand
    EXPECT_TRUE(Encoding::validIndex(5, leftHand));
    EXPECT_FALSE(Encoding::validIndex(15, leftHand));  // Invalid for Left hand

    // Valid index for Right hand
    EXPECT_TRUE(Encoding::validIndex(15, rightHand));
    EXPECT_FALSE(Encoding::validIndex(5, rightHand));  // Invalid for Right hand
}

#endif // ENCODING_TEST_H
