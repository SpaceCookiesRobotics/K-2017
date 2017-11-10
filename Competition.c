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

void vertical (int speed, int turnvar) {
	setleft (speed*turnvar);
	setright (speed*turnvar);
}

void turn (int speed, int turnvar) { //-1 is left, 1 is right
	setleft (turnvar*speed);
	setright (-1*turnvar*speed);
}

void dr4blift (int speed, int direct) { //1 is up, -1 is down
	motor[dr4b1]=speed*direct;
	motor[dr4b2]=speed*direct;
	motor[dr4b3]=speed*direct;
	motor[dr4b4]=speed*direct;
}

void autonomous () { //goes to left of field, picks up mobile goal, and deposits in 10 pt zone
	dr4blift (60, 1);  //dr4b up
	wait1Msec (60);
	dr4blift (0, 1);

	vertical (127, 1); //forward till mobile goal lift
	wait1Msec (3200);
	vertical (0, 1);

	dr4Blift (60, -1); //dr4b down

	motor[claw]=100;  //open claw, release cone
	wait1Msec (5);
	motor[claw]0;

	vertical (127, -1);
	wait1Msec (200);
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
	// DR4B Claw
	motor[claw] = vexRT[Ch3Xmtr2]/2;
	// DR4B motors
	motor[dr4b1] = vexRT[Ch2Xmtr2]/slowdown;
	motor[dr4b2] = vexRT[Ch2Xmtr2]/slowdown;
	motor[dr4b3] = vexRT[Ch2Xmtr2]/slowdown;
	motor[dr4b4] = vexRT[Ch2Xmtr2]/slowdown;
}
}
