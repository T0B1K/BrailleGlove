#ifndef MOCK_WIFI_H
#define MOCK_WIFI_H
#include <Arduino.h>

enum WifiModes {
    WIFI_STA = 1,
    WIFI_AP = 0
};

class MockWiFi {
public:
    static String macAddress() {
        // Return a mock MAC address
        return "00:11:22:33:44:55";
    }

    static void persistent(bool persistent) {
        // Simulate setting persistent mode
    }

    static void mode(int mode) {
        // Simulate setting WiFi mode
    }

    static void disconnect() {
        // Simulate disconnecting from WiFi
    }

    static bool softAP(const String& ssid) {
        // Simulate starting a soft AP
        return true;
    }
};

#endif // MOCK_WIFI_H
