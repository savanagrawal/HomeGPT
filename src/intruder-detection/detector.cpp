#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
using namespace cv;
using namespace cv::face;

std::map<int, std::string> readFileToMap(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    std::map<int, std::string> users;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        std::getline(iss, name, ',');
        std::string numStr;
        std::getline(iss, numStr);
        int num = std::stoi(numStr);
        users[num] = name;
    }

    return users;
}

int main() {
    Ptr<LBPHFaceRecognizer> recognizer = LBPHFaceRecognizer::create();
    recognizer->read("trainner/trainner.yml");
    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    std::string fileName = "Users.txt";
    std::map<int, std::string> users = readFileToMap(fileName);

    VideoCapture cam(0);
    if (!cam.isOpened()) {
        cerr << "Error opening camera." << endl;
        return -1;
    }

    namedWindow("Face Recognition", WINDOW_NORMAL);
    while (true) {
        Mat im, gray;
        cam >> im;
        cvtColor(im, gray, COLOR_BGR2GRAY);
        vector<Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.2, 5);
        for (size_t i = 0; i < faces.size(); i++) {
            rectangle(im, faces[i], Scalar(225, 0, 0), 2);
            int predictedLabel = -1;
            double confidence = 0.0;
            recognizer->predict(gray(faces[i]), predictedLabel, confidence);
            
            string label;
            auto it = users.find(predictedLabel);
            if (confidence < 90 && it != users.end()) {
                label = it->second;
                // std::cout << "The string name of the integer value " << searchValue << " is: " << it->second << std::endl;
            } else {
                label = "Intruder";
            }

            
            // if (confidence < 90) {
            //     label = int_to_name(predictedLabel);
            // } else {
            //     label = "Intruder";
            // }
            cout << "Predicted label: " << predictedLabel << ", Name: " << label << ", Confidence: " << confidence << endl;
            putText(im, label, Point(faces[i].x, faces[i].y - 10), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(225, 0, 0), 2);
        }

        imshow("Face Recognition", im);
        if (waitKey(10) == 'q') {
            break;
        }
    }

    cam.release();
    destroyAllWindows();
    return 0;
}
