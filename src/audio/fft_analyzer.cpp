#include "audio/fft_analyzer.h"
#include <fftw3.h>
#include <cmath>

FFTAnalyzer::FFTAnalyzer(size_t fftSize) : fftSize(fftSize) {}

std::vector<double> FFTAnalyzer::analyze(const std::vector<float>& audioBuffer) {
    std::vector<double> output(fftSize / 2);
    std::vector<double> input(fftSize);
    fftw_complex* result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fftSize);
    fftw_plan plan = fftw_plan_dft_r2c_1d(fftSize, input.data(), result, FFTW_ESTIMATE);

    for (size_t i = 0; i < fftSize && i < audioBuffer.size(); ++i) {
        input[i] = audioBuffer[i];
    }

    fftw_execute(plan);
    
    for (size_t i = 0; i < fftSize / 2; ++i) {
        output[i] = std::sqrt(result[i][0] * result[i][0] + result[i][1] * result[i][1]);
    }

    fftw_destroy_plan(plan);
    fftw_free(result);
    return output;
}
