#pragma once
#include <RtMidi.h>
#include <functional>

class MidiController {
public:
    MidiController(std::function<void(int, int, int)> noteCallback);
    ~MidiController();
    void start();

private:
    RtMidiIn midiIn;
    std::function<void(int, int, int)> noteCallback;
    static void midiCallback(double timeStamp, std::vector<unsigned char>* message, void* userData);
};
