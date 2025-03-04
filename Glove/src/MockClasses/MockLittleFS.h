#ifndef MOCK_LITTLEFS_H
#define MOCK_LITTLEFS_H
#include <Arduino.h>

class MockFile {
public:
    String readString() {
        return "";
    }
    void close();
    operator bool() const;

    // Implement other necessary methods as needed
};

class MockLittleFS {
public:
    static bool begin();
    static bool exists(const String& path);
    static MockFile open(const String& path, const char* mode);

    // Add other methods as needed
};

#endif // MOCK_LITTLEFS_H
