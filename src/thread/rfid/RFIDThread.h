/**
 * @file RFIDThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Handle our rfid detection thread.
 */
#ifndef RFID_THREAD_H
#define RFID_THREAD_H

#include "../CppThread.h"
#include "RFID.h"
#include <opencv2/opencv.hpp>
#include <memory>

/**
 * @brief Mood Thread to manage mood detection functionality.
 * @author Chinmay Nagrale
 */
class RFIDThread : public CppThread {
    public:
        /**
         * Contructor for our mood thread.
         * 
         * @param 
         */
        RFIDThread() {
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
        RFID rfid;
};

#endif