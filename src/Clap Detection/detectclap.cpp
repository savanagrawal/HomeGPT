#include <iostream>
#include <cmath>
#include <portaudio.h>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 1024
#define THRESHOLD 0.50

using namespace std;

static int clapCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags, void *userData) {
    float *input = (float *)inputBuffer;
    float maxAmplitude = 0.0;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        float amplitude = abs(input[i]);
        if (amplitude > maxAmplitude) {
            maxAmplitude = amplitude;
        }
    }
    cout<<maxAmplitude<<endl;
    if (maxAmplitude > THRESHOLD) {
        cout << "Clap detected!" << endl;
    }

    return paContinue;
}

int main() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        return 1;
    }

    PaStreamParameters inputParameters;
    inputParameters.device = Pa_GetDefaultInputDevice();
    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    PaStream *stream;
    err = Pa_OpenStream(&stream, &inputParameters, nullptr, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, clapCallback, nullptr);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        Pa_Terminate();
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    cout << "Listening for claps, press Enter to quit." << endl;
    cin.ignore();

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
    }

    Pa_Terminate();
    return 0;
}
