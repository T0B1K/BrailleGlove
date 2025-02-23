#ifndef DATA_SENDER_H
#define DATA_SENDER_H

#ifdef TEST_ENV
    #include "MockClasses/MockWifiEspNow.h"
#else
    #include <WifiEspNow.h>
#endif

#include <cstdint>
#include <cstring>
#include <vector>

#include <./Models/EncodingScheme/ChordingScheme.h>
#include "../Settings/SingeltonWifiSettings.h"

class DataSender {
public:
    void setup();
    void sendVectorToSlave(const std::vector<int>& reorderedValues, ChordingScheme status);
    void sendIntegerToSlave(int singleValueToSend);
};

#endif