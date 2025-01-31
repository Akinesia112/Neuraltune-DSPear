#include <vector>

class FFTAnalyzer {
public:
    FFTAnalyzer(size_t fftSize);
    std::vector<double> computeFFT(const std::vector<double>& input);

private:
    size_t fftSize;
};
