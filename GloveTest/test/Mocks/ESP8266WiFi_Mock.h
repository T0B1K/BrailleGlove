#ifndef MockESP8266WiFi
#define MockESP8266WiFi

#ifndef String
    #include "String_Mock.h"
#endif

class ESP8266WiFi {
public:
    static void begin(const char* ssid, const char* password) {}
    static bool connected() { return true; }
};

#include <iostream>
#include <functional>
#include <map>
#include <vector>

class ESP8266WebServer {
public:
    ESP8266WebServer(int port) {
        // Initialize with the given port (not used in mock but can be extended if needed)
    }

    // Simulate the server route registration
    void on(const char* uri, std::function<void()> handler) {
        handlers[uri] = handler;
    }
    void on(const char* uri,int i, std::function<void()> handler) {
        handlers[uri] = handler;
    }

    // Simulate starting the server (nothing needed in mock)
    void begin() {
        std::cout << "Server started..." << std::endl;
    }

    // Handle client requests (invoke the corresponding handler)
    void handleClient() {
        for (auto& entry : handlers) {
            // For mock purposes, just print and invoke the handler
            std::cout << "Handling request for " << entry.first << std::endl;
            entry.second();  // Call the handler associated with this URI
        }
    }

    // Simulate sending an HTTP response
    void send(int code, const char* contentType, const MockString& body) {
        std::cout << "HTTP Response: " << code << " " << contentType << " " << body.c_str() << std::endl;
    }

    // Helper methods for mock data (simulating server's arguments)
    bool hasArg(const MockString& arg) {
        return args.find(arg.c_str()) != args.end();
    }

    MockString arg(const MockString& arg) {
        return args[arg.c_str()];
    }

    // Method to simulate setting arguments (for testing)
    void setArg(const MockString& key, const MockString& value) {
        args[key.c_str()] = value.c_str();
    }

private:
    std::map<std::string, std::function<void()>> handlers;  // Store routes and their handlers
    std::map<std::string, std::string> args;  // Simulate query parameters for the request
};


class WiFiServer {
public:
    WiFiServer(int port) {}
    void begin() {}
};

#endif