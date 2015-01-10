/******************************************************************************
* ArmDriver.c - provides access to control articulated robot arm. Main function
* is setPosition(TArmState, position, distance).
* - TArmState stores the physical characteristics of the arm
* - Position is 1 of 5 values (0 - 0 cm, 1 - 30 cm, 2 - 60 cm, 3 - 90 cm, 4 - 120 cm)
*/
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

const int MAX_POSITIONS = 6;
const int POS_HOME = 0;
const int POS_AT_30CM = 1;
const int POS_AT_60CM = 2;
const int POS_AT_90CM = 3;
const int POS_AT_120CM = 4;
const int POS_BALL_COLLECTING = 5;

TArmPosition positions[MAX_POSITIONS];

const float hyp = 14;

// Calculates the servo setting for the shoulder given an angle in degrees
int shoulderRatio(int angle) {
	// A linear ratio does not work because of gravity which puts pressure
	// on the gears and causes some sag. We apply a factor calculated from
	// the sine of the angle; the formula for torque due to gravity applied
	// to a fixed corrective factor... whee!
	return angle * -15 / 45 - sinDegrees(angle) * 8;
}

// Calculates the servo settings for the elbow given an angle in degrees
int elbowRatio(int angle) {
	return angle * 105 / 90;
}

// Calculates the servo setting given the amount of lift in inches
int liftRatio(float height) {
	return height * -180 / 28;
}

// Sets up the TArmState control block and initializes the positions array
void armInit(TArmState& tasr) {
	positions[0].shoulderOver = true;
	positions[0].maxD = 0;
	positions[0].height = 0;

	positions[1].shoulderOver = true;
	positions[1].maxD = 13.4;
	positions[1].height = 11.81;

	positions[2].shoulderOver = true;
	positions[2].maxD = 14;
	positions[2].height = 23.62;

	positions[3].shoulderOver = false;
	positions[3].maxD = 14;
	positions[3].height = 35.43;

	positions[4].shoulderOver = false;
	positions[4].maxD = 14;
	positions[4].height = 47.24;

	positions[5].shoulderOver = true;
	positions[5].maxD = 0;
	positions[5].height = 4;

	servoChangeRate[shoulder] = 20;
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
	tasr.shoulderZero = 155;
	tasr.elbowZero = 25;

	servo[liftLow] = tasr.liftLowZero;
	servo[liftHigh] = tasr.liftHighZero;
	servo[shoulder] = tasr.shoulderZero;
	servo[elbow] = tasr.elbowZero;
}


// Moves the arm so it is at a specified angle, 1 to 180 degrees
void setArmAngle(TArmState& tasr, int angle) {
	if (angle >= 0 && angle <= 180) {
		servo[shoulder] = tasr.shoulderZero + shoulderRatio(angle);
		servo[elbow] = tasr.elbowZero + elbowRatio(angle);
		} else {
		// TODO - Indicate error state somehow
	}
}

// Moves the lift so the height of the shoulder is at a specified height in inches
void setShoulderHeight(TArmState& tasr, float inches) {
	if (inches >= 0 && inches <= 28) {
		servo[liftLow] = tasr.liftLowZero + liftRatio(inches);
		servo[liftHigh] = tasr.liftHighZero + liftRatio(inches);
		} else {
		// TODO - Indicate error state somehow
	}
}


// Main routine set the height of the end of the arm to 1 of 5 presets at a given distance from the robot
void setPosition (TArmState& tasr, int p, float distance) {
	writeDebugStreamLine("Position = %d",p);
	writeDebugStreamLine("Distance = %d",distance);
	writeDebugStreamLine("maxD = %d",positions[p].maxD);
	tasr.distance = distance;
	tasr.position = p;

	float d;
	if (p == 0) {
		setShoulderHeight(tasr,0);
		setArmAngle(tasr,0);
		} else if (p == 5) {
		setShoulderHeight(tasr,4);
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
		if (p < 5) {
			writeDebugStreamLine("D = %f",d);
			writeDebugStreamLine("Position.height = %f",positions[p].height);

			// Calculate the angle from the distance and arm-length
			float angle = asin(d / hyp);
			//Fetch the target height from the preset
			float targetHeight = positions[p].height;
			writeDebugStreamLine("Target Height = %f",targetHeight);
			//Calculate the height contribution from the arm angle
			float b = cos(angle)*hyp;

			writeDebugStreamLine("Target angle before adjustment = %f",radiansToDegrees(angle));
			// Adjust for positions where the collector is above the shoulder
			if (!positions[p].shoulderOver) {
				//Invert the angle from 180 degrees
				angle = 180 - radiansToDegrees(angle);
				b = -b;
			}
			float shoulderHeight = targetHeight + b - 16;

			writeDebugStreamLine("Target angle after adjustment = %f",angle);
			writeDebugStreamLine("Target adjustment = %f",b);
			writeDebugStreamLine("Target shoulder height = %f",shoulderHeight);

			//Make it so
			setShoulderHeight(tasr, shoulderHeight);
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
