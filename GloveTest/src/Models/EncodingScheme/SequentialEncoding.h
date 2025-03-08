#ifndef SEQUENTIAL_ENCODING_H
#define SEQUENTIAL_ENCODING_H

#include "../../ActuatorTypes/Actuator.h"
#include "../../Settings/SingeltonGloveSettings.h"
#include "../../Models/HandEnum.h"
#include "Encoding.h"

/**
 * @class SequentialEncoding
 * @brief Handles the sequential encoding scheme for actuators.
 * 
 * This class defines the sequential encoding scheme and how the actuators should be activated in sequence.
 */
class SequentialEncoding : public Encoding {
public:
    /**
     * @brief Activates and deactivates an actuator based on the sequential encoding scheme.
     * 
     * This function handles the sequential encoding scheme by activating the actuator corresponding to the
     * given pin number and hand (left or right). After activation, the actuator is deactivated after a 
     * specified duration. A delay is applied both after activation and deactivation.
     * 
     * @param number The index number representing the actuator to be activated.
     * @param actuators The array of actuator pointers to be used.
     * @param hand The hand (left or right) to which the actuator belongs.
     */
    static void handle(int number, Actuator** actuators, Hand hand) {
        if (validIndex(number, hand)) {
            int actuatorIdx = (number - 1) % SingeltonGloveSettings::getInstance().NUM_ACTUATORS;
            actuators[actuatorIdx]->activate();
            customDelay(SingeltonGloveSettings::getInstance().DURATION);
            actuators[actuatorIdx]->deactivate();
            customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET);
        } else {
            customDelay(SingeltonGloveSettings::getInstance().DURATION);
            customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET);
        }
    }
};

#endif
