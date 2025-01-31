#pragma once
#include <string>

class MLflowClient {
public:
    MLflowClient();
    void startRun(const std::string& runName);
    void logMetric(const std::string& name, double value);
    void logParam(const std::string& name, const std::string& value);
    void endRun();
    ~MLflowClient();
};
