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

/**
 * @brief Rfid Thread to manage rfid detection functionality.
 * @author Chinmay Nagrale
 */
class RFIDThread : public CppThread {
    public:
        /**
         * Contructor for our rfid thread.
         * 
         * @param 
         */
        RFIDThread() {
        }

        /**
         * Stop our thread's inner functionality.
         */
        void stop(){}

    private:
        void run();
};
#endif
