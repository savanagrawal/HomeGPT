/**
 * @file ControllerThread.cpp
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Functions related to controller thread. We will initialize more child threads from here.
 */

#include "mood-detection/MoodThread.h"
#include "intruder-detection/IntruderThread.h"
#include "ControllerThread.h"
#include "Controller.h"
#include "Camera.h"
#include "MoodDetection.h"
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

    // moodThread.start();

    // moodThread.join();

    IntruderThread intruderThread(cam);

    std::cout << ControllerThread::argc << std::endl;

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
            default:

                // moodThread.start();

                // moodThread.join();
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
    printf("Shutting down...\n");
}