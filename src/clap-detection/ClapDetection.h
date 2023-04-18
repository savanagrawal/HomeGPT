/**
 * @file ClapDetection.h
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Header file for clap detection.
 */
#ifndef CLAP_DETECTION_H
#define CLAP_DETECTION_H

#include "CppTimer.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <complex>
#include <limits>
#include <stdexcept>
#include <portaudio.h>
#include <cstring>
#include <stdio.h>

class ClapDetection {
    public:
        ClapDetection() {

        }

        void Initialize();

        void start() {
            running = 1;
            
            while(running) { 
                std::vector<float> audioData;
            
                err = Pa_OpenStream(&stream,
                                    &inputParameters,
                                    nullptr, // No output
                                    44100,   // Sample rate
                                    256,     // Frames per buffer
                                    paClipOff,
                                    paCallback,
                                    &audioData);
                
                if (err != paNoError) {
                    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
                    raise(SIGHUP);
                    return;
                }

                err = Pa_StartStream(stream);
                if (err != paNoError) {
                    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
                    Pa_CloseStream(stream);
                    Pa_Terminate();
                    raise(SIGHUP);
                    return;
                }

                // Record for 1 seconds
                std::cout << "Recording audio for 1.0 seconds..." << std::endl;
                Pa_Sleep(1000);


                // Run clap detection
                std::cout << "Running clap detection on recorded audio..." << std::endl;

                std::vector<double> audioDataDouble(audioData.begin(), audioData.end());
                double per = find_per_data(audioDataDouble, y_find);

                // double per = find_per("recorded_audio.wav", "sample4.wav");
                result(per, 0.5);
                

                // Stop audio stream
                err = Pa_AbortStream(stream);
                if (err != paNoError) {
                    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
                    raise(SIGHUP);
                    return;
                }

                // Close audio stream
                err = Pa_CloseStream(stream);
                if (err != paNoError) {
                    std::cerr << "Portudio error: " << Pa_GetErrorText(err) << std::endl;
                    raise(SIGHUP);
                    return;
                }
            }
        }

        void stop() {
            // Terminate PortAudio
            running = 0;
            Pa_Terminate();
        }

        // Helper function to reverse bits of a number
        static int reverse_bits(int num, int bit_length) {
            int result = 0;
            for (int i = 0; i < bit_length; i++) {
                result = (result << 1) | (num & 1);
                num >>= 1;
            }
            return result;
        }

        // Compute the iterative in-place FFT of a vector
        static void fft(std::vector<std::complex<double>>& a, bool inverse) {
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
        static std::vector<double> convolve(const std::vector<double>& a, const std::vector<double>& b) {
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

        // Load the audio file for sampling.
        static std::vector<double> load_audio_file(const std::string& filename) {
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

        // 
        static double percentage_above_threshold(const std::vector<double>& a, double threshold) {
            const int count = std::count_if(a.begin(), a.end(), [threshold](double i) { return i > threshold; });
            return static_cast<double>(count) / static_cast<double>(a.size()) * 100.0;
        }

        // 
        static double find_per(const std::string& within_file, const std::string& find_file) {
            std::vector<double> y_within = load_audio_file(within_file);
            std::vector<double> y_find = load_audio_file(find_file);

            std::vector<double> c = convolve(y_within, y_find);
            
            double thres = *std::max_element(c.begin(), c.end()) / 8.0;
            double count = percentage_above_threshold(c, thres);


            return count;
        }

        // 
        static double find_per_data(const std::vector<double>& within_data, const std::vector<double>& y_find) {
            std::vector<double> c = convolve(within_data, y_find);
            
            double thres = *std::max_element(c.begin(), c.end()) / 8.0;
            double count = percentage_above_threshold(c, thres);


            return count;
        }

        // 
        static void result(double per, double check){
            if (per <= check) {
                std::cout << "Clap Detected" << std::endl;
            } else {
                std::cout << "Clap not Detected" << std::endl;
            }
        }

        static int paCallback(const void *inputBuffer, void *outputBuffer,
               unsigned long framesPerBuffer,
               const PaStreamCallbackTimeInfo *timeInfo,
               PaStreamCallbackFlags statusFlags,
               void *userData) {
            std::vector<float> *audioData = reinterpret_cast<std::vector<float> *>(userData);
            const float *readPtr = (const float *)inputBuffer;
            audioData->insert(audioData->end(), readPtr, readPtr + framesPerBuffer);
            return paContinue;
        }

    private:
        std::vector<double> y_find;
        std::string clapSamplePath = "../src/resources/clap-detection/sample.wav";
        
        PaError err;
        PaStream *stream;
        PaStreamParameters inputParameters;

        int running = 0;
};

#endif