#ifndef SINGELTON_GLOVE_SETTINGS
#define SINGELTON_GLOVE_SETTINGS

/**
 * @class SingeltonGloveSettings
 * @brief Singleton class that defines all the different glove settings.
 * 
 * This class follows the Singleton pattern, ensuring that only one instance of the glove settings exists.
 * It contains various constants that define the parameters for actuator timing, offsets, and repetitions
 * related to the glove's operation.
 */
class SingeltonGloveSettings {
private:
    /**
     * @brief Private constructor to prevent instantiation.
     * 
     * The Singleton pattern ensures only one instance of this class exists.
     */
    SingeltonGloveSettings() {}

    /**
     * @brief Deleted copy constructor to prevent copying the singleton instance.
     */
    SingeltonGloveSettings(const SingeltonGloveSettings&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment of the singleton instance.
     */
    void operator=(const SingeltonGloveSettings&) = delete;

public:
    /**
     * @brief Gets the singleton instance of the SingeltonGloveSettings class.
     * @return A reference to the single instance of SingeltonGloveSettings.
     */
    static SingeltonGloveSettings& getInstance() {
        static SingeltonGloveSettings instance;
        return instance;
    }

    /** @brief The offset between activations in the OST encoding. */
    const int OST_OFFSET = 10;

    /** @brief Duration of actuator activation in milliseconds. */
    const int DURATION = 200;

    /** @brief Pause time between two characters in milliseconds. */
    const int PAUSE = 2000;

    /** @brief The number of actuators used in the glove. */
    const int NUM_ACTUATORS = 3;

    /** @brief The offset between audio stimuli and tactile stimuli in milliseconds. */
    const int AUDIO_STIMULI_OFFSET = 100;

    /** @brief The offset between characters in the Sequential encoding scheme. */
    const int SEQ_OFFSET = 1000;

    /** @brief Number of repetitions for the OST encoding in the study. */
    const int studyOstRepititions = 126;

    /** @brief Number of repetitions for the Sequential encoding in the study. */
    const int studySeqRepititions = 44;
};

#endif
