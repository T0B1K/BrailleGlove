#ifndef DATA_SENDER_H
#define DATA_SENDER_H

#include <cstdint>
#include <cstring>
#include <vector>
#include <WifiEspNow.h>
#include <./Models/EncodingScheme/ChordingScheme.h>
#include "../Settings/SingeltonWifiSettings.h"

class DataSender {
public:
    void setup();
    void sendVectorToSlave(const std::vector<int>& reorderedValues, ChordingScheme status);
    void sendIntegerToSlave(int singleValueToSend);
};

#endif