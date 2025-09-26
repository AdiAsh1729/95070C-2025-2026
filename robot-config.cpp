#include "vex.h"
#include "robot-config.hpp"
using namespace vex;
using signature = vision::signature;
using code = vision::code;


brain Brain;
controller Controller;


motor FL = motor(PORT10, ratio6_1, true);
motor ML = motor(PORT14, ratio6_1, true);
motor BL = motor(PORT13, ratio6_1, true);
motor_group LeftDrive = motor_group(FL, ML, BL);
motor FR = motor(PORT1, ratio6_1, false);
motor MR = motor(PORT17, ratio6_1, false);
motor BR = motor(PORT18, ratio6_1, false);
motor_group RightDrive = motor_group(FR, MR, BR);

motor Intake1 = motor(PORT8, ratio18_1, true);
motor Intake2 = motor(PORT11, ratio18_1, false);
motor_group Intake = motor_group(Intake1, Intake2);

digital_out Park1 = digital_out(Brain.ThreeWirePort.A);
digital_out Park2 = digital_out(Brain.ThreeWirePort.A);
digital_out MP = digital_out(Brain.ThreeWirePort.H);
digital_out Load = digital_out(Brain.ThreeWirePort.B);
digital_out Bunny = digital_out(Brain.ThreeWirePort.G);

inertial Inertial = inertial(PORT16);
rotation Rotation = rotation(PORT22, true);

void vexcodeInit(void);
