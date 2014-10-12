#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorR,         sensorCOLORFULL)
#pragma config(Sensor, S3,     colorL,         sensorCOLORFULL)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorB,          grabL,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          grabR,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    liftLow,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    liftHigh,             tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Motor,  motorB,          motorL,     tmotorNXT, openLoop, encoder)
//#pragma config(Motor,  motorC,          motorR,    tmotorNXT, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
TFileHandle hFileHandle;
TFileIOResult nIoResult;
char sOutput[100];

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "7391RobotDriver.c" //Include file of Robot Drivers.
#include "7391AutoUtils.c" //Include file of Autonomous Utilities


int side = LEFT;
//int side = RIGHT;
int color = REDCOLOR;
//int color = REDCOLOR;
//const int DELAY = 10; //seconds
const int DELAY = 0;

#define IR_LEFT 2
#define IR_RIGHT 8

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	string sFileName = "debug.txt";
	int nFileSize =10000;



	eraseDisplay();
	nxtDisplayTextLine(0, "Autonomous Period");

	Delete(sFileName,nIoResult);
	OpenWrite(hFileHandle, nIoResult, sFileName, nFileSize);
	WriteText(hFileHandle, nIoResult, "Autonomous Period\n");

	nPidUpdateInterval = 20;

	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;

	servoChangeRate[liftHigh] = 1;
	servoChangeRate[liftLow] = 1;

	liftBottom();

	wait1Msec(10);

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

	waitForStart(); // Wait for the beginning of autonomous phase.


	//_______________________________________________________________________________________________________________________
	time100[1] = 0;

	liftBasket();

	wait10Msec(DELAY*100); //wait for other side

	float distance;
	//nxtDisplayTextLine(1, "here 21" );
	//while (nNxtButtonPressed != kLeftButton){}
	if (LEFT == side)
		distance = findBeacon(IR_LEFT);

	else //if (RIGHT == side)
		distance = findBeacon(IR_RIGHT);

	//nxtDisplayTextLine(1, "here 22" );
	//while (nNxtButtonPressed != kEnterButton){}

	dropNramp(side, distance, color);

	Close(hFileHandle, nIoResult);
}
