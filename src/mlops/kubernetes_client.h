#pragma once
#include <string>

class KubernetesClient {
public:
    KubernetesClient();
    int getWorkerCount();
    void scaleRayWorkers(int minWorkers, int maxWorkers);

private:
    std::string executeCommand(const std::string& command);
};
