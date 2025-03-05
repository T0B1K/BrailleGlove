#include "ActuatorProcessingOrderMapper.h"

// Constructor to initialize the sensitivity order
ActuatorProcessingOrderMapper::ActuatorProcessingOrderMapper() {
    initializeSensitivityOrder();
}

// Initialize the sensitivity order map
void ActuatorProcessingOrderMapper::initializeSensitivityOrder() {
    SENSITIVITY_ORDER[1] = 2;
    SENSITIVITY_ORDER[2] = 4;
    SENSITIVITY_ORDER[3] = 6;
    SENSITIVITY_ORDER[4] = 1;
    SENSITIVITY_ORDER[5] = 3;
    SENSITIVITY_ORDER[6] = 5;
}

// Reorder the digits of the given number based on the sensitivity order
int ActuatorProcessingOrderMapper::reorderBySensitivity(int number) {
    if (number == 0) return 0;
    
    std::vector<int> actuatorOrder(6, 0);  // Initialize with 0s
    
    while (number > 0) {
        int lastDigit = number % 10;
        number /= 10;
        actuatorOrder[SENSITIVITY_ORDER[lastDigit] - 1] = lastDigit;
    }

    int newNumber = 0;
    for (int i = 5; i >= 0; i--) {
        if (actuatorOrder[i] != 0) {
            newNumber = newNumber * 10 + actuatorOrder[i];
        }
    }
    return newNumber;
}

// Reorder a vector of values by sensitivity
std::vector<int> ActuatorProcessingOrderMapper::reorderVectorBySensitivity(const std::vector<int>& values) {
    std::vector<int> reorderedValues(values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        reorderedValues[i] = reorderBySensitivity(values[i]);
    }
    return reorderedValues;
}
