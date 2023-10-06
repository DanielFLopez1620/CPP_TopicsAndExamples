/*
Original Code from the AccelStepper library for Arduino in C++
https://github.com/adafruit/AccelStepper/tree/master
It was adapted by DanielFLopez1620 to a C alike program as an example for the lesson.
*/

#ifndef STEPPER_H
#define STEPPER_H

struct stepper_h;

struct stepper_t* stepper_new();

void stepper_ctor(struct stepper_t*,
                  int pins,
                  int pin1,
                  int pin2);

void stepper_dtor(struct stepper_t*);

void stepper_move_to(struct stepper_t*, long int);

void stepper_move(struct stepper_t*, long int);

int stepper_run(struct stepper_t*);

int stepper_run_speed(struct stepper_t*);

void stepper_set_max_speed(struct stepper_t*, float);

void stepper_set_acceleration(struct stepper_t*, float);

void stepper_set_speed(struct stepper_t*, float);

float stepper_speed(struct stepper_t*);

long int stepper_distance_to_go(struct stepper_t*);

long int stepper_target_position(struct stepper_t*);

long int stepper_current_position(struct stepper_t*);

void stepper_set_current_position(struct stepper_t*, long int position);

void stepper_run_to_position(struct stepper_t*);

int stepper_run_speed_to_position(struct stepper_t*);

void stepper_run_to_new_position(struct stepper_t*, long int);

void stepper_disable_outputs(struct stepper_t*);

void stepper_enable_outputs(struct stepper_t*);

void _stepper_compute_new_speed(struct stepper_t*);

void _stepper_step1(struct stepper_t*, unsigned int);

float _stepper_desired_speed(struct stepper_t*);


#endif