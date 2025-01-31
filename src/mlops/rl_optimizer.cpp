#include "mlops/rl_optimizer.h"
#include <iostream>
#include <cmath>

RLOptimizer::RLOptimizer() {}

double RLOptimizer::rewardFunction(std::vector<double> params) {
    return -std::pow(params[0] - 440.0, 2) - std::pow(params[1] - 1000.0, 2);
}

double RLOptimizer::optimizeDSP(std::vector<double> currentParams) {
    double bestParam = currentParams[0];
    double maxReward = rewardFunction(currentParams);
    for (double p = 400; p <= 480; p += 10) {
        currentParams[0] = p;
        double reward = rewardFunction(currentParams);
        if (reward > maxReward) {
            bestParam = p;
            maxReward = reward;
        }
    }
    return bestParam;
}
