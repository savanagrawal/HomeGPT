#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iterator>

using namespace std;
using namespace cv;


bool findStringInFile(const std::string& fileName, const std::string& searchString) {
    std::ifstream file(fileName);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        std::getline(iss, name, ',');
        if (name == searchString) {
            return true;
        }
    }

    return false;
}

int getLastIntegerInFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    int lastInteger = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        std::string numStr;
        std::getline(iss, name, ',');
        std::getline(iss, numStr);
        int num = std::stoi(numStr);
        lastInteger = num;
    }

    return lastInteger;
}

void appendLineToFile(const std::string& fileName, const std::string& line) {
    std::ofstream file(fileName, std::ios_base::app);
    file << line << std::endl;
}

std::string trim(const std::string &str) {
    std::size_t start = str.find_first_not_of(' ');
    std::size_t end = str.find_last_not_of(' ');

    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }

    return str.substr(start, end - start + 1);
}

int count_name(const std::string &str) {
    int count = 0;
    for (const char &c : str) {
        count += 1;
    }
    std::cout << count << std::endl;
    return count;
}

std::string replace_spaces_with_underscores(const std::string &str) {
    std::string result = str;
    for (char &c : result) {
        if (c == ' ') {
            c = '_';
        }
    }
    return result;
}

bool is_valid_name(const std::string &name) {
    if (name.empty()) {
        return false;
    }

    bool has_alpha = false;
    for (char c : name) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false;
        }
        if (std::isalpha(c)) {
            has_alpha = true;
        }
    }

    return has_alpha;
}

int main()
{
    VideoCapture cam(0);
    CascadeClassifier detector("haarcascade_frontalface_default.xml");




    std::string fileName = "Users.txt";
    std::string newUser;
    std::cout << "Enter new user: ";



    while (true) {
        std::getline(std::cin, newUser);
        newUser = trim(newUser);
        cout << newUser << endl;

        if (is_valid_name(newUser)) {
            newUser = replace_spaces_with_underscores(newUser);
            if (!findStringInFile(fileName, newUser)) {
                int lastInteger = getLastIntegerInFile(fileName);
                std::string newLine = newUser + ", " + std::to_string(lastInteger + 1);
                appendLineToFile(fileName, newLine);
                std::cout << "Added new user: " << newLine << std::endl;
                break;
            } else {
                std::cout << "User " << newUser << " already exists in the file." << std::endl;
                continue;
            }
        } 
        else {
            std::cout << "Invalid name. Please enter a valid name: ";
        }
    }
    

    int sampleNum = 0;
    while (true) {
        Mat img;
        bool ret = cam.read(img);
        if (!ret) {
            cerr << "Error: Failed to read camera frame" << endl;
            break;
        }

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        vector<Rect> faces;
        detector.detectMultiScale(gray, faces, 1.3, 5);

        for (Rect face : faces) {
            rectangle(img, face, Scalar(255, 0, 0), 2);

            // incrementing sample number
            sampleNum++;

            // saving the captured face in the dataset folder
            string filename = "dataset/User." + newUser + "." + to_string(sampleNum) + ".jpg";
            imwrite(filename, gray(face));

            imshow("frame", img);
        }

        // wait for 100 milliseconds
        if (waitKey(100) & 0xFF == 'q')
            break;

        // break if the sample number is more than 20
        if (sampleNum > 20)
            break;
    }

    cam.release();
    destroyAllWindows();

    return 0;
}
