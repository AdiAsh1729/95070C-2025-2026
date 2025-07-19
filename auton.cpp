#include "vex.h"
#include <iostream>
#include "auton.h"
#include "robot-config.hpp"

static void drivePID(double kp, double ki, double kd, double target) {
    double lefterror = target;
    double plefterror = lefterror;
    double leftd = 0;
    double lefti = 0;
    double reallefti = 0;
    double plefttotal = 0;
    double lefttotal = 0;
    double leftsaturation = 0;
    double leftsign = 0;

    double righterror = target;
    double prighterror = righterror;
    double rightd = 0;
    double righti = 0;
    double realrighti = 0;
    double prighttotal = 0;
    double righttotal = 0;
    double rightsaturation = 0;
    double rightsign = 0;
    
    LeftDrive.resetPosition();
    RightDrive.resetPosition();
    
    while((fabs(lefterror) + fabs(righterror)) / 2 > 0.5) {
        lefterror = target - LeftDrive.position(turns) * 3.25 * M_PI * 0.75;
        righterror = target - RightDrive.position(turns) * 3.25 * M_PI * 0.75;
        
        leftd = (lefterror - plefterror) * 40;
        rightd = (righterror - prighterror) * 40;
        
        lefttotal = lefterror * kp + lefti * ki - leftd * kd;
        righttotal = righterror * kp + righti * ki - rightd * kd;

        if(plefttotal == lefttotal) {
            leftsaturation = 0;
        }
        else {
            leftsaturation = 1;
        }
        if((plefttotal < 0) && (lefttotal < 0)) {
            leftsign = -1;
        }
        else {
            leftsign = 1;
        }

        if(prighttotal == righttotal) {
            rightsaturation = 0;
        }
        else {
            rightsaturation = 1;
        }
        if((plefttotal < 0) && (lefttotal < 0)) {
            rightsign = -1;
        }
        else {
            rightsign = 1;
        }

        LeftDrive.spin(forward, lefttotal, pct);
        RightDrive.spin(forward, righttotal, pct);

        if((leftsaturation == 1) || (leftsign == 1 )) {
            lefti = 0;
        }
        else {
           lefti = reallefti; 
        }
        if(fabs(lefterror) < 10) {
            reallefti += lefterror / 50;
        }
        
        if((rightsaturation == 1) || (rightsign == 1 )) {
            righti = 0;
        }
        else {
          righti = realrighti;  
        }
        if(fabs(righterror) < 10) {
            realrighti += righterror / 50;
        }

        plefterror = lefterror;
        prighterror = righterror;

        wait(20, msec);
    }

    LeftDrive.stop(brake);
    RightDrive.stop(brake);

    wait(100, msec);
}

static double geterror(double target) {
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

static void turnPID(double kp, double ki, double kd, double tolerance, double target) {
    double error = geterror(target);
    double perror = error;
    double d = 0;
    double i = 0;
    double reali = 0;
    double ptotal  = 0;
    double total = 0;
    double saturation = 0;
    double sign = 0;

    while(fabs(error) > tolerance || (d > 3)) {
        error = geterror(target);
        d = (error - perror) * 40;
        ptotal = total;
        total = error * kp + i * ki - d * kd;
        if(ptotal == total) {
            saturation = 0;
        }
        else {
            saturation = 1;
        }
        if((ptotal < 0) && (total < 0)) {
            sign = -1;
        }
        else {
            sign = 1;
        }
        
        LeftDrive.spin(forward, total, pct);
        RightDrive.spin(reverse, total, pct);

        if((saturation == 1) && (sign == 1)) {
            i = 0;
        }
        else {
            i = reali;
        }
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
        drivePID(1.75, 0.001, 0.775, target);
    }

    if(direction == "reverse") {
        drivePID(1.75, 0.001, 0.775, -target);
    }
}

void slowdrive(std::string direction, double target) {
    if(direction == "forward") {            
        drivePID(1.3, 0.001, 0.75, target);
    }

    if(direction == "reverse") {
        drivePID(1.3, 0.001, 0.75, -target);
    }
}

void turn(double target) {
    turnPID(0.4, 0.002, 0, 1, target);
}

void slowturn(double target){
    turnPID(0.3, 0.002, 0, 1, target);
}

void DrivePID_Test() {
    drive(0);
}

void TurnPID_UnitTest() {
    turn(0);
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
