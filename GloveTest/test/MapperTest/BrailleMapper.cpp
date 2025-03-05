#include <unity.h>
#include "../src/BrailleMapper.h"
#include "BrailleMapperTestHelper.h"

class BrailleMapperTestHelper : public BrailleMapper {
    public:
        // Expose private method initializeBrailleMap for testing purposes
        void testInitializeBrailleMap() {
            initializeBrailleMap(); // Call the private method directly
        }

        // Expose private member brailleMap for testing purposes
        const std::unordered_map<char, int>& getBrailleMap() const {
            return brailleMap;
        }
};

BrailleMapperTestHelper mapperHelper;

// Test for Braille hash retrieval
void test_getBrailleHash() {
    // Test for valid input
    TEST_ASSERT_EQUAL(1, mapperHelper.getBrailleHash('a'));
    TEST_ASSERT_EQUAL(12, mapperHelper.getBrailleHash('b'));
    // Test for invalid input
    TEST_ASSERT_EQUAL(-1, mapperHelper.getBrailleHash('z')); // Invalid letter
    TEST_ASSERT_EQUAL(-1, mapperHelper.getBrailleHash('1')); // Non-letter
}

// Test for string to integer list conversion
void test_stringToIntegerList() {
    std::vector<int> result = mapperHelper.stringToIntegerList("abc");
    TEST_ASSERT_EQUAL(3, result.size());
    TEST_ASSERT_EQUAL(1, result[0]);
    TEST_ASSERT_EQUAL(12, result[1]);
    TEST_ASSERT_EQUAL(14, result[2]);
}

// Test for the braille map initialization
void test_initializeBrailleMap() {
    // Call the private method directly using the test helper
    mapperHelper.testInitializeBrailleMap();
    
    // Verify the internal map (public access via friend class)
    const auto& brailleMap = mapperHelper.getBrailleMap();
    TEST_ASSERT_EQUAL(1, brailleMap.at('a'));
    TEST_ASSERT_EQUAL(12, brailleMap.at('b'));
}

void setup() {
    Serial.begin(115200);
    delay(2000); // Wait for Serial Monitor to initialize
    UNITY_BEGIN(); // Start Unity Test framework
    RUN_TEST(test_getBrailleHash);
    RUN_TEST(test_stringToIntegerList);
    RUN_TEST(test_initializeBrailleMap);
    UNITY_END(); // End the tests and print results to Serial Monitor
}

void loop() {
    // Empty loop since tests are run once during setup
}
