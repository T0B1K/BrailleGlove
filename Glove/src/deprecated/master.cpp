// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <WiFiUdp.h>

// const char* ssid = "ESP-Master";
// const char* password = "masterpassword";
// const int ledPin = LED_BUILTIN; // Internal LED on GPIO 2 (ESP8266)

// const char* slaveIP = "192.168.4.2"; // Replace with the actual IP address of the slave ESP8266
// const int udpPort = 12345;

// const int toggleInterval = 500; // 5ms toggle interval

// ESP8266WebServer server(80);
// WiFiUDP udp;

// void handleRoot() {
//   String html = "<html><body><h1>ESP Master</h1>";
//   html += "<button onclick=\"location.href='/start'\">Start LED Sequence</button>";
//   html += "</body></html>";
//   server.send(200, "text/html", html);
// }


// void handleStart() {
//   // Send LED pattern to slave
//   String pattern = "xoxxoxxxoxoxo"; // Example pattern
//   udp.beginPacket(slaveIP, udpPort);
//   udp.write(pattern.c_str());
//   udp.endPacket();
  
//   delay(1000); // Delay to ensure the pattern is received
  
//   // Send start command to slave
//   udp.beginPacket(slaveIP, udpPort);
//   udp.write("start");
//   udp.endPacket();
  
//   // Start LED sequence on master
//   for (char c : pattern) {
//     digitalWrite(ledPin, (c == 'x') ? LOW : HIGH);
//     delay(toggleInterval);
//     printf("LED: %d\n", c);
//   }
  
//   // Redirect back to root
//   server.sendHeader("Location", "/");
//   server.send(303);
// }

// void setup() {
//   Serial.begin(115200);
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, HIGH); // LED off initially

//   // Start Access Point
//   WiFi.softAP(ssid, password);

//   // Start UDP
//   udp.begin(udpPort);

//   // Serve the web page
//   server.on("/", handleRoot);
//   server.on("/start", handleStart);
//   server.begin();
//   Serial.println("Web server started");
// }

// void loop() {
//   server.handleClient();
// }


