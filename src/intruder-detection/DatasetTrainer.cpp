/**
 * @file DatasetTrainer.cpp
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Functions for Intruder Detection - Dataset Trainer.
 */

#include "DatasetTrainer.h"

#include <iostream>

/**
 * Initializes our Dataset Trainer.
 * 
 * @param
 * 
 * @return
 */
void IntruderDatasetTrainer::Initialize() {
    std::cout << "Initializing trainer..." << std::endl;
    detector.load(cascadePath);
    std::cout << "Trainer ready..." << std::endl;
}