#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorR,         sensorNone)
#pragma config(Sensor, S3,     colorL,         sensorNone)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    liftLow,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    liftHigh,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    collector,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_6,    trapDoor,             tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#define COMPETITION
//#define DEBUG
#define TEST_ARM 0
#define RAMP 0

#ifdef COMPETITION
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#endif

#include "7391RobotDriver.c" //Include file of Robot Drivers.
#include "7391AutoUtils.c" //Include file of Autonomous Utilities.

#include "ArmDriver.c" //Include file of Robot Drivers.


TArmState tas;

const int loc = RAMP;
//int loc = ZONE;
const int color = BLUECOLOR;
//int color = BLUECOLOR;
//const int DELAY = 10; //seconds
const int DELAY = 0;

enum centerGoalPos
{
	  CENTER_GOAL_POS1_0DEG, //kickstand straight ahead
	  CENTER_GOAL_POS2_45DEG, //rotated 45 deg to the right
	  CENTER_GOAL_POS3_90DEG   //rotated 90 deg to the right
};

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

	driveInit();
	armInit(tas);
  //Does armInit need 5 sec wait????

	wait1Msec(10);

	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//Autonomous Period

//-by Arjun Verma (FTC Team Error 7391)



//(POSITION 1 - perpendicular)

//(POSITION 2 - 45 degrees right of POS 1)

//(POSITION 3 - 90 degrees right of POS 1)

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
  int irValue;

	writeDebugStreamLine("initalizing");
	initializeRobot();
	writeDebugStreamLine("initalized");


#if (TEST_ARM == 1)


		int oldButton = kNoButton;
		int Button = kNoButton;
		while(1)
		{
			Button = nNxtButtonPressed;
			if (Button != oldButton)
			{
				switch (Button)
				{
					case kLeftButton:
						setPosition(tas, POS_BALL_COLLECTING, DEFAULT_DISTANCE);
						trapDoorClose();
						collectorIn();

  					while (nNxtButtonPressed != kEnterButton){}
 						setPosition(tas, POS_AT_120CM, DEFAULT_DISTANCE);
						trapDoorOpen();
						collectorStop();


						//moveInches(40);

						break;
					case kEnterButton:
						setPosition(tas, POS_HOME, DEFAULT_DISTANCE);
						break;
					case kRightButton:
						setPosition(tas, POS_BALL_COLLECTING, DEFAULT_DISTANCE);
						trapDoorCl2ose();
						collectorIn();

  					while (nNxtButtonPressed != kEnterButton){}
 						setPosition(tas, POS_AT_30CM, DEFAULT_DISTANCE);
						trapDoorOpen();
						collectorStop();
 							break;
					default:
						Button = kNoButton;
						break;
				}
				oldButton = Button;

			}
		}
#else
		while (nNxtButtonPressed != kEnterButton){}
	//Raise arm while moving
	setPosition (tas, POS_DRIVE, DEFAULT_DISTANCE);
	//Move to first_ postion to read IR
	moveInches(43);

  while (nNxtButtonPressed != kEnterButton){}
	irValue = getBeaconVal(0);
	if(irValue==8){
		//
		writeDebugStreamLine("ir=8");
	}
	else{
		moveInches(12);
		if(irValue==8){
			turnDegrees(-90):
		}
		else{
		}
	}

#endif
}//end main

//		writeDebugStreamLine("move 24 inches");
//	moveInches(24);
//	while (nNxtButtonPressed != kEnterButton){}
//	writeDebugStreamLine("move 24 inches");
//	moveInches(24);
//	while (nNxtButtonPressed != kEnterButton){}

//	writeDebugStreamLine("moved");



//	while (nNxtButtonPressed != kEnterButton){}
//	rotateDegrees(90);
//	writeDebugStreamLine("turned");

//		while (nNxtButtonPressed != kEnterButton){}
//	rotateDegrees(90);
//	writeDebugStreamLine("turned");
//	while (nNxtButtonPressed != kEnterButton){}
//	rotateDegrees(90);
//	writeDebugStreamLine("turned");
//	while (nNxtButtonPressed != kEnterButton){}
//	rotateDegrees(90);
//	writeDebugStreamLine("turned");

//	while (nNxtButtonPressed != kEnterButton){}
//	irValue = getBeaconVal(0);
//	while (nNxtButtonPressed != kEnterButton){}
//	if(irValue==7){
//		turnDegrees(-90);
//		while (nNxtButtonPressed != kEnterButton){}
//		moveInches(18);
//		while (nNxtButtonPressed != kEnterButton){}
//		moveInches(20);
//	}

//	else if(irValue==2 || irValue==3){
//		turnDegrees(-45);
//		while (nNxtButtonPressed != kEnterButton){}
//		moveInches(17);
//	}

//	else if(irValue==5){
//		moveInches(10);
//		while (nNxtButtonPressed != kEnterButton){}
//		turnDegrees(90);
//	}
//}
