#pragma config(Motor,  port1,           middleleft,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           twoleft,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           tworight,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           lift,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           dr4b1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           dr4b2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           dr4b3,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           dr4b4,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          middleright,   tmotorVex393_HBridge, openLoop, reversed)

#include "../Shared/Competition.h"

void setleft (int speed) {
	motor[middleleft]=speed;
	motor[twoleft]=speed;
}

void setright (int speed) {
	motor[middleright]=speed;
	motor[tworight]=speed;
	}

void vertical (int speed) {
	setleft (speed);
	setright (speed);
}

void turnleft (int speed) {
	setleft (-1*speed);
	setright (speed); }

void turnright (int speed) {
	setleft (speed);
	setright (-1*speed); }

void dr4blift (int speed) { //1 is up, -1 is down
	motor[dr4b1]=speed;
	motor[dr4b2]=speed;
	motor[dr4b3]=speed;
	motor[dr4b4]=speed;
}

void autonomous () {
	dr4blift (-127);
	wait1Msec (300);
	motor[claw]=-127;  //close claw, grab cone
	dr4blift (127);  //dr4b up
	vertical (127);
	wait1Msec (600);
	motor[claw]=0;
	turnleft (127);
	wait1Msec (600);
	vertical (127);  //go forward quickly
	wait1Msec (390);
	vertical (-127); //backward quickly
	wait1Msec (500);
	turnright (127);
	wait1Msec (730);
	vertical (127); //forward until mobile goal lift
	wait1Msec (500);
	dr4blift (0);
	wait1Msec (1800);
	motor[claw]= 0;
	vertical (0);
	dr4blift (-60); //dr4b down
	wait1Msec (1250);
	dr4blift (0);
	motor[claw]=127;  //open claw, release cone
	wait1Msec (700);
	motor[claw]= 0;
	dr4blift (127); //move dr4b up slightly
	wait1Msec (500);
	vertical (40);
	wait1Msec (200);
	motor[lift]=60;
	wait1Msec (100);
	turnright (100);
	wait1Msec (1700);
	vertical (127);
	wait1Msec (2000);
	/*vertical (120);
	wait1Msec (1600);
	vertical (30);
	wait1Msec (650);
	motor[lift]=50;
	wait1Msec (100);
	vertical (20);
	wait1Msec (100);
	turnleft (100);
	wait1Msec (1050);
	vertical (120);
	wait1Msec (1700);
	vertical (-120);
	wait1Msec (1400);
	turnleft (120);
	wait1Msec (300);
	vertical (127);
	wait1Msec (2000);
	motor[lift]=30;
	wait1Msec (20);
	turnleft (50);
	wait1Msec (200);
	vertical (120);
	wait1Msec (1400);
	motor[lift]=-50;
	wait1Msec (100);
	vertical (-127);
	wait1Msec (2200);
//	motor[lift]=-60;
//	wait1Msec (300);
//	turnright (120);
//	wait1Msec (200); */
	}

void joystick () {
int joy_x;            // will hold the X value of the analog stick (choices below)
int joy_y;            // will hold the Y value of the analog stick (choices below)
int slowbutton = vexRT[Btn5U];       // either 0 or 1 (pressed or not pressed)
int slowdown;

while(1 == 1) {
	joy_x = vexRT[Ch4];   // This is the left analog stick.
	joy_y = vexRT[Ch3];
	if (slowbutton == 0) {  // If slowbutton is pressed, speed decreases by 5. If not, it stays the same.
		slowdown = 1;
	}
	if (slowbutton == 1) {
		slowdown = 5;
	}
	setleft ((joy_y + joy_x)/slowdown);
	setright ((joy_y - joy_x)/slowdown);

	// Mobile Goal Lift motor
	motor[lift] = vexRT[Ch2]/slowdown;
	// DR4B Claw[
	motor[claw] = vexRT[Ch3Xmtr2]/2;
	// DR4B motors
	motor[dr4b1] = vexRT[Ch2Xmtr2]/slowdown;
	motor[dr4b2] = vexRT[Ch2Xmtr2]/slowdown;
	motor[dr4b3] = vexRT[Ch2Xmtr2]/slowdown;
	motor[dr4b4] = vexRT[Ch2Xmtr2]/slowdown;
	if (vexRT[Btn5UXmtr2] == 1) { //button to raise dr4b to height of preload
		dr4blift (100);
		wait1Msec (220); }
}
}
