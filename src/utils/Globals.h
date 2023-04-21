/**
 * @file Globals.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Anything global that will be set only once.
 */
#ifndef GLOBALS_H
#define GLOBALS_H

#include <opencv2/opencv.hpp>


class Globals {
    public:
        void setMoodSvm() {
            mood_svm = cv::ml::SVM::load("../src/resources/svmhog.xml");
        }

        cv::Ptr<cv::ml::SVM> getMoodSvm() {
            return mood_svm;
        }
        
        int getGarageDoorPin() {
            return garageDoorPin;
        }
        
        int getMainDoorPin() {
            return mainDoorPin;
        }
        
        int getLedPin() {
            return ledPin;
        }
        
        int getLedRedPin() {
            return ledRedPin;
        }
        
        int getLedGreenPin() {
            return ledGreenPin;
        }
        
        int getLedBluePin() {
            return ledBluePin;
        }
        
    private:
        cv::Ptr<cv::ml::SVM> mood_svm;
        int garageDoorPin = 27;
        int mainDoorPin = 22;
        
        int ledPin = 16;
        
        int ledRedPin = 13;
        int ledGreenPin = 19;
        int ledBluePin = 12;
};

#endif
