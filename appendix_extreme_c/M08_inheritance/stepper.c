/*
Original Code from the AccelStepper library for Arduino in C++
https://github.com/adafruit/AccelStepper/tree/master
It was adapted by DanielFLopez1620 to a C alike program as an example for the lesson.
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stepper_p.h"

stepper_t* stepper_new()
{
    return (stepper_t*) malloc(sizeof(stepper_t));
}

void stepper_ctor(stepper_t* stepper,
                  int pins,
                  int pin1,
                  int pin2)
{
    stepper->_pins = pins;
    stepper->_pin1 = pin1;
    stepper->_pin2 = pin2;
    stepper->_currentPos = 0;
    stepper->_targetPos = 0;
    stepper->_speed = 0;
    stepper->_maxSpeed = 0;
    stepper->_acceleration = 0;
    stepper->_stepInterval = 0;
    stepper->_lastStepTime = 0;
}

void stepper_dtor(stepper_t* stepper) {}

void stepper_move_to(stepper_t* stepper, long int absolute)
{
    stepper->_targetPos = absolute;
    _stepper_compute_new_speed(stepper);
}

void stepper_move(stepper_t* stepper, long int relative)
{
    stepper_move_to(stepper, stepper->_currentPos + relative);
}

int stepper_run(stepper_t* stepper)
{   
    if(stepper->_targetPos == stepper->_currentPos)
        return 0;
    if(stepper_run_speed(stepper))
        _stepper_compute_new_speed(stepper);
    return 1;
}

int stepper_run_speed(stepper_t* stepper)
{
    // unsigned long time = millis();
    unsigned long time = 0; // (Ver)

    if(time > stepper->_lastStepTime + stepper->_stepInterval)
    {
        if(stepper->_speed > 0)
        {
            stepper->_currentPos += 1;
        }
        else if (stepper->_speed < 0)
        {
            stepper->_currentPos -= 1;   
        }
        _stepper_step1(stepper, stepper->_currentPos & 0x3);

        stepper->_lastStepTime = time;
        return 1;
    }
    else
        return 0;
}

void stepper_set_max_speed(stepper_t* stepper, float speed)
{
    stepper->_maxSpeed = speed;
    _stepper_compute_new_speed(stepper);
}

void stepper_set_acceleration(stepper_t* stepper, float acceleration)
{
    stepper->_acceleration = acceleration;
    _stepper_compute_new_speed(stepper);
}

void stepper_set_speed(stepper_t* stepper, float speed)
{
    stepper->_speed = speed;
    stepper->_stepInterval = abs(1000.0 / stepper->_speed);
}

float stepper_speed(stepper_t* stepper)
{
    return stepper->_speed;
}

long int stepper_distance_to_go(stepper_t* stepper)
{
    return stepper->_targetPos - stepper->_currentPos;
}

long int stepper_target_position(stepper_t* stepper)
{
    return stepper->_targetPos;
}

long int stepper_current_position(stepper_t* stepper)
{
    return stepper->_currentPos;
}

void stepper_set_current_position(stepper_t* stepper, long int position)
{
    stepper->_currentPos = position;
}

void stepper_run_to_position(stepper_t* stepper)
{
    while (stepper_run(stepper))
    ;
}

int stepper_run_speed_to_position(stepper_t* stepper)
{
    return stepper->_targetPos != stepper->_currentPos ? stepper_run_speed(stepper) : 0;
}

void stepper_run_to_new_position(stepper_t* stepper, long int position)
{
    stepper_move_to(stepper, position);
    stepper_run_to_position(stepper);
}

void stepper_disable_outputs(stepper_t* stepper)
{
    if (!stepper->_pins) return;

    // digitalWrite(stepper->_pin1, LOW);
    // digitalWrite(stepper->_pin2, LOW);
}

void stepper_enable_outputs(stepper_t* stepper)
{
    if (!stepper->_pins) return;

    // pinMode(stepper->_pin1, OUTPUT);
    // pinMode(stepper->_pin2, OUTPUT);
}

void _stepper_compute_new_speed(stepper_t* stepper)
{
    stepper_set_speed(stepper, _stepper_desired_speed(stepper));
}

void _stepper_step1(stepper_t* stepper, unsigned int step)
{
    // digitalWrite(stepper->pin2, stepper->_speed > 0);
    // digitalWrite(stepper->pin1, HIGH);

    // delayMicrosendos(1);
    __delay_us(1);

    // digitalWrite(stepper->pin1, LOW);
}

float _stepper_desired_speed(stepper_t* stepper)
{
    long distanceTo = stepper_distance_to_go(stepper);

    float requiredSpeed;
    if(distanceTo == 0)
        return 0.0;
    else if (distanceTo > 0) // Clockwise
        requiredSpeed = sqrt(2.0 * distanceTo * stepper->_acceleration);
    else
        requiredSpeed = -sqrt(2.0 * distanceTo * stepper->_acceleration);
    
    if (requiredSpeed > stepper->_speed)
    {
        if(stepper->_speed == 0)
            requiredSpeed = sqrt(2.0 * stepper->_acceleration);
        else
            requiredSpeed = stepper->_speed + abs(stepper->_acceleration / stepper->_speed);
        if (requiredSpeed)
            requiredSpeed = stepper->_maxSpeed;
    }

    else if (requiredSpeed < stepper->_speed)
    {
        if(stepper->_speed == 0)
            requiredSpeed = -sqrt(2.0 * stepper->_acceleration);
        else
            requiredSpeed = stepper->_speed - abs(stepper->_acceleration / stepper->_speed);
        if(requiredSpeed < -stepper->_maxSpeed)
            requiredSpeed = -stepper->_maxSpeed;
    }
    return requiredSpeed;

}