#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	intakeRoller = new Victor(INTAKE_ROLLER_VICTOR_CHANNEL);
	intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	intakeArm = new DoubleSolenoid(INTAKE_ARM_SOLENOID_CHANNEL_A, INTAKE_ARM_SOLENOID_CHANNEL_B);
	
	stopper = new DoubleSolenoid(STOPPER_SOLENOID_CHANNEL_A, STOPPER_SOLENOID_CHANNEL_B);
	cameraMotor = new Victor(CAMERA_VICTOR_CHANNEL);
	pot = new AnalogChannel(1, POT_CHANNEL);
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	delete intakeArm;
	delete stopper;
	delete cameraMotor;
	delete pot;
	
	intakeRoller = NULL;
	intakeSwitch = NULL;
	intakeArm = NULL;
	stopper = NULL;
	cameraMotor = NULL;
	pot = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool intake, bool outtake, double speed)
{
	bool lastSwitchHit = false;
	bool lastPressed = true;
	
	if(!lastSwitchHit && intakeSwitch->Get() == 0)
	{
		if(intake)
		{
			//intakeRoller->Set(speed<0?speed*-1.0:speed, SYNC_STATE_OFF);
			intakeRoller->Set(speed, SYNC_STATE_OFF);
		}
		else if(outtake)
		{
			//intakeRoller->Set(-1, SYNC_STATE_OFF);
			intakeRoller->Set(speed*-1, SYNC_STATE_OFF);
		}
		else
		{
			intakeRoller->Set(0, SYNC_STATE_OFF);
		}
	}
	
	if(!lastSwitchHit && intakeSwitch->Get() == 1)//TODO: test for 0 or 1
	{
		intakeRoller->Set(0, SYNC_STATE_OFF);
		lastSwitchHit = true;
	}
	
	if(lastSwitchHit && intakeSwitch->Get() == 1)
	{
		if(lastPressed && (!intake && !outtake))
		{
			lastPressed = false;
		}
		if(!lastPressed && ( intake || outtake))
		{
			if(intake)
			{
				intakeRoller->Set(speed, SYNC_STATE_OFF);
			}
			else if(outtake)
			{
				intakeRoller->Set(speed*-1, SYNC_STATE_OFF);
			}
			else
			{
				intakeRoller->Set(0, SYNC_STATE_OFF);
			}
		}
	}		
}

void AnesthesiologistManipulator::moveArm(bool isIntake, bool isStored)
{
	if(isIntake)
	{
		intakeArm->Set(DoubleSolenoid::kForward);
	}
	else if(isStored)
	{
		intakeArm->Set(DoubleSolenoid::kReverse);
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

void AnesthesiologistManipulator::toggleCameraPosition(bool isForward)
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
	if(!isForward && !isBackLimit)
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
	if(intakeArm->Get() == DoubleSolenoid::kForward)
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
