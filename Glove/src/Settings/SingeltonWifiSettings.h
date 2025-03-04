#include <cstdint>
#ifndef SINGELTON_WIFI_SETTINGS
#define SINGELTON_WIFI_SETTINGS


class SingeltonWifiConnector {
    private:
        SingeltonWifiConnector() {}
        SingeltonWifiConnector(const SingeltonWifiConnector&) = delete;
        void operator=(const SingeltonWifiConnector&) = delete;

    public:
        static SingeltonWifiConnector& getInstance() {
            static SingeltonWifiConnector instance;
            return instance;
        }

        const char* MASTER_SSID = "MV-Glove";
        const char* SLAVE_SSID = "VS-Glove";
        const uint8_t SLAVE_MAC[6] = {0x48, 0x55, 0x19, 0xF6, 0xC9, 0xB3}; //use the right slave mac
};

#endif