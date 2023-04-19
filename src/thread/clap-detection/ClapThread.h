/**
 * @file ClapThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Handle our clap detection thread.
 */
#ifndef CLAP_THREAD_H
#define CLAP_THREAD_H

#include "../CppThread.h"
#include "../../utils/Globals.h"

#include "ClapDetection.h"
#include <string>

class ClapThread : public CppThread {
    public:
        ClapThread() {}

    private:
        void run();

    private:
        Globals globals;
  
        ClapDetection* clapDetection;
};

#endif