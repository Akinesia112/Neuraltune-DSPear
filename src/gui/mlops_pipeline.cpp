//　Use Ray RLlib to control DSP parameters

#include "gui/mlops_pipeline.h"
#include <iostream>

MLOpsPipeline::MLOpsPipeline() : learningRate(0.01f) {}

void MLOpsPipeline::render() {
    ImGui::Begin("🎛️ MLOps Control Panel");

    if (ImGui::SliderFloat("Learning Rate", &learningRate, 0.001f, 0.1f)) {
        std::cout << "🔄 Adjusting Learning Rate: " << learningRate << std::endl;
    }

    if (ImGui::Button("🚀 Train Model")) {
        trainModel();
    }

    ImGui::End();
}

void MLOpsPipeline::trainModel() {
    std::cout << "🎯 Training RL Model with Learning Rate: " << learningRate << std::endl;
    // Ray RLlib 訓練
}
