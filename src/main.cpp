#include <iostream>
#include <thread>

#include "audio/real_time_synthesis.h"
#include "audio/eq.h"
#include "audio/effects.h"
#include "audio/mixer.h"
#include "audio/fft_analysis.h"
#include "audio/fft_analyzer.h"
#include "audio/oscillator.h"
#include "audio/portaudio_wrapper.h"

#include "midi/midi_controller.h"
#include "midi/midi_recorder.h"

#include "gui/daw_gui.h"

#include "mlops/rl_optimizer.h"
#include "mlops/torchserve_client.h"
#include "mlops/kubernetes_client.h"
#include "mlops/ml_controller.h"
#include "mlops/mlflow.h"
#include "mlops/pytorch_inference.h"
#include "mlops/mlflow_client.h"
#include "mlops/kubernetes_client.h"

Equalizer eq;
MidiRecorder midiRecorder;

void midiNoteHandler(int status, int note, int velocity) {
    if (status == 144) {
        double frequency = 440.0 * pow(2.0, (note - 69) / 12.0);
        std::cout << "🎹 MIDI Note: " << note << " (Freq: " << frequency << " Hz)" << std::endl;
        midiRecorder.recordEvent(status, note, velocity);
    }
}

void midiNoteHandler(int status, int note, int velocity) {
    if (status == 144) {  // Note On
        double frequency = 440.0 * pow(2.0, (note - 69) / 12.0);
        std::cout << "🎹 Note On: " << note << " (Freq: " << frequency << " Hz)" << std::endl;
    }
}

void runDSPPipeline() {
    std::cout << "🚀 Initializing DSP Engine...\n";
    RealTimeSynth synth;
    EffectsProcessor effects;
    Mixer mixer;
    FFTAnalyzer fft;

    // Set initial DSP parameters
    synth.setSynthFrequency(440.0);
    effects.setReverb(0.2);
    effects.setEQGain(0, 0.0);  // Default EQ gain

    float buffer[1024];
    while (true) {
        synth.processAudio(buffer, 1024);
        effects.applyEffects(buffer, 1024);
        mixer.mix(buffer, 1024);
        fft.analyze(buffer, 1024);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void runAIOptimization() {
    std::cout << "🤖 Running AI DSP Optimization...\n";
    TorchServeClient aiModel("http://torchserve:8080");
    std::vector<double> inputParams = {440.0, 0.0};  // Example input (frequency & gain)
    std::vector<double> optimizedParams = aiModel.predict(inputParams);

    std::cout << "🎯 AI Optimized DSP Parameters:\n";
    std::cout << "   Frequency: " << optimizedParams[0] << " Hz\n";
    std::cout << "   EQ Gain: " << optimizedParams[1] << " dB\n";
}

void runKubernetesScaling() {
    std::cout << "⚡ Checking Kubernetes AutoScaler...\n";
    KubernetesClient k8s;
    k8s.scaleRayWorkers(2, 6);  // Ensure at least 2 workers, max 6
}

int main() {
    std::cout << "🎵 Starting Neuraltune DSPear Engine...\n";

    PortAudioWrapper audioPlayer;
    Oscillator osc(Waveform::Sine, 440.0, 0.5);
    FFTAnalyzer fftAnalyzer(1024);
    MidiController midi(midiNoteHandler);
    DAW_GUI gui(eq, midiRecorder);

    // 🎵 Generate a simple sine wave (440Hz, 2 sec)
    std::vector<float> sineWave;
    std::vector<float> audioData;
    float frequency = 440.0f;
    for (int i = 0; i < 44100 * 2; i++) {
        // sineWave.push_back(0.5f * sinf(2.0f * M_PI * frequency * i / 44100));
        sineWave.push_back(osc.process());

        float sample = osc.process();
        audioData.push_back(eq.process(sample));
    }

    std::thread midiThread(&MidiController::start, &midi);
    audioPlayer.startPlayback(sineWave);
    audioPlayer.startPlayback(audioData);


    // fft analyzing
    std::vector<double> spectrum = fftAnalyzer.analyze(sineWave);
    for (double val : spectrum) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    midiThread.join();

    // Launch DSP Processing
    std::thread dspThread(runDSPPipeline);

    // Launch AI Optimization
    std::thread aiThread(runAIOptimization);

    // Monitor Kubernetes Scaling
    KubernetesClient k8s;
    k8s.scaleRayWorkers(2, 6); // Ensure at least 2 workers, max 6
    std::thread k8sThread(runKubernetesScaling);

    // Join all threads
    dspThread.join();
    aiThread.join();
    k8sThread.join();

    MLflowClient mlflow;
    mlflow.startRun("DSP Optimization");
    mlflow.logParam("DSP Model", "Neuraltune Optimized");
    mlflow.logMetric("AI Accuracy", 0.987);
    mlflow.endRun();

    return 0;
}
