/**
 * @file MoodDetection.h
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Header file for mood detection.
 */
#ifndef MOOD_DETECTION_H
#define MOOD_DETECTION_H

#include "CppTimer.h"
// #include "Camera.h"

#include "../utils/Globals.h"

#include <opencv2/opencv.hpp>
#include <iostream>

class MoodDetection : public CppTimer {
    /** Timer function for Mood detection. */
    void timerEvent() {
        // Color values
        cv::Scalar color(255, 0, 255);

        // Take input from camera and return if no image could be found.
        masterCamera >> im;
        if(im.empty()) return;

        // Set color to grayscale for easier detection.
        cvtColor(im, gray, cv::COLOR_BGR2GRAY);

        // Try to detect faces for multiple people.
        faceCascade.detectMultiScale(gray, faces, 1.2, 5);

        // Set some neutral value for mood detection.
        int pred = 4;

        // Go through all faces and detect the emotion.
        for (auto& face : faces) {
            cv::rectangle(im, face, cv::Scalar(225, 0, 0), 2);

            this->roi = gray(face);

            resize(this->roi, this->roi, cv::Size(64, 128));
            
            std::vector<float> hog_features;
			
            hog.compute(roi, hog_features);
            float prediction = svm->predict(hog_features);
            
            pred = static_cast<int>(prediction);
            
            std::cout << emotion[pred] << std::endl;
            putText(im, emotion[pred], cv::Point(face.x, face.y - 5), cv::FONT_HERSHEY_SIMPLEX, 1, color, 2);
        }

        try {
            imshow("im", im);
        } catch (cv::Exception e) {
            std::cout << "Expect a segmentation fault to stop mood detection." << std::endl;
            raise(SIGHUP);
        }

        // wait for 10 milliseconds
        cv::waitKey(10);
        // char c = (char)cv::waitKey(10);
        // if (c == 'q') raise(SIGHUP);
    }

    public:
        /** Constructor */
        MoodDetection() {
            cv::Size win_size(64, 128);
            cv::Size block_size(16, 16);
            cv::Size block_stride(8, 8);
            cv::Size cell_size(8, 8);

            cv::HOGDescriptor hog(win_size, block_size, block_stride, cell_size, nbins);
        }

        /** Handling class functions */
        void stop() {
            masterCamera.release();
            cv::destroyAllWindows();

            stop();
        }

        void Initialize(cv::VideoCapture camera);

        /** Camera setup functions */
        void setCameraId(int id);

        void setContrasts(int low, int high);

        void setShutter(int shutter);

        int checkCameraOpen(cv::VideoCapture camera);

        /** Camera functions */
        cv::Mat takePicture();

        void savePicture(cv::VideoCapture*, std::string filename);

        /** Mood detection related functions */


    private:
        /** Variables for camera */
        int CameraID = 0;
        int nbins = 9;

        Globals globals;

	    cv::VideoCapture masterCamera;

        /** Variables */
        cv::CascadeClassifier faceCascade;
        cv::Mat im;
        cv::Mat gray;
        cv::Mat roi;

        cv::Scalar color;

        std::string cascadePath = "../src/resources/haarcascade_frontalface_default.xml";
        cv::Ptr<cv::ml::SVM> svm;

        cv::Size block_size;
        cv::Size block_stride;
        cv::Size cell_size;

        cv::HOGDescriptor hog;

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