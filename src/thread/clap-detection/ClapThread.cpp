/**
 * @file ClapThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to clap detection thread.
 */

#include "../../utils/Events.h"
#include "ClapDetection.h"
#include "ClapThread.h"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the intruder detection thread runnable.
 */
void ClapThread::run(void) {
    printf("Clap Thread...\n");
    
    while(true) {
        std::cout << "Detecting clap..." << std::endl;
        bool found = clapDetection->detectClap();
        
        if(!found) {
            std::cout << "Clap not found... Recording..." << std::endl;
            clapDetection->record();
        } else {
            std::cout << "Found clap..." << std::endl;
            clapDetection->stop();
            break;
        }
    }
}
