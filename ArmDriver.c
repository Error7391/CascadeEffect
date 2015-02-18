/******************************************************************************
* ArmDriver.c - provides access to control articulated robot arm. Main function
* is setPosition(TArmState, position, distance).
* - TArmState stores the physical characteristics of the arm
* - Position is 1 of 5 values (0 - 0 cm, 1 - 30 cm, 2 - 60 cm, 3 - 90 cm, 4 - 120 cm)
*/


enum collectorState
{
	COLLECTOR_IDLE = 128,
	COLLECTOR_IN = 255,
	COLLECTOR_OUT = 0
};

enum trapDoorState
{
	TRAP_DOOR_CLOSED = 167,
	TRAP_DOOR_OPEN = 255
};

typedef struct {
	int liftLowZero;
	int liftHighZero;
	int shoulderZero;
	int elbowZero;
	int distance;
	int position;
} TArmState;

typedef struct {
	bool shoulderOver;
	float maxD;
	float height;
} TArmPosition;

const int MAX_POSITIONS = 7;
const int POS_HOME = 0;
const int POS_AT_30CM = 1;
const int POS_AT_60CM = 2;
const int POS_AT_90CM = 3;
const int POS_AT_120CM = 4;
const int POS_BALL_COLLECTING = 5;
const int POS_DRIVE = 6;
const float DEFAULT_DISTANCE = 6.5;
//const float DEFAULT_DISTANCE = 5.0; //for 60cm

TArmPosition positions[MAX_POSITIONS];

const float hyp = 14;

void collectorStop()
{
	servo[collector] = COLLECTOR_IDLE;
}

void collectorIn()
{
	servo[collector] = COLLECTOR_IN;
}

void collectorOut()
{
	servo[collector] = COLLECTOR_OUT;
}

void trapDoorClose()
{
	writeDebugStreamLine("TrapDoor CLOSE");
	servo[trapDoor] = TRAP_DOOR_CLOSED;
}

void trapDoorOpen()
{
	writeDebugStreamLine("TrapDoor OPEN");
	servo[trapDoor] = TRAP_DOOR_OPEN;
}

// Calculates the servo setting for the shoulder given an angle in degrees
int shoulderRatio(int angle) {
	// A linear ratio does not work because of gravity which puts pressure
	// on the gears and causes some sag. We apply a factor calculated from
	// the sine of the angle; the formula for torque due to gravity applied
	// to a fixed corrective factor... whee!
	return angle * -15 / 45 - sinDegrees(angle) * 15;
}

// Calculates the servo settings for the elbow given an angle in degrees
int elbowRatio(int angle) {
	return angle * 105 / 90;
}

// Calculates the servo setting given the amount of lift in inches
int liftRatio(float height) {
	return height * -180 / 30;
}

// Sets up the TArmState control block and initializes the positions array
void armInit(TArmState& tasr) {
	positions[0].shoulderOver = true;
	positions[0].maxD = 0;
	positions[0].height = 0;

	positions[1].shoulderOver = true;
	positions[1].maxD = 13.4;
	//positions[1].height = 11.81;
	positions[1].height = 13.0;

	positions[POS_AT_60CM].shoulderOver = true;
	positions[2].maxD = 14;
//	positions[2].height = 23.62;
	positions[2].height = 24.5;  //bring arm in 1.5 in. make height too low

	positions[POS_AT_90CM].shoulderOver = false;
	//positions[3].maxD = 14;
	positions[3].maxD = 16;
	//positions[3].height = 35.43;
	positions[3].height = 34.00;

	positions[4].shoulderOver = false;
	positions[4].maxD = 14;
	positions[4].height = 47.24;

	positions[5].shoulderOver = true;
	positions[5].maxD = 0;
	positions[5].height = 7;

	positions[POS_DRIVE].shoulderOver = true;
	positions[6].maxD = 2;
	positions[6].height = 4;

	servoChangeRate[shoulder] = 40;
	//servoChangeRate[shoulder] = 1;
	servoChangeRate[elbow] = 1;
	servoChangeRate[liftHigh] = 0;
	servoChangeRate[liftLow] = 0;

	// TODO - How do we get the current "actual" values from the servos before setting them to a position?
	//tasr.liftLowZero = ServoValue[liftLow];
	//tasr.liftHighZero = ServoValue[liftHigh];
	//tasr.shoulderZero = ServoValue[shoulder];
	//tasr.elbowZero = ServoValue[elbow];

	// Hard coding the initial positions until calibration can be made
	tasr.liftLowZero = 200;
	tasr.liftHighZero = 200;
	//tasr.shoulderZero = 155;
	tasr.shoulderZero = 101;
	//tasr.elbowZero = 25;
	tasr.elbowZero = 15; //Servo came off so changed value

	servo[liftLow] = tasr.liftLowZero;
	servo[liftHigh] = tasr.liftHighZero;
	servo[shoulder] = tasr.shoulderZero;
	servo[elbow] = tasr.elbowZero;

	servo[collector] = COLLECTOR_IDLE;
	servo[trapDoor] = TRAP_DOOR_CLOSED;
}


// Moves the arm so it is at a specified angle, 1 to 180 degrees
void setArmAngle(TArmState& tasr, int angle) {
	if (angle >= 0 && angle <= 180) {
		servo[shoulder] = tasr.shoulderZero + shoulderRatio(angle);
		int elbowSetting = tasr.elbowZero + elbowRatio(angle);
		if (elbowSetting > 100) { //for pos 90
			wait10Msec(180);
	    servo[elbow] = 80;
	    wait10Msec(250);
	 }
		servo[elbow] = tasr.elbowZero + elbowRatio(angle);
		} else {
		// TODO - Indicate error state somehow
	}
}

