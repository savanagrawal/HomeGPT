/**
 * @file MoodThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to mood detection thread.
 */

#include "MoodDetection.h"
#include "MoodThread.h"
#include <stdio.h>
#include <thread>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the mood thread runnable.
 */
void MoodThread::run(void) {
    printf("Mood Thread...\n");

    // Initialize mood detection controller.
    moodDetection.Initialize(MoodThread::camera);

    // Detect mood every 10ms.
    moodDetection.startms(10);
}