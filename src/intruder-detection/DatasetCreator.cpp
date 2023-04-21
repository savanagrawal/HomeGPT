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
    

    std::cout << "Enter new user: ";
    while (true) {
        std::getline(std::cin, IntruderDatasetCreator::newUser);
        IntruderDatasetCreator::newUser = IntruderDatasetCreator::trim(newUser);

        if (IntruderDatasetCreator::is_valid_name(IntruderDatasetCreator::newUser)) {
            IntruderDatasetCreator::newUser = IntruderDatasetCreator::replace_spaces_with_underscores(IntruderDatasetCreator::newUser);
            if (!IntruderDatasetCreator::findStringInFile(IntruderDatasetCreator::fileName, IntruderDatasetCreator::newUser)) {
                int lastInteger = IntruderDatasetCreator::getLastIntegerInFile(IntruderDatasetCreator::fileName);
                std::string newLine = IntruderDatasetCreator::newUser + ", " + std::to_string(lastInteger + 1);
                IntruderDatasetCreator::appendLineToFile(IntruderDatasetCreator::fileName, newLine);
                std::cout << "Added new user: " << newLine << std::endl;
                break;
            } else {
                std::cout << "User " << IntruderDatasetCreator::newUser << " already exists in the file." << std::endl;
                continue;
            }
        } 
        else {
            std::cout << "Invalid name. Please enter a valid name: ";
        }
    }
}

int IntruderDatasetCreator::checkCameraOpen(cv::VideoCapture camera){
    if(!camera.isOpened()){
        std::cerr<<"Failed to open camera at ID = "<<IntruderDatasetCreator::CameraID<<std::endl;
        return -1;
    } else {
        std::cout<<"Camera opened successfully."<<std::endl;
    }
    return 0;
}
