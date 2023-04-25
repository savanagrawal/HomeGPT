/**
 * @file IntruderMoodThread.h
 * @author Chinmay Nagrale & Savan Agrawal
 * @version 0.1
 * 
 * Handle our intruder detection thread.
 */
#ifndef INTRUDER_MOOD_THREAD_H
#define INTRUDER_MOOD_THREAD_H

#include "../CppThread.h"
// #include "../../utils/Globals.h"
// #include "../../utils/Events.h"

#include "IntruderMoodDetection.h"
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>
#include "../utils/EventHandler.h"


class IntruderMoodThread : public CppThread {
    public:
        /**
         * Contructor for our intruder mood thread.
         */
        IntruderMoodThread(cv::VideoCapture camera) {
            IntruderMoodThread::camera = camera;
        }

        void stop(){
            // intruderDetection.stop();
            intruderMoodDetection.stop();
            
            camera.release();
        }
        
        void unlock() {
            intruderMoodDetection.unlock();
        }
        
        void restart() {
            camera.open(0);
            
            intruderMoodDetection.restart();
            intruderMoodDetection.start();
        }

    private:
        // void run();
        void run(void);
    
    private:
        // Globals globals;


        cv::VideoCapture camera;

        IntruderMoodDetection intruderMoodDetection;


};

#endif
