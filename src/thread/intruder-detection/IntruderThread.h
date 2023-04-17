/**
 * @file IntruderThread.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Handle our intruder detection thread.
 */
#ifndef INTRUDER_THREAD_H
#define INTRUDER_THREAD_H

#include "../CppThread.h"
#include "../../utils/Globals.h"

#include "IntruderDetection.h"
#include "DatasetCreator.h"
#include "DatasetTrainer.h"
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>

/**
 * @brief Intruder Thread to manage intruder detection functionality.
 * @author Chinmay Nagrale
 */
class IntruderThread : public CppThread {
    public:
        /**
         * Contructor for our intruder thread.
         */
        IntruderThread(cv::VideoCapture camera) {
            IntruderThread::camera = camera;
        }

        void setModule(std::string module) {
            if(modules.find(module) == modules.end()) {
                std::cerr << "Invalid argument for module passed!" << std::endl;
                raise(SIGHUP);
            } else {
                IntruderThread::module = module;
            }
        }

        void stop(){
            // intruderDetection.stop();
            datasetCreator.stop();
        }

    private:
        void run();
    
    private:
        Globals globals;

        cv::VideoCapture camera;

        IntruderDetection intruderDetection;
        IntruderDatasetCreator datasetCreator;
        IntruderDatasetTrainer datasetTrainer;

        std::string module = "create-dataset";

        std::map<std::string, int> modules = {
            {"create-dataset", 1},
            {"train-model", 2},
            {"detect-intruder", 3}
        };
};

#endif