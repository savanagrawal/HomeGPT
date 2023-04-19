/**
 * @file IntruderMoodThread.cpp
 * @author Chinmay Nagrale & Savan Agrawal
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
 */

// #include "IntruderDetection.h"
// #include "../../utils/Events.h"
#include "../utils/EventHandler.h"
#include "IntruderMoodThread.h"
#include <stdio.h>
#include <thread>



enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the intruder detection thread runnable.
 */

void IntruderMoodThread::run(void) {
    printf("Intruder Mood Thread...\n");
    EventHandler& eventHandler = EventHandler::getInstance();

    if (eventHandler.isEventRegistered(Event::DatasetCreatorComplete)) {
        // Do something if the event is registered
        
        // std::cout<<"Not Reg"<<std::endl ;
    } 
    else{
        
        // std::cout<<"Reg"<<std::endl;
    //     eventHandler.addListener(Event::DatasetCreatorComplete, [&]() {
    //     datasetCreator.stop();
    //     datasetTrainer.Initialize();
    //     datasetTrainer.generateModel();
    //     eventHandler.emit(Event::DatasetTrainerComplete);
    // });

    // eventHandler.addListener(Event::DatasetTrainerComplete, [&]() {
    //     eventHandler.emit(Event::IntruderMoodThreadKill);
    // });
    }
    intruderMoodDetection.Initialize(IntruderMoodThread::camera);
    intruderMoodDetection.startms(100);


    // switch (IntruderMoodThread::modules.at(IntruderMoodThread::module)) {
    //     case 1:
    //         // std::cout<<"Not Reg"<<std::endl;
    //         intruderMoodDetection.Initialize(IntruderMoodThread::camera);
    //         intruderMoodDetection.startms(100);
    //         break;

    //     default:
    //         intruderMoodDetection.Initialize(IntruderMoodThread::camera);
    //         intruderMoodDetection.startms(100);
    //         break;
    // }
}
