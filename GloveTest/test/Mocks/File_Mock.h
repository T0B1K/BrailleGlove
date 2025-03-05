#ifndef MOCK_FILE
#define MOCK_FILE

#ifndef String
#include "String_Mock.h"
#endif

class MockFile {
public:
    // Default constructor
    MockFile() : isOpen(false) {}

    // Function to simulate reading from a file
    std::string readString() {
        return "";  // Return empty string for now
    }

    // Method to simulate opening the file
    bool open(const std::string& filename) {
        // Simulate opening the file (return true if "opened")
        isOpen = true;
        return isOpen;
    }
    // Method to simulate opening the file
    bool close() {
        // Simulate opening the file (return true if "opened")
        isOpen = false;
        return isOpen;
    }

    // Implement operator bool to convert File object to bool
    explicit operator bool() const {
        return isOpen;  // Return true if file is open, false otherwise
    }

private:
    bool isOpen;  // Internal flag to track if the file is "opened"
};

#endif // MOCK_FILE
