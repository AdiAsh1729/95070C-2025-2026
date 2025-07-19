#pragma once
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

void vexcodeInit(void);
