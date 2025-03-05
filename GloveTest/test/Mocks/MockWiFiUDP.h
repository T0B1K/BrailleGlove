#ifndef WifiMock
#define WifiMock

// Ensure the mock is only included during unit testing
#ifdef UNIT_TEST
    #include <iostream>
    #include <functional>
#endif

class MockWiFiUDP {
public:
    void begin(int port) {}
    int parsePacket() { return 0; }
    void read(char* buffer, size_t len) {}
    void beginPacket(const char* ip, int port) {}
    void write(const char* data) {}
    void endPacket() {}
};

// Mock WiFi class used for testing
#ifdef UNIT_TEST
class WiFi {
public:
    // Mock persistent method (simply does nothing or prints a message)
    static void persistent(bool value) {
        std::cout << "MockWiFi persistent set to " << value << std::endl;
    }

    // Mock mode method (set to WIFI_STA for Station mode or other modes)
    static void mode(int mode) {
        std::cout << "MockWiFi mode set to " << mode << std::endl;
    }

    // Mock disconnect method
    static void disconnect() {
        std::cout << "MockWiFi disconnected" << std::endl;
    }

    // Mock softAP method to simulate setting up Access Point mode with an SSID
    static void softAP(const char* ssid) {
        std::cout << "MockSoftAP started with SSID: " << ssid << std::endl;
    }

    // Mock static method to simulate getting the MAC address
    static char macAddress() {
        return 'a';  // Just return 'a' as a placeholder for the MAC address
    }
};
#endif  // End of UNIT_TEST check

#endif // End of WifiMock guard
