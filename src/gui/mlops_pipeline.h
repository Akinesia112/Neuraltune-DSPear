//　Use Ray RLlib to control DSP parameters
#pragma once
#include "imgui.h"
#include "ray/api.h"

class MLOpsPipeline {
public:
    MLOpsPipeline();
    void render();
    void trainModel();
private:
    float learningRate;
};
