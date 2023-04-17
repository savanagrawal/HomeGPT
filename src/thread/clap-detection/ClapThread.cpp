/**
 * @file IntruderThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
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

    clapDetection.Initialize();
    clapDetection.start();

    eventHandler.getDispatcher().appendListener(EVENT_CODES::CLAP_DETECTED, [&]() {
        std::cout << "Clap detected" << std::endl;
        eventHandler.getDispatcher().dispatch(EVENT_CODES::CLAP_DETECTED_THREAD);
    });
    

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
