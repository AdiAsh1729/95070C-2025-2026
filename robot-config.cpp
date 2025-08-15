#include "vex.h"
#include "robot-config.hpp"
using namespace vex;
using signature = vision::signature;
using code = vision::code;


brain Brain;
controller Controller;


motor FL = motor(PORT1, ratio6_1, false);
motor ML = motor(PORT3, ratio6_1, false);
motor BL = motor(PORT15, ratio6_1, false);
motor_group LeftDrive = motor_group(FL, ML, BL);
motor FR = motor(PORT16, ratio6_1, true);
motor MR = motor(PORT19, ratio6_1, true);
motor BR = motor(PORT17, ratio6_1, true);
motor_group RightDrive = motor_group(FR, MR, BR);

motor Store = motor(PORT18, ratio6_1, true);
motor Intake1 = motor(PORT14, ratio18_1, false);
motor Intake2 = motor(PORT10, ratio18_1, false);
motor Intake3 = motor(PORT11, ratio18_1, false);

digital_out PL = digital_out(Brain.ThreeWirePort.A);

inertial Inertial = inertial(PORT11);

void vexcodeInit(void);
