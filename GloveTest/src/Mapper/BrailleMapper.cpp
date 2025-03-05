#include "BrailleMapper.h"

// Constructor to initialize the braille mapping
BrailleMapper::BrailleMapper() {
    initializeBrailleMap(); // Initialize the mapping in a separate function
}

// Initializes the brailleMap with predefined letter-to-Braille mappings
void BrailleMapper::initializeBrailleMap() {
    brailleMap['a'] = 1;
    brailleMap['b'] = 12;
    brailleMap['c'] = 14;
    brailleMap['d'] = 145;
    brailleMap['e'] = 15;
    brailleMap['f'] = 124;
    brailleMap['g'] = 1245;
    brailleMap['h'] = 125;
    brailleMap['i'] = 24;
    brailleMap['j'] = 245;
    brailleMap['k'] = 13;
    brailleMap['l'] = 123;
    brailleMap['m'] = 134;
    brailleMap['n'] = 1345;
    brailleMap['o'] = 135;
    brailleMap['p'] = 1234;
    brailleMap['q'] = 12345;
    brailleMap['r'] = 1235;
    brailleMap['s'] = 234;
    brailleMap['t'] = 2345;
    brailleMap['u'] = 136;
    brailleMap['v'] = 1236;
    brailleMap['w'] = 2456;
    brailleMap['x'] = 1346;
    brailleMap['y'] = 13456;
    brailleMap['z'] = 1356;
}

// Get the Braille hash for a given letter
int BrailleMapper::getBrailleHash(char letter) const {
    auto it = brailleMap.find(letter);
    return (it != brailleMap.end()) ? it->second : -1; // Return -1 for invalid letters
}

// Convert a string to a list of integers representing the Braille mappings
std::vector<int> BrailleMapper::stringToIntegerList(const String& input) const {
    std::vector<int> result;

    for (char c : input) {
        if (c == ' ') {
            result.push_back(0); // Append 0 for whitespace
        } else {
            result.push_back(getBrailleHash(c)); // Append the Braille value of the character
        }
    }

    return result;
}
