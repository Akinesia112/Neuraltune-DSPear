#pragma once
#include <vector>
#include <utility>

class Mixer {
public:
    explicit Mixer(size_t numTracks);

    void addTrack(size_t trackIndex, const std::vector<float>& audioData);
    void setVolume(size_t trackIndex, float volume);
    void setPan(size_t trackIndex, float pan);
    
    std::vector<std::pair<float, float>> mixTracks(size_t outputLength);

private:
    struct Track {
        std::vector<float> audioBuffer;
        float volume;
        float pan;
    };

    size_t numTracks;
    std::vector<Track> tracks;
};

