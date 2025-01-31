#include "mlops/mlflow_client.h"
#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

MLflowClient::MLflowClient() {
    try {
        // ✅ Start Python interpreter
        py::initialize_interpreter();

        // ✅ Import MLflow and set tracking URI
        py::module_ mlflow = py::module_::import("mlflow");
        mlflow.attr("set_tracking_uri")("http://localhost:5000");

        std::cout << "📊 MLflow tracking initialized." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "⚠️ Error initializing MLflow: " << e.what() << std::endl;
    }
}

void MLflowClient::startRun(const std::string& runName) {
    try {
        py::module_ mlflow = py::module_::import("mlflow");
        mlflow.attr("start_run")();
        mlflow.attr("set_experiment")(runName);
        std::cout << "🚀 MLflow Run Started: " << runName << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "⚠️ Error starting MLflow run: " << e.what() << std::endl;
    }
}

void MLflowClient::logMetric(const std::string& name, double value) {
    try {
        py::module_ mlflow = py::module_::import("mlflow");
        mlflow.attr("log_metric")(name, value);
        std::cout << "✅ Logged Metric: " << name << " = " << value << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "⚠️ Error logging metric: " << e.what() << std::endl;
    }
}

void MLflowClient::logParam(const std::string& name, const std::string& value) {
    try {
        py::module_ mlflow = py::module_::import("mlflow");
        mlflow.attr("log_param")(name, value);
        std::cout << "✅ Logged Param: " << name << " = " << value << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "⚠️ Error logging param: " << e.what() << std::endl;
    }
}

void MLflowClient::endRun() {
    try {
        py::module_ mlflow = py::module_::import("mlflow");
        mlflow.attr("end_run")();
        std::cout << "🏁 MLflow Run Ended." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "⚠️ Error ending MLflow run: " << e.what() << std::endl;
    }
}

MLflowClient::~MLflowClient() {
    py::finalize_interpreter(); // ✅ Stop Python interpreter
    std::cout << "📊 MLflow tracking session closed." << std::endl;
}
