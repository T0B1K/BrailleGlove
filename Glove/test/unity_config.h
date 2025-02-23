#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

// Enable/disable Unity test runner verbosity
#define UNITY_OUTPUT_COLOR         1  // Enable colored output (1 = On, 0 = Off)

// Disable all checks (e.g. for memory allocation) for faster testing
#define UNITY_DISABLE_TEST_WARNINGS 1

// Define the test runner framework
#define UNITY_INCLUDE_CONFIG_H     1  // Include the config file
#define UNITY_USE_SERIAL           1  // Output results via serial monitor (optional)

// If you are using Arduino, you might need to enable these:
#if defined(ARDUINO)
    #define UNITY_USE_STDOUT        1  // Enable serial output
    #define UNITY_ENABLE_ARDUINO_INTERRUPTS 0
#endif

#endif // UNITY_CONFIG_H
