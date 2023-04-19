/**
 * @file RFIDThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to rfid detection thread.
 */

#include "EventHandler.h"
#include "RFID.h"
#include "RFIDThread.h"
#include <stdio.h>
#include <thread>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the rfid thread runnable.
 */
void RFIDThread::run(void) {
    printf("RFID Thread...\n");
    EventHandler& eventHandler = EventHandler::getInstance();

    eventHandler.addListener(Event::RfidAuthenticated, [&](){
        // We are authenticated, so we will open our garage door.
        eventHandler.emit(Event::OpenGarageDoor);
    });

    // Detect rfid.
    std::cout << "Running rfid detection..." << std::endl;
    RFID rfid;
}
