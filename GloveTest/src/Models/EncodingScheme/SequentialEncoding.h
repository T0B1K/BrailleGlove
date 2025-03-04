#ifndef SEQUENTIAL_ENCODING_H
#define SEQUENTIAL_ENCODING_H

#include "../../ActuatorTypes/Actuator.h"
#include "../../Settings/SingeltonGloveSettings.h"
#include "../../Models/HandEnum.h"
#include "Encoding.h"

class SequentialEncoding : public Encoding {
public:
    static void handle(int number, Actuator** actuators, Hand hand) {
        if (validIndex(number, hand)) {
            int actuatorIdx = (number - 1) % SingeltonGloveSettings::getInstance().NUM_ACTUATORS; // 3 actuators on each hand
            actuators[actuatorIdx]->activate();
            Serial.println("PAUSE: " + String(SingeltonGloveSettings::getInstance().DURATION) + " (DURATION)");
            customDelay(SingeltonGloveSettings::getInstance().DURATION);
            actuators[actuatorIdx]->deactivate();
            Serial.println("PAUSE: " + String(SingeltonGloveSettings::getInstance().SEQ_OFFSET) + " (SEQ-OFFSET)");
            customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET);
        }else{
            Serial.println("Ignoring Character on this glove: " + String(number));
            Serial.println("PAUSE: " + String(SingeltonGloveSettings::getInstance().DURATION) + " (DURATION)");
            customDelay(SingeltonGloveSettings::getInstance().DURATION);
            Serial.println("PAUSE: " + String(SingeltonGloveSettings::getInstance().SEQ_OFFSET) + " (SEQ-OFFSET)");
            customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET);
        }
    }
};

#endif
