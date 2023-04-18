/**
 * @file AudioRecordThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Handle our audio record thread.
 */
#ifndef AUDIO_RECORD_THREAD_H
#define AUDIO_RECORD_THREAD_H

#include "../CppThread.h"
#include "../../utils/Globals.h"

#include "ClapDetection.h"
#include <string>

class AudioRecordThread : public CppThread {
    public:
        AudioRecordThread(ClapDetection* clapDetection) {
            AudioRecordThread::clapDetection = clapDetection;
        }

    private:
        void run();

    private:
        Globals globals;

        // Events& eventHandler = Events::getInstance();
        // using EVENT_CODES = Events::EVENT_CODES;

        ClapDetection* clapDetection;
};

#endif
