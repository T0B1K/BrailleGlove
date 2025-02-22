// #include <ESP8266WebServer.h>
// #include <LittleFS.h>

// class FrontendView {
// public:
//     FrontendView(ESP8266WebServer* server) : server(server) {}
    
//     void setFrontend() {
//         if (LittleFS.exists("/switch.html")) {
//             File file = LittleFS.open("/switch.html", "r");
//             if (file) {
//                 String content = file.readString();
//                 server->send(200, "text/html", content);
//                 file.close();
//             } else {
//                 server->send(500, "text/plain", "Server error: Unable to read file");
//             }
//         } else {
//             server->send(404, "text/plain", "File not found");
//         }
//     }
    
// private:
//     ESP8266WebServer* server;
// };
