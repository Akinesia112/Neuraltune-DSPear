#pragma once
#include <pybind11/embed.h>

namespace py = pybind11;

class MLflowClient {
public:
    MLflowClient();
    void logMetric(const std::string& name, double value);
    void logParam(const std::string& name, const std::string& value);
};

MLflowClient::MLflowClient() {
    py::initialize_interpreter();
    py::module_ mlflow = py::module_::import("mlflow");
    mlflow.attr("set_tracking_uri")("http://localhost:5000");
}

void MLflowClient::logMetric(const std::string& name, double value) {
    py::module_ mlflow = py::module_::import("mlflow");
    mlflow.attr("log_metric")(name, value);
}

void MLflowClient::logParam(const std::string& name, const std::string& value) {
    py::module_ mlflow = py::module_::import("mlflow");
    mlflow.attr("log_param")(name, value);
}
