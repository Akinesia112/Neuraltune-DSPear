#include <torch/script.h>  // PyTorch JIT API
#include <iostream>
#include <vector>

class PyTorchModel {
public:
    PyTorchModel(const std::string& modelPath) {
        try {
            module = torch::jit::load(modelPath);  // Load JIT model
            module.to(at::kCUDA);  // Move to GPU
            std::cout << "✅ PyTorch Model Loaded Successfully!" << std::endl;
        } catch (const c10::Error& e) {
            std::cerr << "⚠️ Error loading PyTorch model: " << e.what() << std::endl;
        }
    }

    std::vector<float> predict(const std::vector<float>& input) {
        at::Tensor tensorInput = torch::from_blob((void*)input.data(), {1, (int64_t)input.size()}, at::kFloat);
        tensorInput = tensorInput.to(at::kCUDA);

        at::Tensor output = module.forward({tensorInput}).toTensor();
        output = output.to(at::kCPU);

        return std::vector<float>(output.data_ptr<float>(), output.data_ptr<float>() + output.numel());
    }

private:
    torch::jit::script::Module module;
};
