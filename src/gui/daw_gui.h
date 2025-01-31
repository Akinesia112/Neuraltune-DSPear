// Use Dear ImGui to integrate EQ control, MIDI recording, automatic quantization, and WAV recording into the GUI.

#pragma once
#include "audio/eq.h"
#include "audio/wav_recorder.h"
#include "midi/midi_recorder.h"
#include "midi/midi_quantizer.h"
#include "midi/midi_controller.h"

#include "imgui.h"
#include "imnodes.h"
#include <vector>

class DAW_GUI {
public:
    DAW_GUI(Equalizer& eq, MidiRecorder& midi, MidiQuantizer& quantizer, WAVRecorder& recorder);
    void render();  // 繪製 GUI 介面

private:
    Equalizer& eq;
    MidiRecorder& midi;
    MidiQuantizer& quantizer;
    WAVRecorder& recorder;
};


class DSPGraph {
public:
    DSPGraph();
    void render(); // 繪製 DSP 節點編輯器

private:
    struct Node {
        int id;
        std::string label;
        float value;
    };

    std::vector<Node> nodes;
    std::vector<std::pair<int, int>> links;
};
