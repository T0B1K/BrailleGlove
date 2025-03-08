#ifndef ACTUATOR_TYPE_H
#define ACTUATOR_TYPE_H

/**
 * @enum ActuatorType
 * @brief Enum representing different types of actuators.
 * 
 * This enumeration defines the available actuator types used in the system.
 */
enum ActuatorType {
    Vibration, ///< Actuator type for vibration-based sensation.
    Tabbing,   ///< Actuator type for tabbing (tapping) sensation.
    Stroking   ///< Actuator type for stroking sensation.
};

#endif // ACTUATOR_TYPE_H
