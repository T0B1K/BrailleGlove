#include <Arduino.h>
#include <unity.h>
#include "../src/Mapper/ActuatorProcessingOrderMapper.h"

// Test helper class that inherits ActuatorProcessingOrderMapper
// and has access to private methods when UNIT_TEST is defined
class ActuatorProcessingOrderMapperTestHelper : public ActuatorProcessingOrderMapper {
public:
    // Expose the private method reorderBySensitvity for testing purposes
    int reorderBySensitvity(int number) {
        return ActuatorProcessingOrderMapper::reorderBySensitivity(number);
    }
};

ActuatorProcessingOrderMapperTestHelper mapperHelper;

void test_reorderBySensitvity() {
    TEST_ASSERT_EQUAL(245631, mapperHelper.reorderBySensitvity(123456)); // Map the number 123456 to 245631
    TEST_ASSERT_EQUAL(0, mapperHelper.reorderBySensitvity(0));  // Edge case: The number is zero
    TEST_ASSERT_EQUAL(1, mapperHelper.reorderBySensitvity(4));  // Single digit, should return 1 (as per the sensitivity order)
    TEST_ASSERT_EQUAL(532, mapperHelper.reorderBySensitvity(123)); // Reordering for 123 -> 532
}

void test_reorderVectorBySensitivity() {
    std::vector<int> input = {123456, 654321, 111222};
    std::vector<int> expected = {245631, 654321, 123111};
    std::vector<int> result = mapperHelper.reorderVectorBySensitivity(input);

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
