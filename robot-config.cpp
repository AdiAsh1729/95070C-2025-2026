#include "vex.h"
#include "robot-config.hpp"
using namespace vex;
using signature = vision::signature;
using code = vision::code;


brain Brain;
controller Controller;


motor FL = motor(PORT2, ratio6_1, true);
motor ML = motor(PORT1, ratio6_1, false);
motor BL = motor(PORT10, ratio6_1, true);
motor_group LeftDrive = motor_group(FL, ML, BL);
motor FR = motor(PORT8, ratio6_1, false);
motor MR = motor(PORT19, ratio6_1, true);
motor BR = motor(PORT4, ratio6_1, false);
motor_group RightDrive = motor_group(FR, MR, BR);

void vexcodeInit(void);
