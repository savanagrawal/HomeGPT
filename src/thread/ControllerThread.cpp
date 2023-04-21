/**
 * @file ControllerThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to controller thread. We will initialize more child threads from here.
 */

#include "mood-detection/MoodThread.h"
#include "intruder-detection/IntruderThread.h"
#include "intruder-mood-detection/IntruderMoodThread.h"
#include "clap-detection/ClapThread.h"
// #include "clap-detection/AudioRecordThread.h"
#include "rfid/RFIDThread.h"
#include "doors/DoorsThread.h"
#include "ServoMotor.h"
#include "LEDController.h"

#include "../utils/Globals.h"
#include "EventHandler.h"

#include "ControllerThread.h"

#include "ClapDetection.h"
#include "Controller.h"

#include <stdio.h>
#include <thread>

#include <typeinfo>

// Global variable for detecting if the program is running or not.
int running = 1;

// A ctrl+c handler. Basically handles exiting the program safely.
void sigHandler(int sig) {
    if((sig == SIGHUP) || (sig == SIGINT) || (sig == SIGTERM)) {
        running = 0;
    }
}

// A function to detect ctrl+c press.
void setHUPHandler() {
    struct sigaction act;

    memset (&act, 0, sizeof(act));

    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    act.sa_handler = sigHandler;

    if(sigaction(SIGHUP, &act, NULL) < 0) {
        perror("sigaction");
        exit(-1);
    }

    if(sigaction(SIGTERM, &act, NULL) < 0) {
        perror("sigaction");
        exit(-1);
    }

    if(sigaction(SIGINT, &act, NULL) < 0) {
        perror("sigaction");
        exit(-1);
    }
}

// I don't even know anymore.
enum EVENT_OP_CODES {

    
    EXIT_APPLICATION = 255
};

/**
 * Manage the controller thread runnable.
 */
void ControllerThread::run(void) {
    printf("Main Controller Thread...\n");

    // Proper termination catcher.
    setHUPHandler();

    // Initialize main controller.
    Controller controller;

    cv::VideoCapture cam(0);
    // Camera cam(0);

    MoodThread moodThread(cam);
    
    Globals globals;
    
    // moodThread.start();

    // moodThread.join();
    
    ClapDetection clapDetection;
    clapDetection.Initialize();

    IntruderThread intruderThread(cam);
    IntruderMoodThread intruderMoodThread(cam);
    ClapThread clapThread(&clapDetection);
    // AudioRecordThread audioRecordThread(&clapDetection);
    
    RFIDThread rfidThread;
    DoorsThread doorsThread;

    std::cout << ControllerThread::argc << std::endl;
    
    doorsThread.start();
    doorsThread.join();
    
    EventHandler& eventHandler = EventHandler::getInstance();
    
    ServoMotor mainDoor(globals.getMainDoorPin());
    ServoMotor garageDoor(globals.getGarageDoorPin());
    
    if(!eventHandler.isEventRegistered(Event::IntruderMoodThreadKill)) {
        eventHandler.addListener(Event::IntruderMoodThreadKill, [&](){
            intruderMoodThread.stop();
        });
    }
    
    std::map<int, std::string> emotionToLED = {
        {0, "Angry"},
        {1, "Disgust"},
        {2, "Fear"},
        {3, "Happy"},
        {4, "Neutral"},
        {5, "Sad"},
        {6, "Surprise"}
    };
    
    LEDController ledController(globals.getLedPin(), globals.getLedRedPin(), globals.getLedGreenPin(), globals.getLedBluePin());
    
    //ledController.turnOnLED();
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    //ledController.turnOffLED();
    
    //ledController.setRGBColor("red");
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    //ledController.turnOffRGBLED();
    
    //mainDoor.write(90);
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    //mainDoor.write(0);
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    
    //garageDoor.write(90);
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    //garageDoor.write(0);
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    
    if(!eventHandler.isEventRegistered(Event::OpenMainDoor)) {
        eventHandler.addListener(Event::OpenMainDoor, [&](){
            mainDoor.write(90);
            
            clapDetection.openStream();
            
            // mainDoor.write(0);
            
            std::cout << "test" << std::endl;
            
            clapThread.start();
            clapThread.join();
            
            std::cout << "test" << std::endl;
        });
    }
    
    if(!eventHandler.isEventRegistered(Event::test)) {
        eventHandler.addListener(Event::test, [&](){
            
            std::cout << "test" << std::endl;
        });
    }
    
    if(ControllerThread::argc > 1) {
        switch(ControllerThread::argvValues.at(ControllerThread::argv[1])){
            case CreateIntruderDataset:
                intruderThread.setModule("create-dataset");

                intruderThread.start();
                intruderThread.join();
            break;
            case TrainIntruderModel:
                intruderThread.setModule("train-model");

                intruderThread.start();
                intruderThread.join();
            break;
            case DetectIntruder:
                intruderThread.setModule("detect-intruder");

                intruderThread.start();
                intruderThread.join();
            break;
            case DetectClap:
                clapDetection.openStream();
                
                clapThread.start();
                clapThread.join();
            break;
            case IntruderMoodDetectionStart:
                intruderMoodThread.start();
                intruderMoodThread.join();
            break;
            case RfidStart:
                rfidThread.start();
                rfidThread.join();
            break;
            case Debug:
                //eventHandler.emit(Event::OpenMainDoor);
                //eventHandler.emit(Event::test, 1) ;
            break;
            default:
            break;
        }
    } else {
        
        moodThread.start();
        moodThread.join();
    }

    printf("Main Loop...\n");
    while(running) sleep(1);

    moodThread.stop();

    intruderThread.stop();
    intruderMoodThread.stop();
    rfidThread.stop();
    doorsThread.stop();
    
    printf("Shutting down...\n");
}
