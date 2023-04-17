#include <iostream>
#include <cmath>
#include <fftw3.h>
#include <portaudio.h>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 2048*5
#define HIGH_FREQ_THRESHOLD 20000.0

using namespace std;

// Apply a Hanning window function to the input buffer
void applyHanningWindow(float *buffer, unsigned long bufferLength) {
    for (unsigned long i = 0; i < bufferLength; i++) {
        buffer[i] *= 0.5 * (1.0 - cos(2.0 * M_PI * i / (bufferLength - 1)));
    }
}
static int clapCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags, void *userData) {
    float *input = (float *)inputBuffer;
    applyHanningWindow(input, framesPerBuffer);

    double *input_double = new double[framesPerBuffer];
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        input_double[i] = static_cast<double>(input[i]);
    }

    fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * framesPerBuffer);
    fftw_plan p = fftw_plan_dft_r2c_1d(framesPerBuffer, input_double, out, FFTW_ESTIMATE);
    fftw_execute(p);

    double highFrequencyEnergy = 0.0;
    double totalEnergy = 0.0;
    for (unsigned long i = framesPerBuffer * 1000 / SAMPLE_RATE; i < framesPerBuffer / 2 + 1; i++) {
    //for (unsigned long i = 0; i < framesPerBuffer / 2 + 1; i++) {
        double magnitude = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        double frequency = (double)i * SAMPLE_RATE / framesPerBuffer;

        totalEnergy += magnitude;
        if (frequency >= HIGH_FREQ_THRESHOLD) {
            highFrequencyEnergy += magnitude;
        }
    }

    double highFrequencyRatio = highFrequencyEnergy / totalEnergy;

    if (highFrequencyRatio > 0.1) {
        cout << "Clap detected!" << endl;
    }

    delete[] input_double;
    fftw_destroy_plan(p);
    fftw_free(out);

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
