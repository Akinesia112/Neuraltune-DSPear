#include "mlops/mlflow.h"
#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

MLflowClient::MLflowClient() {
    try {
        py::initialize_interpreter(); // Start Python interpreter
        py::module_ mlflow = py::module_::import("mlflow");
        mlflow.attr("set_tracking_uri")("http://localhost:5000");
        std::cout << "📊 MLflow tracking initialized." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "⚠️ Error initializing MLflow: " << e.what() << std::endl;
    }
}

void MLflowClient::logMetric(const std::string& name, double value) {
    try {
        py::module_ mlflow = py::module_::import("mlflow");
        mlflow.attr("log_me
