#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	intakeRoller = new Victor(INTAKE_ROLLER_VICTOR_CHANNEL);
	intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	leftIntakeArm = new DoubleSolenoid(LEFT_INTAKE_ARM_SOLENOID_CHANNEL_A, LEFT_INTAKE_ARM_SOLENOID_CHANNEL_B);
	rightIntakeArm = new DoubleSolenoid(RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_A, RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_B);
	cameraMotor = new Victor(CAMERA_VICTOR_CHANNEL);
	pot = new AnalogChannel(1, 1);
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	delete leftIntakeArm;
	delete rightIntakeArm;
	delete cameraMotor;
	delete pot;
	
	intakeRoller = NULL;
	intakeSwitch = NULL;
	leftIntakeArm = NULL;
	rightIntakeArm = NULL;
	cameraMotor = NULL;
	pot = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool intake)
{
	bool lastSwitchHit = false;
	
	if(intake && !lastSwitchHit && intakeSwitch->Get() == 1)//TODO: test for 0 or 1
	{
		intakeRoller->Set(0);
		//TODO: add a 1 second wait here
	}
	else
	{
		setRoller();
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

void AnesthesiologistManipulator::toggleCameraPosition(bool isForward, bool isBack)
{
	bool isForwardLimit = false;
	bool isBackLimit = false;
	
	if(true)//TODO: set as top pot value
	{
		isForwardLimit = true;
	}
	else if(false)//TODO: set as bottom pot value
	{
		isBackLimit = true;
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
		cameraMotor->Set(1, SYNC_STATE_OFF);
	}
	if(isBack && !isBackLimit)
	{
		cameraMotor->Set(-1, SYNC_STATE_OFF);
	}
	
}

void AnesthesiologistManipulator::setRoller()
{
	intakeRoller->Set(targetVelocity * REDUCTION); 
}

void AnesthesiologistManipulator::setVelocity(double input)
{
	targetVelocity = input;
}

double AnesthesiologistManipulator::getVelocity()
{
	return targetVelocity;
}

bool AnesthesiologistManipulator::getArmPosition()
{
	if(leftIntakeArm->Get())
	{
		return true;
	}
	return false;
}

bool AnesthesiologistManipulator::getCameraPosition()
{
	if(true)//TODO: set as top pot value
	{
		return true;
	}
	return false;
}
