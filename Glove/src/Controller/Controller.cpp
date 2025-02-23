#include "Controller.h"
#include <ActuatorTypes/TabbingActuator.h>
#include <ActuatorTypes/StrokingActuator.h>
#include <ActuatorTypes/VibrationActuator.h>

Controller::Controller(bool isSlave) : isSlave(isSlave), master(nullptr), slave(nullptr) {}

void Controller::setup() {
    if (isSlave) {
        initializeSlave();
    } else {
        initializeMaster();
    }
}

void Controller::initializeMaster() {
    // TabbingActuator* strokingAct = new TabbingActuator(5);
    // TabbingActuator* tabbingAct2 = new TabbingActuator(4);
    // TabbingActuator* g1VibAct3 = new TabbingActuator(2);

    // StrokingActuator* strokingAct = new StrokingActuator(5);
    // StrokingActuator* tabbingAct2 = new StrokingActuator(4);
    // StrokingActuator* g1VibAct3 = new StrokingActuator(2);

    VibrationActuator* strokingAct = new VibrationActuator(5);
    VibrationActuator* tabbingAct2 = new VibrationActuator(4);
    VibrationActuator* g1VibAct3 = new VibrationActuator(2);


    GloveModel rightGloveModel(Right, *g1VibAct3, *tabbingAct2, *strokingAct);

    // Now pass rightGloveModel to WifiMaster
    //master = new WifiMaster(rightGloveModel);
    master = new WifiMaster(rightGloveModel);
    master->setup();
}

void Controller::initializeSlave() {
    // //esp8266mod
    // TabbingActuator* g1VibAct1 = new TabbingActuator(5);
    // TabbingActuator* g1VibAct2 = new TabbingActuator(4);
    // TabbingActuator* g1VibAct3 = new TabbingActuator(2);

    VibrationActuator* g1VibAct1 = new VibrationActuator(5);
    VibrationActuator* g1VibAct2 = new VibrationActuator(4);
    VibrationActuator* g1VibAct3 = new VibrationActuator(2);

    
    // StrokingActuator* g1VibAct1 = new StrokingActuator(5);
    // StrokingActuator* g1VibAct2 = new StrokingActuator(4);
    // StrokingActuator* g1VibAct3 = new StrokingActuator(2);

    // GloveModel is being initialized as a regular object, not a pointer.
    GloveModel leftGloveModel(Left, *g1VibAct3, *g1VibAct2, *g1VibAct1);

    // Now pass rightGloveModel to WifiMaster
    slave = new WifiSlave(leftGloveModel);
    slave->setup();
}

void Controller::loop() {
    if (isSlave) {
        slave->loop();
    } else {
        master->loop();
    }
}

