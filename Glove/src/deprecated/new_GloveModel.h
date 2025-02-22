// #ifndef GLOVE_MODEL_H
// #define GLOVE_MODEL_H

// #include <Arduino.h>
// #include "../ActuatorTypes/Actuator.h"
// #include <unordered_map>
// #include <vector>
// #include "../Models/HandEnum.h"
// #include "../Settings/SingeltonGloveSettings.h"
// #include "ChordingScheme.h"



// class GloveModel {
//   private:
//     Actuator* actuators[3];
//     Hand hand;
//     std::vector<int> values;
//     ChordingScheme playMode; 
    
//   public:
//     GloveModel(Hand hand, Actuator& actuator1, Actuator& actuator2, Actuator& actuator3) {
//       actuators[0] = &actuator1;
//       actuators[1] = &actuator2;
//       actuators[2] = &actuator3;
//       this->hand = hand;
//     }

//     void resetAllActuators() {
//       Serial.println("Resetting all actuators");
//       for (int i = 0; i < SingeltonGloveSettings::getInstance().NUM_ACTUATORS; i++) {
//         if (actuators[i] != nullptr) {
//             //Serial.println("Deactivating actuator: " + String(i));
//             actuators[i]->deactivate();
//         }
//         //else {Serial.println("Actuator " + String(i) + " is not initialized");}
//       }
//     }

//     void executePatternAt(int index) {
//       resetAllActuators();
//       Serial.println("Executing pattern at index: " + String(index) + " values " + String(values.size()) + " idx " + index +" value " + values[index]);
//       vibrateOnNumber(values[index]);
//     }

//     void customDelay(unsigned long timeInMs){ //this is needed for wifi compatability
//       unsigned long startMillis = millis();  // Get the current time
//       while (millis() - startMillis < timeInMs) { 
//           yield();  //the programm doesn't stop
//       }
//     }


//     void executePattern() {
//       resetAllActuators();
//       Serial.println("Executing pattern > Pattern size: " + String(values.size()));
//       for (int i = 0; i < (int)values.size(); i++) {
//         vibrateOnNumber(values[i]);
//       }
//       Serial.println("Pattern executed");
//       resetAllActuators();
//     }

//     void vibrateOnNumber(int number){
//       if(number < 1){   //-1 is a pause, so reset every actuator
//         Serial.println("pause DURATION" + SingeltonGloveSettings::getInstance().DURATION);
//         customDelay(SingeltonGloveSettings::getInstance().DURATION);
//         resetAllActuators();
//         Serial.println("pause " + SingeltonGloveSettings::getInstance().PAUSE);
//         customDelay(SingeltonGloveSettings::getInstance().PAUSE);
//         return;
//       }
//       while (number > 0){
//         Serial.println("Number: " + String(number));
//         int lastDigit = number%10;
//         number = (int)number/10;

//         if(playMode == SEQUENTIAL_ENCODING){
//           secquentialModeHandeling(lastDigit);
//         }else{
//           ostModeHandeling(lastDigit);
//         }
        

//         }
//         customDelay(SingeltonGloveSettings::getInstance().DURATION);
//         resetAllActuators();
//     }

//     void setPattern(std::vector<int> newValues) {
//       values = newValues;
//     }
//     std::vector<int> getPattern() {
//       return values;
//     }

//     int getPatternLength(){
//       return values.size();
//     }


// void secquentialModeHandeling(int number){
     
//         if((hand == Left && number > SingeltonGloveSettings::getInstance().NUM_ACTUATORS) || (hand == Right && number < SingeltonGloveSettings::getInstance().NUM_ACTUATORS+1)){

//           //if the number is on the wrong hand, add a ost offset and ignore
//           Serial.println("Ignoring number (OST offset): " + String(number) + "\nOST offset" + SingeltonGloveSettings::getInstance().OST_OFFSET);
//           customDelay(SingeltonGloveSettings::getInstance().OST_OFFSET);
//           return;
//         }
//         int actuatorIdx = (number-1) % SingeltonGloveSettings::getInstance().NUM_ACTUATORS; //3 actuators on each hand
//         actuators[actuatorIdx]->activate();
// }

// void ostModeHandeling(int number){
// if((hand == Left && number > SingeltonGloveSettings::getInstance().NUM_ACTUATORS) || (hand == Right && number < SingeltonGloveSettings::getInstance().NUM_ACTUATORS+1)){

// }
//     int actuatorIdx = (number-1) % SingeltonGloveSettings::getInstance().NUM_ACTUATORS; //3 actuators on each hand
//     actuators[actuatorIdx]->activate();
//     Serial.println("Seq offset" + SingeltonGloveSettings::getInstance().SEQ_OFFSET);
//     customDelay(SingeltonGloveSettings::getInstance().SEQ_OFFSET);
//     actuators[actuatorIdx]->deactivate();
// }


// void setChordMode(ChordingScheme chordMode){
//   playMode = chordMode;
// }
    
// };
// #endif
