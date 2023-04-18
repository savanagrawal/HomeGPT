/**
 * @file LEDController.h
 * @author Savan Agrawal
 * @version 0.1
 * 
 * LED Controller Main file to control normal and RGB ligth
 */

#include <iostream>
#include "LEDController.h"
#include <unistd.h>

int main() {
    int ledPin = 27; // GPIO 27
    int redPin = 13; // GPIO 13
    int greenPin = 19; // GPIO 19
    int bluePin = 12; // GPIO 12

    LEDController ledController(ledPin, redPin, greenPin, bluePin);

    std::cout << "Turning on LED" << std::endl;
    ledController.turnOnLED();
    sleep(2);

    std::cout << "Turning off LED" << std::endl;
    ledController.turnOffLED();
    sleep(2);

    std::cout << "Setting RGB LED to red" << std::endl;
    ledController.setRGBColor("red");
    sleep(2);

    std::cout << "Setting RGB LED to green" << std::endl;
    ledController.setRGBColor("green");
    sleep(2);

    std::cout << "Setting RGB LED to blue" << std::endl;
    ledController.setRGBColor("blue");
    sleep(2);

    std::cout << "Turning off RGB LED" << std::endl;
    ledController.turnOffRGBLED();
	sleep(2);

	std::cout << "Program finished" << std::endl;

	return 0;
}

