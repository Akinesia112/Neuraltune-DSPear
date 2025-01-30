import ray
from ray import tune
from ray.rllib.agents.ppo import PPOTrainer
from dsp_env import DSPEnv

# Initialize Ray (Automatically detects Kubernetes setup if available)
ray.init(address="auto", ignore_reinit_error=True)

# RL Training Configuration
config = {
    "env": DSPEnv,  # Custom Gym environment for DSP optimization
    "num_workers": 3,  # Number of distributed workers (scales automatically)
    "num_gpus": 1,  # Use 1 GPU for training
    "num_gpus_per_worker": 0.25,  # Each worker gets 1/4 of a GPU (useful with MIG)
    "train_batch_size": 8000,  # Larger batch size improves stability
    "sgd_minibatch_size": 1024,  # Size of each training mini-batch
    "framework": "torch",  # Use PyTorch backend
    "use_pytorch_native_fp16": True,  # Enable mixed-precision training (reduces memory usage)
}

# Start RL training using PPO (Proximal Policy Optimization)
tune.run(
    PPOTrainer,
    config=config,
    stop={"training_iteration": 200},  # Stop after 200 training iterations
    checkpoint_at_end=True,  # Save model checkpoint at the end
)
