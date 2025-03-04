#include <Arduino.h>
#include <unity.h>

// Example function to test
int add(int a, int b) {
    return a + b;
}

void setUp() {
  // This will run before each test
}

void tearDown() {
  // This will run after each test
}

void test_add() {
  TEST_ASSERT_EQUAL(3, add(1, 2));
  TEST_ASSERT_EQUAL(5, add(2, 3));
}

void setup() {
  // Start the Unity test framework
  UNITY_BEGIN();
  
  // Run the test
  RUN_TEST(test_add);
  
  UNITY_END();
}

void loop() {
  // Nothing needed here
}
