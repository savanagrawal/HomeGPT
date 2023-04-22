// /**
//  * @file IntruderMoodDetection.cpp
//  * @author Savan Agrawal
//  * @version 0.1
//  * 
//  * Header file for Intruder and Mood Detection Combined.
//   *
//  * https://opencv.org/
// */

#ifndef INTRUDER_MOOD_DETECTION_H
#define INTRUDER_MOOD_DETECTION_H

#include "CppTimer.h"
#include "../utils/Globals.h"
#include "EventHandler.h"
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <deque>
#include <algorithm>


class IntruderMoodDetection : public CppTimer {
    void timerEvent () {
        if (!masterCamera.isOpened()) {
            std::cerr << "Error opening camera." << std::endl;
            return;
        }
    
        EventHandler& eventHandler = EventHandler::getInstance();

        users = readFileToMap(fileName);

        masterCamera >> im;
        if(im.empty()) return;

        cv::namedWindow("Face & Mood Recognition", cv::WINDOW_NORMAL);

        cvtColor(im, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> faces;
        
        detector.detectMultiScale(gray, faces, 1.2, 5);

        // Initialize queues
        //std::deque<std::string> intruderValue;
        //std::deque<int> predValue;

        for (auto& face : faces) {
            cv::rectangle(im, face, cv::Scalar(225, 0, 0), 2);
            int predictedLabel = -1;
            double confidence = 0.0;
            recognizer->predict(gray(face), predictedLabel, confidence);

            std::string label;
            auto it = users.find(predictedLabel);

            this->roi = gray(face);

            //resize(this->roi, this->roi, cv::Size(64, 128));
            
            //std::vector<float> hog_features;
			
            //hog.compute(roi, hog_features);
            float pred = -1;

            // Update intruderValue queue
            //if (intruderValue.size() == 10) {
            //    intruderValue.pop_front();
            //}

            // Update predValue queue
            //if (predValue.size() == 10) {
            //    predValue.pop_front();
            //}
            
                                                
            if (confidence < 90 && it != users.end()) {
                label = it->second;

                //hog.compute(roi, hog_features);
                //float prediction = svm->predict(hog_features);
                
                //pred = static_cast<int>(prediction);
                
                //intruderValue.push_back(label);
                //predValue.push_back(pred);
                eventHandler.emit<int>(Event::OpenMainDoor, 0);
                eventHandler.emit(Event::IntruderMoodThreadKill);
            } else {        
                label = "Intruder";
            }

            // Calculate the percentage of "Intruder" values in intruderValue queue
            //int intruderCount = std::count(intruderValue.begin(), intruderValue.end(), "Intruder");
            //double intruderPercentage = (static_cast<double>(intruderCount) / intruderValue.size()) * 100;

            //if (intruderPercentage <= 20) {
            //    std::cout << "User Welcome" << std::endl;
            //}

            // Find the most frequent integer in the predValue queue
            //std::map<int, int> predFrequency;
            //for (int p : predValue) {
            //    predFrequency[p]++;
            //}

            //int maxRepetitiveInteger = std::max_element(
            //    predFrequency.begin(), predFrequency.end(),
            //    [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            //       return a.second < b.second;
            //    }
            //)->first;

            //std::cout << "Max repetitive emotion: " << emotion[maxRepetitiveInteger] << std::endl;


            std::cout << "Predicted label: " << predictedLabel << ", Name: " << label << ", Confidence: " << confidence << std::endl;
            //std::cout << "Emotion: " << emotion[pred] << std::endl;
            putText(im, label, cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(225, 0, 0), 2);
        }
        // Clean up the memory
        //intruderValue.clear();
        //predValue.clear();
        
        try {
            imshow("Face & Mood Recognition", im);
        } catch (cv::Exception e) {
            std::cout << "Expect a segmentation fault to stop intruder detection." << std::endl;
            raise(SIGHUP);
        }
        
        // wait for 10 milliseconds
        cv::waitKey(10);
    }

    public:
        IntruderMoodDetection() {
            cv::Size win_size(64, 128);
            cv::Size block_size(16, 16);
            cv::Size block_stride(8, 8);
            cv::Size cell_size(8, 8);
            
            cv::HOGDescriptor hog(win_size, block_size, block_stride, cell_size, nbins);
            
        }

        void Initialize(cv::VideoCapture camera);

        void stop() {
            masterCamera.release();
            cv::destroyAllWindows();
            
            running = false;
            stop();
        }
        
        void start() {
            while(running) {
                if (!masterCamera.isOpened()) {
                    std::cerr << "Error opening camera." << std::endl;
                    break;
                }
            
                EventHandler& eventHandler = EventHandler::getInstance();

                users = readFileToMap(fileName);

                masterCamera >> im;
                if(im.empty()) break;

                cv::namedWindow("Face & Mood Recognition", cv::WINDOW_NORMAL);

                cvtColor(im, gray, cv::COLOR_BGR2GRAY);

                std::vector<cv::Rect> faces;
                
                detector.detectMultiScale(gray, faces, 1.2, 5);

                for (auto& face : faces) {
                    cv::rectangle(im, face, cv::Scalar(225, 0, 0), 2);
                    int predictedLabel = -1;
                    double confidence = 0.0;
                    recognizer->predict(gray(face), predictedLabel, confidence);

                    std::string label;
                    auto it = users.find(predictedLabel);

                    this->roi = gray(face);

                    resize(this->roi, this->roi, cv::Size(64, 128));
                    
                    std::vector<float> hog_features;
                    
                    hog.compute(roi, hog_features);
                    float pred = -1;
                                                        
                    if (confidence < 90 && it != users.end()) {
                        label = it->second;

                        hog.compute(roi, hog_features);
                        float prediction = svm->predict(hog_features);
                        
                        pred = static_cast<int>(prediction);
                        
                        //ledControllerPtr->setRGBColor(emotion.at(pred));
                        //sleep(3);
                        //ledControllerPtr->turnOffRGBLED();
                        running = false;

                        std::cout << "Predicted label: " << predictedLabel << ", Name: " << label << ", Confidence: " << confidence << std::endl;
                        std::cout << "Emotion: " << emotion[pred] << std::endl;
                        putText(im, label+", "+emotion[pred], cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(225, 0, 0), 2);
                
                        try {
                            imshow("Face & Mood Recognition", im);
                        } catch (cv::Exception e) {
                            std::cout << "Expect a segmentation fault to stop intruder detection." << std::endl;
                            raise(SIGHUP);
                        }
                
                        // wait for 10 milliseconds
                        cv::waitKey(10);
                        
                        eventHandler.emit<int>(Event::OpenMainDoor, pred);
                        //sleep(2);
                        //eventHandler.emit(Event::IntruderMoodThreadKill);
                        //return;
                    } else {
                        label = "Intruder";

                        std::cout << "Predicted label: " << predictedLabel << ", Name: " << label << ", Confidence: " << confidence << std::endl;
                        std::cout << "Emotion: " << emotion[pred] << std::endl;
                        putText(im, label+", "+emotion[pred], cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(225, 0, 0), 2);
                
                        try {
                            imshow("Face & Mood Recognition", im);
                        } catch (cv::Exception e) {
                            std::cout << "Expect a segmentation fault to stop intruder detection." << std::endl;
                            raise(SIGHUP);
                        }
                
                        // wait for 10 milliseconds
                        cv::waitKey(10);
                    }

                    //std::cout << "Predicted label: " << predictedLabel << ", Name: " << label << ", Confidence: " << confidence << std::endl;
                    //std::cout << "Emotion: " << emotion[pred] << std::endl;
                    //putText(im, label+", "+emotion[pred], cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(225, 0, 0), 2);
                }
            }
        }
        
        void unlock() {
            running = true;
            start();
        }
        
        std::map<int, std::string> readFileToMap(const std::string& fileName) {
            std::ifstream file(fileName);
            std::string line;
            std::map<int, std::string> users;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string name;
                std::getline(iss, name, ',');
                std::string numStr;
                std::getline(iss, numStr);
                int num = std::stoi(numStr);
                users[num] = name;
            }

            return users;
        }
        
