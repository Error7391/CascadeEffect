//includes
#include "7391RobotDriver.c"; //include file of Robot Drivers

//Function Declarations
void findColor(int color);
int getBeaconVal(int irGoal);
void dropNramp (int side, float distance_traveled, int color);

//defines
#define RIGHT  1
#define LEFT 0
#define TOTAL_DISTANCE 72




/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Find Color
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void findColor(int color)
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

		motor[motorR] = 70;
		motor[motorL] = 70;
		color1 = SensorValue(colorR);

		if (color == color1){
			wait1Msec(5);
			color2 = SensorValue(colorR);
			if (color == color2){
				bFound = true;
			}
		}
		nAtoDValue    = 0;
		nRawValue     = SensorRaw[colorR];

		nxtDisplayTextLine(4, "raw:%d color1%d color2%d", nRawValue, color1, color2);
		//getColorSensorData(colorPort, colorRaw,    &nRawValues[0]);
		writeDebugStreamLine("raw:%d color1%d color2%d\n", nRawValue, color1, color2);
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
//                                         getBeaconVal
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

int getBeaconVal(int irGoal)
{

	int irValue = 0;

//	while (SensorValue(irSeeker) != irGoal){

		irValue = SensorValue(irSeeker);
		eraseDisplay();

		nxtDisplayTextLine(4, "irValue %d", irValue);
		//getColorSensorData(colorPort, colorRaw,    &nRawValues[0]);
		writeDebugStreamLine( "irValue%d\n", irValue);
	//}
		if(irValue==0){
			writeDebugStreamLine("read again");

			irValue = SensorValue(irSeeker);
			eraseDisplay();

			nxtDisplayTextLine(4, "irValue %d", irValue);
			//getColorSensorData(colorPort, colorRaw,    &nRawValues[0]);
			writeDebugStreamLine( "irValue%d\n", irValue);

		}
		return(irValue);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         goDownRamp
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

const int DIST_BEACON2BASKET = 10;
const float DIST_LINE2BASKET = 9;

void goDownRamp ()
{
	nxtDisplayTextLine(1, "here 1" );
	//nxtDisplayTextLine(2, "%d", distance_traveled);
	//while (nNxtButtonPressed != kLeftButton){}
	moveInches(40);





	//nxtDisplayTextLine(2, "%d", distance_traveled);
	nxtDisplayTextLine(1, "here 2" );
	while (nNxtButtonPressed != kEnterButton){}

//	if (LEFT == side)
//	{

//		pivotDegrees(-95, 40, FORWARD);
//		//nxtDisplayTextLine(1, "here 3" );
//		//while (nNxtButtonPressed != kLeftButton){}

//		while (time100[1] < 90){}

//		moveInches(DIST_LINE2BASKET, 40);
//		//nxtDisplayTextLine(1, "here 4" );
//		//while (nNxtButtonPressed != kEnterButton){}

//		//DROP CUBE
//		ungrab();
//		//nxtDisplayTextLine(1, "here 5" );
//		//while (nNxtButtonPressed != kLeftButton){}

//		//moveInches(-DIST_LINE2BASKET + 1, 40);
//		moveInches(-7.5, 40);


//		//nxtDisplayTextLine(1, "here 6" );
//		//while (nNxtButtonPressed != kEnterButton){}

//		pivotDegrees(94, 50, BACKWARD);
//		//nxtDisplayTextLine(1, "here 7" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		liftRamp();

//		motor[motorR] = 0;
//		motor[motorL] = 0;
//		moveInches(-distance_traveled, 60);
//		//moveInches(DIST_BEACON2BASKET, 40);

//		//nxtDisplayTextLine(1, "here 8" );
//		//while (nNxtButtonPressed != kEnterButton){}

//		pivotDegrees(-45, 50, FORWARD);
//		//nxtDisplayTextLine(1, "here 9" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		moveInches(16, 70);
//		//nxtDisplayTextLine(1, "here 10" );
//		//while (nNxtButtonPressed != kEnterButton){}
//		pivotDegrees(-45, 50, FORWARD);
//		//nxtDisplayTextLine(1, "here 11" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		findColor(color);
//		moveInches(3, 60);
//		//nxtDisplayTextLine(1, "here 12" );
//		//while (nNxtButtonPressed != kEnterButton){}
//		pivotDegrees(94, 50, BACKWARD);
//		//nxtDisplayTextLine(1, "here 13" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		moveInches(-30, 100);
//		//nxtDisplayTextLine(1, "here 14" );
//		//while (nNxtButtonPressed != kEnterButton){}


//	}
//	else
//	{

//		pivotDegrees(95, 40, FORWARD);
//		//nxtDisplayTextLine(1, "here 3" );
//		//while (nNxtButtonPressed != kLeftButton){}

//		while (time100[1] < 90){}

//		moveInches(DIST_LINE2BASKET, 40);
//		//nxtDisplayTextLine(1, "here 4" );
//		//while (nNxtButtonPressed != kEnterButton){}

//		//DROP CUBE
//		ungrab();
//		//nxtDisplayTextLine(1, "here 5" );
//		//while (nNxtButtonPressed != kLeftButton){}

//		moveInches(-7.5, 60);

//		//nxtDisplayTextLine(1, "here 6" );
//		//while (nNxtButtonPressed != kEnterButton){}

//		pivotDegrees(-94, 50, BACKWARD);
//		//nxtDisplayTextLine(1, "here 7" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		liftRamp();

//		motor[motorR] = 0;
//		motor[motorL] = 0;
//		moveInches(-distance_traveled, 60);
//		//nxtDisplayTextLine(1, "here 8" );
//		//while (nNxtButtonPressed != kEnterButton){}

//		pivotDegrees(45, 50, FORWARD);
//		//nxtDisplayTextLine(1, "here 9" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		moveInches(16, 70);
//		//nxtDisplayTextLine(1, "here 10" );
//		//while (nNxtButtonPressed != kEnterButton){}
//		pivotDegrees(45, 50, FORWARD);
//		//nxtDisplayTextLine(1, "here 11" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		findColor(color);
//		moveInches(3, 60);
//		//nxtDisplayTextLine(1, "here 12" );
//		//while (nNxtButtonPressed != kEnterButton){}
//		pivotDegrees(-94, 50, BACKWARD);
//		//nxtDisplayTextLine(1, "here 13" );
//		//while (nNxtButtonPressed != kLeftButton){}
//		moveInches(-30, 100);
//		//nxtDisplayTextLine(1, "here 14" );
//		//while (nNxtButtonPressed != kEnterButton){}

//	}
}
