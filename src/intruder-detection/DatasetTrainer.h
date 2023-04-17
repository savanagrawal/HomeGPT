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
#include <map>
#include <fstream>

class IntruderDatasetTrainer {
    public:
        IntruderDatasetTrainer() {
        }

        void Initialize();

        std::string extract_username(std::string &input) {
            input = input.substr(2);
            std::size_t first_dot = input.find('.');
            std::size_t second_dot = input.find('.', first_dot + 1);

            return input.substr(first_dot + 1, second_dot - first_dot - 1);
        }

        std::map<std::string, int> readFileToMap(const std::string& fileName) {
            std::ifstream file(fileName);
            std::string line;
            std::map<std::string, int> users;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string name;
                std::getline(iss, name, ',');
                std::string numStr;
                std::getline(iss, numStr);
                int num = std::stoi(numStr);
                users[name] = num;
            }

            return users;
        }

        void generateModel(){
            std::cout << "Started model trainer..." << std::endl;

            cv::glob(base_path + "/dataset/*.jpg", imagePaths, false);

            users = readFileToMap(fileName);

            for (std::string imagePath : imagePaths) {
                cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
                std::cout << imagePath << std::endl;
                std::string extracted_username = extract_username(imagePath);
                auto it = users.find(extracted_username);
                int Id = it->second;

                std::cout << extracted_username << ", " << Id << std::endl;

                std::vector<cv::Rect> faces;
                detector.detectMultiScale(image, faces, 1.3, 5);

                for (cv::Rect face : faces) {
                    faceSamples.push_back(image(face));
                    Ids.push_back(Id);
                }
            }

            std::cout << "Completed training. Storing model to file storage..." << std::endl;

            recognizer->train(faceSamples, Ids);
            recognizer->save(base_path + "/trainer/trainer.yml");

            std::cout << "Done..." << std::endl;
        }
    
    private:
        cv::CascadeClassifier detector;
        std::string cascadePath = "../src/resources/haarcascade_frontalface_default.xml";
        
        cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer = cv::face::LBPHFaceRecognizer::create();

        std::vector<cv::Mat> faceSamples;
        std::vector<int> Ids;

        std::string base_path = "../src/resources/intruder-detection";
        std::vector<std::string> imagePaths;

        std::string fileName = "../src/resources/intruder-detection/Users.txt";
        std::map<std::string, int> users;

};

#endif