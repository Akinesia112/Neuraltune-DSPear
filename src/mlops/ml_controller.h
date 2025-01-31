#pragma once
#include <string>
#include <mlflow.h>
#include <tensorflow/c/c_api.h>
#include <kubernetes_client.h>

class MLOpsController {
public:
    MLOpsController();
    void monitorDSP();
    void optimizeDSP();
    std::vector<double> denoiseAudio(const std::vector<double>& input);
    std::vector<double> styleTransferAudio(const std::vector<double>& input);

private:
    mlflow::MLflowClient mlClient;
    KubernetesClient k8sClient;
};
