/**
 * @file IntruderThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
 */

// #include "IntruderDetection.h"
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

    switch(IntruderThread::modules.at(IntruderThread::module)) {
        case 1:
            datasetCreator.Initialize(IntruderThread::camera);
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