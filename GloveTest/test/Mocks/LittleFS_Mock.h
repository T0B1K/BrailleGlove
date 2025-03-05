#ifndef MockLittleFS
#define MockLittleFS

#include <string>  // Include std::string

#ifndef File
#include "File_Mock.h"
#endif

class LittleFSMock {
public:
    static bool begin() { return true; }
    bool exists(std::string s) { return true; }
    MockFile open(std::string a, std::string b) {
        MockFile f;
        return f;
    }
};

#endif
