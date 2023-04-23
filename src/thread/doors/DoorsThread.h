/**
 * @file DoorsThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Handle our doors detection thread.
 */
#ifndef DOORS_THREAD_H
#define DOORS_THREAD_H

#include "../CppThread.h"
#include "ServoMotor.h"
#include "../../utils/Globals.h"

/**
 * @brief Doors Thread to manage doors detection functionality.
 * @author Chinmay Nagrale
 */
class DoorsThread : public CppThread {
    public:
        /**
         * Contructor for our doors thread.
         * 
         * @param 
         */
        DoorsThread() {
        }

        /**
         * Stop our thread's inner functionality.
         */
        void stop(){}
        
    private:
        void run();
    
    private:
        Globals globals;
};
#endif
