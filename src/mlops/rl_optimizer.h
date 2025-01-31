#pragma once
#include <vector>

class RLOptimizer {
public:
    RLOptimizer();
    double optimizeDSP(std::vector<double> currentParams);

private:
    double rewardFunction(std::vector<double> params);
};
