/**
 * @file ServoMotor.cpp
 * @author Savan Agrawal
 * @version 0.1
 * 
 * Servo Moto cpp file to take pin and angle of motor
 */
#include "ServoMotor.h"

#include <iostream>
#include <unistd.h>
#include <pigpio.h>

ServoMotor::ServoMotor(int pin) {
    _pin = pin;
    _angle = 0;
    gpioSetMode(_pin, PI_OUTPUT);
}

ServoMotor::~ServoMotor() {
}

void ServoMotor::write(int angle) {
    _angle = angle;
    if (_angle < 0) _angle = 0;
    if (_angle > 180) _angle = 180;

    int pulseWidthMin = 500; 
    int pulseWidthMax = 2500; 

    int pulseWidth = pulseWidthMin + (_angle * (pulseWidthMax - pulseWidthMin) / 180);
    std::cout << "Pulse width: " << pulseWidth << std::endl;
    gpioServo(_pin, pulseWidth);
}

// int main() {
//     if (gpioInitialise() < 0) {
//         std::cerr << "Error initializing pigpio" << std::endl;
//         return 1;
//     }

//     ServoMotor servo(27); 
//     int angle;

//     while (true) {
//         std::cout << "Enter angle (0-180, -1 to exit): ";
//         std::cin >> angle;

//         if (angle == -1) {
//             break;
//         }

//         servo.write(angle);
//         sleep(1);
//     }

//     gpioTerminate();
//     return 0;
// }