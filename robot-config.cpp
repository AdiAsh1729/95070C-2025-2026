#include "vex.h"
#include "robot-config.hpp"
using namespace vex;
using signature = vision::signature;
using code = vision::code;


brain Brain;
controller Controller;


motor FL = motor(PORT4, ratio6_1, true);
motor ML = motor(PORT7, ratio6_1, true);
motor BL = motor(PORT2, ratio6_1, true);
motor_group LeftDrive = motor_group(FL, ML, BL);
motor FR = motor(PORT5, ratio6_1, false);
motor MR = motor(PORT6, ratio6_1, false);
motor BR = motor(PORT3, ratio6_1, false);
motor_group RightDrive = motor_group(FR, MR, BR);

motor Intake1 = motor(PORT1, ratio18_1, true);
motor Intake2 = motor(PORT16, ratio18_1, false);
motor_group Intake = motor_group(Intake1, Intake2);

digital_out StickyStickyBoom = digital_out(Brain.ThreeWirePort.C);
digital_out Park1 = digital_out(Brain.ThreeWirePort.B);
//digital_out Park2 = digital_out(Brain.ThreeWirePort.B);
digital_out MiddleGoal = digital_out(Brain.ThreeWirePort.A);

inertial Inertial = inertial(PORT8);
rotation Rotation = rotation(PORT22, true);

void vexcodeInit(void);
