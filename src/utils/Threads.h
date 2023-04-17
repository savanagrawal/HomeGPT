/**
 * @file Threads.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Store all threads at a single class and use them to kill whenever we want.
 * Note the difference an 's' makes for this class.
 */
#ifndef THREADS_H
#define THREADS_H

#include "../thread/intruder-detection/IntruderThread.h"
#include "../thread/mood-detection/MoodThread.h"

class Threads {
    public:
        void setIntruderThread(IntruderThread* it) {
            intruderThread = it;
        }

        IntruderThread getIntruderThread() {
            return &intruderThread;
        }

    private:
        IntruderThread* intruderThread;
        MoodThread moodThread;
}