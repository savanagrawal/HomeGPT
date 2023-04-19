/**
 * @file DatasetCreator.h
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Header file for Intruder Detection - Dataset Creator.
 */
#ifndef DATASET_CREATOR_H
#define DATASET_CREATOR_H

#include "CppTimer.h"
#include "EventHandler.h"

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

class IntruderDatasetCreator : public CppTimer {
    /** Timer function for intruder detector's dataset creation functionality. */
    void timerEvent() {
        // std::cout<<"Hi"<<std::endl;

        EventHandler& eventHandler = EventHandler::getInstance();

        // break if the sample number is more than 200
        if (samples > 20){
            std::cout << "Exiting dataset creator..." << std::endl;
            eventHandler.emit(Event::DatasetCreatorComplete);
            return;
        }

        if(newUser.empty()) {
            std::cerr << "Error: No User ID found. Try to initialize the dataset creator first then start the loop." << std::endl;
            raise(SIGHUP);
            return;
        }
        
        cv::Mat img;

        masterCamera >> img;
        if(img.empty()) return;

        cvtColor(img, gray, cv::COLOR_BGR2GRAY);

        detector.detectMultiScale(gray, faces, 1.2, 5);

        for (cv::Rect face : faces) {
            cv::rectangle(img, face, cv::Scalar(255, 0, 0), 2);

            // incrementing sample number
            samples++;

            // saving the captured face in the dataset folder
            std::string filename = "../src/resources/intruder-detection/dataset/User." + newUser + "." + std::to_string(samples) + ".jpg";
            imwrite(filename, gray(face));

            imshow("frame", img);

            std::cout << "Sample #" << std::to_string(samples) << std::endl;

            // wait for 10 milliseconds
            cv::waitKey(10);
        }
    }

    public:
        /** Constructor */
        IntruderDatasetCreator() {

        }

        void Initialize(cv::VideoCapture camera);

        void stop() {
            masterCamera.release();
            cv::destroyAllWindows();

            stop();
        }

        std::string trim(const std::string &str) {
            std::size_t start = str.find_first_not_of(' ');
            std::size_t end = str.find_last_not_of(' ');
        
            if (start == std::string::npos || end == std::string::npos) {
                return "";
            }
        
            return str.substr(start, end - start + 1);
        }

        int count_name(const std::string &str) {
            int count = 0;
            for (const char &c : str) {
                count += 1;
            }
            std::cout << count << std::endl;
            return count;
        }

        std::string replace_spaces_with_underscores(const std::string &str) {
            std::string result = str;
            for (char &c : result) {
                if (c == ' ') {
                    c = '_';
                }
            }
            return result;
        }

        bool is_valid_name(const std::string &name) {
            if (name.empty()) {
                return false;
            }
        
            bool has_alpha = false;
            for (char c : name) {
                if (!std::isalpha(c) && !std::isspace(c)) {
                    return false;
                }
                if (std::isalpha(c)) {
                    has_alpha = true;
                }
            }
        
            return has_alpha;
        }

        bool findStringInFile(const std::string& fileName, const std::string& searchString) {
            std::ifstream file(fileName);
            std::string line;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string name;
                std::getline(iss, name, ',');
                if (name == searchString) {
                    return true;
                }
            }

            return false;
        }

        int getLastIntegerInFile(const std::string& fileName) {
            std::ifstream file(fileName);
            std::string line;
            int lastInteger = 0;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string name;
                std::string numStr;
                std::getline(iss, name, ',');
                std::getline(iss, numStr);
                int num = std::stoi(numStr);
                lastInteger = num;
            }

            return lastInteger;
        }

        void appendLineToFile(const std::string& fileName, const std::string& line) {
            std::ofstream file(fileName, std::ios_base::app);
            file << line << std::endl;
        }
        
        int checkCameraOpen(cv::VideoCapture camera);

    private:
        cv::VideoCapture masterCamera;

        cv::CascadeClassifier detector;
        std::string cascadePath = "../src/resources/haarcascade_frontalface_default.xml";
        // EventHandler& eventHandler = EventHandler::getInstance();


        // Events& eventHandler = Events::getInstance();
        // using EVENT_CODES = Events::EVENT_CODES;

        std::string fileName = "../src/resources/intruder-detection/Users.txt";
        std::string newUser;

        int samples = 0;
        int CameraID = 0;

        cv::Mat gray;

        std::vector<cv::Rect> faces;
};

#endif
