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

        void killProcess() {
            raise(SIGHUP);
        }
    private:
        cv::Ptr<cv::ml::SVM> mood_svm;
        int garageDoorPin = 16;
        int mainDoorPin = 16;
};

#endif
