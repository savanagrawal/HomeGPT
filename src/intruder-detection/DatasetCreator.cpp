/**
 * @file DatasetCreator.cpp
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Functions for Intruder Detection - Dataset Creator.
 */

#include "DatasetCreator.h"

/**
 * Initializes our Dataset Creator.
 * 
 * @param camera Camera object.
 * 
 * @return
 */
void IntruderDatasetCreator::Initialize(cv::VideoCapture camera) {
    IntruderDatasetCreator::masterCamera = camera;
    detector.load(cascadePath);
    
    std::string name;

    std::cout << "Enter your name: ";
    while (true) {
        std::getline(std::cin, name);
        name = IntruderDatasetCreator::trim(name);
 
        if (IntruderDatasetCreator::is_valid_name(name) && (IntruderDatasetCreator::count_name(name) <= 8)) {
            break;
        } 
        else {
            std::cout << "Invalid name. Please enter a valid name: ";
        }
    }
    name = IntruderDatasetCreator::replace_spaces_with_underscores(name);
    std::cout << "Valid name entered: " << name << std::endl;

    IntruderDatasetCreator::Id = name;
}

// void IntruderDatasetCreator::setParentCallback(CppTimerCallback callback) {
//     IntruderDatasetCreator::parentCallback = callback;
// }