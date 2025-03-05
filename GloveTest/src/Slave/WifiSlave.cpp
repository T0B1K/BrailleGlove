#include "WifiSlave.h"
#include <Settings/SingeltonWifiSettings.h>

#ifdef UNIT_TEST
    #include "../test/Mocks/ESP_Mock.h"
    extern MockESPClass ESP;
#endif
#ifdef UNIT_TEST
    #ifndef HTTP_GET
        #define HTTP_GET 1
    #endif
    #ifndef HTTP_POST
        #define HTTP_POST 0
    #endif
    
    #ifndef WiFi
        extern MockWiFi WiFi;
    #endif

    #ifndef WifiEspNow
        extern MockWifiEspNow WifiEspNow;
    #endif

#endif

void WifiSlave::onReceiveCallback(const uint8_t* mac, const uint8_t* buf, unsigned int count, void* arg) { //size_t count
    WifiSlave* instance = static_cast<WifiSlave*>(arg); // Cast to instance
    instance->processMessage(mac, buf, count); // Call the non-static method
}


void WifiSlave::receivedIndex(int index){
    if (hasPatternFlag && index >= 0 && index < gloveModel.getPatternLength()) {
        nextCharacterFlag = true;
        this-> characterIndex = index;
    }
}

void WifiSlave::receivedPatten(std::vector<int> sensitivityPattern){
    nextCharacterFlag = false;  //stop code from executing
    hasPatternFlag = true;      //signal new pattern
    this-> characterIndex = 0;  //set index to start
    gloveModel.setPattern(sensitivityPattern);  //init new pattern
}


void WifiSlave::processMessage(const uint8_t* mac, const uint8_t* buf, unsigned int count) {

    if (count > 0) {
        uint8_t messageType = buf[0];
        if (messageType == 0) { // 0 indicates a vector
            uint8_t encoding = buf[1];
            if (encoding == 0) {
                gloveModel.setChordMode(OST_ENCODING);
            } else {
                gloveModel.setChordMode(SEQUENTIAL_ENCODING);
            }

            size_t vectorSize;
            memcpy(&vectorSize, buf + 2, sizeof(size_t));

            int repeat = 0;
            int offset = 2 + sizeof(size_t);  // Initial offset after message type, encoding, and vector size
            int firstValue;
            memcpy(&firstValue, buf + offset, sizeof(int));
            
            repeat = firstValue;  // Extract the repeat value (stored as a negative)
            offset += sizeof(int); // Move offset forward since repeat was found
            vectorSize -= 1;       // Adjust the vector size because repeat was counted
            std::vector<int> sensitivityPattern(vectorSize);
            for (size_t i = 0; i < vectorSize; i++) {
                int value;
                memcpy(&value, buf + offset + i * sizeof(int), sizeof(int));

                if (value == -1) {
                    sensitivityPattern[i] = 0;
                } else {
                    sensitivityPattern[i] = value;
                }
            }
            if(repeat > 1){
                std::vector<int> sensitivityValues = sensitivityPattern;
                for(int i = 1; i < (int)repeat; i++){
                    sensitivityPattern.insert(sensitivityPattern.end(), sensitivityValues.begin(), sensitivityValues.end());
                }
            }

            receivedPatten(sensitivityPattern);

        } else if (messageType == 1) { // 1 indicates an integer
            int receivedInteger;
            memcpy(&receivedInteger, buf + 1, sizeof(int));

            receivedIndex(receivedInteger);

        }
    }
}

void WifiSlave::runProgram(){
    //Serial.println("hasPatternFlag: " + String(hasPatternFlag) + " nextCharacterFlag: " + String(nextCharacterFlag));
    if (hasPatternFlag && nextCharacterFlag){//pol if pattern and index otherwise disregard
        int oldCharacterIndex = characterIndex;
        gloveModel.executePatternAt(oldCharacterIndex);

        if(oldCharacterIndex == characterIndex){//check for race condition, disable if flag wasn't changed in the meantime
            nextCharacterFlag = false;
        }
    }
}

WifiSlave::WifiSlave(GloveModel gloveModel)
    : gloveModel(gloveModel) {}




void WifiSlave::setup() {
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA); // Set to Access Point mode
    WiFi.disconnect();
    WiFi.softAP(SingeltonWifiConnector::getInstance().SLAVE_SSID);

    // Initialize ESP-NOW
    if (!WifiEspNow.begin()) {
        ESP.restart(); // Restart if initialization fails
    }


    WifiEspNow.onReceive(WifiSlave::onReceiveCallback, this);
}

void WifiSlave::loop() {
   runProgram();
}

