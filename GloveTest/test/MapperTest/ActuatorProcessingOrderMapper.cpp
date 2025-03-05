#include <Arduino.h>
#include <unity.h>
#include "../src/Mapper/ActuatorProcessingOrderMapper.h"

// Create an instance of ActuatorProcessingOrderMapper to test
ActuatorProcessingOrderMapper mapper;

void test_reorderBySensitvity() {
    // Test individual reorder of numbers
    TEST_ASSERT_EQUAL(245631, mapper.reorderBySensitvity(123456)); // Map the number 123456 to 245631

    // Edge cases
    TEST_ASSERT_EQUAL(0, mapper.reorderBySensitvity(0));  // The number is zero
    TEST_ASSERT_EQUAL(1, mapper.reorderBySensitvity(4));  // Single digit, should return 1 (as per the sensitivity order)
    TEST_ASSERT_EQUAL(532, mapper.reorderBySensitvity(123)); // Reordering for 123 -> 532
}

void test_reorderVectorBySensitivity() {
    // Test vector reorder
    std::vector<int> input = {123456, 654321, 111222};
    std::vector<int> expected = {245631, 654321, 123111};

    std::vector<int> result = mapper.reorderVectorBySensitivity(input);
    
    // Compare expected with result
    for (size_t i = 0; i < input.size(); ++i) {
        TEST_ASSERT_EQUAL(expected[i], result[i]);
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000);  // Wait for Serial Monitor to initialize
    
    UNITY_BEGIN();  // Start Unity Test framework

    RUN_TEST(test_reorderBySensitvity);
    RUN_TEST(test_reorderVectorBySensitivity);

    UNITY_END();  // End the tests and print results to Serial Monitor
}

void loop() {
    // Empty loop since tests are run once during setup
}
