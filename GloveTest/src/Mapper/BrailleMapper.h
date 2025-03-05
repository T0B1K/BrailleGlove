#ifndef BRAILLEMAPPER_H
#define BRAILLEMAPPER_H

#ifdef UNIT_TEST
    #include "../test/Mocks/String_Mock.h"
    // Forward declare the test helper class
    class BrailleMapperTestHelper;
#else
    #include <Arduino.h>
#endif

#include <unordered_map>
#include <vector>

class BrailleMapper {
private:
    std::unordered_map<char, int> brailleMap; // HashMap to store mappings

    void initializeBrailleMap(); // Initializes the braille mappings

public:
    BrailleMapper(); // Constructor to initialize the mappings

    int getBrailleHash(char letter) const; // Retrieve Braille hash for a letter
    std::vector<int> stringToIntegerList(const String& input) const; // Convert string to a list of Braille integers

#ifdef UNIT_TEST
    // Grant access to BrailleMapperTestHelper during unit tests
    friend class BrailleMapperTestHelper;
#endif
};

#endif // BRAILLEMAPPER_H
