// Use the Infinite Impulse Response(IIR) filter to achieve 3-band EQ: low frequency (Bass), medium frequency (Mid), and high frequency (Treble).

#include "audio/eq.h"
#include <cmath>

Equalizer::Equalizer() : bassGain(1.0f), midGain(1.0f), trebleGain(1.0f),
                         bassPrev(0.0f), midPrev(0.0f), treblePrev(0.0f) {}

float Equalizer::process(float sample) {
    float bass = bassGain * (0.1f * sample + 0.9f * bassPrev);
    float mid = midGain * (0.3f * sample + 0.7f * midPrev);
    float treble = trebleGain * (0.7f * sample + 0.3f * treblePrev);

    bassPrev = bass;
    midPrev = mid;
    treblePrev = treble;

    return bass + mid + treble;
}

void Equalizer::setBassGain(float gain) { bassGain = gain; }
void Equalizer::setMidGain(float gain) { midGain = gain; }
void Equalizer::setTrebleGain(float gain) { trebleGain = gain; }
