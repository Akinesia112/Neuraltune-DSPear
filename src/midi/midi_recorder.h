// MIDI Recorder stores MIDI input as timestamped events and allows playback of recorded MIDI.

#pragma once
#include <vector>
#include <tuple>
#include <chrono>

class MidiRecorder {
public:
    void recordEvent(int status, int note, int velocity);
    void playBack();
    void clear();

private:
    std::vector<std::tuple<int, int, int, std::chrono::milliseconds>> events;
    std::chrono::steady_clock::time_point startTime;
};
