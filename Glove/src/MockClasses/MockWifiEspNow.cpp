#include "MockWifiEspNow.h"

void (*MockWifiEspNow::onReceiveCallback)(const uint8_t*, const uint8_t*, unsigned int, void*) = nullptr;
void* MockWifiEspNow::onReceiveThisPointer = nullptr;

// Implement the static methods
bool MockWifiEspNow::begin() {
    // Implementation
    return true;
}

bool MockWifiEspNow::addPeer(const uint8_t* macAddress) {
    // Implementation
    return true;
}

bool MockWifiEspNow::send(const uint8_t* macAddress, const uint8_t* data, size_t len) {
    // Implementation
    return true;
}

void MockWifiEspNow::onReceive(void (*callback)(const uint8_t*, const uint8_t*, unsigned int, void*), void* thisPointer) {
    onReceiveCallback = callback;
    onReceiveThisPointer = thisPointer;
}

void MockWifiEspNow::simulateReceive(const uint8_t* mac, const uint8_t* buf, unsigned int count) {
    if (onReceiveCallback) {
        onReceiveCallback(mac, buf, count, onReceiveThisPointer);
    }
}
