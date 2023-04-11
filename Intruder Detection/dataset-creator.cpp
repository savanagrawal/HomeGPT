#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cam(0);
    CascadeClassifier detector("haarcascade_frontalface_default.xml");

    string Id;
    cout << "Enter your id: ";
    cin >> Id;

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
            string filename = "dataset/User." + Id + "." + to_string(sampleNum) + ".jpg";
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
