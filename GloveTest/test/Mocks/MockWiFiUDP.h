#ifndef Mock_WiFI
#define Mock_WiFI

#ifndef WIFI_STA
    #define WIFI_STA 1
    #define WIFI_AP 0
    
#endif

class MockWiFi {
    public:
        MockWiFi(){}
        static void persistent(bool enable) {}

        static void mode(int mode) {}

        static void disconnect() {}

        static void softAP(const char* ssid) {}
};
#endif
