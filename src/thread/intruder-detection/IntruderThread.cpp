/**
 * @file IntruderThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
 */

// #include "IntruderDetection.h"
#include "../../utils/Events.h"
#include "DatasetCreator.h"
#include "DatasetTrainer.h"
#include "IntruderThread.h"
#include <stdio.h>
#include <thread>


// #include <exception>
// #include <stdexcept>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the intruder detection thread runnable.
 */
void IntruderThread::run(void) {
    printf("Intruder Thread...\n");

    // std::exception_ptr eptr;
    
    std::cout << &eventHandler << std::endl;
    
    eventHandler->getDispatcher()->appendListener(EVENT_CODES::DATASET_CREATOR_COMPLETE, [&]() {
        // Now we can queue our model generation.
        std::cout << "test" << std::endl;
        
        datasetCreator.stop();
        datasetTrainer.Initialize();
        datasetTrainer.generateModel();
        
        eventHandler->getDispatcher()->dispatch(EVENT_CODES::DATASET_TRAINER_COMPLETE);
    });

    std::cout << "IT " << eventHandler->getDispatcher()->hasAnyListener(EVENT_CODES::DATASET_CREATOR_COMPLETE) << std::endl;

    eventHandler->getDispatcher()->appendListener(EVENT_CODES::DATASET_TRAINER_COMPLETE, [&]() {
        // Time to kill the thread.
        eventHandler->getDispatcher()->dispatch(EVENT_CODES::INTRUDER_THREAD_KILL);
    });

    switch(IntruderThread::modules.at(IntruderThread::module)) {
        case 1:
            datasetCreator.Initialize(IntruderThread::camera, eventHandler);
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
    
    // try {
        // CppTimerCallback intruderCallback;

        // Initialize intruder detection controller.
        // intruderDetection.Initialize(IntruderThread::camera);

        // intruderCallback.registerEventRunnable(datasetCreator);
        // datasetCreator.setParentCallback(intruderCallback);

        // intruderCallback.startms(100);

    // } catch (...) {
    //     eptr = std::current_exception();
    // }

    // try {
    //     if (eptr) {
    //         std::rethrow_exception(eptr);
    //     }
    // } catch(const std::exception& e) {
    //     std::cout << "Caught exception \"" << e.what() << "\"\n";
    // }

    // Detect intruder every 10ms.
    // intruderDetection.startms(10);
}
