#ifndef ACTUATOR_PROCESSING__ORDER_MAPPER_H
#define ACTUATOR_PROCESSING__ORDER_MAPPER_H

#ifdef UNIT_TEST
    // Only define the friend class relationship during unit testing
    class ActuatorProcessingOrderMapperTestHelper;
#endif

#include <unordered_map>
#include <vector>

class ActuatorProcessingOrderMapper {
  private:
    // Sensitivity order for the actuators, from most to least sensitive based on the braille number
    std::unordered_map<int, int> SENSITIVITY_ORDER;

    void initializeSensitivityOrder();

    int reorderBySensitivity(int number);
    
  public:
    ActuatorProcessingOrderMapper();

    std::vector<int> reorderVectorBySensitivity(const std::vector<int>& values);

#ifdef UNIT_TEST
    // Define the friend class only if UNIT_TEST is defined
    friend class ActuatorProcessingOrderMapperTestHelper;
#endif
};

#endif // ACTUATOR_PROCESSING__ORDER_MAPPER_H
