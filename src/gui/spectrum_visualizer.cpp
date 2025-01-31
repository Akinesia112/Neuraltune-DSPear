#include "gui/spectrum_visualizer.h"

SpectrumVisualizer::SpectrumVisualizer(FFTAnalyzer& fftAnalyzer) 
    : fftAnalyzer(fftAnalyzer) {}

void SpectrumVisualizer::render(const std::vector<float>& audioBuffer) {
    spectrumData = fftAnalyzer.analyze(audioBuffer);

    ImGui::Begin("📊 Spectrum Analyzer");

    if (!spectrumData.empty()) {
        ImGui::PlotLines("FFT Spectrum", spectrumData.data(), spectrumData.size(), 0, nullptr, 0.0f, 1.0f, ImVec2(400, 150));
    } else {
        ImGui::Text("🎶 No Audio Data Available");
    }

    ImGui::End();
}
