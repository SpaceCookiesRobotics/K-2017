#pragma config(Motor,  port1,           middleleft,    tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           twoleft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           tworight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           lift,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           dr4b1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           dr4b2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           dr4b3,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           dr4b4,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          middleright,   tmotorVex393_HBridge, openLoop, reversed)

int turnvar = 1;
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

void turn (int speed) {
	setleft (turnvar*speed);
	setright (-1*turnvar*speed);
}

void auton () {
	turn (1);
	wait1Msec (2000);
	vertical (100);
	wait1Msec (400);
	turn (1);
	wait1Msec (2000);
	turn (-1);
	wait1Msec (2000);
	vertical (100);
	wait1Msec (1000);
	motor [lift] = -100;
	wait1Msec (500);
	motor [lift] = 100;
	wait1Msec (1000);
  vertical (50);
  wait1Msec (500);
  vertical (-100);
  wait1Msec (1100);
  turn (-1);
  wait1Msec (1300);
  vertical (127);
  wait1Msec (3200);
}

	task main () {
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
			motor[claw] = vexRT[Ch3Xmtr2]/slowdown;
			// DR4B motors
			motor[dr4b1] = vexRT[Ch3Xmtr2]/slowdown;
			motor[dr4b2] = vexRT[Ch3Xmtr2]/slowdown;
			motor[dr4b3] = vexRT[Ch3Xmtr2]/slowdown;
			motor[dr4b4] = vexRT[Ch3Xmtr2]/slowdown;
		}
	}
