#pragma once
#include <vector>
#include <complex>

class FFTAnalyzer {
public:
    FFTAnalyzer(size_t fftSize);
    std::vector<double> analyze(const std::vector<float>& audioBuffer);

private:
    size_t fftSize;
};
