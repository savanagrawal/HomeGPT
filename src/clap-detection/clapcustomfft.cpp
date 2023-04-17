#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>
#include <portaudio.h>


#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 1024
#define HIGH_FREQ_THRESHOLD 1000.0

using namespace std;

// Helper function to reverse bits of a number
int reverse_bits(int num, int bit_length) {
    int result = 0;
    for (int i = 0; i < bit_length; i++) {
        result = (result << 1) | (num & 1);
        num >>= 1;
    }
    return result;
}

// Compute the iterative in-place FFT of a vector
void fft(std::vector<std::complex<double>>& a, bool inverse) {
    int n = a.size();
    int log_n = std::log2(n);

    // Bit-reverse permutation
    for (int i = 0; i < n; i++) {
        int j = reverse_bits(i, log_n);
        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }

    // Iterative FFT
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * M_PI / len * (inverse ? -1 : 1);
        std::complex<double> wn(std::cos(angle), std::sin(angle));
        for (int i = 0; i < n; i += len) {
            std::complex<double> w(1);
            for (int j = 0; j < len / 2; j++) {
                std::complex<double> u = a[i + j];
                std::complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wn;
            }
        }
    }

    // If inverse FFT, divide by n
    if (inverse) {
        for (auto& x : a) {
            x /= n;
        }
    }
}


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

    vector<complex<double>> input_complex(framesPerBuffer);
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        input_complex[i] = complex<double>(input[i], 0);
    }

    fft(input_complex, false);

    double highFrequencyEnergy = 0.0;
    double totalEnergy = 0.0;
    for (unsigned long i = framesPerBuffer * 500 / SAMPLE_RATE; i < framesPerBuffer / 2 + 1; i++) {
   // for (unsigned long i = 0; i < framesPerBuffer / 2 + 1; i++) {
        double magnitude = abs(input_complex[i]);
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
