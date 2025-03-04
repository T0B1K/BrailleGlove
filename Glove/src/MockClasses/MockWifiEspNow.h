#ifndef MOCK_WIFI_ESPNOW_H
#define MOCK_WIFI_ESPNOW_H
#include <Arduino.h>

class MockWifiEspNow {
public:
    static bool begin();
    static bool addPeer(const uint8_t* macAddress);
    bool send(const uint8_t* macAddress, const uint8_t* data, size_t len);

    // Modify onReceive to accept a callback with the correct signature
    static void onReceive(void (*callback)(const uint8_t*, const uint8_t*, unsigned int, void*), void* thisPointer);

    // Simulate receiving data
    static void simulateReceive(const uint8_t* mac, const uint8_t* buf, unsigned int count);

private:
    static void (*onReceiveCallback)(const uint8_t*, const uint8_t*, unsigned int, void*);
    static void* onReceiveThisPointer;
};

#endif // MOCK_WIFI_ESPNOW_H
