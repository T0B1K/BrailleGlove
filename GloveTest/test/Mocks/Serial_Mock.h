#ifndef MOCK_SERIAL_H
#define MOCK_SERIAL_H

#include <iostream>

class MockSerial {
    public:
        MockSerial(){}
        // Simulate the initialization of Serial communication with a baud rate
        void begin(long baudrate) {
            std::cout << "Serial started at baud rate: " << baudrate << std::endl;
        }

        // Mock Serial.print for unit testing
        void print(const std::string& data) {
            std::cout << data;
        }

        // Mock Serial.println for unit testing
        void println(const std::string& data) {
            std::cout << data << std::endl;
        }

        // Mock Serial.read to simulate reading a character
        char read() {
            // Return a dummy character for mocking purposes (e.g., 'A')
            return 'A';
        }

        // Mock Serial.available to simulate checking for data availability
        int available() {
            // Return 1 to simulate that there is data available
            return 1;
        }
};

#endif // MOCK_SERIAL_H
