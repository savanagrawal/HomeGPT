/**
 * @file IntruderDetection.cpp
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Functions for Intruder Detection.
 */

#include "IntruderDetection.h"

#include <iostream>

/**
 * Initializes our Intruder Detection.
 * 
 * @param
 * 
 * @return
 */
void IntruderDetection::Initialize(cv::VideoCapture camera) {
    IntruderDetection::masterCamera = camera;

    std::cout << "Initializing detector..." << std::endl;
    recognizer->read(trainedModelPath);
    detector.load(cascadePath);
    std::cout << "Detector ready..." << std::endl;
}