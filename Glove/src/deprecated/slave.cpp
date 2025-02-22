// #include <ESP8266WiFi.h>
// #include <WiFiUdp.h>

// const char* ssid = "ESP-Master";
// const char* password = "masterpassword";
// const int ledPin = LED_BUILTIN; // Internal LED on GPIO 2 (ESP8266)
// const int udpPort = 12345;
// const int toggleInterval = 5; // 5ms toggle interval

// WiFiUDP udp;
// String pattern = "";
// bool startSequence = false;

// void setup() {
//   Serial.begin(115200);
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, HIGH); // LED off initially

//   // Connect to master ESP's Wi-Fi network
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nConnected to Master ESP");

//   // Start UDP
//   udp.begin(udpPort);
//   Serial.println("UDP listener started");
// }

// void loop() {
//   int packetSize = udp.parsePacket();
//   if (packetSize) {
//     String message = "";
//     while (udp.available()) {
//       char c = udp.read();
//       message += c;
//     }
//     if (message == "start") {
//       startSequence = true;
//     } else {
//       pattern = message; // Receive pattern
//     }
//   }

//   if (startSequence && pattern.length() > 0) {
//     for (char c : pattern) {
//       digitalWrite(ledPin, (c == 'x') ? LOW : HIGH);
//       delay(toggleInterval);
//     }
//     startSequence = false; // Reset sequence state
//   }
// }
