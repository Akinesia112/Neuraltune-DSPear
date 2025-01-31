#include "audio/real_time_synthesis.h"
#include <cmath>

RealTimeSynth::RealTimeSynth() : frequency(440.0), phase(0.0) {}

void RealTimeSynth::setSynthFrequency(double freq) {
    frequency = freq;
}

void RealTimeSynth::processAudio(float* output, unsigned long framesPerBuffer) {
    for (unsigned long i = 0; i < framesPerBuffer; ++i) {
        output[i] = sin(2.0 * M_PI * phase);
        phase += frequency / 44100.0;
        if (phase >= 1.0) phase -= 1.0;
    }
}
