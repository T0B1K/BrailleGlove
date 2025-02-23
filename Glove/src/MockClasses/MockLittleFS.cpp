#include "MockLittleFS.h"



bool MockLittleFS::exists(const String& path) {
    // Mock implementation: always return true
    return true;
}

MockFile MockLittleFS::open(const String& path, const char* mode) {
    // Mock implementation: return a MockFile instance
    return MockFile();
}

MockFile::operator bool() const {
    return true;  // Return true to simulate a valid file
}