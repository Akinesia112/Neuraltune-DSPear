import gym
from gym import spaces
import numpy as np

class DSPEnv(gym.Env):
    """
    Custom Gym environment for DSP optimization.
    The agent will try to optimize DSP parameters to achieve the best sound quality.
    """

    def __init__(self):
        super(DSPEnv, self).__init__()

        # DSP parameters to optimize:
        # - Synth frequency: [20 Hz, 20 kHz]
        # - EQ gain: [-12 dB, +12 dB]
        self.action_space = spaces.Box(
            low=np.array([20, -12]), high=np.array([20000, 12]), dtype=np.float32
        )

        # Observations (Dummy for now, can be extended with real-time audio data)
        self.observation_space = spaces.Box(
            low=-1, high=1, shape=(1,), dtype=np.float32
        )

        # Initial DSP parameters
        self.state = np.array([440.0, 0.0])  # Default: A4 note, 0 dB EQ gain

    def step(self, action):
        """
        Execute one step in the environment.
        The RL model suggests DSP parameters, and we evaluate the sound quality.
        """
        freq, eq_gain = action
        reward = -abs(freq - 440) - abs(eq_gain)  # Closer to 440Hz & 0dB → higher reward

        # Update state (Can be extended with real DSP feedback)
        self.state = np.array([freq, eq_gain])

        # RL environment always returns:
        # - Next state
        # - Reward
        # - Done flag (False since we run continuously)
        # - Extra info (empty dictionary for now)
        return self.state, reward, False, {}

    def reset(self):
        """
        Reset the environment to the default state.
        """
        self.state = np.array([440.0, 0.0])
        return self.state
