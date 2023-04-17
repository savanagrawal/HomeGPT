/**
 * @file MoodDetection.cpp
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Functions for mood detection.
 *
 * https://opencv.org/
*/
#include "MoodDetection.h"

/**
 * Initializes our Mood Detection
 * 
 * @param camera Camera object.
 * 
 * @return
 */
void MoodDetection::Initialize(cv::VideoCapture camera) {
    MoodDetection::masterCamera = camera;
    faceCascade.load(cascadePath);

    std::cout << "Loading SVM Model file..." << std::endl;
    MoodDetection::globals.setMoodSvm();
    std::cout << "Loaded SVM Model file. Mood detection initialized..." << std::endl;

    MoodDetection::svm = MoodDetection::globals.getMoodSvm();
}

/**
 * Set the Mood Detection Camera ID object.
 * 
 * @param id Set a Camera ID.
 * 
 * @return Updated MoodDetection::CameraID
 */
void MoodDetection::setCameraId(int id) {
    MoodDetection::CameraID = id;
}

/**
 * Checks if camera is open. Mainly used for debugging.
 *
 * @param camera Camera object.
 *
 * @return Error Code
 */
int MoodDetection::checkCameraOpen(cv::VideoCapture camera){
    if(!camera.isOpened()){
        std::cerr<<"Failed to open camera at ID = "<<MoodDetection::CameraID<<std::endl;
        return -1;
    } else {
        std::cout<<"Camera opened successfully."<<std::endl;
    }
    return 0;
}