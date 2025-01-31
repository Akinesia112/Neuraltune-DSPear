import requests
import numpy as np

class TorchServeClient:
    def __init__(self, server_url="http://torchserve:8080"):
        self.server_url = server_url

    def predict(self, audio_features):
        data = {"data": audio_features.tolist()}
        response = requests.post(f"{self.server_url}/predictions/dsp_model", json=data)
        return np.array(response.json())

if __name__ == "__main__":
    client = TorchServeClient()
    test_input = np.random.rand(10).tolist()
    result = client.predict(test_input)
    print("Prediction:", result)
