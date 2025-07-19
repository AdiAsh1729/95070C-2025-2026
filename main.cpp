#include "vex.h"
#include "driver-control.hpp"
#include <iostream>
#include "auton.h"
#include <cstdlib>
#include "robot-config.hpp"
using namespace vex;
using signature = vision::signature;
using code = vision::code;


competition Competition;
bool inauton = false;


void vexcodeInit() {

}

int autons = 11;
int displayautons = 0;

void select(){
  while(1) {
    if (Controller.ButtonRight.pressing()) {
      displayautons++;
    }
    
    if (Controller.ButtonLeft.pressing()) {
      displayautons--;
    }

    if (Controller.ButtonA.pressing()) {
      wait(1000, msec);
      if (Controller.ButtonA.pressing()) {
        Controller.rumble(rumbleLong);
        break;
      }
    }
    
    if (displayautons > autons) {
      displayautons = 0;
    }

    if (displayautons < 0) {
      displayautons = autons;
    }

    if (displayautons == 0) {
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("Please select an auton");
    }

    if (displayautons == 1){
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("DrivePID_Test");
    }

    if (displayautons == 2){
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("TurnPID_Test");
    }
    
    if (displayautons == 3){
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("AWPRed");
    }
    
    if (displayautons == 4){
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("AWPBlue");
    }
    
    if (displayautons == 5){
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("Red");
    }
    
    if (displayautons == 6){
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("Blue");
    }

    if (displayautons == 7){
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("GoalRushRed");
    }

    if (displayautons == 8){
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("GoalRushBlue");
    }

    if (displayautons == 9){
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("AutonSkills");
    }

  }
}

void pre_auton(void) {
  
  select();
  vexcodeInit();

}

void autonomous(void) {
  
  inauton = true;
  
  if(displayautons == 1) {
    drivePID_Test();
  }

  if(displayautons == 2) {
    TurnPID_Test();
  }

  if(displayautons == 3) {
    AWPRed();
  }
  
  if(displayautons == 4) {
    AWPBlue();
  }
  
  if(displayautons == 5) {
    Red();
  }
  
  if(displayautons == 6) {
    Blue();
  }

  if(displayautons == 7) {
    GoalRushRed();
  }

  if(displayautons == 8) {
    GoalRushBlue();
  }

  if(displayautons == 9) {
    AutonSkills();
  }
  
  inauton=false;

}

int main() {
  Competition.drivercontrol(drivercontrol);
  Competition.autonomous(autonomous);

  pre_auton();
  
  while(1) {
    wait(20, msec);
  }
  void vexcodeInit(void);

}
