//Function declarations
void driveInit();


void moveInches(float distance/*inches*/);
void rotateDegrees(float degrees);
//void pivotDegrees(float degrees);  //Not Updated
float ticks2inches(float ticks);
float inches2ticks(float inches, int distance);



//defines
#define DRIVE_DIAMETER 3
#define FORWARD 0
#define BACKWARD 1

#define INIT_MOVE1	128
#define INIT_MOVE2	128




/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        driveInit
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void driveInit(){
	motor[motorR] = 0;
	motor[motorL] = 0;

	//nPidUpdateInterval = 20;


	nxtDisplayTextLine(4, "driveInit");
	writeDebugStreamLine("driveInit");

}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        TurnDegrees
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void turnDegrees(int degrees){

}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        moveInches
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void moveInches(float distance)
{
	const int power = 30;
	int ticks = 65*1440/(DRIVE_DIAMETER*PI)*distance;
	if(distance > 0){
		motor[motorR] = power;
		motor[motorL] = power;
	}
	else{
		motor[motorR] = -power;
		motor[motorL] = -power;
	}
	wait1Msec(44.5*distance);

	motor[motorR] = 0;
	motor[motorL] = 0;
}

float ticks2inches(float ticks){
	float inches;
	inches = ticks/(1440/(DRIVE_DIAMETER*PI));
	return inches*2;
}

float inches2ticks(float inches, int distance){
	float ticks = 1440/(DRIVE_DIAMETER*PI)*distance;
	return ticks;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        PivotDegrees
//
/////////////////////////////////////////////////////////////////////////////////////////////////////



//void pivotDegrees(float degrees, int speed, bool dir )
//{
//	int lastEncoderL = -1;
//	int currEncoderL = 0;
//	int ticks = 3200*degrees/90;

//	nMotorEncoder[motorR] = 0;
//	nMotorEncoder[motorL] = 0;


//	if(degrees > 0 && dir == FORWARD){
//		nMotorEncoderTarget[motorR] = ticks;
//		motor[motorR] = speed;
//		motor[motorL] = 0;
//		while(nMotorRunState[motorR] != runStateIdle)
//		{
//			//currEncoderL =	nMotorEncoder[motorL];
//			//if (lastEncoderL < currEncoderL + 10){
//			//	break;
//			//}
//			//lastEncoderL = currEncoderL;
//		}

//	}//endif
//	else if(degrees < 0 && dir == BACKWARD){
//		nMotorEncoderTarget[motorR] = -ticks;
//		motor[motorR] = -speed;
//		motor[motorL] = 0;
//		while(nMotorRunState[motorR] != runStateIdle)
//		{
//			//currEncoderL =	nMotorEncoder[motorL];
//			//if (lastEncoderL < currEncoderL + 10){
//			//	break;
//			//}
//			//lastEncoderL = currEncoderL;
//		}
//	}//endif

//	else if(degrees < 0 && dir == FORWARD){
//		nMotorEncoderTarget[motorL] = ticks;
//		motor[motorR] = 0;
//		motor[motorL] = speed;
//		while(nMotorRunState[motorL] != runStateIdle)
//		{
//			//currEncoderL =	nMotorEncoder[motorL];
//			//if (lastEncoderL < currEncoderL + 10){
//			//	break;
//			//}
//			//lastEncoderL = currEncoderL;
//		}

//	}
//	else if(degrees > 0 && dir == BACKWARD){
//		nMotorEncoderTarget[motorL] = -ticks;
//		motor[motorR] = 0;
//		motor[motorL] = -speed;
//		while(nMotorRunState[motorL] != runStateIdle)
//		{
//			//currEncoderL =	nMotorEncoder[motorL];
//			//if (lastEncoderL < currEncoderL + 10){
//			//	break;
//			//}
//			//lastEncoderL = currEncoderL;
//		}

//	}
//	motor[motorR] = 0;
//	motor[motorL] = 0;
//}




//ungrab the block



/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         RotateDegrees
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void rotateDegrees(float degrees)
{
	int ticks = 0;

	if (degrees > 0)
	{
		ticks = 3050*degrees/(90*2);//half of ticks because of rotation
	}
	else
	{
		ticks = 3250*degrees/(90*2);//half of ticks because of rotation
	}


	if(degrees > 0){
		motor[motorR] = 80;
		motor[motorL] = -80;
	}//endif
	else{ //if(degrees < 0)
		motor[motorR] = 80;
		motor[motorL] = -80;
	}
	wait1Msec(degrees*9.6);

	motor[motorR] = 0;
	motor[motorL] = 0;
}
