task main()
{
nSyncedMotors = synchBC;
nSyncedTurnRatio = 100;
nMotorEncoder[motorB] = 0;
while(nMotorEncoder[motorB] < 360)
{
	motor[motorB] = 50;
}

motor[motorC] = 0;
motor[motorB] = 0;





}
