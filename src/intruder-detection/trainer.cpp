#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;
using namespace cv::face;

std::string extract_username(const std::string &input) {
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

int main()
{
    Ptr<LBPHFaceRecognizer> recognizer = LBPHFaceRecognizer::create();
    CascadeClassifier detector("haarcascade_frontalface_default.xml");

    vector<Mat> faceSamples;
    vector<int> Ids;

    string path = "dataset";
    vector<string> imagePaths;
    glob(path + "/*.jpg", imagePaths, false);

    std::string fileName = "Users.txt";
    std::map<std::string, int> users = readFileToMap(fileName);

    for (string imagePath : imagePaths) {
        Mat image = imread(imagePath, IMREAD_GRAYSCALE);

        std::string extracted_username = extract_username(imagePath);
        auto it = users.find(extracted_username);
        int Id = it->second;

        cout << extracted_username << ", " << Id << endl;

        vector<Rect> faces;
        detector.detectMultiScale(image, faces, 1.3, 5);

        for (Rect face : faces) {
            faceSamples.push_back(image(face));
            Ids.push_back(Id);
        }
    }

    recognizer->train(faceSamples, Ids);
    recognizer->save("trainner/trainner.yml");

    return 0;
}
