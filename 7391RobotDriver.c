//Function declarations
void driveInit();


void moveInches(float distance/*inches*/, int speed/*0-100*/ );
void rotateDegrees(float degrees, int speed, bool dir );
void pivotDegrees(float degrees, int speed, bool dir );
void ungrab();
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
	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;

	nxtDisplayTextLine(4, "driveInit");

}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        TurnDegrees
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void turnDegrees(int degrees){
	//16degrees = 90 degrees
  //positive is right
	//negative is left
	int ticks = 128+(16/90)*degrees;
	servo[motorL] = ticks;
	servo[motorR] = ticks;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        moveInches
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void moveInches(float distance, int speed)
{
	int lastEncoderL = -1;
	int currEncoderL = 0;
	int ticks = 1440/(DRIVE_DIAMETER*PI)*distance;
	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;
	nMotorEncoderTarget[motorR] = ticks*2;
	nMotorEncoderTarget[motorL] = ticks*2;

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
		currEncoderL =	nMotorEncoder[motorL];
		if (lastEncoderL < currEncoderL + 10){
			break;
		}
		lastEncoderL = currEncoderL;
	}
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



void pivotDegrees(float degrees, int speed, bool dir )
{
	int lastEncoderL = -1;
	int currEncoderL = 0;
	int ticks = 3200*degrees/90;

	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;


	if(degrees > 0 && dir == FORWARD){
		nMotorEncoderTarget[motorR] = ticks;
		motor[motorR] = speed;
		motor[motorL] = 0;
		while(nMotorRunState[motorR] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break;
			//}
			//lastEncoderL = currEncoderL;
		}

	}//endif
	else if(degrees < 0 && dir == BACKWARD){
		nMotorEncoderTarget[motorR] = -ticks;
		motor[motorR] = -speed;
		motor[motorL] = 0;
		while(nMotorRunState[motorR] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break;
			//}
			//lastEncoderL = currEncoderL;
		}
	}//endif

	else if(degrees < 0 && dir == FORWARD){
		nMotorEncoderTarget[motorL] = ticks;
		motor[motorR] = 0;
		motor[motorL] = speed;
		while(nMotorRunState[motorL] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break;
			//}
			//lastEncoderL = currEncoderL;
		}

	}
	else if(degrees > 0 && dir == BACKWARD){
		nMotorEncoderTarget[motorL] = -ticks;
		motor[motorR] = 0;
		motor[motorL] = -speed;
		while(nMotorRunState[motorL] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break;
			//}
			//lastEncoderL = currEncoderL;
		}

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


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         RotateDegrees
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void rotateDegrees(float degrees, int speed, bool dir )
{
	int lastEncoderL = -1;
	int currEncoderL = 0;
	int ticks = 0;

	if (degrees > 0)
	{
		ticks = 3050*degrees/(90*2);//half of ticks because of rotation
	}
	else
	{
		ticks = 3250*degrees/(90*2);//half of ticks because of rotation
	}

	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;


	if(degrees > 0 && dir == FORWARD){
		nMotorEncoderTarget[motorR] = ticks;
		motor[motorR] = speed;
		motor[motorL] = -speed;
		while(nMotorRunState[motorR] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break;
			//}
			//lastEncoderL = currEncoderL;
		}
	}//endif
	else if(degrees < 0 && dir == BACKWARD){
		nMotorEncoderTarget[motorR] = -ticks;
		motor[motorR] = -speed;
		motor[motorL] = speed;
		while(nMotorRunState[motorR] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break;
			//}
			//lastEncoderL = currEncoderL;
		}
	}//endif
	//else if(degrees < 0 && dir == FORWARD){
	//	nMotorEncoderTarget[motorL] = ticks;
	//	motor[motorR] = -speed;
	//	motor[motorL] = speed;
	//	while(nMotorRunState[motorL] != runStateIdle)
	//	{
	//		//currEncoderL =	nMotorEncoder[motorL];
	//		//if (lastEncoderL < currEncoderL + 10){
	//		//	break;
	//		//}
	//		//lastEncoderL = currEncoderL;
	//	}

	//}
	else if(degrees < 0 && dir == FORWARD){
		nMotorEncoderTarget[motorR] = -ticks;
		motor[motorR] = -speed;
		motor[motorL] = speed;
		while(nMotorRunState[motorR] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break
			//}
			//lastEncoderL = currEncoderL;
		}

	}

	else if(degrees > 0 && dir == BACKWARD){
		nMotorEncoderTarget[motorR] = ticks;
		motor[motorR] = speed;
		motor[motorL] = -speed;
		while(nMotorRunState[motorR] != runStateIdle)
		{
			//currEncoderL =	nMotorEncoder[motorL];
			//if (lastEncoderL < currEncoderL + 10){
			//	break;
			//}
			//lastEncoderL = currEncoderL;
		}
	}
	motor[motorR] = 0;
	motor[motorL] = 0;
}
