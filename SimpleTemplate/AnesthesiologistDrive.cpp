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
	
//	leftDriveEncoder = new Encoder(LEFT_DRIVE_ENCODER_CHANNEL_A, LEFT_DRIVE_ENCODER_CHANNEL_B, true, Encoder::k1X);
//	rightDriveEncoder = new Encoder(RIGHT_DRIVE_ENCODER_CHANNEL_A, RIGHT_DRIVE_ENCODER_CHANNEL_B, false, Encoder::k1X);
//	leftDriveEncoder->Start();
//	rightDriveEncoder->Start();
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
	frontRightMotor->Set(velocity, SYNC_STATE_OFF);
	rearRightMotor->Set(velocity, SYNC_STATE_OFF);
}

//void AnesthesiologistDrive::setEncodersLinear(double target, double speed)
//{
//	bool bInit = true;
//	if(bInit)
//	{
//		leftDriveEncoder->Reset();
//		rightDriveEncoder->Reset();
//		bInit = false;
//	}
//	if(isAtLeftTarget && isAtRightTarget)
//	{
//		
//		isAtLinearTarget = true;
//		bInit = true;
//	}
//	else
//	{
//		isAtLeftTarget = false;
//		isAtRightTarget = false;	
//		isAtLinearTarget = false;
//	}
//	
//	currentTicksLeft = leftDriveEncoder->Get();
//	currentTicksRight = rightDriveEncoder->Get();
//	
//	if (currentTicksLeft < (target / INCHES_PER_TICK) - TICKS_DEADZONE)
//	{
//		setLeftMotors(speed);
//	}
//	else if (currentTicksLeft > (target / INCHES_PER_TICK) + TICKS_DEADZONE)
//	{
//		setLeftMotors(-speed);
//	}
//	else
//	{
//		setLeftMotors(0);
//		isAtLeftTarget = true;
//	}
//	
//	if (currentTicksRight < (target / INCHES_PER_TICK) - TICKS_DEADZONE)
//	{
//		setRightMotors(speed);
//	}
//	else if (currentTicksRight > (target / INCHES_PER_TICK) + TICKS_DEADZONE)
//	{
//		setRightMotors(-speed);
//	}
//	else
//	{
//		setRightMotors(0);
//		isAtRightTarget = true;
//	}
//	
//}
//
//void AnesthesiologistDrive::setEncoderLeft(double target, double speed)
//{
//	if(isAtLeftTarget)
//	{
//		leftDriveEncoder->Reset();
//	}
//	else
//	{
//		isAtLeftTarget = false;
//	}
//	
//	currentTicksLeft = leftDriveEncoder->Get();
//	
//	if (currentTicksLeft < target - TICKS_DEADZONE)
//	{
//		setLeftMotors(speed);
//	}
//	else if (currentTicksLeft > target + TICKS_DEADZONE)
//	{
//		setLeftMotors(-speed);
//	}
//	else
//	{
//		setLeftMotors(0);
//		isAtLeftTarget = true;
//	}
//	
//}
//
//void AnesthesiologistDrive::setEncoderRight(double target, double speed)
//{
//	if(isAtRightTarget)
//	{
//		rightDriveEncoder->Reset();
//	}
//	else
//	{
//		isAtRightTarget = false;	
//	}
//	
//	currentTicksRight = rightDriveEncoder->Get();
//	
//	if (currentTicksRight < target - TICKS_DEADZONE)
//	{
//		setRightMotors(speed);
//	}
//	else if (currentTicksRight > target + TICKS_DEADZONE)
//	{
//		setRightMotors(-speed);
//	}
//	else
//	{
//		setRightMotors(0);
//		isAtRightTarget = true;
//	}
//	
//}
//
//void AnesthesiologistDrive::autoLinear(double target, double speed)
//{
//	setEncodersLinear(target, speed);
//}
//
//void AnesthesiologistDrive::autoLeft(double target, double speed)
//{
//	setEncoderLeft(target, speed);
//}
//
//void AnesthesiologistDrive::autoRight(double target, double speed)
//{
//	setEncoderRight(target, speed);
//}

void AnesthesiologistDrive::drive()
{
	leftCmd = linearVelocity + turnSpeed;
	rightCmd = linearVelocity - turnSpeed;
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}
