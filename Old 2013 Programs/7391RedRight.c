#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     colorR,         sensorCOLORFULL)
#pragma config(Sensor, S3,     colorL,         sensorCOLORFULL)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorB,          grabL,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          grabR,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
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

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#define RIGHT  1
#define LEFT 0

#define DRIVE_DIAMETER 3

//#define ALLIANCE_COLOR BLUECOLOR
#define ALLIANCE_COLOR REDCOLOR

int side = LEFT;

//Function declarations
void findColor();
void findBeacon();
void moveInches(float distance, int speed );
void ungrab();

TFileHandle hFileHandle;
TFileIOResult nIoResult;
char sOutput[100];


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

	string sFileName = "debug.txt";
	int nFileSize =10000;

	nPidUpdateInterval = 20;

	wait1Msec(10);

	eraseDisplay();
	nxtDisplayTextLine(0, "Autonomous Period");

	Delete(sFileName,nIoResult);
	OpenWrite(hFileHandle, nIoResult, sFileName, nFileSize);
	WriteText(hFileHandle, nIoResult, "Autonomous Period\n");

	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;

	//turn right from wall
	//motor[motorL] = 50;
	//while (nMotorEncoder[motorL] < 1000){}
	//motor[motorL] = 0;

	moveInches(26,30);

	ungrab();

	moveInches(-3,30);

	//pivot back right 90deg
	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;
	motor[motorR] = -50;
	while (nMotorEncoder[motorR] > -2400){}
	motor[motorL] = 0;
	motor[motorR] = 0;

	findColor();

	//rotate back right 90deg
	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;
	motor[motorR] = -50;
	motor[motorL] = 50;
	while (nMotorEncoder[motorL] < 1200){}
	motor[motorL] = 0;
	motor[motorR] = 0;

	//go up the ramp
	moveInches(-38, 100);


	Close(hFileHandle, nIoResult);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Find Color
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void findColor()
{
	word nAtoDValue;
	word nRawValue;
	word nColorValue;
	string sTemp;
	int nRed, nGreen, nBlue;
	//change color to correspond to team color
	bool bFound = false;
	int color1, color2;

	while (false == bFound){

		motor[motorR] = 30;
		motor[motorL] = 30;
		color1 = SensorValue(colorR);

		if (ALLIANCE_COLOR == color1){
			wait1Msec(5);
			color2 = SensorValue(colorR);
			if (ALLIANCE_COLOR == color2){
				bFound = true;
			}
		}
		nAtoDValue    = 0;
		nRawValue     = SensorRaw[colorR];

		nxtDisplayTextLine(4, "raw:%d color1%d color2%d", nRawValue, color1, color2);
		//getColorSensorData(colorPort, colorRaw,    &nRawValues[0]);
		sprintf(sOutput, "raw:%d color1%d color2%d\n", nRawValue, color1, color2);
		WriteText(hFileHandle, nIoResult, sOutput);
	}

	motor[motorR] = 0;
	motor[motorL] = 0;
	//until (value of irSeeker = (9/0))
	//line followright)
	//end until
	//nMotorEncoder[motorR] = 0;
	//nMotorEncoder[motorL] = 0;
	//motor[motorR] = 100;
	//while (nMotorEncoder[motorR] < 90){

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Find Beacon
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void findBeacon()
{
	int irValue = 0;
	motor[motorR] = 0;
	while (SensorValue(irSeeker) != 8){
		motor[motorR] = 30;
		motor[motorL] = 30;
		irValue = SensorValue(irSeeker);

		nxtDisplayTextLine(4, "irValue%d", irValue);
		//getColorSensorData(colorPort, colorRaw,    &nRawValues[0]);
		sprintf(sOutput, "irValue%d\n", irValue);
		WriteText(hFileHandle, nIoResult, sOutput);
	}
	motor[motorR] = 0 ;
	motor[motorL] = 0 ;
	//until (value of irSeeker = (5))
	//turn right
	//end until
	//if motor left is used then side is eu
	while (SensorValue(irSeeker) != 5){
		motor[motorR] = -30;
		motor[motorL] = 30;
		irValue  = SensorValue(irSeeker);
		nxtDisplayTextLine(4, "irValue%d", irValue);
		sprintf(sOutput, "irValue%d\n", irValue);
		WriteText(hFileHandle, nIoResult, sOutput);
	}
	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;
	motor[motorR] = 30;
	motor[motorL] = 30;
	while (nmotorEncoder[motorR] < 500){

	}
	motor[motorR] = 0;
	motor[motorL] = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        moveInches
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void moveInches(float distance, int speed )
{
	int lastEncoderL = -1;
	int currEncoderL = 0;
	int ticks = 1440/(DRIVE_DIAMETER*PI)*distance;

	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;
	nMotorEncoderTarget[motorR] = ticks;
	nMotorEncoderTarget[motorL] = ticks;

	if(distance > 0){
		motor[motorR] = speed;
		motor[motorL] = speed;
	}
	else{
		motor[motorR] = -speed;
		motor[motorL] = -speed;
	}

	while(nMotorRunState[motorR] != runStateIdle)
	{
		//currEncoderL =	nMotorEncoder[motorL];
		//if (lastEncoderL < currEncoderL + 10){
		//	break;
		//}
		//lastEncoderL = currEncoderL;
	}
	motor[motorR] = 0;
	motor[motorL] = 0;
}
//ungrab the block

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Ungrab
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ungrab()
{
	nMotorEncoder[grabR] = 0;
	while(nMotorEncoder[grabR] > -1000)
	{
		motor[grabR] = -100;
		motor[grabL] = -100;
	}
	motor[grabR] = 0;
	motor[grabL] = 0;
}
