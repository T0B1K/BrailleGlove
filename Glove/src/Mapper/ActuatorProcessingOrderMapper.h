#ifndef ACTUATOR_PROCESSING__ORDER_MAPPER_H
#define ACTUATOR_PROCESSING__ORDER_MAPPER_H

#include <Arduino.h>

class ActuatorProcessingOrderMapper {
  private:
    // Sensitivity order for the actuators, from most to most least sensitive given the braille number
    std::unordered_map<int, int> SENSITIVITY_ORDER; // HashMap to store mappings

  public:
    ActuatorProcessingOrderMapper() {
      SENSITIVITY_ORDER[1] = 2;
      SENSITIVITY_ORDER[2] = 4;
      SENSITIVITY_ORDER[3] = 6;
      SENSITIVITY_ORDER[4] = 1;
      SENSITIVITY_ORDER[5] = 3;
      SENSITIVITY_ORDER[6] = 5;

    }

    int reorderBySensitvity(int number){
      if (number == 0) return 0;
      std::vector<int> actuatorOrder = {0, 0, 0, 0, 0, 0};
      while (number > 0){
        int lastDigit = number%10;
        number = (int)number/10;
        actuatorOrder[SENSITIVITY_ORDER[lastDigit]-1] = lastDigit;
      }

      int newNumber = 0;
      for (int i = 5; i >= 0; i--) {
        if(actuatorOrder[i] == 0) continue;
        newNumber = newNumber*10 + actuatorOrder[i];
      }
      return newNumber;
    }

    std::vector<int> reorderVectorBySensitivity(std::vector<int> values){
      std::vector<int> reorderedValues(values.size());
      for (int i = 0; i < (int)values.size(); i++) {
        reorderedValues[i] = reorderBySensitvity(values[i]);
      }
      return reorderedValues;
    }
};

#endif