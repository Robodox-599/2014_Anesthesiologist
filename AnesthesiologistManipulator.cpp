#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	intakeRoller = new Victor(INTAKE_ROLLER_VICTOR_CHANNEL);
	intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	leftIntakeArm = new DoubleSolenoid(LEFT_INTAKE_ARM_SOLENOID_CHANNEL_A, LEFT_INTAKE_ARM_SOLENOID_CHANNEL_B);
	rightIntakeArm = new DoubleSolenoid(RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_A, RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_B);
	stopper = new DoubleSolenoid(STOPPER_SOLENOID_CHANNEL_A, STOPPER_SOLENOID_CHANNEL_B);
	cameraMotor = new Victor(CAMERA_VICTOR_CHANNEL);
	pot = new AnalogChannel(1, 1);
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	delete leftIntakeArm;
	delete rightIntakeArm;
	delete stopper;
	delete cameraMotor;
	delete pot;
	
	intakeRoller = NULL;
	intakeSwitch = NULL;
	leftIntakeArm = NULL;
	rightIntakeArm = NULL;
	stopper = NULL;
	cameraMotor = NULL;
	pot = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool intakeSlow, bool intakeFast)
{
	bool lastSwitchHit = false;
	
	if(!lastSwitchHit && intakeSwitch->Get() == 1)//TODO: test for 0 or 1
	{
		intakeRoller->Set(0, SYNC_STATE_OFF);
		//TODO: add a 1 second wait here
	}
	else if(intakeSlow)
	{
		intakeRoller->Set(.5, SYNC_STATE_OFF);
	}
	else if(intakeFast)
	{
		intakeRoller->Set(1, SYNC_STATE_OFF);
	}
	
	lastSwitchHit = intakeSwitch->Get();	
}

void AnesthesiologistManipulator::moveArm(bool isIntake, bool isStored)
{
	if(isIntake)
	{
		leftIntakeArm->Set(DoubleSolenoid::kForward);
		rightIntakeArm->Set(DoubleSolenoid::kForward);
	}
	else if(isStored)
	{
		leftIntakeArm->Set(DoubleSolenoid::kReverse);
		rightIntakeArm->Set(DoubleSolenoid::kReverse);	
	}
}

void AnesthesiologistManipulator::moveStopper(bool shortShot, bool longShot)
{
	if(shortShot)
	{
		stopper->Set(DoubleSolenoid::kForward);
	}
	else if(longShot)
	{
		stopper->Set(DoubleSolenoid::kReverse);
	}
}

void AnesthesiologistManipulator::toggleCameraPosition(bool isForward, bool isBack)
{
	bool isForwardLimit = false;
	bool isBackLimit = false;
	
	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
	{
		isBackLimit = true;
	}
	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
	{
		isForwardLimit = true;
	}
	else
	{
		isForwardLimit = false;
		isBackLimit = false;
	}
	
	if(isForwardLimit || isBackLimit)
	{
		cameraMotor->Set(0, SYNC_STATE_OFF);
	}
	if(isForward && !isForwardLimit)
	{
		cameraMotor->Set(-1, SYNC_STATE_OFF);
	}
	if(isBack && !isBackLimit)
	{
		cameraMotor->Set(1, SYNC_STATE_OFF);
	}
	
}

bool AnesthesiologistManipulator::getStopperPosition()
{
	if(stopper->Get() == DoubleSolenoid::kForward)
	{
		return true;
	}
	return false;
}

bool AnesthesiologistManipulator::getArmPosition()
{
	if(leftIntakeArm->Get() == DoubleSolenoid::kForward)
	{
		return true;
	}
	return false;
}

int AnesthesiologistManipulator::getCameraPosition()
{
	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
	{
		return 2;
	}
	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
	{
		return 1;
	}
	return 0;
}
