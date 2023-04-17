/**
 * @file ControllerThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Create a controller thread for whole program.
 */
#ifndef CONTROLLER_THREAD_H
#define CONTROLLER_THREAD_H

#include "CppThread.h"
// #include "Controller.h"

/**
 * @brief Controller Thread to manage all child threads.
 * @author Chinmay Nagrale
 */
class ControllerThread : public CppThread {
    public:
        /**
         * Contructor for our controller thread. All child threads are initiallized here.
         */
        ControllerThread() {

        }
    private:
        void run();
    
    private:

};

#endif