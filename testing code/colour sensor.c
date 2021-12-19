void colourSensors()
{
	if(SensorValue [S3] == (int)colorGreen)
	{
	   displayString(1, "green");
	   playPoker();
	}
	else if(SensorValue [S3] == (int)colorBlue)
	{
	   displayString(2, "blue");
	   playGofish ();
	}
	else if  (SensorValue [S3] == (int)colorRed)
	{
	   displayString(3, "red");
	   President();
	}
	else if(SensorValue [S3] == (int)colorYellow)
	{
	   displayString(4, "yellow");
	   quickDeal();
	}
	else
	{
		motor[motorA]=motor[motorD]= 0;
	}
}
task main()
{
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

  while (true)
  {
    colourSensors();
  }
}
