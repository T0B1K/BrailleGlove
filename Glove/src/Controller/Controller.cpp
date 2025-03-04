#include "Controller.h"

Controller::Controller(bool isSlave) : isSlave(isSlave) {
    #ifdef MASTER_DEVICE
        master = nullptr;
    #else
        slave = nullptr;
    #endif
}

void Controller::setup() {
    initializeDevice(isSlave);
}

void Controller::initializeDevice(bool isSlave) {
    if (isSlave) {
        #ifdef SLAVE_DEVICE
            VibrationActuator* g1VibAct1 = new VibrationActuator(5);
            VibrationActuator* g1VibAct2 = new VibrationActuator(4);
            VibrationActuator* g1VibAct3 = new VibrationActuator(2);

            GloveModel leftGloveModel(Left, *g1VibAct3, *g1VibAct2, *g1VibAct1);
            slave = new WifiSlave(leftGloveModel);
            slave->setup();
        #endif
    } else {
        #ifdef MASTER_DEVICE
            VibrationActuator* strokingAct = new VibrationActuator(5);
            VibrationActuator* tabbingAct2 = new VibrationActuator(4);
            VibrationActuator* g1VibAct3 = new VibrationActuator(2);

            GloveModel rightGloveModel(Right, *g1VibAct3, *tabbingAct2, *strokingAct);
            master = new WifiMaster(rightGloveModel);
            master->setup();
        #endif
    }
}

void Controller::loop() {
    if (!isSlave) {
        #ifdef MASTER_DEVICE
            master->loop();
        #endif
    } else {
        #ifdef SLAVE_DEVICE
            slave->loop();
        #endif
    }
}
