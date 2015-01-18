#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorR,         sensorNone)
#pragma config(Sensor, S3,     colorL,         sensorNone)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          grabL,         tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          grabR,         tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    move1,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    move2,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    collector,            tServoContinuousRotation)
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
//#include "7391RobotDriver.c"


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
	// Place code here to sinitialize servos to starting positions.
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
//void  setWheelDegrees(int value);

task main()
{
	//	initializeRobot();
	waitForStart();   // wait for start of tele-op phase

	while (true)
	{
		servo[move1] = 144;
		servo[move2] = 144;

	while (nNxtButtonPressed != kEnterButton){}

	motor[motorL] = 30;
	motor[motorR] = 30;
	wait10Msec(400);

	motor[motorL] = 0;
	motor[motorR] = 0;
	}
}