#pragma config(Hubs,   S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     					,               sensorI2CMuxController)
#pragma config(Sensor, S2,     					colorR,         sensorNone)
#pragma config(Sensor, S3,     					colorL,         sensorNone)
#pragma config(Sensor, S4,     				  irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorB,          grabL,         	tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          grabR,         	tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        	tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        	tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    liftLow,        tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    liftHigh,       tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    shoulder,       tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    elbow,          tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    scoop,          tServoNone)

#include "ArmDriver.c" //Include file of Robot Drivers.

TArmState tas;

task main()
{
	armInit(tas);
	wait1Msec(1000);

	// Testing the robot at the highest position at 12 inches and 2 inches away from the robot
	// Change the second argument to different postions (1-3) to test other heights
	// ======================================================================================

	while (nNxtButtonPressed != kEnterButton){ wait1Msec(10); }
	writeDebugStreamLine("=====================");
	writeDebugStreamLine("Setting pos 1 @ 8.5 in");
	setPosition(tas,4,8.5);
	wait1Msec(1000);

	while (nNxtButtonPressed != kEnterButton){ wait1Msec(10); }
	writeDebugStreamLine("=====================");
	writeDebugStreamLine("Setting pos 1 @ 4 in");
	setPosition(tas,4,6);
	wait1Msec(1000);

	while (nNxtButtonPressed != kEnterButton){ wait1Msec(10); }
	writeDebugStreamLine("=====================");
	writeDebugStreamLine("Setting pos 0");
	setPosition(tas,0,0);
	wait1Msec(1000);

	while (nNxtButtonPressed != kEnterButton){ wait1Msec(10); }
}
