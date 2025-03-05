#ifndef MockLittleFS
#define MockLittleFS

#include <string>  // Include std::string

#ifndef File
#include "File_Mock.h"
#endif

class LittleFS {
public:
    static bool begin() { return true; }
    bool exists(std::string s) { return true; }
    File open(std::string a, std::string b) {
        File f;
        return f;
    }
};

#endif
