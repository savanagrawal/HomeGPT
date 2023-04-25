/**
 * @file IntruderMoodDetection.cpp
 * @author Savan Agrawal
 * @version 0.1
 * 
 * Functions for Intruder and Mood Detection Combined.
  *
 * https://opencv.org/
*/

#include "IntruderMoodDetection.h"

#include <iostream>

/**
 * Initializes our Intruder & Mood Detection.
 * 
 * @param
 * 
 * @return
 */
void IntruderMoodDetection::Initialize(cv::VideoCapture camera) {
    IntruderMoodDetection::masterCamera = camera;
    std::cout << "Initializing detector..." << std::endl;
    recognizer->read(trainedModelPath);
    detector.load(cascadePath);

    std::cout << "Loading Trained Model files..." << std::endl;
    IntruderMoodDetection::globals.setMoodSvm();
    std::cout << "Face & Mood detection initialized..." << std::endl;

    IntruderMoodDetection::svm = IntruderMoodDetection::globals.getMoodSvm();

}

void IntruderMoodDetection::setCameraId(int id) {
    IntruderMoodDetection::CameraID = id;
}

int IntruderMoodDetection::checkCameraOpen(cv::VideoCapture camera){
    if(!camera.isOpened()){
        std::cerr<<"Failed to open camera at ID = "<<IntruderMoodDetection::CameraID<<std::endl;
        return -1;
    } else {
        std::cout<<"Camera opened successfully."<<std::endl;
    }
    return 0;
}
