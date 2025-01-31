#include "mlops/ml_controller.h"
#include <iostream>

MLOpsController::MLOpsController() {
    mlClient = mlflow::MLflowClient("http://localhost:5000");
    k8sClient = KubernetesClient();
}

void MLOpsController::monitorDSP() {
    mlClient.log_metric("synth_frequency", 440.0);
    k8sClient.send_metric("DSP Load", 75.0);
}

void MLOpsController::optimizeDSP() {
    double bestFreq = mlClient.get_best_hyperparameter("synth_frequency");
    std::cout << "Optimized Synth Frequency: " << bestFreq << std::endl;
}
