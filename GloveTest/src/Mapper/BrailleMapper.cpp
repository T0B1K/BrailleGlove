#include "BrailleMapper.h"

// Constructor to initialize the braille mapping
BrailleMapper::BrailleMapper() {
    initializeBrailleMap(); // Initialize the mapping in a separate function
}

// Initializes the brailleMap with predefined letter-to-Braille mappings
void BrailleMapper::initializeBrailleMap() {
    brailleMap = {
        {'a', 1},   {'b', 12},  {'c', 14},  {'d', 145}, {'e', 15},
        {'f', 124}, {'g', 1245},{'h', 125}, {'i', 24},  {'j', 245},
        {'k', 13},  {'l', 123}, {'m', 134}, {'n', 1345},{'o', 135},
        {'p', 1234},{'q', 12345},{'r', 1235},{'s', 234}, {'t', 2345},
        {'u', 136}, {'v', 1236},{'w', 2456},{'x', 1346},{'y', 13456},
        {'z', 1356}
    };
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
