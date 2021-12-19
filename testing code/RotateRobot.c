//Rotate Gyro
void rotateRobot(int angle)
{
int motorPower = 25;
tSensors gyroPort = S4;
resetGyro(gyroPort);
if (angle > 0)
{
motor[motorA] = -motorPower;
motor[motorD] = motorPower;
}
else
{
motor[motorA] = motorPower;
motor[motorD] = -motorPower;
}
angle = abs(angle);
while (abs(getGyroDegrees(gyroPort)) < angle)
{}

motor[motorA] = motor[motorD] = 0;
}
