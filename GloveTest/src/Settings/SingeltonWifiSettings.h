#ifndef SINGELTON_WIFI_SETTINGS
#define SINGELTON_WIFI_SETTINGS

#include <cstdint>

/**
 * @class SingeltonWifiConnector
 * @brief Singleton class for Wi-Fi settings.
 * 
 * This class follows the Singleton pattern to ensure only one instance
 * exists for managing Wi-Fi settings, including SSID names and MAC address
 * for master and slave devices in the system.
 */
class SingeltonWifiConnector {
private:
    /**
     * @brief Private constructor to prevent instantiation.
     * 
     * The Singleton pattern ensures that only one instance of this class exists.
     */
    SingeltonWifiConnector() {}

    /**
     * @brief Deleted copy constructor to prevent copying the singleton instance.
     */
    SingeltonWifiConnector(const SingeltonWifiConnector&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment of the singleton instance.
     */
    void operator=(const SingeltonWifiConnector&) = delete;

public:
    /**
     * @brief Gets the singleton instance of the SingeltonWifiConnector class.
     * @return A reference to the single instance of SingeltonWifiConnector.
     */
    static SingeltonWifiConnector& getInstance() {
        static SingeltonWifiConnector instance;
        return instance;
    }

    /** @brief The SSID name for the master Wi-Fi network. */
    const char* MASTER_SSID = "MV-Glove";

    /** @brief The SSID name for the slave Wi-Fi network. */
    const char* SLAVE_SSID = "VS-Glove";

    /** 
     * @brief The MAC address of the slave device for the Wi-Fi connection.
     * 
     * The MAC address is used to identify the slave device in the network.
     */
    const uint8_t SLAVE_MAC[6] = {0x48, 0x55, 0x19, 0xF6, 0xC9, 0xB3};
};

#endif
