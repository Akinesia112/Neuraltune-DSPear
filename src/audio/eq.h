// Use the Infinite Impulse Response(IIR) filter to achieve 3-band EQ: low frequency (Bass), medium frequency (Mid), and high frequency (Treble).

#pragma once
#include <vector>

class Equalizer {
public:
    Equalizer();
    float process(float sample);
    void setBassGain(float gain);
    void setMidGain(float gain);
    void setTrebleGain(float gain);

private:
    float bassGain, midGain, trebleGain;
    float bassPrev, midPrev, treblePrev;
};
