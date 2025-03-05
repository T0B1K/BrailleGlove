#ifndef WIFI_SLAVE_H
#define WIFI_SLAVE_H

#ifdef UNIT_TEST
    #include "../test/Mocks/ESP8266WiFi_Mock.h"
    #include "../test/Mocks/ESPNOW_Mock.h"
    #include "../test/Mocks/MockWiFiUDP.h"
#else
    #include <ESP8266WiFi.h>
    #include <WifiEspNow.h>
#endif


#include <vector>

#include "Models/GloveModel.h"

class WifiSlave {
public:
    WifiSlave(GloveModel gloveModel);
    void setup();
    void loop();
    static void onReceiveCallback(const uint8_t* mac, const uint8_t* buf, size_t count, void* arg);
    void processMessage(const uint8_t* mac, const uint8_t* buf, size_t count);

private:
    GloveModel gloveModel;
    bool hasPatternFlag = false;
    bool nextCharacterFlag = false;
    int characterIndex = 0;

    void runProgram();
    void receivedIndex(int index);
    void receivedPatten(std::vector<int> sensitivityPattern);
};

#endif // WIFI_SLAVE_H
