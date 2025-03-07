# GloveTest
This repository contains the code for creating a braille glove 

# Internals
## Project Structure  

```
GloveTest/
│── data/
│   ├── switch.html          # This is the mobile website for controlling the microcontrollers
│   ├── TestingSite.html     # This is the testing site used on the laptop
│
│── src/
│   │── ActuatorTypes/
│   │   ├── Actuator.h        # Abstract class for any kind of actuator
│   │   ├── ActuatorType.h    # Enum file for actuator names
│   │   ├── StrokingActuator.h  # Code for the stroking actuator
│   │   ├── TabbingActuator.h   # Code for the tabbing actuator
│   │   ├── VibrationActuator.h # Code for the vibration actuator
│   │
│   │── Controller/
│   │   ├── Controller.h      # Controls whether the microcontroller is a master or slave
│   │
│   │── Mapper/
│   │   ├── ActuatorProcessingOrderMapper.h # Defines processing order for actuator sensitivity
│   │   ├── BrailleMapper.h   # Maps characters to Braille encoded for controller pins
│   │
│   │── Master/
│   │   ├── WifiMaster.h      # Handles WiFi communication and website setup for master
│   │
│   │── Models/
│   │   │── EncodingScheme/
│   │   │   ├── ChordingScheme.h    # Enum for OST and Sequential encoding
│   │   │   ├── Encoding.h          # Controls encoding and switches encoding type
│   │   │   ├── OSTEncoding.h       # OST encoding implementation
│   │   │   ├── SequentialEncoding.h # Sequential encoding implementation
│   │   │
│   │   ├── GloveModel.h      # Defines glove functions, timings, and pin mapping
│   │   ├── HandEnum.h        # Enum for left or right hand
│   │
│   │── Settings/
│   │   ├── SingletonGloveSettings.h # Stores OST and Sequential timing settings
│   │   ├── SingletonWifiSettings.h  # Stores WiFi settings including slave MAC and network names
│   │
│   │── Slave/
│   │   ├── WifiSlave.h       # Handles data reception and glove model execution on the slave
│
│── main.ino                  # Main program file
│── platform.ini               # PlatformIO configuration file
```

## Description  

This project is designed for controlling a **Passive Haptic Learning Braille Glove** using an ESP8266 d1 mini microcontroller. It consists of a **master-slave** architecture where the **master** handles **WiFi communication** and the **website interface**, while the **slave** receives data and executes actuator commands.  

## Components  

- **data/**: Contains web files for controlling the microcontrollers.  
- **src/ActuatorTypes/**: Defines different actuator types (stroking, tabbing, vibration).  
- **src/Controller/**: Determines master/slave functionality.  
- **src/Mapper/**: Handles encoding mapping for Braille and actuator sensitivity.  
- **src/Master/**: Implements the master controller handling WiFi and web setup.  
- **src/Models/**: Includes encoding logic (OST and Sequential) and glove functions.  
- **src/Settings/**: Stores configuration settings for the glove and WiFi.  
- **src/Slave/**: Implements the slave microcontroller logic.  
- **main.ino**: The primary entry point of the program.  
- **platform.ini**: Configuration file for PlatformIO, which is used for the arduino code.


## Tests
The tests are contained in the test files.
Moreover, we are using a CI/CD pipeline to build the project in GitHub directly using GitHub actions.

```
GloveTest/
│── test/ 
│   ├── ActuatorTypesTest          # This is the testing site for the actuator types
│   ├── MapperTest    # This is the testing site for the mappers
│   ├── Mocks    # This is the testing site that creates the mocks in order to let it compile without the right controller on the github actions
│   ├── ModelsTest    # This is the testing site for the different encodings
```
