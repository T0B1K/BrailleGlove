#include "MockWifiEspNow.h"

// Implement other methods as needed
void MockESP::restart() {
    // Mock implementation
}

bool MockWifiEspNow::send(const uint8_t* macAddress, const uint8_t* data, size_t len) {
    // Mock implementation
    // For example, log the data to be sent
    Serial.print("Sending data to ");
    Serial.println(macAddress[0]);
    // Return true to indicate success
    return true;
}

bool MockWifiEspNow::begin() {
    // Mock implementation
    return true;
}

bool MockWifiEspNow::addPeer(const uint8_t* macAddress) {
    // Mock implementation
    return true;
}

String MockWiFi::macAddress() {
    // Mock implementation
    return "00:11:22:33:44:55";
}

void MockWiFi::persistent(bool persistent) {
    // Mock implementation: just log the call or do nothing
    Serial.print("WiFi persistent: ");
    Serial.println(persistent ? "true" : "false");
}

void MockWiFi::mode(int mode) {
    // Mock implementation: log the Wi-Fi mode being set
    String modeStr = (mode == WIFI_AP) ? "WIFI_AP" : "Unknown Mode";
    Serial.print("WiFi mode set to: ");
    Serial.println(modeStr);
}

void MockWiFi::disconnect() {
    // Mock implementation: just log the disconnect action
    Serial.println("WiFi disconnected");
}

bool MockWiFi::softAP(const String& ssid) {
    // Mock implementation: log the SSID for the softAP mode
    Serial.print("WiFi softAP started with SSID: ");
    Serial.println(ssid);
    return true;  // Simulate successful operation
}
