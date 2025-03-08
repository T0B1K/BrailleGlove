#ifndef OST_ENCODING_H
#define OST_ENCODING_H

#include "../../ActuatorTypes/Actuator.h"
#include "../../Settings/SingeltonGloveSettings.h"
#include "../../Models/HandEnum.h"
#include "Encoding.h"

/**
 * @class OSTEncoding
 * @brief Handles the OST encoding scheme for actuators.
 * 
 * This class defines the OST encoding scheme and how the actuators should be activated based on that scheme.
 */
class OSTEncoding : public Encoding {
public:
    /**
     * @brief Activates an actuator based on the OST encoding sequence.
     * 
     * This function handles the activation of actuators based on the OST encoding scheme. The activation sequence
     * is determined by the index number and the hand (left or right). The appropriate actuator is activated according
     * to the given index, and a custom delay is applied.
     * 
     * @param number The index number representing the actuator to be activated.
     * @param actuators The array of actuator pointers to be used.
     * @param hand The hand (left or right) to which the actuator belongs.
     */
    static void handle(int number, Actuator** actuators, Hand hand) {
        if (validIndex(number, hand)) {
            int actuatorIdx = (number - 1) % SingeltonGloveSettings::getInstance().NUM_ACTUATORS;
            actuators[actuatorIdx]->activate();
        }
        customDelay(SingeltonGloveSettings::getInstance().OST_OFFSET);
    }
};

#endif
