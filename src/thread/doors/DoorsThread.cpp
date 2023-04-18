/**
 * @file RFIDThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to doors thread.
 */

#include "EventHandler.h"
#include "ServoMotor.h"
#include "DoorsThread.h"
#include <stdio.h>
#include <thread>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the doors thread runnable.
 */
void DoorsThread::run(void) {
    printf("Doors Thread...\n");
    EventHandler& eventHandler = EventHandler::getInstance();

    if(!eventHandler.isEventRegistered(Event::RfidAuthenticated)){
        eventHandler.addListener(Event::RfidAuthenticated, [&](){
            // We are authenticated, so we will open our garage door.
            // garageDoor.write(90);


            eventHandler.emit(Event::OpenGarageDoor);
        });
    }
}