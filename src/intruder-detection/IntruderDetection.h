/**
 * @file IntruderDetection.h
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Header file for Intruder Detection.
 */
#ifndef INTRUDER_DETECTION_H
#define INTRUDER_DETECTION_H

#include "CppTimer.h"

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

class IntruderDetection : public CppTimer {
    void timerEvent () {
        if (!masterCamera.isOpened()) {
            std::cerr << "Error opening camera." << std::endl;
            return;
        }

        users = readFileToMap(fileName);

        masterCamera >> im;
        if(im.empty()) return;

        cv::namedWindow("Face Recognition", cv::WINDOW_NORMAL);

        cvtColor(im, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> faces;
        
        detector.detectMultiScale(gray, faces, 1.2, 5);

        for (size_t i = 0; i < faces.size(); i++) {
            cv::rectangle(im, faces[i], cv::Scalar(225, 0, 0), 2);
            int predictedLabel = -1;
            double confidence = 0.0;
            recognizer->predict(gray(faces[i]), predictedLabel, confidence);

            std::string label = "Intruder";
            auto it = users.find(predictedLabel);
            if (confidence < 55 && it != users.end()) {
            //if (confidence < 55 ) {
                label = it->second;
                //label = predictedLabel;
            } else {
                label = "Intruder";
            }

            std::cout << "Predicted label: " << predictedLabel << ", Name: " << label << ", Confidence: " << confidence << std::endl;
            putText(im, label, cv::Point(faces[i].x, faces[i].y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(225, 0, 0), 2);
        }
        
        try {
            imshow("Face Recognition", im);
        } catch (cv::Exception e) {
            std::cout << "Expect a segmentation fault to stop intruder detection." << std::endl;
            raise(SIGHUP);
        }
        
        // wait for 10 milliseconds
        cv::waitKey(10);
    }

    public:
        IntruderDetection() {}

        void Initialize(cv::VideoCapture camera);

        void stop() {
            masterCamera.release();
            cv::destroyAllWindows();

            stop();
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

    private:
        cv::VideoCapture masterCamera;

        cv::Mat im, gray;

        cv::CascadeClassifier detector;
        std::string cascadePath = "../src/resources/haarcascade_frontalface_default.xml";
        std::string trainedModelPath = "../src/resources/intruder-detection/trainer/trainer.yml";

        cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer = cv::face::LBPHFaceRecognizer::create();

        std::string fileName = "../src/resources/intruder-detection/Users.txt";
        std::map<int, std::string> users;
};

#endif
