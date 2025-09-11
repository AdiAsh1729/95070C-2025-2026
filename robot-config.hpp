#pragma once
#include "vex.h"
using namespace vex;

extern brain Brain;
extern controller Controller;

extern motor FL;
extern motor ML;
extern motor BL;
extern motor_group LeftDrive;
extern motor FR;
extern motor MR;
extern motor BR;
extern motor_group RightDrive;

extern motor Intake1;
extern motor Intake2;
extern motor_group Intake;

extern digital_out MP;
extern digital_out Park;
extern digital_out Park_two;
extern digital_out_group Park_group

extern inertial Inertial;
extern rotation Rotation;

void vexcodeInit(void);
