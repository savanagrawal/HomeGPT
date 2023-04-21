/**
 * @file LEDController.h
 * @author Savan Agrawal
 * @version 0.1
 * 
 * LED Controller header file to control normal and RGB ligth
 */
 
#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <wiringPi.h>
#include <string>

class LEDController {
    public:
        LEDController(int ledPin, int redPin, int greenPin, int bluePin);
        void turnOnLED();
        void turnOffLED();
        void setRGBColor(const std::string& color);
        void turnOffRGBLED();

    private:
        int ledPin;
        int redPin;
        int greenPin;
        int bluePin;
        void setColor(int red, int green, int blue);
};

#endif // LEDCONTROLLER_H


//g++ -o led_test LEDMain.cpp LEDController.cpp -lwiringPi
