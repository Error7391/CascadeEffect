#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorR,         sensorNone)
#pragma config(Sensor, S3,     colorL,         sensorNone)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorB,          grabL,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          grabR,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    move1,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    move2,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Motor,  motorB,          motorL,     tmotorNXT, openLoop, encoder)
//#pragma config(Motor,  motorC,          motorR,    tmotorNXT, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//Function declarations
void driveInit();
void armInit();

void liftBottom();
void liftRamp();
void liftHang();
void liftBasket();

void turnDegrees(int degrees);

void moveInches(float distance/*inches*/, int speed/*0-100*/ );
void rotateDegrees(float degrees, int speed, bool dir );
void pivotDegrees(float degrees, int speed, bool dir );
void ungrab();
float ticks2inches(float ticks);
float inches2ticks(float inches, int distance);



//defines
<<<<<<< HEAD

=======
#define DRIVE_DIAMETER 3
#define FORWARD 0
#define BACKWARD 1

#define HIGH_LIFT_BOTTOM 158
#define HIGH_LIFT_TOP 35
#define LOW_LIFT_BOTTOM 87
#define LOW_LIFT_TOP 240

#define THE_CENTER_GOAL_ELBOW	100
#define THE_90CM_GOAL_ELBOW		100
#define THE_60CM_GOAL_ELBOW		100
#define THE _30CM_GOAL_ELBOW	100

#define THE_CENTER_GOAL_SHOULDER	100
#define THE_90CM_GOAL_SHOULDER		100
#define THE_60CM_GOAL_SHOULDER		100
#define THE_30CM_GOAL_SHOULDER		100

#define THE_CENTER_GOAL_WRIST		100
#define THE_90CM_GOAL_WRIST			100
#define THE_60CM_GOAL_WRIST			100
#define THE_30CM_GOAL_WRIST			100

#define INIT_ELBOW 		100
#define INIT_SHOULDER 100
#define INIT_WRIST 		100

#define INIT_MOVE1	128
#define INIT_MOVE2	128

>>>>>>> origin/master


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        driveInit
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void driveInit(){
	nMotorEncoder[motorR] = 0;
	nMotorEncoder[motorL] = 0;

	servoChangeRate[move1] = 1;
	servoChangeRate[move2] = 1;

	servo[move1] = INIT_MOVE1;
	servo[move2] = INIT_MOVE2;


}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        armInit
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void armInit(){
	servoChangeRate[shoulder] = 1;
	servoChangeRate[elbow] = 1;
	servoChangeRate[wrist] = 1;
	servo[shoulder] = INIT_SHOULDER;
	servo[elbow] = INIT_ELBOW;
	servo[wrist] = INIT_WRIST;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        liftBottom
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void liftBottom()
{
	//servo[liftHigh] = HIGH_LIFT_BOTTOM;
	//servo[liftLow] = LOW_LIFT_BOTTOM;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        liftRamp
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void liftRamp()
{
	//servo[liftHigh] = HIGH_LIFT_BOTTOM - 15;
	//servo[liftLow] = LOW_LIFT_BOTTOM + 15;

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
	servo[move1] = ticks;
	servo[move2] = ticks;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        liftHang
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void liftHang()
{
	//servo[liftHigh] = HIGH_LIFT_HANG;
	//servo[liftLow] = LOW_LIFT_HANG;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        liftBasket
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void liftBasket()
{
	//	servo[liftHigh] = HIGH_LIFT_TOP + 15;
	//servo[liftHigh] = HIGH_LIFT_TOP;
	//servo[liftLow] = LOW_LIFT_TOP;

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
		//currEncoderL =	nMotorEncoder[motorL];
		//if (lastEncoderL < currEncoderL + 10){
		//	break;
		//}
		//lastEncoderL = currEncoderL;
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
