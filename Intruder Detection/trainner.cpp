#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;
using namespace cv::face;

int main()
{
    Ptr<LBPHFaceRecognizer> recognizer = LBPHFaceRecognizer::create();
    CascadeClassifier detector("haarcascade_frontalface_default.xml");

    vector<Mat> faceSamples;
    vector<int> Ids;

    string path = "dataset";
    vector<string> imagePaths;
    glob(path + "/*.jpg", imagePaths, false);

    for (string imagePath : imagePaths) {
        Mat image = imread(imagePath, IMREAD_GRAYSCALE);

        int Id = stoi(imagePath.substr(path.length() + 6, 2));
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
