#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    ExpanderBattery, sensorAnalog)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           armMotorL2,    tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftMotorR,    tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port3,           leftMotorF,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rollerMotor,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           armMotorL1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           armMotorR1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           clawMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightMotorF,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightMotorR,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port10,          armMotorR2,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

//Function-variable creation begin
int dist;//distance, used by encoded movement functions
int convertfactor = 19.2923076923;//formula to get this number is wheel circumfrence in centimeters divided by number of ticks. Currently set up for IMEs on a 393 motor(geared for torque) powering a mechanum wheel
int joy1X = 0;//used for recalibration of left joystick
int joy1Y = 0;//see above
int joy2X = 0;//used for recalibration of right joystick
int joy2Y = 0;//see above
int gX = 0;//used for gyroscope threshold
int gY = 0;//see above
int auton = 1;//used to select automomous code with a switch-case, set number to default program.
int ExpanderBatteryLevel = 0;//used to display battery level of power expander, always displays "replace" for some reason
bool batteryLCDBool = true;//used to select which battery level is displayed, defaults to primary
void clear(){//resets encoders
	nMotorEncoder[leftMotorR] = 0;
	nMotorEncoder[rightMotorR] = 0;
}
void halt(int set = 0){//stops all movement: 0 stops chassis, 1 stops arm, 2 stops everything. Defaults to chassis.
	if (set==0||set==2){
		motor[leftMotorF] = 0;
		motor[leftMotorR] = 0;
		motor[rightMotorF] = 0;
  		motor[rightMotorR] = 0;
  		motor[clawMotor] = 0;
  		motor[rollerMotor] = 0;
	}
	if (set==1||set==2){
		motor[armMotorL1] = 0;
		motor[armMotorL2] = 0;
		motor[armMotorR1] = 0;
		motor[armMotorR2] = 0;
		motor[rollerMotor] = 0;
	}
}
void forward(int cm, int speed = 63){//forward for designated distance
	clear();
	dist = cm / convertfactor;
	while (nMotorEncoder[leftMotorR]>-dist && nMotorEncoder[rightMotorR]<dist){
		motor[leftMotorF] = speed;
		motor[leftMotorR] = speed;
		motor[rightMotorF] = speed;
		motor[rightMotorR] = speed;
	}
	motor[armMotorL1] = 0;
	motor[armMotorL2] = 0;
	motor[armMotorR1] = 0;
	motor[armMotorR2] = 0;
	halt();
}
void backward(int cm, int speed = 63){//see above, but moves backwards
	clear();
	dist = cm / convertfactor;
	while (nMotorEncoder[leftMotorR]<dist && nMotorEncoder[rightMotorR]>-dist){
		motor[leftMotorF] = -speed;
		motor[leftMotorR] = -speed;
		motor[rightMotorF] = -speed;
		motor[rightMotorR] = -speed;
	}
}
void backwardTime(int time, int speed){//moves backward for a time, not a distance
	motor[leftMotorF] = -speed;
	motor[leftMotorR] = -speed;
	motor[rightMotorF] = -speed;
	motor[rightMotorR] = -speed;
	wait1Msec(time);
}
void left(int speed = 63, int cm = 0){//moves left for a designated distance
	clear();
	if (cm == 0){
		motor[rightMotorF] = speed;
		motor[rightMotorR] = -speed;
		motor[leftMotorF] = -speed;
		motor[leftMotorR] = speed;
	}
	else{
		dist = cm / convertfactor;
		while (nMotorEncoder[leftMotorR]<dist && nMotorEncoder[rightMotorR]<dist){
			motor[rightMotorF] = speed;
			motor[rightMotorR] = -speed;
			motor[leftMotorF] = -speed;
			motor[leftMotorR] = speed;
		}
		halt();
	}
}
void right(int speed = 63, int cm = 0){//see above, but moves right
	clear();
	if (cm == 0){
		motor[rightMotorF] = -speed;
		motor[rightMotorR] = speed;
		motor[leftMotorF] = speed;
		motor[leftMotorR] = -speed;
	}
	else{
		dist = cm / convertfactor;
		while (nMotorEncoder[leftMotorR]<dist && nMotorEncoder[rightMotorR]<dist){
			motor[rightMotorF] = -speed;
			motor[rightMotorR] = speed;
			motor[leftMotorF] = speed;
			motor[leftMotorR] = -speed;
		}
		halt();
	}
}
void turnLeftPlace(int cm, int speed = 127){//turns left in one place
	clear();
	dist = cm / convertfactor;
	while (nMotorEncoder[leftMotorR]<dist && nMotorEncoder[rightMotorR]<dist){
		motor[leftMotorF] = -speed;
		motor[leftMotorR] = -speed;
		motor[rightMotorF] = speed;
		motor[rightMotorR] = speed;
	}
	motor[armMotorL1] = 0;
	motor[armMotorL2] = 0;
	motor[armMotorR1] = 0;
	motor[armMotorR2] = 0;
	halt();
}
void turnLeftArc(int cm, int speed = 63){//see above, but moves forward while turning
	clear();
	dist = cm / convertfactor;
	while (nMotorEncoder[leftMotorR]<(dist/5) && nMotorEncoder[rightMotorR]<dist){
		motor[leftMotorF] = (speed/5);
		motor[leftMotorR] = (speed/5);
		motor[rightMotorF] = speed;
		motor[rightMotorR] = speed;
	}
	motor[armMotorL1] = 0;
	motor[armMotorL2] = 0;
	motor[armMotorR1] = 0;
	motor[armMotorR2] = 0;
	halt();
}
void turnRightPlace(int cm, int speed = 63){//turns right in one place
	clear();
	dist = cm / convertfactor;
	while (nMotorEncoder[leftMotorR]>-dist && nMotorEncoder[rightMotorR]>-dist){
		motor[leftMotorF] = speed;
		motor[leftMotorR] = speed;
		motor[rightMotorF] = -speed;
		motor[rightMotorR] = -speed;
	}
	motor[armMotorL1] = 0;
	motor[armMotorL2] = 0;
	motor[armMotorR1] = 0;
	motor[armMotorR2] = 0;
	halt();
}
void turnRightArc(int cm, int speed = 63){//see above, but movesforward while turning
	clear();
	dist = cm / convertfactor;
	while (nMotorEncoder[leftMotorR]>-dist && nMotorEncoder[rightMotorR]>-(dist/2)){
		motor[leftMotorF] = speed;
		motor[leftMotorR] = speed;
		motor[rightMotorF] = (speed/2);
		motor[rightMotorR] = (speed/2);
	}
	motor[armMotorL1] = 0;
	motor[armMotorL2] = 0;
	motor[armMotorR1] = 0;
	motor[armMotorR2] = 0;
	halt();
}
void raiseArm(int time, int speed = 63){//raises arm
	motor[armMotorL1] = -speed;
	motor[armMotorL2] = -speed;
	motor[armMotorR1] = -speed;
	motor[armMotorR2] = -speed;
	wait1Msec(time);
}
void lowerArm(int time, int speed = 63){//lowers arm
	motor[armMotorL1] = speed;
	motor[armMotorL2] = speed;
	motor[armMotorR1] = speed;
	motor[armMotorR2] = speed;
	wait1Msec(time);
}
void openClaw(int time, int speed = 63){//opens claw
	motor[clawMotor] = speed;
	wait1Msec(time);
}
void closeClaw(int time,int speed = 63){//closes claw
	motor[clawMotor] = -speed;
	wait1Msec(time);
}
void batteryLCD(){//displaysbatterylevels on LCD, malfunctioning
	if (time1[T1]%100 == 0)
	{
		switch(batteryLCDBool)
		{
		case true:
			clearLCDLine(0);
			displayLCDString(0, 0, "Primary: ");
			if (nAvgBatteryLevel < 5500)
			{
				displayNextLCDString("Replace");
			}
			else if (nAvgBatteryLevel < 6500)
			{
				displayNextLCDString("Low");
			}
			else
			{
				displayNextLCDString("Good");
			}
			break;
		case false:
			ExpanderBatteryLevel = SensorValue[ExpanderBattery] / 7;
			clearLCDLine(0);
			displayLCDString(0, 0, "Secondary: ");
			if (ExpanderBatteryLevel < 550)
			{
				displayNextLCDString("Replace");
			}
			else if (ExpanderBatteryLevel < 650)
			{
				displayNextLCDString("Low");
			}
			else
			{
				displayNextLCDString("Good");
			}
			break;
		}
	}
}
void calJoy(){//recalibrates joystick on-the-fly by saving values while joystick is released
  halt();
	clearLCDLine(1);
	displayLCDString(1, 0, "joyCal: Waiting");
	delay(2000);
	if (abs(vexRT[Ch4]) < 30 && abs(vexRT[Ch3]) < 30)
	{
		joy1X = vexRT[Ch4];
		joy1Y = vexRT[Ch3];
	}
	if (abs(vexRT[Ch1]) < 30 && abs(vexRT[Ch2]) < 30)
	{
		joy2X = vexRT[Ch1];
		joy2Y = vexRT[Ch2];
	}
	clearLCDLine(1);
}//Function-variable creation end
void pre_auton(){//Pre-Autonomous block begin
	clear();
	while (bIfiRobotDisabled)//outputs true when robot is disabled, ends subroutine when autonomous starts
	{
		displayLCDString(1, 0, "<<");
		displayLCDString(1, 14, ">>");
		switch(auton)
		{
		case 1://red autoloader
			displayLCDCenteredString(0, "Red 1");
			if (nLCDButtons == 1)
			{
				while (nLCDButtons == 1)
				{
				}
				auton = 6;
			}
			else
			{
			}
			if (nLCDButtons == 4)
			{
				while (nLCDButtons == 4)
				{
				}
				auton = 2;
			}
			else
			{
			}
			break;
		case 2://red posts
			displayLCDCenteredString(0, "Red 2");
			if (nLCDButtons == 1)
			{
				while (nLCDButtons == 1)
				{
				}
				auton = 1;
			}
			else
			{
			}
			if (nLCDButtons == 4)
			{
				while (nLCDButtons == 4)
				{
				}
				auton = 3;
			}
			else
			{
			}
			break;
		case 3://blue autoloader
			displayLCDCenteredString(0, "Blue 1");
			if (nLCDButtons == 1)
			{
				while (nLCDButtons == 1)
				{
				}
				auton = 2;
			}
			else
			{
			}
			if (nLCDButtons == 4)
			{
				while (nLCDButtons == 4)
				{
				}
				auton = 4;
			}
			else
			{
			}
			break;
		case 4://blue posts
			displayLCDCenteredString(0, "Blue 2");
			if (nLCDButtons == 1)
			{
				while (nLCDButtons == 1)
				{
				}
				auton = 3;
			}
			else
			{
			}
			if (nLCDButtons == 4)
			{
				while (nLCDButtons == 4)
				{
				}
				auton = 5;
			}
			else
			{
			}
			break;
		case 5://Programming skills
			displayLCDCenteredString(0, "Pr. Skills");
			if (nLCDButtons == 1)
			{
				while (nLCDButtons == 1)
				{
				}
				auton = 4;
			}
			else
			{
			}
			if (nLCDButtons == 4)
			{
				while (nLCDButtons == 4)
				{
				}
				auton = 6;
			}
			else
			{
			}
			break;
		case 6://Emergency fallback
			displayLCDCenteredString(0, "Emergency");
			if (nLCDButtons == 1)
			{
				while (nLCDButtons == 1)
				{
				}
				auton = 5;
			}
			else
			{
			}
			if (nLCDButtons == 4)
			{
				while (nLCDButtons == 4)
				{
				}
				auton = 1;
			}
			else
			{
			}
			break;
		}
	}
}//Pre-autonomous block end
task autonomous(){//Autonomous block begin
	clearLCDLine(1);
	switch(auton)
	{
	case 1://red 1
		
		break;
	case 2://red 2
		
		break;
	case 3://blue 1
		
		break;
	case 4://blue 2
		
		break;
	case 5://programming skills
		
		break;
	case 6://emergency fallback
		
		break;
	}
	while(bIfiAutonomousMode){//"catch" program while autonomous mode is active to stop auton code from looping
		halt();
	}
}//Autonomous block end
task usercontrol(){//Usercontrol block begin
	clearDebugStream();
	writeDebugStreamLine("Program start");
	clearLCDLine(0);
	bLCDBacklight = true;
	clearTimer(T1);
	while (true){
		batteryLCD();
		if (vexRT[Btn8D]==1){
			halt();
		}
		else if (nLCDButtons==2){
			halt();
		}
		else if (vexRT[Btn5U] == 1){
			left(127);
		}
		else if (vexRT[Btn6U] == 1){
			right(127);
		}
		else if (vexRT[Btn8R] == 1){
			calJoy();
		}
		else if (vexRT[Btn8U] == 1){
			if (batteryLCDBool == true){
				batteryLCDBool = false;
				wait1Msec(500);
			}
			else if (batteryLCDBool == false){
				batteryLCDBool = true;
				wait1Msec(500);
			}
		}
		else if (vexRT[Btn6D] == 1){
			if (-vexRT[AccelX]*2 > 127){
				gX = 127;
			}
			else if (vexRT[AccelX]*2 < -127){
				gX = -127;
			}
			else{
				gX = (-vexRT[AccelX]*2);
			}
			if (-vexRT[AccelY]*2 > 127){
				gY = 127;
			}
			else if (vexRT[AccelY]*2 < -127){
				gY = -127;
			}
			else{
				gY = (-vexRT[AccelY]*2);
			}
			motor[leftMotorF] = (gY + gX);
			motor[leftMotorR] = (gY + gX);
			motor[rightMotorF] = (gY - gX);
			motor[rightMotorR] = (gY - gX);
		}
		else{
			motor[leftMotorF] = vexRT[Ch3] - joy1Y;
			motor[leftMotorR] = vexRT[Ch3] - joy1Y;
			motor[rightMotorF] = vexRT[Ch2] - joy2Y;
			motor[rightMotorR] = vexRT[Ch2] - joy2Y;
		}
		motor[armMotorL1] = vexRT[Ch2Xmtr2];
		motor[armMotorL2] = vexRT[Ch2Xmtr2];
		motor[armMotorR1] = vexRT[Ch2Xmtr2];
		motor[armMotorR2] = vexRT[Ch2Xmtr2];
		motor[rollerMotor] = vexRT[Ch3Xmtr2];
		if (vexRT[Btn6UXmtr2] == 1){
			motor[clawMotor] = 75;
		}
		else if (vexRT[Btn6DXmtr2] == 1){
			motor[clawMotor] = -75;
		}
		else{
			motor[clawMotor] = 0;
		}
	}
}
//usercontrol block end
