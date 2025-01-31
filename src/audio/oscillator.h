#pragma once
#include <cmath>

enum class Waveform { Sine, Square, Sawtooth, Triangle };

class Oscillator {
public:
    Oscillator(Waveform waveform, double frequency, double amplitude);

    double process();
    void setFrequency(double freq);
    void setAmplitude(double amp);
    void setWaveform(Waveform wf);

private:
    Waveform waveform;
    double frequency;
    double amplitude;
    double phase;
};
