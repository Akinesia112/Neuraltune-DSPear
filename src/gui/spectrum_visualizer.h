#pragma once
#include <vector>
#include "audio/fft_analyzer.h"
#include "imgui.h"

class SpectrumVisualizer {
public:
    SpectrumVisualizer(FFTAnalyzer& fftAnalyzer);
    void render(const std::vector<float>& audioBuffer); // 繪製頻譜視覺化圖

private:
    FFTAnalyzer& fftAnalyzer;
    std::vector<double> spectrumData;
};
