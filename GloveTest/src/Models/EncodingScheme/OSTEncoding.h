#ifndef OST_ENCODING_H
#define OST_ENCODING_H

#include "../../ActuatorTypes/Actuator.h"
#include "../../Settings/SingeltonGloveSettings.h"
#include "../../Models/HandEnum.h"
#include "Encoding.h"

class OSTEncoding : public Encoding {
public:
    static void handle(int number, Actuator** actuators, Hand hand) {
        if (validIndex(number, hand)) {
            int actuatorIdx = (number - 1) % SingeltonGloveSettings::getInstance().NUM_ACTUATORS; // 3 actuators on each hand
            actuators[actuatorIdx]->activate();
        }
        customDelay(SingeltonGloveSettings::getInstance().OST_OFFSET);
    }
};

#endif
