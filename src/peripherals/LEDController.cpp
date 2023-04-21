/**
 * @file LEDController.cpp
 * @author Savan Agrawal
 * @version 0.1
 * 
 * LED Controller CPP file to control normal and RGB ligth
 */

#include "LEDController.h"

LEDController::LEDController(int ledPin, int redPin, int greenPin, int bluePin)
    : ledPin(ledPin), redPin(redPin), greenPin(greenPin), bluePin(bluePin) {
    wiringPiSetupGpio(); // Use BCM numbering
    pinMode(ledPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void LEDController::turnOnLED() {
    digitalWrite(ledPin, HIGH);
}

void LEDController::turnOffLED() {
    digitalWrite(ledPin, LOW);
}

void LEDController::setRGBColor(const std::string& color) {
    if (color == "red") {
        setColor(255, 0, 0);
    } else if (color == "green") {
        setColor(0, 255, 0);
    } else if (color == "blue") {
        setColor(0, 0, 255);
    } else if (color == "white") {
        setColor(255, 255, 255);
    } else {
        if (color == "Angry") {
            setColor(255, 0, 0);
        } else if (color == "Disgust") {
            setColor(0, 255, 0);
        } else if (color == "Fear") {
            setColor(0, 0, 255);
        } else if (color == "Happy") {
            setColor(255, 255, 0);
        } else if (color == "Neutral") {
            setColor(255, 0, 255);
        } else if (color == "Sad") {
            setColor(0, 255, 255);
        } else {
            setColor(255, 255, 255);
        }
    }
}

void LEDController::turnOffRGBLED() {
    setColor(0, 0, 0);
}

void LEDController::setColor(int red, int green, int blue) {
    digitalWrite(redPin, red);
    digitalWrite(greenPin, green);
    digitalWrite(bluePin, blue);
}

