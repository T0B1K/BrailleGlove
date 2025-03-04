#ifndef SINGELTON_GLOVE_SETTINGS
#define SINGELTON_GLOVE_SETTINGS


class SingeltonGloveSettings {
    private:
        SingeltonGloveSettings() {}
        SingeltonGloveSettings(const SingeltonGloveSettings&) = delete;
        void operator=(const SingeltonGloveSettings&) = delete;

    public:
        static SingeltonGloveSettings& getInstance() {
            static SingeltonGloveSettings instance;
            return instance;
        }

        //TODO change settings accordingly
        const int OST_OFFSET = 10;
        const int DURATION = 200;
        const int PAUSE = 2000;
        const int NUM_ACTUATORS = 3;
        const int AUDIO_VIBRATION_OFFSET = 100;

        const int SEQ_OFFSET = 1000;
        const int studyOstRepititions = 126;
        const int studySeqRepititions = 44;

        
};

#endif