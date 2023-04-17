/**
 * @file
 * @author
 * @version 0.1
 * 
 * Support for camera as a class
 */
#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/opencv.hpp>
#include <iostream>

class Camera : public cv::VideoCapture {
    public:
        Camera(int id) {
            cv::VideoCapture cam(id);
        }

        cv::VideoCapture getCamera() {
            return cam;
        }


    
    private:
        cv::VideoCapture cam;
};

#endif