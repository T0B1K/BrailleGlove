#ifndef MOCK_ESP8266_WEBSERVER_H
#define MOCK_ESP8266_WEBSERVER_H

#include <Arduino.h>
#include <functional>

class MockESP8266WebServer {
public:
    // Constructor
    MockESP8266WebServer(int port) {
    }

    // Method to register a route
    void on(const String& uri, int method, std::function<void()> handler) {
        // Log the registration of the route
        Serial.print("Route registered: ");
        Serial.print(uri);
        Serial.print(" with method: ");
        Serial.println(method);

        // Store the handler to be called in the test
        this->handler = handler;
    }

    // Simulate the handler call in unit tests
    void simulateRequest() {
        if (handler) {
            handler();
        }
    }

    // Simulate sending an HTTP response
    void send(int code, const String& contentType, const String& content) {
        // Log response details for debugging
        Serial.print("HTTP Response sent: ");
        Serial.print("Code: ");
        Serial.print(code);
        Serial.print(", Content-Type: ");
        Serial.print(contentType);
        Serial.print(", Content: ");
        Serial.println(content);

        // Store response details for test verification
        this->responseCode = code;
        this->responseContentType = contentType;
        this->responseContent = content;
    }

    // Methods to retrieve response details for assertions
    int getResponseCode() { return responseCode; }
    String getResponseContentType() { return responseContentType; }
    String getResponseContent() { return responseContent; }

private:
    std::function<void()> handler;  // Store the handler function

    // Store response details
    int responseCode = 0;
    String responseContentType;
    String responseContent;
};

#endif  // MOCK_ESP8266_WEBSERVER_H
