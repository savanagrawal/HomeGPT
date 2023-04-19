/**
 * @file IntruderThread.cpp
 * @author Chinmay Nagrale & Savan Agrawal
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
 */

// #include "IntruderDetection.h"
#include "EventHandler.h"
#include "DatasetCreator.h"
#include "DatasetTrainer.h"
#include "IntruderThread.h"
#include <stdio.h>
#include <thread>



enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the intruder detection thread runnable.
 */

void IntruderThread::run(void) {
    printf("Intruder Thread...\n");
    EventHandler& eventHandler = EventHandler::getInstance();

    if (eventHandler.isEventRegistered(Event::DatasetCreatorComplete)) {
        // Do something if the event is registered
        
        // std::cout<<"Not Reg"<<std::endl ;
    } else {
        
        // std::cout<<"Reg"<<std::endl;

        eventHandler.addListener(Event::DatasetTrainerComplete, [&]() {
            eventHandler.emit(Event::IntruderThreadKill);
        });
        
        eventHandler.addListener(Event::DatasetCreatorComplete, [&]() {
            datasetCreator.stop();
            datasetTrainer.Initialize();
            datasetTrainer.generateModel();
            eventHandler.emit(Event::DatasetTrainerComplete);
        });
    }
    
    switch (IntruderThread::modules.at(IntruderThread::module)) {
        case 1:
            std::cout<<"Not Reg"<<std::endl;
            datasetCreator.Initialize(IntruderThread::camera);
            datasetCreator.checkCameraOpen(IntruderThread::camera);
            datasetCreator.startms(100);
            break;
        case 2:
            datasetTrainer.Initialize();
            datasetTrainer.generateModel();
            globals.killProcess();
            break;
        case 3:
        default:
            intruderDetection.Initialize(IntruderThread::camera);
            intruderDetection.startms(100);
            break;
    }
}