        void restart() {
            masterCamera.open(CameraID);
        }
        
        /** Camera setup functions */
        void setCameraId(int id);

        void setContrasts(int low, int high);

        void setShutter(int shutter);

        int checkCameraOpen(cv::VideoCapture camera);

        /** Camera functions */
        cv::Mat takePicture();

        void savePicture(cv::VideoCapture*, std::string filename);

    private:
        /** Variables for camera */
        int CameraID = 0;
        int nbins = 9;

        Globals globals;
        cv::VideoCapture masterCamera;
        
        cv::Mat im, gray, roi;

        cv::CascadeClassifier detector;
        std::string cascadePath = "../src/resources/haarcascade_frontalface_default.xml";
        std::string trainedModelPath = "../src/resources/intruder-detection/trainer/trainer.yml";

        cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer = cv::face::LBPHFaceRecognizer::create();

        std::string fileName = "../src/resources/intruder-detection/Users.txt";
        std::map<int, std::string> users;

        cv::Ptr<cv::ml::SVM> svm;

        cv::Size block_size;
        cv::Size block_stride;
        cv::Size cell_size;

        cv::HOGDescriptor hog;
        
        bool running = true;
        
        bool locked = false;
        
        int emits = 0;
        
        // LEDController* ledControllerPtr;

        std::vector<cv::Rect> faces;
        std::map<int, std::string> emotion = {
            {0, "Angry"},
            {1, "Disgust"},
            {2, "Fear"},
            {3, "Happy"},
            {4, "Neutral"},
            {5, "Sad"},
            {6, "Surprise"}
        };
};

#endif
