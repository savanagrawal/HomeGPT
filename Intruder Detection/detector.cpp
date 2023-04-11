#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;
using namespace cv::face;

int main() {
    Ptr<LBPHFaceRecognizer> recognizer = LBPHFaceRecognizer::create();
    recognizer->read("trainner/trainner.yml");
    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

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
            cout << "Predicted label: " << predictedLabel << ", Confidence: " << confidence << endl;

            string label;
            if (confidence < 90) {
                if (predictedLabel == 1) {
                    label = "Savan";
                } else if (predictedLabel == 2) {
                    label = "Bibek";
                }
            } else {
                label = "Unknown";
            }
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
