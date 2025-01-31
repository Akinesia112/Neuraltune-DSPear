#pragma once
#include <vector>
#include <portaudio.h>

class PortAudioWrapper {
public:
    PortAudioWrapper();
    ~PortAudioWrapper();

    bool startPlayback(std::vector<float> &audioData);

private:
    struct AudioBuffer {
        std::vector<float> buffer;
        size_t currentIndex = 0;
    };

    static int audioCallback(const void *input, void *output,
                             unsigned long frameCount,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData);

    AudioBuffer data;
};
