#ifndef MockESP8266WiFi
#define MockESP8266WiFi

class ESP8266WiFi {
public:
    static void begin(const char* ssid, const char* password) {}
    static bool connected() { return true; }
};

class ESP8266WebServer {
public:
    ESP8266WebServer(int port) {}
    void on(const char* uri, void (*handler)()) {}
    void begin() {}
    void handleClient() {}
};

class WiFiServer {
public:
    WiFiServer(int port) {}
    void begin() {}
};

#endif