#include "WifiSlave.h"
#include <Settings/SingeltonWifiSettings.h>

#ifdef TEST_ENV
    MockWifiEspNow WifiEspNow;
    MockWiFi WiFi;
    
#else
    WifiEspNow WifiEspNow;
    WiFi WiFi;
#endif

#ifdef SLAVE_DEVICE


void WifiSlave::onReceiveCallback(const uint8_t* mac, const uint8_t* buf, unsigned int count, void* arg) { //size_t count
    Serial.println("receiving messages");
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
    Serial.printf("Message from %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    if (count > 0) {
        uint8_t messageType = buf[0];
        if (messageType == 0) { // 0 indicates a vector
            uint8_t encoding = buf[1];
            if (encoding == 0) {
                // 0 == OST
                Serial.println("Setting encoding: (OST_ENCODING)");
                gloveModel.setChordMode(OST_ENCODING);
            } else {
                // 1 == Sequential
                Serial.println("Setting encoding: (SEQUENTIAL_ENCODING)");
                gloveModel.setChordMode(SEQUENTIAL_ENCODING);
            }

            // unsigned int vectorSize;
            // // Adjusted to use unsigned int for vectorSize
            // memcpy(&vectorSize, buf + 2, sizeof(unsigned int));
            // Read the vector size (size_t) after the first two bytes
            size_t vectorSize;
            memcpy(&vectorSize, buf + 2, sizeof(size_t));

            int repeat = 0;
            int offset = 2 + sizeof(size_t);  // Initial offset after message type, encoding, and vector size
            int firstValue;
            memcpy(&firstValue, buf + offset, sizeof(int));
            
            repeat = firstValue;  // Extract the repeat value (stored as a negative)
            offset += sizeof(int); // Move offset forward since repeat was found
            vectorSize -= 1;       // Adjust the vector size because repeat was counted
            Serial.printf("Repeat value detected: %d\n", repeat);
            
            Serial.printf("repeat: %u\n", repeat);

            Serial.printf("Received vector of size: %u\n", vectorSize);
            Serial.print("Vector values: ");
            std::vector<int> sensitivityPattern(vectorSize);
            for (size_t i = 0; i < vectorSize; i++) {
                int value;
                memcpy(&value, buf + offset + i * sizeof(int), sizeof(int));

                if (value == -1) {
                    sensitivityPattern[i] = 0;
                    Serial.print(" ");
                } else {
                    sensitivityPattern[i] = value;
                    Serial.print(value);
                }
            }
            Serial.println();
            if(repeat > 1){
                std::vector<int> sensitivityValues = sensitivityPattern;
                for(int i = 1; i < (int)repeat; i++){
                    sensitivityPattern.insert(sensitivityPattern.end(), sensitivityValues.begin(), sensitivityValues.end());
                }
                Serial.println();
            }

            receivedPatten(sensitivityPattern);

        } else if (messageType == 1) { // 1 indicates an integer
            int receivedInteger;
            memcpy(&receivedInteger, buf + 1, sizeof(int));

            Serial.printf("Received integer: %d\n", receivedInteger);
            receivedIndex(receivedInteger);

        } else {
            Serial.println("Unknown message type");
        }
    } else {
        Serial.println("Received empty message");
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
    Serial.println();

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA); // Set to Access Point mode
    WiFi.disconnect();
    WiFi.softAP(SingeltonWifiConnector::getInstance().SLAVE_SSID);

    // Initialize ESP-NOW
    if (!WifiEspNow.begin()) {
        Serial.print("Error initializing ESP-NOW");
        ESP.restart(); // Restart if initialization fails
    }

    // Print the MAC address of this node
    Serial.print("MAC address of this slave is: ");
    Serial.println(WiFi.macAddress());

    // Register the callback function for received data

    WifiEspNow.onReceive(WifiSlave::onReceiveCallback, this);
    // WifiEspNow.onReceive(onDataReceive, nullptr);
}

void WifiSlave::loop() {
   runProgram();
}

#endif