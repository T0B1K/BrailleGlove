#include "MockClasses/MockESP8266WebServer.h"

// The `send()` method is already implemented in the header, but it can be extended if needed.
void MockESP8266WebServer::send(int code, const String& contentType, const String& content) {
    Serial.print("HTTP Response sent: ");
    Serial.print("Code: ");
    Serial.print(code);
    Serial.print(", Content-Type: ");
    Serial.print(contentType);
    Serial.print(", Content: ");
    Serial.println(content);

    this->responseCode = code;
    this->responseContentType = contentType;
    this->responseContent = content;
}
