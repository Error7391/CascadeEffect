void moveInches(float distance, float diameter)
{

	float degrees = distance* (360/(diameter*PI));

	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < degrees)
	{
		motor[motorB] = 50;
	}
	motor[motorB]= 0;

}

task main()
{

	moveInches(5,3);

}
