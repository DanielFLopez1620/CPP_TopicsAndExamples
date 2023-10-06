/*
Original Code from the AccelStepper library for Arduino in C++
https://github.com/adafruit/AccelStepper/tree/master
It was adapted by DanielFLopez1620 to a C alike program as an example for the lesson.
*/

#ifndef STEPPER_P_H
#define STEPPER_P_H

typedef struct
{
    unsigned int _pins;               // Total number of pins used
    unsigned int _pin1;               // If driver it is step
    unsigned int _pin2;               // If driver ii is dir
    unsigned int _pin3;
    unsigned int _pin4;
    long int _currentPos;             // Absolut position in steps
    long int _targetPos;              // Target position in steps
    float _speed;                     // Steps per second, Positive is clockwise
    float _maxSpeed;                  // Maximum steps permitted per second
    float _acceleration;              // works for deceleration to
    unsigned long int _stepInterval;  // Interval between steps in milliseconds
    unsigned long int _lastStepTime;  // Last step in millisecond

} stepper_t;

#endif