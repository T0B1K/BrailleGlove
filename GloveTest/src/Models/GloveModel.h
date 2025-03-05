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

class GloveModel {
private:
    Actuator* actuators[3];
    Hand hand;
    std::vector<int> values;
    ChordingScheme playMode; 

public:
    GloveModel(Hand hand, Actuator& actuator1, Actuator& actuator2, Actuator& actuator3) {
        actuators[0] = &actuator1;
        actuators[1] = &actuator2;
        actuators[2] = &actuator3;
        this->hand = hand;
    }

    void resetAllActuators() {
        for (int i = 0; i < SingeltonGloveSettings::getInstance().NUM_ACTUATORS; i++) {
            if (actuators[i] != nullptr) {
                actuators[i]->deactivate();
            }
        }
    }

    void executePatternAt(int index) {
        resetAllActuators();
        vibrateOnNumber(values[index]);
    }

    void pauseBetweenLetters(){
        SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().DURATION);
        resetAllActuators();
        SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().PAUSE);
    }

    void vibrateOnNumber(int number) {
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
        if(playMode == OST_ENCODING){
            SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().DURATION);
            resetAllActuators();
        }
        SequentialEncoding::customDelay(SingeltonGloveSettings::getInstance().PAUSE);
    }

    void setPattern(std::vector<int> newValues) {
        values = newValues;
    }

    std::vector<int> getPattern() {
        return values;
    }

    int getPatternLength() {
        return values.size();
    }

    void setChordMode(ChordingScheme chordMode) {
        playMode = chordMode;
    }
};

#endif
