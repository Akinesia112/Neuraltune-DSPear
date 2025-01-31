#pragma once
#include <vector>
#include <string>

class WAVRecorder {
public:
    void startRecording();
    void stopRecording();
    void saveToFile(const std::string& filename);

private:
    std::vector<float> recordedAudio;
    bool isRecording = false;
};
