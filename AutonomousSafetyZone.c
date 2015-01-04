#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorR,         sensorNone)
#pragma config(Sensor, S3,     colorL,         sensorNone)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorB,          grabL,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          grabR,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    liftLow,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    liftHigh,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    scoop,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "ArmDriver.c" //Include file of Robot Drivers.

#define COMPETITION
#define RAMP 1
//#define DEBUG

TArmState tas;

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

#ifdef COMPETITION
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#endif

#include "7391RobotDriver.c" //Include file of Robot Drivers.
#include "7391AutoUtils.c" //Include file of Autonomous Utilities.


int loc = RAMP;
//int loc = ZONE;
int color = BLUECOLOR;
//int color = BLUECOLOR;
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
	char * sFileName = "debug.txt";
	short nFileSize =10000;

	eraseDisplay();
	nxtDisplayTextLine(0, "Autonomous Period");

	Delete(sFileName,nIoResult);
	OpenWrite(hFileHandle, nIoResult, sFileName, nFileSize);
	WriteText(hFileHandle, nIoResult, "Autonomous Period\n");

	nPidUpdateInterval = 20;


	armInit(tas);
	driveInit();
	wait1Msec(10);

	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//Autonomous Period

//-by Arjun Verma (FTC Team Error 7391)



//(POSITION 1 - perpendicular)

//(POSITION 2 - 45 degrees left of POS 2)

//(POSITION 3 - 45 degrees right of POS 1)

//RAMP MODE

//Get off ramp
//Find optimal position to detect IR beacon
	//if IR beacon is detected at position one then do:
		//go forward till IR beacon is perpendicular to robot
		//go to the rolling goals and score in the highest goal
		//pick up rolling goal
		//turn toward IR beacon
		//score one ball in the center goal
		//place rolling goal in the parking zone
		//get other rolling goals if time
////////////////////////////////////////////////////////////////////////////////////////////////////


task main()
{
	initializeRobot();
	int irValue;
	while (nNxtButtonPressed != kEnterButton){}
	moveInches(24, 30);
	turnDegrees(90);

	irValue = getBeaconVal(0);
	while (nNxtButtonPressed != kEnterButton){}
	if(irValue==7){
		turnDegrees(-90);
		while (nNxtButtonPressed != kEnterButton){}
		moveInches(18, 30);
		while (nNxtButtonPressed != kEnterButton){}
		moveInches(20, 30);
	}

	else if(irValue==2 || irValue==3){
		turnDegrees(-45);
		while (nNxtButtonPressed != kEnterButton){}
		moveInches(17, 30);
	}

	else if(irValue==5){
		moveInches(10, 30);
		while (nNxtButtonPressed != kEnterButton){}
		turnDegrees(90);
	}

}
