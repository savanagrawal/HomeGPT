/**
 * @file IntruderThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to intruder detection thread.
 */

#include "ClapDetection.h"
#include "ClapThread.h"
#include "EventHandler.h"
#include "ServoMotor.h"
#include "LEDController.h"
#include <stdio.h>
#include <thread>

enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the intruder detection thread runnable.
 */
void ClapThread::run(void) {
            std::cout << "Hello" << std::endl;
    printf("Clap Thread...\n");
    
    while(true) {
        std::cout << "Detecting clap..." << std::endl;
        bool found = clapDetection->detectClap();
        
        if(!found) {
            std::cout << "Clap not found... Recording..." << std::endl;
            clapDetection->record();
        } else {
            EventHandler& eventHandler = EventHandler::getInstance();
            
            std::cout << "Found clap..." << std::endl;
            
            ServoMotor mainDoor(globals.getMainDoorPin());
            
            mainDoor.write(0);
            
            LEDController ledController(globals.getLedPin(), globals.getLedRedPin(), globals.getLedGreenPin(), globals.getLedBluePin());
    
            ledController.turnOffRGBLED();
            
            eventHandler.emit(Event::ClosedMainDoor);
            
            //clapDetection->stop();
            break;
        }
    }
}
