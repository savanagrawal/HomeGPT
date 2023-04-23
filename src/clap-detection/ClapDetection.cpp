/**
 * @file ClapDetection.cpp
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Functions for Clap Detection.
 */

#include "ClapDetection.h"

/**
 * Initializes our Clap Detector.
 * 
 * @param
 * 
 * @return
 */
void ClapDetection::Initialize() {
    // Initialize PortAudio
    ClapDetection::y_find = ClapDetection::load_audio_file(ClapDetection::clapSamplePath);
    ClapDetection::err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        raise(SIGHUP);
        return;
    }

    ClapDetection::inputParameters.device = Pa_GetDefaultInputDevice();
    ClapDetection::inputParameters.channelCount = 1;
    ClapDetection::inputParameters.sampleFormat = paFloat32;
    ClapDetection::inputParameters.suggestedLatency = Pa_GetDeviceInfo(ClapDetection::inputParameters.device)->defaultLowInputLatency;
    ClapDetection::inputParameters.hostApiSpecificStreamInfo = nullptr;
}