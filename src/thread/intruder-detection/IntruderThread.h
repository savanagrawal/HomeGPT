/**
 * @file IntruderThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Handle our intruder detection thread.
 */
#ifndef INTRUDER_THREAD_H
#define INTRUDER_THREAD_H

#include "../CppThread.h"
#include "IntruderDetection.h"
#include <opencv2/opencv.hpp>
#include <memory>

/**
 * @brief Intruder Thread to manage intruder detection functionality.
 * @author Chinmay Nagrale
 */
class IntruderThread : public CppThread {
    public:
        /**
         * Contructor for our intruder thread.
         */
        IntruderThread(cv::VideoCapture camera) {
            IntruderThread::camera = camera;
        }

    public:
        void stop(){
            intruderDetection.stop();
        }

    private:
        void run();
    
    private:
        cv::VideoCapture camera;

        IntruderDetection intruderDetection;
};

#endif