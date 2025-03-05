#ifndef BrailleMapper_H
#define BrailleMapper_H

#ifdef UNIT_TEST
    #include "../test/Mocks/Arduino_Mock.h"
#else
    #include <Arduino.h>
#endif

#include <string>
#include <unordered_map>
#include <vector>

class BrailleMapper {
private:
    std::unordered_map<char, int> brailleMap; // HashMap to store mappings

public:
    BrailleMapper() {
        // Initialize the mapping
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

    int getBrailleHash(char letter) {
        if (brailleMap.find(letter) != brailleMap.end()) {
            return brailleMap[letter];
        } else {
            return -1; // Return -1 for invalid letters
        }
    }

    std::vector<int> stringToIntegerList(std::string input) {
        std::vector<int> result;
        std::string encodedString = "";

        for (char c : input) {
            if (c == ' ') {
                encodedString += " ";
                result.push_back(0); // Append 0 for whitespace
            } else {
                encodedString += getBrailleHash(c);
                result.push_back(getBrailleHash(c)); // Append the braille value of the character
            }
        }
        return result;
    }


};

#endif