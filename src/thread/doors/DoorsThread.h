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
        int garageDoorPin = 27;
        int mainDoorPin = 22;

        // ServoMotor garageDoor(garageDoorPin);
        // ServoMotor mainDoor(garageDoorPin);
};
#endif