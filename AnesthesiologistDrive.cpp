#include "AnesthesiologistDrive.h"

AnesthesiologistDrive::AnesthesiologistDrive(AnesthesiologistOperatorInterface *opInt)
{
	if(opInt) oi = opInt;
	
	linearVelocity = 0;
	turnSpeed = 0;
	
	shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B);   
	shifter->Set(DoubleSolenoid::kReverse);
	
	frontLeftMotor = new Talon(1, DRIVE_FRONT_LEFT_MOTOR_CHANNEL);   
	rearLeftMotor = new Talon(1, DRIVE_REAR_LEFT_MOTOR_CHANNEL);   
	frontRightMotor = new Talon(1, DRIVE_FRONT_RIGHT_MOTOR_CHANNEL); 
	rearRightMotor = new Talon(1, DRIVE_REAR_RIGHT_MOTOR_CHANNEL);
}

AnesthesiologistDrive::~AnesthesiologistDrive()
{
	delete shifter;
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
	
	shifter = NULL;
	frontLeftMotor = NULL;
	rearLeftMotor = NULL;
	frontRightMotor = NULL;
	rearRightMotor = NULL;
}

bool AnesthesiologistDrive::shift(UINT8 highButton, UINT8 lowButton)
{
	//static?
	bool lastGearWasHi = true;
	
	if(lowButton)
	{
		shifter->Set(DoubleSolenoid::kForward);
		lastGearWasHi = false;
	}
	else if(highButton)
	{
		shifter->Set(DoubleSolenoid::kReverse);
		lastGearWasHi = true;
	}
	
	return lastGearWasHi;	
}

void AnesthesiologistDrive::setLinVelocity(double linVal)
{
	if(linVal > DEADZONE)
	{
		linearVelocity = linVal;
	}
	else if(linVal < -DEADZONE)
	{
		linearVelocity = linVal;
	}
	else 
	{
		linearVelocity = 0; //NEUTRAL
	}	
}

double AnesthesiologistDrive::getLinVelocity()
{
	return linearVelocity;
}

void AnesthesiologistDrive::setTurnSpeed(double turn, bool turboButton)
{
	if((turn > DEADZONE && !turboButton) || (turn < -DEADZONE && !turboButton)) 
	{
		turnSpeed = turn * REDUCTION;
	}
	if(turn < DEADZONE && turn > -DEADZONE) 
	{
		turnSpeed = 0; //NEUTRAL
	}
	if((turn > DEADZONE && turboButton) || (turn < -DEADZONE && turboButton)) 
	{
		turnSpeed = turn;
	}
}

double AnesthesiologistDrive::getTurnSpeed()
{
	return turnSpeed;
}

double AnesthesiologistDrive::reduceTurn(double reduceBy)
{
	return turnSpeed * reduceBy;
}

void AnesthesiologistDrive::setLeftMotors(double velocity)
{
	frontLeftMotor->Set(-velocity, SYNC_STATE_OFF);
	rearLeftMotor->Set(-velocity, SYNC_STATE_OFF);
}

void AnesthesiologistDrive::setRightMotors(double velocity)
{
	frontRightMotor->Set(-velocity, SYNC_STATE_OFF);
	rearRightMotor->Set(-velocity, SYNC_STATE_OFF);
}

void AnesthesiologistDrive::drive()
{
	leftCmd = linearVelocity + turnSpeed;
	rightCmd = linearVelocity - turnSpeed;
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}
