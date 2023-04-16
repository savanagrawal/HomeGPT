/**
 * @file IntruderThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
 */

#include "IntruderDetection.h"
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

    // Initialize intruder detection controller.
    intruderDetection.Initialize(IntruderThread::camera);

    // Detect intruder every 10ms.
    intruderDetection.startms(10);
}