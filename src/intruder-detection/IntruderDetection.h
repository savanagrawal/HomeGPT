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

class IntruderDetection : public CppTimer {
    void timerEvent () {
        if (!masterCamera.isOpened()) {
            std::cerr << "Error opening camera." << std::endl;
            return;
        }

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
            std::cout << "Predicted label: " << predictedLabel << ", Confidence: " << confidence << std::endl;

            std::string label;
            if (confidence < 90) {
                if (predictedLabel == 1) {
                    label = "Savan";
                } else if (predictedLabel == 22) {
                    label = "Chinmay";
                }
            } else {
                label = "Intruder";
            }
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

    private:
        cv::VideoCapture masterCamera;

        cv::Mat im, gray;

        cv::CascadeClassifier detector;
        std::string cascadePath = "../src/resources/haarcascade_frontalface_default.xml";
        std::string trainedModelPath = "../src/resources/intruder-detection/trainer/trainer.yml";

        cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer = cv::face::LBPHFaceRecognizer::create();
};

#endif