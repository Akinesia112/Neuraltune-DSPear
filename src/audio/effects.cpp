#include "effects.h"

Equalizer::Equalizer(double lowGain, double midGain, double highGain)
    : lowGain(lowGain), midGain(midGain), highGain(highGain) {}

double Equalizer::process(double input) {
    // Example: Simplified 3-band EQ
    return input * (lowGain + midGain + highGain) / 3.0;
}

Limiter::Limiter(double threshold) : threshold(threshold) {}

double Limiter::process(double input) {
    if (input > threshold) return threshold;
    if (input < -threshold) return -threshold;
    return input;
}
