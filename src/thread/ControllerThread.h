/**
 * @file ControllerThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Create a controller thread for whole program.
 */
#ifndef CONTROLLER_THREAD_H
#define CONTROLLER_THREAD_H

#include "../utils/Events.h"
#include "CppThread.h"
#include <vector>
#include <iostream>
#include <map>
// #include "Controller.h"

/**
 * @brief Controller Thread to manage all child threads.
 * @author Chinmay Nagrale
 */
class ControllerThread : public CppThread {
    public:
        /**
         * Contructor for our controller thread. All child threads are initiallized here.
         */
        ControllerThread() {}

        void setArgs(int ac, std::vector<std::string> av) {
            ControllerThread::argc = ac;

            if(ac > 1) {
                for(int i = 0; i < ac; i++){
                    ControllerThread::argv.push_back(av[i]);
                }
            }
        }
    private:
        void run();
    
    private:
        int argc = 1;
        
        Events eventHandler;
        using EVENT_CODES = Events::EVENT_CODES;
        
        // Events& eventHandler = Events::getInstance();
        // using EVENT_CODES = Events::EVENT_CODES;

        std::vector<std::string> argv;

        enum argvEnum {
            CreateIntruderDataset,
            TrainIntruderModel,
            DetectIntruder,
            DetectClap,
            RfidStart
        };

        std::map<std::string, argvEnum> argvValues = {
            {"--create-intruder-dataset", CreateIntruderDataset},
            {"--cid", CreateIntruderDataset},
            {"--train-intruder-model", TrainIntruderModel},
            {"--tim", TrainIntruderModel},
            {"--detect-intruder", DetectIntruder},
            {"--di", DetectIntruder},
            {"--detect-clap", DetectClap},
            {"--dc", DetectClap},
            {"--rfid", RfidStart},
        };
};

#endif
