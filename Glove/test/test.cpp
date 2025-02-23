#include "Arduino.h"
#include <unity.h>

void setUp(void) {
    // Setup code before each test
}

void tearDown(void) {
    // Cleanup code after each test
}

void test_addition(void) {
    int result = 2 + 2;
    TEST_ASSERT_EQUAL(4, result);
}

void test_subtraction(void) {
    int result = 5 - 3;
    TEST_ASSERT_EQUAL(2, result);
}

void setup() {
    UNITY_BEGIN(); // Start Unity test framework

    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);

    UNITY_END(); // End Unity test framework
}

void loop() {
    // Empty loop since this is a unit test
}
