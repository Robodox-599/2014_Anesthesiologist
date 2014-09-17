#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	intakeRoller = new Talon(1, INTAKE_ROLLER_CHANNEL);
	intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	intakeArm = new DoubleSolenoid(INTAKE_ARM_SOLENOID_CHANNEL_A, INTAKE_ARM_SOLENOID_CHANNEL_B);
	
//	cameraMotor = new Victor(CAMERA_VICTOR_CHANNEL);
//	pot = new AnalogChannel(1, POT_CHANNEL);
	
	step = 0;
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	delete intakeArm;
//	delete stopper;
//	delete cameraMotor;
//	delete pot;
	
	intakeRoller = NULL;
	intakeSwitch = NULL;
	intakeArm = NULL;
//	stopper = NULL;
//	cameraMotor = NULL;
//	pot = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool outtake, bool intake, double speed)
{
	bool lastSwitchHit = false;

	if(!lastSwitchHit)
	{
		step = 1;
		if(outtake)
		{
			intakeRoller->Set(-speed, SYNC_STATE_OFF);
		}
		else if(intake)
		{
			intakeRoller->Set(speed, SYNC_STATE_OFF);
		}
		else
		{
			intakeRoller->Set(0, SYNC_STATE_OFF);
		}
	}
}

void AnesthesiologistManipulator::moveArm(bool isIntake, bool isStored)
{
	if(isIntake)
	{
		intakeArm->Set(DoubleSolenoid::kReverse);
	}
	else if(isStored)
	{
		intakeArm->Set(DoubleSolenoid::kForward);
	}
}

//void AnesthesiologistManipulator::toggleCameraPosition(bool isForward)
//{
//	bool isForwardLimit = false;
//	bool isBackLimit = false;
//	
//	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
//	{
//		isBackLimit = true;
//	}
//	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
//	{
//		isForwardLimit = true;
//	}
//	else
//	{
//		isForwardLimit = false;
//		isBackLimit = false;
//	}
//	
//	if(isForwardLimit || isBackLimit)
//	{
//		cameraMotor->Set(0, SYNC_STATE_OFF);
//	}
//	if(isForward && !isForwardLimit)
//	{
//		cameraMotor->Set(1, SYNC_STATE_OFF);
//	}
//	if(!isForward && !isBackLimit)
//	{
//		cameraMotor->Set(-1, SYNC_STATE_OFF);
//	}
//	
//}

bool AnesthesiologistManipulator::getArmPosition()
{
	if(intakeArm->Get() == DoubleSolenoid::kReverse)
	{
		return true;
	}
	return false;
}

//int AnesthesiologistManipulator::getCameraPosition()
//{
//	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
//	{
//		return 2;
//	}
//	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
//	{
//		return 1;
//	}
//	return 0;
//}
