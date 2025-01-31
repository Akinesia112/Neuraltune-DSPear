// MIDI Recorder stores MIDI input as timestamped events and allows playback of recorded MIDI.

#include "midi/midi_recorder.h"
#include <iostream>
#include <thread>

void MidiRecorder::recordEvent(int status, int note, int velocity) {
    auto now = std::chrono::steady_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
    events.emplace_back(status, note, velocity, timestamp);
    std::cout << "🎤 Recorded MIDI Note: " << note << " Velocity: " << velocity << " Time: " << timestamp.count() << " ms" << std::endl;
}

void MidiRecorder::playBack() {
    if (events.empty()) return;

    std::cout << "▶️ Playing Back MIDI..." << std::endl;
    auto playbackStart = std::chrono::steady_clock::now();

    for (const auto& [status, note, velocity, timestamp] : events) {
        std::this_thread::sleep_until(playbackStart + timestamp);
        std::cout << "🔊 MIDI Note: " << note << " (Velocity: " << velocity << ")" << std::endl;
    }
}

void MidiRecorder::clear() {
    events.clear();
    std::cout << "🗑️ Cleared MIDI Recording" << std::endl;
}
