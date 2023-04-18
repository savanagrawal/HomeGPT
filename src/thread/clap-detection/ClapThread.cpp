/**
 * @file IntruderThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
 */

// #include "IntruderDetection.h"
#include "ClapDetection.h"
#include "ClapThread.h"
#include <stdio.h>
#include <thread>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the intruder detection thread runnable.
 */
void ClapThread::run(void) {
    printf("Clap Thread...\n");

    clapDetection.Initialize();
    clapDetection.start();
    

    // switch(IntruderThread::modules.at(IntruderThread::module)) {
    //     case 1:
    //         datasetCreator.Initialize(IntruderThread::camera);
    //         datasetCreator.startms(100);
    //     break;
    //     case 2:
    //         datasetTrainer.Initialize();
    //         datasetTrainer.generateModel();
    //         globals.killProcess();
    //     break;
    //     case 3:
    //     default:
    //         intruderDetection.Initialize(IntruderThread::camera);
    //         intruderDetection.startms(100);
    //     break;
    // }
}