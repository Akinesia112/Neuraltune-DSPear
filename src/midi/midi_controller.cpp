#include "midi/midi_controller.h"
#include <iostream>

MidiController::MidiController(std::function<void(int, int, int)> noteCallback)
    : midiIn(), noteCallback(noteCallback) {
    if (midiIn.getPortCount() == 0) {
        std::cerr << "❌ No MIDI devices found." << std::endl;
        return;
    }
    midiIn.openPort(0);
    midiIn.setCallback(midiCallback, this);
    midiIn.ignoreTypes(false, false, false);
}

MidiController::~MidiController() { midiIn.closePort(); }

void MidiController::midiCallback(double timeStamp, std::vector<unsigned char>* message, void* userData) {
    if (message->size() == 3) {
        int status = (*message)[0];
        int note = (*message)[1];
        int velocity = (*message)[2];
        auto* controller = static_cast<MidiController*>(userData);
        if (controller) controller->noteCallback(status, note, velocity);
    }
}

void MidiController::start() {
    std::cout << "🎹 MIDI Controller Started. Listening for input..." << std::endl;
    while (true) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
}
