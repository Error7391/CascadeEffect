#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    wheel2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	//servo[wheel1] = 50;
	//stopAllTasks();
	//servo[wheel2] = 50;
	while(true){
		servo[wheel2] = 50;
	}
	//	if(joystick.joy1_y1>6){
	//		motor[motorD] = joystick.joy1_y1;
	//		motor[motorE] = joystick.joy1_y1;
	//	}
	//	else if(joystick.joy1_y1<-6){
	//		motor[motorD] = -joystick.joy1_y1;
	//		motor[motorE] = -joystick.joy1_y1;
	//	}

		//motor[motorD] = 75;
		//motor[motorE] = 75;
		//servo[wheel3] = 0;
		//servo[wheel4] = 0;
		//wait10Msec(500);
		//servo[wheel1] = 256;
		//servo[wheel2] = 256;
	//}
}