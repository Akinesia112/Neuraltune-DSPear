#include "audio/oscillator.h"
constexpr double sampleRate = 44100.0;
constexpr double pi = 3.141592653589793;

Oscillator::Oscillator(Waveform waveform, double frequency, double amplitude)
    : waveform(waveform), frequency(frequency), amplitude(amplitude), phase(0.0) {}

double Oscillator::process() {
    double sample = 0.0;
    switch (waveform) {
        case Waveform::Sine: sample = std::sin(2.0 * pi * phase); break;
        case Waveform::Square: sample = (std::sin(2.0 * pi * phase) > 0.0) ? 1.0 : -1.0; break;
        case Waveform::Sawtooth: sample = 2.0 * (phase - std::floor(phase + 0.5)); break;
        case Waveform::Triangle: sample = 2.0 * std::abs(2.0 * (phase - std::floor(phase + 0.5))) - 1.0; break;
    }
    phase += frequency / sampleRate;
    if (phase >= 1.0) phase -= 1.0;
    return sample * amplitude;
}
