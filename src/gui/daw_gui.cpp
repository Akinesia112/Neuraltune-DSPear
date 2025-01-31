// Use Dear ImGui to integrate EQ control, MIDI recording, automatic quantization, and WAV recording into the GUI.

#include "gui/daw_gui.h"


DAW_GUI::DAW_GUI(Equalizer& eq, MidiRecorder& midi, MidiQuantizer& quantizer, WAVRecorder& recorder) 
    : eq(eq), midi(midi), quantizer(quantizer), recorder(recorder) {}

void DAW_GUI::render() {
    ImGui::Begin("Neuraltune DSPear Controls");

    static float bass = 1.0f, mid = 1.0f, treble = 1.0f;
    if (ImGui::SliderFloat("Bass", &bass, 0.0f, 2.0f)) eq.setBassGain(bass);
    if (ImGui::SliderFloat("Mid", &mid, 0.0f, 2.0f)) eq.setMidGain(mid);
    if (ImGui::SliderFloat("Treble", &treble, 0.0f, 2.0f)) eq.setTrebleGain(treble);

    if (ImGui::Button("🎤 Record MIDI")) midi.clear();
    ImGui::SameLine();
    if (ImGui::Button("▶️ Play MIDI")) midi.playBack();
    ImGui::SameLine();
    if (ImGui::Button("🎼 Quantize MIDI")) quantizer.quantize(midi.getEvents(), 50);

    if (ImGui::Button("🎙️ Start WAV Recording")) recorder.startRecording();
    ImGui::SameLine();
    if (ImGui::Button("⏹️ Stop WAV Recording")) recorder.stopRecording();
    ImGui::SameLine();
    if (ImGui::Button("💾 Save WAV")) recorder.saveToFile("output.wav");

    ImGui::End();
}
