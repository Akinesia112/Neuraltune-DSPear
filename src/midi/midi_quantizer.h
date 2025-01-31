#pragma once
#include <vector>
#include <tuple>
#include <chrono>

class MidiQuantizer {
public:
    void quantize(std::vector<std::tuple<int, int, int, std::chrono::milliseconds>>& midiEvents, int gridSizeMs);
};
