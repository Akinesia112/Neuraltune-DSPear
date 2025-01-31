#pragma once
#include "imgui.h"
#include "audio/eq.h"

class ParameterControls {
public:
    ParameterControls(Equalizer& eq);
    void render();
private:
    Equalizer& eq;
};
