#ifndef MOCK_ESP8266_WEBSERVER_H
#define MOCK_ESP8266_WEBSERVER_H

#include <Arduino.h>
#include <functional>
#include <map>

enum WiFiModeGet {
    HTTP_GET,
    HTTP_POST,
};

class ESP8266WebServer {
public:
    // Constructor
    ESP8266WebServer(int port) {}

    void begin(){}
    // Mock the 'on' method that registers routes
    void on(const String& uri, WiFiModeGet method, std::function<void()> handler) {
        // Log the registration of the route for the test
        Serial.print("Route registered: ");
        Serial.print(uri);
        Serial.print(" with method: ");
        Serial.println(method);

        // Store the handler to be called in the test
        this->handler = handler;
    }
    
    void on(const String& uri, std::function<void()> handler) {
        // Log the registration of the route for the test
        Serial.print("Route registered: ");
        Serial.print(uri);

        // Store the handler to be called in the test
        this->handler = handler;
    }

    // Simulate an incoming HTTP request that triggers the registered handler
    void simulateRequest() {
        if (handler) {
            handler();  // Call the stored handler function
        }
    }

    // Mock 'send' method to simulate sending an HTTP response
    void send(int code, const String& contentType, const String& content) {
        // Log the response details
        Serial.print("HTTP Response sent: ");
        Serial.print("Code: ");
        Serial.print(code);
        Serial.print(", Content-Type: ");
        Serial.print(contentType);
        Serial.print(", Content: ");
        Serial.println(content);

        // Store the response details for verification in tests
        this->responseCode = code;
        this->responseContentType = contentType;
        this->responseContent = content;
    }

    // Methods to retrieve the sent response for assertions
    int getResponseCode() { return responseCode; }
    String getResponseContentType() { return responseContentType; }
    String getResponseContent() { return responseContent; }

    // Simulate the handling of a client request
    void handleClient() {
        // You can use simulateRequest() to manually invoke a registered handler
        simulateRequest();
    }

    // Mock hasArg() method to check for argument presence
    bool hasArg(const String& arg) {
        return args.find(arg) != args.end();
    }

    // Mock arg() method to retrieve argument values
    String arg(const String& arg) {
        return args[arg];
    }

    // Mock method to simulate setting arguments
    void setArg(const String& arg, const String& value) {
        args[arg] = value;
    }

private:
    std::function<void()> handler;  // Store the handler function

    // Store response details for testing
    int responseCode = 0;
    String responseContentType;
    String responseContent;

    // Store mock arguments for the request
    std::map<String, String> args;
};

#endif // MOCK_ESP8266_WEBSERVER_H
