#include "gui/parameter_controls.h"

ParameterControls::ParameterControls(Equalizer& eq) : eq(eq) {}

void ParameterControls::render() {
    ImGui::Begin("🎚️ DSP Parameter Adjustments");

    static float bass = 1.0f, mid = 1.0f, treble = 1.0f;
    if (ImGui::SliderFloat("Bass", &bass, 0.0f, 2.0f)) eq.setBassGain(bass);
    if (ImGui::SliderFloat("Mid", &mid, 0.0f, 2.0f)) eq.setMidGain(mid);
    if (ImGui::SliderFloat("Treble", &treble, 0.0f, 2.0f)) eq.setTrebleGain(treble);

    ImGui::End();
}