// Moves the lift so the height of the shoulder is at a specified height in inches
void setShoulderHeight(TArmState& tasr, float inches) {
	const int MIN_SERVO = 40;
	int servoHigh, servoLow;
	if (inches >= 0 && inches <= 28) {
		servoLow = tasr.liftLowZero + liftRatio(inches);
	servo[liftLow] = (servoLow < MIN_SERVO) ? MIN_SERVO : servoLow;
		servoHigh = tasr.liftHighZero + liftRatio(inches);
	servo[liftHigh] = (servoHigh < MIN_SERVO) ? MIN_SERVO : servoHigh;
		} else {
		// TODO - Indicate error state somehow
	}
}


// Main routine set the height of the end of the arm to 1 of 5 presets at a given distance from the robot
void setPosition (TArmState& tasr, int p, float distance) {
  writeDebugStreamLine("     Position = %d",p);
	writeDebugStreamLine("     Distance = %d",distance);
	writeDebugStreamLine("      = %d",positions[p].maxD);
	tasr.distance = distance;
	tasr.position = p;

	float d;
	if (p == POS_BALL_COLLECTING) {
		servo[liftLow] = 163;
		servo[liftHigh] = 163;
		servo[shoulder] = 95;
		servo[elbow] = 122;
	}
	else

	if (p == POS_DRIVE){
		servo[liftLow] = 174;
		servo[liftHigh] = 174;
		servo[shoulder] = 95;
		servo[elbow] = 13;
	}
	else
	if (p == POS_AT_60CM){
		servo[liftLow] = 57;
		servo[liftHigh] = 44;
		servo[shoulder] = 85;
		servo[elbow] = 34;
	}
	else
		if (p == POS_AT_90CM){ //start from elbow = 13
		servo[liftLow] = 130;
		servo[liftHigh] = 130;
		servo[shoulder] = 44;
			//start from elbow = 13 in drive
			wait10Msec(170);//170//100-120-150 //150
	    servo[elbow] = 72;//72
	    wait10Msec(90);//90 //70
			servo[elbow] = 80;//80
	    wait10Msec(80);//60 //80
			servo[elbow] = 100; //100
	    wait10Msec(100);//100
	    servo[elbow] = 130;//130
	    wait10Msec(60);//120 //80-100 //60
			servo[elbow] = 150;
	    wait10Msec(30);//120 //80-100
			servo[elbow] = 184;//165
	  //  wait10Msec(100);//120 //80-100//30
			//servo[elbow] = 165;//173
	}
	else
		if (p == POS_AT_120CM){ //start from elbow = 13
		servo[liftLow] = 40;
		servo[liftHigh] = 40;
		servo[shoulder] = 44;
			//start from elbow = 13 in drive
			wait10Msec(180);//170//100-120-150 //150
	    servo[elbow] = 72;//72
	    wait10Msec(80);//90 //70//30
			servo[elbow] = 80;//80
	    wait10Msec(80);//60 //80
			servo[elbow] = 100; //100
	    wait10Msec(100);//100
	    servo[elbow] = 130;//130
	    wait10Msec(100);//120 //80-100 //60
			servo[elbow] = 150;
	    wait10Msec(120);//120 //80-100
			servo[elbow] = 170;//165
	  //  wait10Msec(100);//120 //80-100//30
			//servo[elbow] = 165;//173
	}
	else

	if (p == 0) {
		setShoulderHeight(tasr,0);
		setArmAngle(tasr,0);
	} else if (p == POS_BALL_COLLECTING) {
		setShoulderHeight(tasr,4);
		servo[liftLow] = servo[liftLow]-21;		//set to 155. Fix Better Later
		setArmAngle(tasr,0);
		servo[elbow] = tasr.elbowZero + elbowRatio(90);
	} else {
		if (distance < 0) {
			d = 0;
			} else if (distance > positions[p].maxD) {
			d = positions[p].maxD;
			}	else {
			d = distance;
		}
		if (p != POS_BALL_COLLECTING) {
			writeDebugStreamLine("     D = %f",d);
			writeDebugStreamLine("     Position.height = %f",positions[p].height);

			// Calculate the angle from the distance and arm-length
			float angle = asin(d / hyp);
			//Fetch the target height from the preset
			float targetHeight = positions[p].height;
			writeDebugStreamLine("     Target Height = %f",targetHeight);
			//Calculate the height contribution from the arm angle
			float b = cos(angle)*hyp;

			writeDebugStreamLine("     Target angle before adjustment = %f",radiansToDegrees(angle));
			// Adjust for positions where the collector is above the shoulder
			if (!positions[p].shoulderOver) {
				//Invert the angle from 180 degrees
				angle = 180 - radiansToDegrees(angle);
				b = -b;
			} else {
				angle = radiansToDegrees(angle);
			}
			float shoulderHeight = targetHeight + b - 13;

			writeDebugStreamLine("     Target angle after adjustment = %f, %f",angle, degreesToRadians(angle));
			writeDebugStreamLine("     Target adjustment = %f",b);
			writeDebugStreamLine("     Target shoulder height = %f",shoulderHeight);

			//Make it so
			setShoulderHeight(tasr, shoulderHeight);
			//if (p == POS_AT_90CM || p == POS_AT_120CM) {
			//	wait10Msec(200);
			//}
			setArmAngle(tasr, angle);
		}
	}
}

void incDistance (TArmState& tasr) {
	if (tasr.distance + 0.1 <= positions[tasr.position].maxD) {
		setPosition (tasr,tasr.position,tasr.distance + 0.1);
	}
}

void decDistance (TArmState& tasr) {
	if (tasr.distance - 0.1 >= 0) {
		setPosition (tasr,tasr.position,tasr.distance - 0.1);
	}
}
