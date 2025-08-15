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

extern motor Store;
extern motor Intake1;
extern motor Intake2;
extern motor Intake3;

extern digital_out PL;

extern inertial Inertial;

void vexcodeInit(void);
