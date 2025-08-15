#include "vex.h"
#include "auton.h"
#include <iostream>
#include <cstdlib>
using namespace vex;
#include "robot-config.hpp"

double correctionPID(double currentheading) {
    double kp = 0.3; //testvalue
    double kd = 0; //testvalue 
    double error = geterror(0);
    double perror = error;
    double d = 0;
    double total = 0;

    Inertial.setHeading(0, deg);
    if(fabs(error) > 1) {
        error = geterror(0);
        d = (error - perror) * 50;
        total = error * kp - d * kd;
        
        perror = error;

        wait(20, msec);
    }
    
    return total;
}

void MoveDrivetrain() {
    double TempSpeed = 1;

    if (((FL.temperature(temperatureUnits::fahrenheit)) >= 131) || ((ML.temperature(temperatureUnits::fahrenheit)) >= 131) || 
    ((BL.temperature(temperatureUnits::fahrenheit)) >= 131) || ((FR.temperature(temperatureUnits::fahrenheit)) >= 131) || 
    ((MR.temperature(temperatureUnits::fahrenheit)) >= 131) || ((BR.temperature(temperatureUnits::fahrenheit)) >= 131)) {
      TempSpeed = 0.13;
    }
    else if (((FL.temperature(temperatureUnits::fahrenheit)) > 90) || ((ML.temperature(temperatureUnits::fahrenheit)) > 90) || 
    ((BL.temperature(temperatureUnits::fahrenheit)) > 90) || ((FR.temperature(temperatureUnits::fahrenheit)) > 90) || 
    ((MR.temperature(temperatureUnits::fahrenheit)) > 90) || ((BR.temperature(temperatureUnits::fahrenheit)) > 90)) {
      TempSpeed = 0.66;
    }
    else {
      TempSpeed = 1;
    }
    
    double DriveSpeed = (Controller.Axis3.position()) * 0.99 * TempSpeed;
    double TurnSpeed = (Controller.Axis1.position()) * 0.99 * TempSpeed;
    double LeftSpeed = 0;
    double RightSpeed = 0;
    double currentheading = Inertial.heading(deg);

    if((LeftDrive.velocity(pct) > 0 && RightDrive.velocity(pct) == 0) || (RightDrive.velocity(pct) > 0 && LeftDrive.velocity(pct) == 0)) {
        LeftSpeed = 0;
        RightSpeed = 0;
    }
    else {
        LeftSpeed = DriveSpeed - TurnSpeed + correctionPID(currentheading);
        RightSpeed = DriveSpeed + TurnSpeed - correctionPID(currentheading);
    }
    LeftDrive.spin(forward, LeftSpeed, pct);
    RightDrive.spin(forward, RightSpeed, pct);
}

void MoveIntake() {
    if(Controller.ButtonR1.pressing()) {
        Store.spin(reverse, 12, volt);
        Intake1.spin(forward, 12, volt);
        Intake2.spin(reverse, 12, volt);
        Intake3.spin(forward, 12, volt);
    }

    if(Controller.ButtonL1.pressing()) {
        Store.spin(reverse, 12, volt);
        Intake1.spin(forward, 12, volt);
        Intake2.spin(reverse, 12, volt);
        Intake3.spin(reverse, 12, volt);
    }

    if(Controller.ButtonR2.pressing()){
        Store.spin(forward, 12, volt);
        Intake1.spin(forward, 12, volt);
        Intake2.spin(forward, 12, volt);
    }

    if(Controller.ButtonL2.pressing()) {
        Store.spin(reverse, 12, volt);
        Intake1.spin(reverse, 12, volt);
        Intake2.spin(reverse, 12,  volt);
    }

    if(Controller.ButtonB.pressing()) {
        Store.stop();
        Intake1.stop();
        Intake2.stop();
        Intake3.stop();
    }
}

void MoveTopScorer() {
    static int tspressed = 0;
    tspressed += 1;

    if(tspressed%2 == 0) {
        PL.set(true);
    }

    else if(tspressed%2 == 1) {
        PL.set(false);
    }
}

void drivercontrol() {
    while(true){
      MoveDrivetrain();
      MoveIntake();
      Controller.ButtonY.pressed(MoveTopScorer);
      wait(20, msec);
    }
}

void vexcodeInit();
