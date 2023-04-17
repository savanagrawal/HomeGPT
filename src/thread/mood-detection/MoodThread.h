/**
 * @file MoodThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Handle our mood detection thread.
 */
#ifndef MOOD_THREAD_H
#define MOOD_THREAD_H

#include "../CppThread.h"
#include "MoodDetection.h"
#include <opencv2/opencv.hpp>
#include <memory>

/**
 * @brief Mood Thread to manage mood detection functionality.
 * @author Chinmay Nagrale
 */
class MoodThread : public CppThread {
    public:
        /**
         * Contructor for our mood thread.
         * 
         * @param camera Camera Object.
         */
        MoodThread(cv::VideoCapture camera) {
            MoodThread::camera = camera;
        }

        /**
         * Stop our thread's inner functionality.
         */
        void stop(){
            moodDetection.stop();
        }

    private:
        void run();
    
    private:
        cv::VideoCapture camera;

        MoodDetection moodDetection;
};

#endif