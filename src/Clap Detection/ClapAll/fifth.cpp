#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>
#include <limits>
#include <portaudio.h>
#include <fstream>

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


//Compute the circular convolution of two vectors using the DFT
std::vector<double> convolve(const std::vector<double>& a, const std::vector<double>& b) {
    int n = a.size();
    int m = b.size();
    int l = n + m - 1;
    int p = 1;
    while (p < l) {
        p <<= 1;
    }
    std::vector<std::complex<double>> pa(p), pb(p), pc(p);
    std::copy(a.begin(), a.end(), pa.begin());
    std::copy(b.begin(), b.end(), pb.begin());
    fft(pa, false);
    fft(pb, false);
    std::transform(pa.begin(), pa.end(), pb.begin(), pc.begin(),
               [](const std::complex<double>& a, const std::complex<double>& b) { return a * b; });
    fft(pc, true);
    std::vector<double> result(l);
    // Use std::transform to compute the real part of each complex number
    std::transform(pc.begin(), pc.begin() + l, result.begin(),
               [](const std::complex<double>& cplx) { return std::real(cplx) * std::real(cplx); });

    return result;
}

std::vector<double> load_audio_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file!");
    }
    
    // read the header
    char header[44];
    file.read(header, 44);
    
    // read data
    const int BUFFER_SIZE = 4096; // arbitrary buffer size
    std::vector<double> data;
    short buffer[BUFFER_SIZE];
    while (file.read(reinterpret_cast<char*>(&buffer[0]), BUFFER_SIZE * sizeof(short))) {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            data.push_back(static_cast<double>(buffer[i]) / std::numeric_limits<short>::max());
        }
    }
    
    return data;
}

std::vector<double> y_find = load_audio_file("sample.wav");
std::vector<std::complex<double>> y_find_fft(y_find.size());

void prepare_y_find_fft() {
    std::copy(y_find.begin(), y_find.end(), y_find_fft.begin());
    fft(y_find_fft, false);
}


double percentage_above_threshold(const std::vector<double>& a, double threshold) {
    const int count = std::count_if(a.begin(), a.end(), [threshold](double i) { return i > threshold; });
    return static_cast<double>(count) / static_cast<double>(a.size()) * 100.0;
}


// Callback function for PortAudio
int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
               const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    std::vector<double> *buffer = static_cast<std::vector<double>*>(userData);
    short *input = (short*)inputBuffer;

    for (unsigned long i = 0; i < framesPerBuffer; ++i) {
        buffer->push_back(static_cast<double>(input[i]) / std::numeric_limits<short>::max());
        if (buffer->size() >= 4096) {
            // Perform the convolution
            std::vector<std::complex<double>> buffer_fft(buffer->size());
            std::copy(buffer->begin(), buffer->end(), buffer_fft.begin());
            fft(buffer_fft, false);
            
            std::vector<std::complex<double>> conv_result(buffer_fft.size());
            std::transform(buffer_fft.begin(), buffer_fft.end(), y_find_fft.begin(), conv_result.begin(),
                           [](const std::complex<double>& a, const std::complex<double>& b) { return a * std::conj(b); });
            fft(conv_result, true);
            
            std::vector<double> c(conv_result.size());
            std::transform(conv_result.begin(), conv_result.end(), c.begin(),
                           [](const std::complex<double>& cplx) { return std::real(cplx); });

            // Detect the event
            double thres = *std::max_element(c.begin(), c.end()) / 10.0;
            double count = percentage_above_threshold(c, thres);

            if (count <= 0.5) {
                std::cout << "Match Found" << std::endl;
            } else {
                std::cout << "Match not found" << std::endl;
            }

            // Clear the buffer after processing
            buffer->clear();
        }
    }

    return paContinue;
}


void initializePortAudio(PaStream **stream, std::vector<double> *buffer) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Error: Failed to initialize PortAudio" << std::endl;
        exit(1);
    }

    err = Pa_OpenDefaultStream(stream, 1, 0, paInt16, 44100, 256, paCallback, buffer);
    if (err != paNoError) {
        std::cerr << "Error: Failed to open PortAudio stream" << std::endl;
        exit(1);
    }
}

void startPortAudioStream(PaStream *stream) {
    PaError err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Error: Failed to start PortAudio stream" << std::endl;
        exit(1);
    }
}

void stopPortAudioStream(PaStream *stream) {
    PaError err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "Error: Failed to stop PortAudio stream" << std::endl;
        exit(1);
    }
}

void terminatePortAudio() {
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "Error: Failed to terminate PortAudio" << std::endl;
        exit(1);
    }
}

int main() {
    prepare_y_find_fft();
    PaStream *stream;
    std::vector<double> buffer;
    initializePortAudio(&stream, &buffer);
    startPortAudioStream(stream);

    std::cout << "Listening for audio input..." << std::endl;
    Pa_Sleep(10000); // Listen for 10 seconds

    stopPortAudioStream(stream);
    terminatePortAudio();

    return 0;
}
