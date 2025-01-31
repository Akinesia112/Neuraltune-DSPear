#include "mlops/kubernetes_client.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <json/json.h> // Using JSONCPP to parse Kubernetes API responses

KubernetesClient::KubernetesClient() {
    std::cout << "🌐 Kubernetes Client Initialized." << std::endl;
}

std::string KubernetesClient::executeCommand(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("Failed to execute command: " + command);
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}

int KubernetesClient::getWorkerCount() {
    std::string command = "kubectl get deployment ray-worker -o json";
    std::string output = executeCommand(command);

    Json::Value jsonData;
    Json::CharReaderBuilder reader;
    std::string errors;
    std::istringstream stream(output);
    
    if (!Json::parseFromStream(reader, stream, &jsonData, &errors)) {
        std::cerr << "❌ Error parsing Kubernetes response: " << errors << std::endl;
        return -1;
    }

    return jsonData["status"]["replicas"].asInt();
}

void KubernetesClient::scaleRayWorkers(int minWorkers, int maxWorkers) {
    int currentWorkers = getWorkerCount();
    if (currentWorkers < 0) {
        std::cerr << "⚠️ Unable to determine current worker count." << std::endl;
        return;
    }

    if (currentWorkers < minWorkers) {
        std::cout << "📈 Scaling UP Ray workers to: " << minWorkers << std::endl;
        executeCommand("kubectl scale deployment ray-worker --replicas=" + std::to_string(minWorkers));
    } else if (currentWorkers > maxWorkers) {
        std::cout << "📉 Scaling DOWN Ray workers to: " << maxWorkers << std::endl;
        executeCommand("kubectl scale deployment ray-worker --replicas=" + std::to_string(maxWorkers));
    } else {
        std::cout << "✅ Ray worker count is optimal (" << currentWorkers << " workers)." << std::endl;
    }
}
