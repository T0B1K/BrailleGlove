#ifndef BRAILLEMAPPER_H
#define BRAILLEMAPPER_H

#ifdef UNIT_TEST
    #include "../test/Mocks/String_Mock.h"
    /**
     * @brief Forward declaration of the test helper class for unit testing.
     */
    class BrailleMapperTestHelper;
#else
    #include <Arduino.h>
#endif

#include <unordered_map>
#include <vector>

/**
 * @class BrailleMapper
 * @brief Maps characters to their corresponding Braille integer representations.
 * 
 * This class provides functionality to convert individual characters and strings 
 * into Braille numerical representations based on English Tier One Braille.
 */
class BrailleMapper {
private:
    /**
     * @brief Stores character-to-Braille mappings.
     * 
     * Maps characters (e.g., 'c') to their corresponding Braille chord integer (e.g., '14').
     */
    std::unordered_map<char, int> brailleMap;

    /**
     * @brief Initializes the character-to-Braille mappings.
     * 
     * This function sets up the predefined Braille chord values for each character.
     */
    void initializeBrailleMap();

public:
    /**
     * @brief Constructs a BrailleMapper object and initializes mappings.
     */
    BrailleMapper();

    /**
     * @brief Retrieves the Braille integer representation of a given letter.
     * 
     * @param letter The character to be mapped.
     * @return The corresponding Braille integer representation.
     */
    int getBrailleHash(char letter) const;

    /**
     * @brief Converts a string into a list of Braille integer representations.
     * 
     * Given an input string (e.g., "hello"), this function returns a vector 
     * containing the corresponding Braille integer values for each character.
     * 
     * @param input The input string to convert.
     * @return A vector of integers representing the Braille values of the characters.
     */
    std::vector<int> stringToIntegerList(const String& input) const;

#ifdef UNIT_TEST
    /**
     * @brief Grants access to private members for unit testing.
     */
    friend class BrailleMapperTestHelper;
#endif
};

#endif // BRAILLEMAPPER_H
