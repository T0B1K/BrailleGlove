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
        // const char* PASSWORD = "masterpassword";

        // const uint8_t SLAVE_MAC[] = {0x82, 0x7D, 0x3A, 0x6E, 0x58, 0x7E}; // big esp
        // const uint8_t SLAVE_MAC[6] = {0x48, 0x55, 0x19, 0xEE, 0xC7, 0xF5};//{0xBE, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; // Only define here {BE:DD:C2:51:3E:FC} = (small esp device)
        //MAC address of this slave is: B4:E6:2D:17:E2:FD
        //C8:C9:A3:29:5E:44 //normal mode
        
        //const uint8_t SLAVE_MAC[6] = {0xC8, 0xC9, 0xA3, 0x25, 0x1A, 0x23};//{0xBE, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; // Only define here {BE:DD:C2:51:3E:FC} = (small esp device)

        //stroking slave 48:55:19:F6:C9:B3!!!!!
        // const uint8_t SLAVE_MAC[6] = {0x48, 0x55, 0x19, 0xF6, 0xC9, 0xB3};//{0xBE, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; // Only define here {BE:DD:C2:51:3E:FC} = (small esp device)
        
        //tabbing slave C8:C9:A3:29:5B:66 (cahnged)
        // const uint8_t SLAVE_MAC[6] = {0xC8, 0xC9, 0xA3, 0x29, 0x5B, 0x66};//{0xBE, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; // Only define here {BE:DD:C2:51:3E:FC} = (small esp device)

        //(slave old prototype)
        // const uint8_t SLAVE_MAC[6] = {0x48, 0x55, 0x19, 0xEE, 0xC7, 0xF5};//{0xBE, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; // Only define here {BE:DD:C2:51:3E:FC} = (small esp device)

        // C8:C9:A3:25:1A:23 (master old prototype)
        // const uint8_t SLAVE_MAC[6] = {0xC8, 0xC9, 0xA3, 0x25, 0x1A, 0x23};//{0xBE, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; // Only define here {BE:DD:C2:51:3E:FC} = (small esp device)

        // const uint8_t SLAVE_MAC[6] = {0x48, 0x55, 0x19, 0xEE, 0xC7, 0xF5};//{0xBE, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; // Only define here {BE:DD:C2:51:3E:FC} = (small esp device)
        // const uint8_t SLAVE_MAC[6] = {0xBC, 0xDD, 0xC2, 0x51, 0x3E, 0xFC}; //special blue slav yellowe
        // const uint8_t SLAVE_MAC[6] = {0xC8, 0xC9, 0xA3, 0x29, 0x5E, 0x44}; //special vibration slave 2
        const uint8_t SLAVE_MAC[6] = {0x48, 0x55, 0x19, 0xF6, 0xC9, 0xB3}; //black slave 2
};

#endif