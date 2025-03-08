#ifndef CHORDING_SCHEME_H
#define CHORDING_SCHEME_H

/**
 * @enum ChordingScheme
 * @brief Enum to define the encoding schemes for braille chord processing.
 * 
 * This enum is used to differentiate between two types of encoding schemes: 
 * OST_ENCODING and SEQUENTIAL_ENCODING.
 */
enum ChordingScheme { 
    OST_ENCODING,     ///< Encoding based on OST (One-Shot Timing) scheme.
    SEQUENTIAL_ENCODING ///< Encoding based on sequential timing scheme.
};

#endif
