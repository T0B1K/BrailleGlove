#ifndef MOCK_WIFI_ESPNOW
#define MOCK_WIFI_ESPNOW

#include <iostream>
#include <cstring>  // For memcpy
#include <functional>



class WifiEspNow {
public:
    // Mock begin() function
    static bool begin() { 
        std::cout << "WifiEspNow begin called" << std::endl;
        return true;
    }

    // Mock onReceive method that accepts a callback
    void onReceive(std::function<void()> callback, void* instance) {
        // Store the callback and instance (for testing purposes, just call the callback immediately)
        std::cout << "Mock onReceive: Callback registered." << std::endl;
        callback();
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
};



class ESP{
    public:
    static void restart(){}
};

#endif