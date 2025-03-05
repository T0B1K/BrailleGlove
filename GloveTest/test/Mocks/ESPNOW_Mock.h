#ifndef MOCK_WIFI_ESPNOW
#define MOCK_WIFI_ESPNOW

#include <iostream>
#include <cstring>  // For memcpy
#include <functional>

// Define a mock class to simulate the ESP-NOW functionality
class MockWifiEspNow {
public:
    // Mock begin() function
    static bool begin() { 
        std::cout << "WifiEspNow begin called" << std::endl;
        return true;
    }

    // Mock onReceive method that accepts a callback with the correct signature
    void onReceive(std::function<void(const uint8_t*, const uint8_t*, unsigned int, void*)> callback, void* instance) {
        // Store the callback and instance (for testing purposes, just call the callback immediately)
        std::cout << "Mock onReceive: Callback registered." << std::endl;

        // Example data to pass to the callback
        uint8_t mac[6] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
        uint8_t buf[4] = { 0x11, 0x22, 0x33, 0x44 };
        unsigned int count = 4;
        void* arg = nullptr;  // You can customize this if needed

        // Call the callback function
        callback(mac, buf, count, arg);
    }

    // Mock send method
    void send(const uint8_t mac[6], const uint8_t* data, size_t size) {
        // Simulate sending data by printing the MAC address and the data
        std::cout << "Sending data to MAC: ";
        for (int i = 0; i < 6; ++i) {
            std::cout << std::hex << (int)mac[i] << " ";  // Print MAC in hex
        }
        std::cout << std::dec << std::endl;  // Switch back to decimal
        
        std::cout << "Data to send: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::hex << (int)data[i] << " ";  // Print data in hex
        }
        std::cout << std::dec << std::endl;
    }

    bool addPeer(const uint8_t* mac) {
        std::cout << "Adding Peer: ";
        for (int i = 0; i < 6; ++i) {
            std::cout << std::hex << (int)mac[i] << " ";  // Print MAC in hex
        }
        return true;
    }

};

#endif
