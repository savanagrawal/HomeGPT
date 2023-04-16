#include <iostream>
#include <fstream>
#include <cstring>
#include "portaudio.h"

#define SAMPLE_RATE (8000)
#define FRAMES_PER_BUFFER (1024)
#define NUM_SECONDS (5)
#define NUM_CHANNELS (1)
#define PA_SAMPLE_TYPE paFloat32
#define FILE_NAME "audio.wav"

using namespace std;

struct UserData {
    float *recordedSamples;
    int numSamples;
    int frameIndex;
    ofstream *outputFile;
};

static int recordingCallback(const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo *timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData) {
    UserData *data = (UserData *) userData;
    const float *input = (const float *) inputBuffer;
    float *recordedSamples = data->recordedSamples;
    int numSamples = data->numSamples;
    int frameIndex = data->frameIndex;
    ofstream *outputFile = data->outputFile;

    if (framesPerBuffer > FRAMES_PER_BUFFER) {
        framesPerBuffer = FRAMES_PER_BUFFER;
    }

    for (int i = 0; i < framesPerBuffer; i++) {
        recordedSamples[frameIndex++] = input[i];
        if (frameIndex >= numSamples) {
            frameIndex = 0;
        }
    }

    data->frameIndex = frameIndex;

    outputFile->write((const char *) input, sizeof(float) * framesPerBuffer);

    return paContinue;
}

int main() {
    PaStream *stream;
    PaError err;
    const PaDeviceInfo *deviceInfo;
    const PaHostApiInfo *hostApiInfo;
    PaStreamParameters inputParameters;
    int numDevices;
    int defaultDeviceIndex;
    int numBytes;
    int numSamples;
    float *recordedSamples;
    ofstream outputFile(FILE_NAME, ios::binary);

    err = Pa_Initialize();
    if (err != paNoError) {
        cout << "Error: Pa_Initialize returned " << err << endl;
        return 1;
    }

    numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        cout << "Error: Pa_GetDeviceCount returned " << numDevices << endl;
        Pa_Terminate();
        return 1;
    }

    defaultDeviceIndex = Pa_GetDefaultInputDevice();
    deviceInfo = Pa_GetDeviceInfo(defaultDeviceIndex);
    hostApiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);

    cout << "Using device: " << deviceInfo->name << endl;
    cout << "Host API: " << hostApiInfo->name << endl;
    cout << "Max input channels: " << deviceInfo->maxInputChannels << endl;
    cout << "Default sample rate: " << deviceInfo->defaultSampleRate << endl;

    inputParameters.device = defaultDeviceIndex;
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = 0.1; // Increase the suggested latency
    inputParameters.hostApiSpecificStreamInfo = NULL;
    numSamples = NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS;
    numBytes = numSamples * sizeof(float);
    recordedSamples = new (nothrow) float[numSamples];
    if (recordedSamples == nullptr) {
        cout << "Error: Failed to allocate memory for recordedSamples." << endl;
        Pa_Terminate();
        return 1;
    }
    memset(recordedSamples, 0, numBytes);

    UserData data;
    data.recordedSamples = recordedSamples;
    data.numSamples = numSamples;
    data.frameIndex = 0;
    data.outputFile = &outputFile;

    err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER,
                        paClipOff, recordingCallback, &data);
    if (err != paNoError) {
        cout << "Error: Pa_OpenStream returned " << err << endl;
        Pa_Terminate();
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        cout << "Error: Pa_StartStream returned " << err << endl;
        Pa_Terminate();
        return 1;
    }

    cout << "Recording started..." << endl;

    Pa_Sleep(NUM_SECONDS * 1000);

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        cout << "Error: Pa_StopStream returned " << err << endl;
        Pa_Terminate();
        return 1;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        cout << "Error: Pa_CloseStream returned " << err << endl;
        Pa_Terminate();
        return 1;
    }

    for (int i = 0; i < numSamples; i++) {
        outputFile.write((const char *) &recordedSamples[i], sizeof(float));
    }

    outputFile.close();

    Pa_Terminate();

    delete[] recordedSamples;

    cout << "Recording stopped." << endl;

    return 0;
}
