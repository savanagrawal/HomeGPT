#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    CascadeClassifier faceCascade;
    std::string cascadePath = "haarcascade_frontalface_default.xml";
    faceCascade.load(cascadePath);

    // Load the trained SVM model
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::load("svmhog.xml");

    // Initialize the HOG descriptor
    cv::Size win_size(64, 128);
    cv::Size block_size(16, 16);
    cv::Size block_stride(8, 8);
    cv::Size cell_size(8, 8);
    int nbins = 9;
    cv::HOGDescriptor hog(win_size, block_size, block_stride, cell_size, nbins);

    cv::Scalar color(255, 0, 255);
    VideoCapture cam(0);

    std::map<int, std::string> emotion = {
            {0, "Angry"},
            {1, "Disgust"},
            {2, "Fear"},
            {3, "Happy"},
            {4, "Neutral"},
            {5, "Sad"},
            {6, "Surprise"}
        };
    while (true)
    {
        Mat im;
        cam >> im;
        if (im.empty()) break;

        Mat gray;
        cvtColor(im, gray, COLOR_BGR2GRAY);

        std::vector<Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.2, 5);
		
		int pred =4;
        for (auto& face : faces)
        {
            rectangle(im, face, Scalar(225, 0, 0), 2);

            Mat roi = gray(face);
            resize(roi, roi, win_size);
            std::vector<float> hog_features;
			hog.compute(roi, hog_features);
            float prediction = svm->predict(hog_features);
            pred = static_cast<int>(prediction);
            std::cout << emotion[pred] << std::endl;
            putText(im, emotion[pred], Point(face.x, face.y - 5), FONT_HERSHEY_SIMPLEX, 1, color, 2);
        }

        imshow("im", im);

        char c = (char)waitKey(10);
        if (c == 'q') break;
    }

    cam.release();
    destroyAllWindows();

    return 0;
}
