#include "Controller.h"
#include <ActuatorTypes/TabbingActuator.h>
#include <ActuatorTypes/StrokingActuator.h>

Controller::Controller(bool isSlave) : isSlave(isSlave), master(nullptr), slave(nullptr) {}

void Controller::setup() {
    if (isSlave) {
        initializeSlave();
    } else {
        initializeMaster();
    }
}

void Controller::initializeMaster() {
    VibrationActuator* strokingAct = new VibrationActuator(5);
    VibrationActuator* tabbingAct2 = new VibrationActuator(4);
    VibrationActuator* g1VibAct3 = new VibrationActuator(2);

    GloveModel rightGloveModel(Right, *g1VibAct3, *tabbingAct2, *strokingAct);

    master = new WifiMaster(rightGloveModel);
    master->setup();
}

void Controller::initializeSlave() {
    VibrationActuator* g1VibAct1 = new VibrationActuator(5);
    VibrationActuator* g1VibAct2 = new VibrationActuator(4);
    VibrationActuator* g1VibAct3 = new VibrationActuator(2);

    GloveModel leftGloveModel(Left, *g1VibAct3, *g1VibAct2, *g1VibAct1);

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

