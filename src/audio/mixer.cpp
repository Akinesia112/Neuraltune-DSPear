#include "audio/mixer.h"
#include <cmath>
#include <iostream>
#include <vector>

// Constructor: Initialize mixer with default volume and panning
Mixer::Mixer(size_t numTracks) : numTracks(numTracks) {
    tracks.resize(numTracks);
    for (auto& track : tracks) {
        track.volume = 1.0f;  // Default volume (100%)
        track.pan = 0.0f;      // Centered stereo balance
    }
}

// Add an audio track (WAV buffer)
void Mixer::addTrack(size_t trackIndex, const std::vector<float>& audioData) {
    if (trackIndex >= numTracks) {
        std::cerr << "❌ Error: Track index out of range." << std::endl;
        return;
    }
    tracks[trackIndex].audioBuffer = audioData;
}

// Set volume (0.0 = mute, 1.0 = full)
void Mixer::setVolume(size_t trackIndex, float volume) {
    if (trackIndex >= numTracks) return;
    tracks[trackIndex].volume = volume;
}

// Set stereo panning (-1.0 = left, 0.0 = center, 1.0 = right)
void Mixer::setPan(size_t trackIndex, float pan) {
    if (trackIndex >= numTracks) return;
    tracks[trackIndex].pan = pan;
}

// Mix all tracks into a single stereo buffer
std::vector<std::pair<float, float>> Mixer::mixTracks(size_t outputLength) {
    std::vector<std::pair<float, float>> mixedOutput(outputLength, {0.0f, 0.0f});

    for (const auto& track : tracks) {
        size_t trackSize = track.audioBuffer.size();
        if (trackSize == 0) continue;

        float leftGain = 1.0f - std::max(0.0f, track.pan);
        float rightGain = 1.0f - std::max(0.0f, -track.pan);

        for (size_t i = 0; i < outputLength && i < trackSize; ++i) {
            float sample = track.audioBuffer[i] * track.volume;
            mixedOutput[i].first += sample * leftGain;
            mixedOutput[i].second += sample * rightGain;
        }
    }
    return mixedOutput;
}
