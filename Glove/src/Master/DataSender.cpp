#include "./DataSender.h"



void DataSender::setup(){
    // Initialize ESP-NOW
    if (!WifiEspNow.begin()) {
        Serial.println("Error initializing ESP-NOW");
        ESP.restart(); // Restart if initialization fails
    }

    // Print the MAC address of this node
    Serial.print("MAC address of this master is: ");
    Serial.println(WiFi.macAddress());
  
    // Add the slave as a peer
    if (!WifiEspNow.addPeer(SingeltonWifiConnector::getInstance().SLAVE_MAC)) {
        Serial.println("Failed to add peer");
        ESP.restart(); // Restart if adding peer fails
    }
}

void DataSender::sendVectorToSlave(const std::vector<int>& reorderedValues, const ChordingScheme status) {
    std::vector<int> vectorToSend;

    for (int value : reorderedValues) {
        if (value == 0) {
            vectorToSend.push_back(-1);  // Replace 0 with -1, otherwise can't be sent
        } else {
            vectorToSend.push_back(value);  // Keep the original value
        }
    }

    size_t vectorSize = vectorToSend.size();
    size_t totalSize = sizeof(uint8_t) * 2 + sizeof(size_t) + vectorSize * sizeof(int);  // Adjusted total size for two bytes at the beginning
    uint8_t* dataToSend = new uint8_t[totalSize];

    dataToSend[0] = 0;  // 0 for vector

    // Set the second character based on the status
    if (status == OST_ENCODING) {
        dataToSend[1] = 0;  // 0 if status is OST
    } else if (status == SEQUENTIAL_ENCODING) {
        dataToSend[1] = 1;  // 1 if status is SEQ
    }

    // Copy the vector size after the first two characters
    memcpy(dataToSend + 2, &vectorSize, sizeof(size_t));
    // Copy the vector data after the size
    memcpy(dataToSend + 2 + sizeof(size_t), vectorToSend.data(), vectorSize * sizeof(int));

    WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, totalSize);
    Serial.printf("==> Sent vector of size %zu to slave\n\n", vectorSize);
    delete[] dataToSend;
}

void DataSender::sendIntegerToSlave(int singleValueToSend){
     uint8_t dataToSend[sizeof(uint8_t) + sizeof(int)];
    dataToSend[0] = 1; // 1 for integer
    memcpy(dataToSend + 1, &singleValueToSend, sizeof(int));

    WifiEspNow.send(SingeltonWifiConnector::getInstance().SLAVE_MAC, dataToSend, sizeof(dataToSend));
    Serial.printf("==> Sent integer %d to slave\n\n", singleValueToSend);
}
