#include "midi/midi_quantizer.h"
#include <iostream>
#include <cmath>

void MidiQuantizer::quantize(std::vector<std::tuple<int, int, int, std::chrono::milliseconds>>& midiEvents, int gridSizeMs) {
    for (auto& [status, note, velocity, timestamp] : midiEvents) {
        int newTime = std::round(timestamp.count() / (double)gridSizeMs) * gridSizeMs;
        timestamp = std::chrono::milliseconds(newTime);
    }
    std::cout << "🎼 MIDI 量化完成 (Grid: " << gridSizeMs << "ms)" << std::endl;
}
