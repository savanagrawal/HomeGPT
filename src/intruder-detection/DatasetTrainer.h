/**
 * @file DatasetTrainer.h
 * @author Savan Agrawal & Chinmay Nagrale
 * @version 0.1
 * 
 * Header file for Intruder Detection - Trainer.
 */
#ifndef DATASET_TRAINER_H
#define DATASET_TRAINER_H

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <string>

class IntruderDatasetTrainer {
    public:
        IntruderDatasetTrainer() {
        }

        void Initialize();

        void generateModel(){
            std::cout << "Started model trainer..." << std::endl;

            cv::glob(base_path + "/dataset/*.jpg", imagePaths, false);

            for (std::string imagePath : imagePaths) {
                cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

                std::cout << imagePath.substr(base_path.length() + 14, 2) << std::endl;
                break;

                int Id = std::stoi(imagePath.substr(base_path.length() + 6, 2));
                std::vector<cv::Rect> faces;
                detector.detectMultiScale(image, faces, 1.3, 5);

                for (cv::Rect face : faces) {
                    faceSamples.push_back(image(face));
                    Ids.push_back(Id);
                }
            }

            std::cout << "Completed training. Storing model to file storage..." << std::endl;

            // recognizer->train(faceSamples, Ids);
            // recognizer->save(base_path + "/trainer/trainer.yml");

            std::cout << "Done..." << std::endl;
        }
    
    private:
        cv::CascadeClassifier detector;
        std::string cascadePath = "../src/resources/haarcascade_frontalface_default.xml";
        
        cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer = cv::face::LBPHFaceRecognizer::create();

        std::vector<cv::Mat> faceSamples;
        std::vector<int> Ids;

        std::string base_path = "../src/resources/intruder-detection/";
        std::vector<std::string> imagePaths;

};

#endif