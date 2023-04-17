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
 * @param
 * 
 * @return
 */
void MoodDetection::Initialize(cv::VideoCapture camera) {
    MoodDetection::masterCamera = camera;
    faceCascade.load(cascadePath);
}

/**
 * Set the Mood Detection Camera ID object.
 * 
 * @param id 
 * 
 * @return Updated MoodDetection::CameraID
 */
void MoodDetection::setCameraId(int id) {
    MoodDetection::CameraID = id;
}

/**
 * Checks if camera is open. Mainly used for debugging.
 *
 * @param camera 
 *
 * @return
 */
int MoodDetection::checkCameraOpen(cv::VideoCapture camera){
    if(!camera.isOpened()){
        std::cerr<<"Failed to open camera at ID = "<<MoodDetection::CameraID<<std::endl;
        return -1; //Should I change this to a specific error code within the camera class?
    }
    else{
        std::cout<<"Camera opened successfully."<<std::endl;
        //do nothing; camera has opened.
    }
    return 0;
}