#include "vex.h"
#include <iostream>
#include "auton.h"
#include "robot-config.hpp"

void drivePID(double kp, double ki, double kd, double target) {
    double lefterror = target;
    double plefterror = lefterror;
    double leftd = 0;
    double lefti = 0;
    double lefttotal = 0;

    double righterror = target;
    double prighterror = righterror;
    double rightd = 0;
    double righti = 0;
    double righttotal = 0;
    
    LeftDrive.resetPosition();
    RightDrive.resetPosition();
    
    while((fabs(lefterror) + fabs(righterror)) / 2 > 0.1) {
        lefterror = target - LeftDrive.position(turns) * 3.25 * M_PI * 0.75;
        righterror = target - RightDrive.position(turns) * 3.25 * M_PI * 0.75;
         
        leftd = (lefterror - plefterror) * 50;
        rightd = (righterror - prighterror) * 50;
        
        lefttotal = lefterror * kp + lefti * ki + leftd * kd;
        righttotal = righterror * kp + righti * ki + rightd * kd;

        LeftDrive.spin(forward, lefttotal, pct);
        RightDrive.spin(forward, righttotal, pct);
        std::cout << LeftDrive.position(turns) * 3.25 * M_PI * 0.75 << ", " << RightDrive.position(turns) * 3.25 * M_PI * 0.75 << ", " << LeftDrive.velocity(pct) << ", " << RightDrive.velocity(pct) << "\n";

        if(fabs(lefterror) < 10) {
            lefti += lefterror/50;
        }
        
        if(fabs(righterror) < 10) {
            righti += righterror/50;
        }

        plefterror = lefterror;
        prighterror = righterror;

        wait(20, msec);
    }

    LeftDrive.stop(brake);
    RightDrive.stop(brake);

    wait(100, msec);
}

double geterror(double target) {
    if((std::max(target, Inertial.heading()) - std::min(target, Inertial.heading())) > 180) {
        if(std::min(target, Inertial.heading()) == target) {
            return (360 - std::max(target, Inertial.heading()) + std::min(target, Inertial.heading()));
        }
        else {
            return -(360 - std::max(target, Inertial.heading()) + std::min(target, Inertial.heading()));
        }
    }
    else {
        return (target - Inertial.heading());
    }
}

void turnPID(double kp, double ki, double kd, double tolerance, double target) {
    double error = geterror(target);
    double perror = error;
    double d = 0;
    double i = 0;
    double total = 0;

    Inertial.setHeading(0, deg);
    while(fabs(error) > tolerance) {
        error = geterror(target);
        d = (error - perror) * 50;
        total = error * kp + i * ki - d * kd;
        
        LeftDrive.spin(forward, total, pct);
        RightDrive.spin(reverse, total, pct);

        if(fabs(error) < 20) {
            i += error/50;
        }
        
        perror = error;

        wait(20, msec);
    }

    LeftDrive.stop(brake);
    RightDrive.stop(brake);

    wait(100, msec);
}

void drive(std::string direction, double target) {
    if(direction == "forward") {            
        drivePID(1.8, 0, 0, target);
    }

    if(direction == "reverse") {
        drivePID(0, 0, 0, -target);
    }
}

void slowdrive(std::string direction, double target) {
    if(direction == "forward") {            
        drivePID(1.3, 0.00, 0.66, target);
    }

    if(direction == "reverse") {
        drivePID(1.3, 0.00, 0.66, -target);
    }
}

void turn(double target) {
    turnPID(0.397, 0.002, 0, 1, target);
}

void slowturn(double target){
    turnPID(0.3, 0.002, 0, 1, target);
}

void DrivePID_Test() {
    drive("forward", 24);
}

void TurnPID_Test() {
    turn(180);
}

void AWPRed() {
    
}

void AWPBlue() {
    
}

void Red() {

}

void Blue() {
    
}

void GoalRushRed() {
    
}

void GoalRushBlue() {
    
}

void AutonSkills() {

}
