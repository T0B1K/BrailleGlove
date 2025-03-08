#ifndef GLOVE_MODEL_H
#define GLOVE_MODEL_H

#ifdef UNIT_TEST
#else
    #include <Arduino.h>
#endif

#include <unordered_map>
#include <vector>
#include "../ActuatorTypes/Actuator.h"
#include "../Models/HandEnum.h"
#include "../Settings/SingeltonGloveSettings.h"
#include "./EncodingScheme/ChordingScheme.h"
#include "./EncodingScheme/SequentialEncoding.h"
#include "./EncodingScheme/OSTEncoding.h"

/**
 * @class GloveModel
 * @brief Represents the glove model, simulating actuator behavior on a given hand.
 * 
 * This class is used to simulate the actuations of actuators on a glove. It defines the pattern of actuations
 * and the chording scheme (OST or sequential). The class also provides methods to control and reset actuators
 * and manage the sequence of actuations.
 */
class GloveModel {
private:
    Actuator* actuators[SingeltonGloveSettings::getInstance().NUM_ACTUATORS]; ///< Array of actuators for a single hand
    Hand hand; ///< Represents whether the glove is for the left or right hand
    std::vector<int> values; ///< The pattern of actuations to be played
    ChordingScheme playMode; ///< Defines the chording scheme (OST or sequential)

public:
    /**
     * @brief Constructs a GloveModel object with the given hand and actuators.
     * 
     * Initializes the glove with actuators and assigns the specified hand (left or right).
     * 
     * @param hand The hand (left or right) of the glove.
     * @param actuator1 First actuator of the glove.
     * @param actuator2 Second actuator of the glove.
     * @param actuator3 Third actuator of the glove.
     */
    GloveModel(Hand hand, Actuator& actuator1, Actuator& actuator2, Actuator& actuator3) {
        actuators[0] = &actuator1;
        actuators[1] = &actuator2;
        actuators[2] = &actuator3;
        this->hand = hand;
    }

    /**
     * @brief Resets all actuators to their initial state.
     * 
     * This method deactivates all actuators, ensuring that they start in the same condition.
     */
    void resetAllActuators() {
        for (int i = 0; i < SingeltonGloveSettings::getInstance().NUM_ACTUATORS; i++) {
            if (actuators[i] != nullptr) {
                actuators[i]->deactivate();
            }
        }
    }

    /**
     * @brief Executes a pattern of actuations at the specified index in the pattern.
     * 
     * Resets all actuators and vibrates based on the pattern at the given index.
     * 
     * @param index The index of the pattern to be executed.
     */
    void executePatternAt(int index) {
        resetAllActuators();
        activateOnNumber(values[index]);
    }

    /**
     * @brief Pauses between letters during a sequence of actuations.
     * 
     * This function applies a custom delay and resets all actuators after the delay.
     */
    void pauseBetweenLetters(){
        SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().DURATION);
        resetAllActuators();
        SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().PAUSE);
    }

    /**
     * @brief Activates the stimuli on a given number representing a specific actuator pattern.
     * 
     * The method activates and deactivates actuators based on the given number and the selected encoding scheme 
     * (OST or sequential).
     * 
     * @param number The number representing the actuator pattern to be activated using the specific stimuli.
     */
    void activateOnNumber(int number) {
        if (number < 1) {   // -1 is a pause, so reset every actuator
            pauseBetweenLetters();
            return;
        }
        while (number > 0) {
            int lastDigit = number % 10;
            number = (int)number / 10;

            if (playMode == SEQUENTIAL_ENCODING) {
                SequentialEncoding::handle(lastDigit, actuators, hand);
            } else {
                OSTEncoding::handle(lastDigit, actuators, hand);
            }
        }
        if (playMode == OST_ENCODING) {
            SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().DURATION);
            resetAllActuators();
        }
        SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().PAUSE);
    }

    /**
     * @brief Sets a new pattern of actuations to be played.
     * 
     * This method allows the user to define a new pattern of actuations.
     * 
     * @param newValues A vector containing the new pattern of actuations.
     */
    void setPattern(std::vector<int> newValues) {
        values = newValues;
    }

    /**
     * @brief Retrieves the current pattern of actuations.
     * 
     * This method returns the current pattern of actuations that is set.
     * 
     * @return A vector containing the current pattern of actuations.
     */
    std::vector<int> getPattern() {
        return values;
    }

    /**
     * @brief Returns the length of the current pattern.
     * 
     * @return The length of the current pattern.
     */
    int getPatternLength() {
        return values.size();
    }

    /**
     * @brief Sets the chording mode for the glove, either sequential or OST encoding.
     * 
     * This method selects the chording mode (either sequential or OST) for the actuations.
     * 
     * @param chordMode The desired chording scheme (SEQUENTIAL_ENCODING or OST_ENCODING).
     */
    void setChordMode(ChordingScheme chordMode) {
        playMode = chordMode;
    }
};

#endif
