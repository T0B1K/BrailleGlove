#ifndef MOCK_WIFI_ESPNOW_H
#define MOCK_WIFI_ESPNOW_H
#include <Arduino.h>

class MockWifiEspNow {
public:
    static bool begin();
    static bool addPeer(const uint8_t* macAddress);
    bool send(const uint8_t* macAddress, const uint8_t* data, size_t len);
    
};

class MockESP {
public:
    static void restart();
};

class MockWiFi {
public:
    static String macAddress();
    static void persistent(bool persistent);
    static void mode(int mode);
    static void disconnect();
    static bool softAP(const String& ssid);
};

enum WiFiMode {
    WIFI_STA = 1,
    WIFI_AP = 2,
    WIFI_AP_STA = 3
};


#endif // MOCK_WIFI_ESPNOW_H
