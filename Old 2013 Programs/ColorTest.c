int calibrateLightSensor(int lightSensor)
{
int whiteValue;
int blackValue;
	nxtDisplayTextLine(1,"White");
	wait1Msec(3000);

while(SensorValue(lightSensor)==0)
{
	whiteValue = SensorValue(lightSensor);
}
eraseDisplay();
nxtDisplayCenteredTextLine(1,whiteValue);

}
nxtDisplayTextLine(1,"Black");
while(SensorValue(touchSensor)==0)
{
	blackValue = SensorValue(lightSensor);
}
nxtDisplayTextLine(1,blackValue);

return (whiteValue+blackValue)*0.5;


}
task main()
{

calibrateLightSensor();

}
