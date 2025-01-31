#include "audio/wav_recorder.h"
#include <sndfile.h>
#include <iostream>

void WAVRecorder::startRecording() {
    isRecording = true;
    recordedAudio.clear();
    std::cout << "🎙️ 開始錄音..." << std::endl;
}

void WAVRecorder::stopRecording() {
    isRecording = false;
    std::cout << "⏹️ 停止錄音。" << std::endl;
}

void WAVRecorder::saveToFile(const std::string& filename) {
    SF_INFO sfInfo;
    sfInfo.samplerate = 44100;
    sfInfo.frames = recordedAudio.size();
    sfInfo.channels = 1;
    sfInfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE* file = sf_open(filename.c_str(), SFM_WRITE, &sfInfo);
    if (!file) {
        std::cerr << "❌ 錄音存檔失敗！" << std::endl;
        return;
    }

    sf_write_float(file, recordedAudio.data(), recordedAudio.size());
    sf_close(file);
    std::cout << "💾 WAV 已儲存：" << filename << std::endl;
}
