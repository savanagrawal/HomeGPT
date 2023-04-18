/**
 * @file RFIDThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to mood detection thread.
 */

#include "RFID.h"
#include "RFIDThread.h"
#include <stdio.h>
#include <thread>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the mood thread runnable.
 */
void RFIDThread::run(void) {
    printf("Mood Thread...\n");

    // Initialize mood detection controller.
    rfid.Initialize();

    // Detect mood every 10ms.
    std::cout << "Running rfid detection..." << std::endl;
    rfid.startms(10);
}