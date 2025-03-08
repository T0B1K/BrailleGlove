#ifndef ACTUATOR_PROCESSING_ORDER_MAPPER_H
#define ACTUATOR_PROCESSING_ORDER_MAPPER_H

#ifdef UNIT_TEST
    /**
     * @brief Helper class for unit testing private functions of ActuatorProcessingOrderMapper.
     */
    class ActuatorProcessingOrderMapperTestHelper;
#endif

#include <unordered_map>
#include <vector>

/**
 * @class ActuatorProcessingOrderMapper
 * @brief Reorders braille dot numbers based on finger sensitivity order.
 * 
 * This class processes braille chords and reorders the actuation sequence 
 * based on predefined sensitivity levels of each dot.
 */
class ActuatorProcessingOrderMapper {
private:
    /**
     * @brief Maps each braille dot number to its sensitivity order.
     * 
     * The sensitivity order is predefined based on braille dot positions, 
     * ranking them from most to least sensitive.
     */
    std::unordered_map<int, int> SENSITIVITY_ORDER;

    /**
     * @brief Initializes the sensitivity order for each braille dot number.
     * 
     * This function defines the mapping of sensitivity levels, determining 
     * which dots should be processed first.
     */
    void initializeSensitivityOrder();

    /**
     * @brief Reorders a given braille chord based on sensitivity.
     * 
     * Given a braille chord represented as an integer (e.g., '14' for 'c'), 
     * this function reorders the dots according to the sensitivity order.
     * 
     * @param number The braille chord represented as an integer.
     * @return The reordered integer representation of the braille chord.
     */
    int reorderBySensitivity(int number);

public:
    /**
     * @brief Constructor for ActuatorProcessingOrderMapper.
     * 
     * Initializes the sensitivity order mapping.
     */
    ActuatorProcessingOrderMapper();

    /**
     * @brief Reorders a vector of braille chords based on sensitivity.
     * 
     * Each braille chord in the vector is restructured based on the predefined 
     * sensitivity order.
     * 
     * @param values A vector of braille chords encoded as integers.
     * @return A reordered vector with braille chords sorted by sensitivity.
     */
    std::vector<int> reorderVectorBySensitivity(const std::vector<int>& values);

#ifdef UNIT_TEST
    /**
     * @brief Allows unit testing access to private members.
     */
    friend class ActuatorProcessingOrderMapperTestHelper;
#endif
};

#endif // ACTUATOR_PROCESSING_ORDER_MAPPER_H
