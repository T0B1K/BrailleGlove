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
            customDelay(SingeltonGloveSettings::getInstance().DURATION);
            actuators[actuatorIdx]->deactivate();
            customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET);
        }else{
            customDelay(SingeltonGloveSettings::getInstance().DURATION);
            customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET);
        }
    }
};

#endif
