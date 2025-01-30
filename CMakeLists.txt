cmake_minimum_required(VERSION 3.20)
project(Neuraltune-DSPear)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type (Release for optimized performance)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Enable verbose compilation output
set(CMAKE_VERBOSE_MAKEFILE ON)

# Define external dependencies directory
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

# Include directories for external dependencies
include_directories(${EXTERNAL_DIR}/imgui)
include_directories(${EXTERNAL_DIR}/imnodes)
include_directories(${EXTERNAL_DIR}/portaudio/include)
include_directories(${EXTERNAL_DIR}/torchserve)
include_directories(${EXTERNAL_DIR}/ray)
include_directories(${EXTERNAL_DIR}/prometheus)
include_directories(${EXTERNAL_DIR}/grafana)

# Link libraries for external dependencies
link_directories(${EXTERNAL_DIR}/portaudio/lib)
link_directories(${EXTERNAL_DIR}/torchserve)
link_directories(${EXTERNAL_DIR}/ray)

# Define source files
set(SOURCES
    src/main.cpp
    src/gui/dsp_graph.cpp
    src/gui/spectrum_visualizer.cpp
    src/gui/mlops_pipeline.cpp
    src/gui/parameter_controls.cpp
    src/mlops/ml_controller.cpp
    src/mlops/pytorch_inference.cpp
    src/mlops/ray_rl_train.py
    src/mlops/dsp_env.py
    src/mlops/torchserve_client.py
    src/mlops/mlflow_client.cpp
    src/mlops/kubernetes_client.cpp
    src/audio/real_time_synthesis.cpp
    src/audio/effects.cpp
    src/audio/mixer.cpp
    src/audio/fft_analysis.cpp
    src/audio/portaudio_wrapper.cpp
)

# Define executable
add_executable(Neuraltune-DSPear ${SOURCES})

# Find and link PortAudio
find_package(PortAudio REQUIRED)
target_link_libraries(Neuraltune-DSPear PRIVATE portaudio)

# Link against required system libraries
target_link_libraries(Neuraltune-DSPear PRIVATE pthread dl)

# Find and link external dependencies (TorchServe, Ray)
target_link_libraries(Neuraltune-DSPear PRIVATE ${EXTERNAL_DIR}/torchserve/libtorch.so)
target_link_libraries(Neuraltune-DSPear PRIVATE ${EXTERNAL_DIR}/ray/libray.so)

# Enable high optimization for DSP processing
target_compile_options(Neuraltune-DSPear PRIVATE -O3 -march=native)

# RL Training Target (Python)
add_custom_target(RL
    COMMAND python3 ${CMAKE_SOURCE_DIR}/rl/train_ray_rl.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/rl
    COMMENT "Running Reinforcement Learning training for DSP optimization..."
)

# Output final build message
message(STATUS "Neuraltune-DSPear successfully configured!")
