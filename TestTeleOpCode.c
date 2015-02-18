#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorR,         sensorNone)
#pragma config(Sensor, S3,     colorL,         sensorNone)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          hook,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    liftLow,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    liftHigh,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    collector,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_6,    trapDoor,             tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
//#include "hitechnic-gyro.h"
#include "7391RobotDriver.c"
#include "ArmDriver.c"

#define COMPETITION

TArmState tas;

const int PowerMaxTurn = 80;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	driveInit();
	armInit(tas);// Place code here to initialize servos to starting positions.
	setPosition(tas, POS_DRIVE, DEFAULT_DISTANCE);
	//wait10Msec(500);
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//const int LOW_MOTOR_THRESH = 15;
const int LOW_MOTOR_THRESH = 25;
const int TURBO_BUTT  = 6;
const int  X_BUTT  = 1;
const int B_BUTT  = 3;
const int A_BUTT  = 2;
const int Y_BUTT  = 4;


void joystick2Move(int powerThresh);


task main()
{
	const int IS_PRESSED = 1;
	//const int IS_NOT_PRESSED = 0;

#ifdef COMPETITION
	waitForStart();   // wait for start of tele-op phase
	initializeRobot();
#else

#endif

	while (true)

	{
		//motor[motorL] = 30;
		//motor[motorR] = 30;
		if(joy1Btn(TURBO_BUTT) == IS_PRESSED){
			joystick2Move(40);
		}
		else{
			joystick2Move(15);
		}

		if(joy2Btn(A_BUTT) == IS_PRESSED){
			setPosition(tas, POS_AT_30CM, DEFAULT_DISTANCE);
			if(joystick.joy1_TopHat == 0){
				incDistance(tas);
			}
			else if(joystick.joy1_TopHat == 4){
				decDistance(tas);
			}
		}
		else if(joy2Btn(B_BUTT) == IS_PRESSED){
			setPosition(tas, POS_AT_60CM,DEFAULT_DISTANCE);
			if(joystick.joy1_TopHat == 0){
				incDistance(tas);
			}
			else if(joystick.joy1_TopHat == 4){
				decDistance(tas);
				//setPosition(tas, 2, distance);
			}
		}
		else if(joy2Btn(X_BUTT) == IS_PRESSED){
				setPosition(tas, POS_AT_90CM, DEFAULT_DISTANCE);
			if(joystick.joy1_TopHat == 0){
				incDistance(tas);
			}
			else if(joystick.joy1_TopHat == 4){
				decDistance(tas);
			}
		}
		else if(joy2Btn(Y_BUTT) == IS_PRESSED){

			//int distance = 0;
			setPosition(tas, POS_AT_120CM, DEFAULT_DISTANCE);
			if(joystick.joy1_TopHat == 0){
				incDistance(tas);
			}
			else if(joystick.joy1_TopHat == 4){
				decDistance(tas);
			}
		}
		if(joy2Btn(TURBO_BUTT)==IS_PRESSED){
			collectorIn();
		}
		else if(joy2Btn(5)==IS_PRESSED){
			collectorOut();
		}
		else if(joy2Btn(TURBO_BUTT)== 0 && joy2Btn(5) == 0){
			collectorStop();
		}
		if(joy2Btn(8)==IS_PRESSED){
			setPosition(tas, POS_BALL_COLLECTING, DEFAULT_DISTANCE);
		}
		else if(joy2Btn(7) == IS_PRESSED){
			setPosition(tas, POS_DRIVE, DEFAULT_DISTANCE);
		}
		if(joystick.joy2_TopHat == 2){
				trapDoorOpen();
		}
		if(joystick.joy2_TopHat == 6){
				trapDoorClose();
		}

	}
}

void joystick2Move(int powerThresh){
	if(abs(joystick.joy1_y1)<LOW_MOTOR_THRESH && abs(joystick.joy1_x2)<LOW_MOTOR_THRESH){
		motor[motorL] = 0;
		motor[motorR] = 0;
}
	else if(joystick.joy1_y1>LOW_MOTOR_THRESH){
		//motor[motorL] = (joystick.joy1_y1*powerThresh)/127;
		//motor[motorR] = (joystick.joy1_y1*powerThresh)/127;
		if(abs(joystick.joy1_x2) < LOW_MOTOR_THRESH){
			int val = (joystick.joy1_y1*powerThresh)/127;
								writeDebugStreamLine("power %d",val);


			motor[motorR] = (joystick.joy1_y1*powerThresh)/127;
			motor[motorL] = (joystick.joy1_y1*powerThresh)/127;
		}
		else if(joystick.joy1_x2 > LOW_MOTOR_THRESH){
			motor[motorL] = ((joystick.joy1_y1-joystick.joy1_x2)*75)/127;
			motor[motorR] = (joystick.joy1_y1*75)/127;
		}
		else if(joystick.joy1_x2 < -LOW_MOTOR_THRESH){
			motor[motorR] = ((joystick.joy1_y1+joystick.joy1_x2)*75)/127;
			motor[motorL] = (joystick.joy1_y1*75)/127;
		}
	}

	else if(joystick.joy1_y1< -LOW_MOTOR_THRESH){
	//	motor[motorL] = (joystick.joy1_y1*powerThresh)/127;
		//motor[motorR] = (joystick.joy1_y1*powerThresh)/127;
		if(abs(joystick.joy1_x2) < LOW_MOTOR_THRESH){
			motor[motorL] = (joystick.joy1_y1*powerThresh)/127;
			motor[motorR] = (joystick.joy1_y1*powerThresh)/127;
		}
		else if(joystick.joy1_x2 > LOW_MOTOR_THRESH){
			motor[motorL] = ((joystick.joy1_y1+joystick.joy1_x2)*70)/127;
			motor[motorR] = (joystick.joy1_y1*70)/127;
		}
		else if(joystick.joy1_x2 < -LOW_MOTOR_THRESH){
			motor[motorR] = ((joystick.joy1_y1-joystick.joy1_x2)*70)/127;
			motor[motorL] = (joystick.joy1_y1*70)/127;
		}
	}
	else if(joystick.joy1_x2>LOW_MOTOR_THRESH){
		motor[motorL] = -(joystick.joy1_x2*70)/127;
		motor[motorR] = (joystick.joy1_x2*70)/127;
	}
	else if(joystick.joy1_x2<-LOW_MOTOR_THRESH){
		motor[motorR]  = (joystick.joy1_x2*70)/127;
		motor[motorL] = -(joystick.joy1_x2*70)/127;
	}
}
