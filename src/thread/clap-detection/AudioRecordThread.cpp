/**
 * @file AudioRecordThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to audio recording thread.
 */

#include "../../utils/Events.h"
#include "ClapDetection.h"
#include "AudioRecordThread.h"
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
void AudioRecordThread::run(void) {
    printf("Audio Record Thread...\n");

	

}

