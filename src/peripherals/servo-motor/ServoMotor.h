/**
 * @file ServoMotor.h
 * @author Savan Agrawal
 * @version 0.1
 * 
 * Servo Moto Header file to take pin and angle of motor
 */
#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

class ServoMotor {
public:
    ServoMotor(int pin);
    ~ServoMotor();
    void write(int angle);

private:
    int _pin;
    int _angle;
};

#endif // SERVOMOTOR_H

//g++ -o servo_control ServoMotor.cpp -lpigpio -lrt && sudo ./servo_control

