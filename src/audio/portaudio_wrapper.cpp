#include "audio/portaudio_wrapper.h"
#include <iostream>
#include <cmath>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

// Constructor: Initialize PortAudio
PortAudioWrapper::PortAudioWrapper() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "❌ PortAudio Initialization Error: " << Pa_GetErrorText(err) << std::endl;
    }
}

// Destructor: Terminate PortAudio
PortAudioWrapper::~PortAudioWrapper() {
    Pa_Terminate();
}

// Audio Processing Callback
int PortAudioWrapper::audioCallback(const void *input, void *output,
                                    unsigned long frameCount, 
                                    const PaStreamCallbackTimeInfo* timeInfo,
                                    PaStreamCallbackFlags statusFlags, 
                                    void *userData) {
    auto *data = static_cast<AudioBuffer*>(userData);
    float *out = static_cast<float*>(output);

    for (unsigned long i = 0; i < frameCount; i++) {
        float sample = 0.0f;

        if (data->buffer.size() > data->currentIndex) {
            sample = data->buffer[data->currentIndex++];
        }

        *out++ = sample;  // Left channel
        *out++ = sample;  // Right channel (stereo)
    }

    return paContinue;
}

// Start Playback
bool PortAudioWrapper::startPlayback(std::vector<float> &audioData) {
    data.buffer = audioData;
    data.currentIndex = 0;

    PaStream *stream;
    PaError err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE,
                                       FRAMES_PER_BUFFER, audioCallback, &data);

    if (err != paNoError) {
        std::cerr << "❌ PortAudio Stream Error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    Pa_StartStream(stream);
    std::cout << "🎵 Playing audio..." << std::endl;

    while (Pa_IsStreamActive(stream) == 1) {
        Pa_Sleep(100);
    }

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    return true;
}
