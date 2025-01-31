#pragma once
#include <vector>

class RealTimeSynth {
public:
    RealTimeSynth();
    void processAudio(float* output, unsigned long framesPerBuffer);
    void setSynthFrequency(double freq);
private:
    double frequency;
    double phase;
};
