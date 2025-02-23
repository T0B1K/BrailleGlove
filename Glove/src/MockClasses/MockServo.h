#ifndef MOCK_SERVO_H
#define MOCK_SERVO_H

class MockServo {
public:
    void attach(int pin);
    void write(int angle);
    void writeMicroseconds(int pulse);
    int read();
    int readMicroseconds();
    bool attached();
    void detach();
};

#endif // MOCK_SERVO_H
