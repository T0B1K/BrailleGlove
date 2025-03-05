#ifndef MOCK_STRING_H
#define MOCK_STRING_H

#include <iostream>
#include <cstring>
#include <string>  // For std::string

class MockString {
public:
    MockString() : data("") {}

    // Constructor to convert std::string to MockString
    MockString(const std::string& str) {
        strncpy(data, str.c_str(), sizeof(data) - 1);  // Copy string safely to the buffer
        data[sizeof(data) - 1] = '\0';  // Ensure null-termination
    }

    // Constructor to convert const char* to MockString
    MockString(const char* str) {
        strncpy(data, str, sizeof(data) - 1);
        data[sizeof(data) - 1] = '\0';
    }

    // Constructor to convert a single char to MockString
    MockString(char c) {
        data[0] = c;
        data[1] = '\0';  // Null-terminate after the single character
    }

    // Overload the assignment operator for std::string
    MockString& operator=(const std::string& str) {
        strncpy(data, str.c_str(), sizeof(data) - 1);
        data[sizeof(data) - 1] = '\0';
        return *this;
    }

    // Length of the string
    size_t length() const {
        return strlen(data);
    }

    // Return the C-string representation
    const char* c_str() const {
        return data;
    }

    // Concatenate another MockString or const char* to the current string using +
    MockString operator+(const MockString& other) const {
        MockString result;
        strncpy(result.data, data, sizeof(result.data) - 1);
        strncat(result.data, other.data, sizeof(result.data) - strlen(result.data) - 1);
        return result;
    }

    MockString operator+(const char* str) const {
        MockString result;
        strncpy(result.data, data, sizeof(result.data) - 1);
        strncat(result.data, str, sizeof(result.data) - strlen(result.data) - 1);
        return result;
    }

    // Concatenate const char[] to the front of MockString using operator+
    friend MockString operator+(const char* str, const MockString& mockStr) {
        MockString result(str);
        result += mockStr;
        return result;
    }

    // Concatenate C-string to the end using += operator
    MockString& operator+=(const char* str) {
        strncat(data, str, sizeof(data) - strlen(data) - 1);  // Concatenate the C-string to data
        return *this;
    }

    // Concatenate another MockString using += operator
    MockString& operator+=(const MockString& other) {
        strncat(data, other.data, sizeof(data) - strlen(data) - 1);
        return *this;
    }

    // Equality operator for comparisons
    bool operator==(const MockString& other) const {
        return strcmp(data, other.data) == 0;
    }

    bool operator==(const char* str) const {
        return strcmp(data, str) == 0;
    }

    // Concatenate C-string to the end
    void concat(const char* str) {
        strncat(data, str, sizeof(data) - strlen(data) - 1);
    }

    // Provide a way to iterate over the string in a range-based for loop
    const char* begin() const {
        return data;  // Return pointer to the start of the string
    }

    const char* end() const {
        return data + strlen(data);  // Return pointer to one past the end of the string
    }

    // Overload the index operator to allow access to individual characters
    char operator[](size_t idx) const {
        if (idx < strlen(data)) {
            return data[idx];
        }
        return '\0';  // Return null character if out of bounds
    }

private:
    char data[256];  // Fixed size buffer to hold the string (can adjust size as needed)
};

#define String MockString  // Replace String with MockString for tests

#endif // MOCK_STRING_H
