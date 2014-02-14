#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	intakeRoller = new Victor(INTAKE_ROLLER_VICTOR_CHANNEL);
	intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	intakeArm = new DoubleSolenoid(INTAKE_ARM_SOLENOID_CHANNEL_A, INTAKE_ARM_SOLENOID_CHANNEL_B);
	
	launcherMotor = new Victor(LAUNCHER_MOTOR_VICTOR_CHANNEL);	
	pulseSwitch = new DigitalInput(1, PULSE_SWITCH_CHANNEL);
	armLauncherSwitch = new DigitalInput(1, ARM_LAUNCHER_SWITCH_CHANNEL);
	isCocked = false;
	lastPulse = false;
	launchState = STATE_OFF;
	
	stopper = new DoubleSolenoid(STOPPER_SOLENOID_CHANNEL_A, STOPPER_SOLENOID_CHANNEL_B);
	cameraMotor = new Victor(CAMERA_VICTOR_CHANNEL);
	pot = new AnalogChannel(1, 1);
	
	timer = new Timer();
	timer->Start();
	initTime = 0;
	currentTime = 0;
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	delete intakeArm;
	delete launcherMotor;
	delete pulseSwitch;
	delete armLauncherSwitch;
	delete stopper;
	delete cameraMotor;
	delete pot;
	
	intakeRoller = NULL;
	intakeSwitch = NULL;
	intakeArm = NULL;
	launcherMotor = NULL;
	pulseSwitch = NULL;
	armLauncherSwitch = NULL;
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
			intakeRoller->Set(speed<0?speed*-1.0:speed, SYNC_STATE_OFF);
		}
		else if(outtake)
		{
			intakeRoller->Set(-1, SYNC_STATE_OFF);
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
				intakeRoller->Set(1, SYNC_STATE_OFF);
			}
			else if(outtake)
			{
				intakeRoller->Set(-1, SYNC_STATE_OFF);
			}
		}
	}		
}

void AnesthesiologistManipulator::launchBall(bool launchTrigger, bool safetySwitch)
{	
	bool lastPressed = true;
	static bool init = true;
	
	switch(launchState)	
	{
	case STATE_OFF:
		
		if(armLauncherSwitch->Get() == 1) 
		{
			launchState = STATE_HOLD;
		}
		break;
	case STATE_HOLD:
		
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
		if(armLauncherSwitch->Get() == 0) 
		{
			launchState = STATE_OFF;
		}
		
		if(launchTrigger && safetySwitch)
		{
			launchState = STATE_RESET;
		}
		break;
	case STATE_RESET:
		
		launcherMotor->Set(1, SYNC_STATE_OFF);
		
		if(armLauncherSwitch->Get() == 0) 
		{
			launchState = STATE_OFF;
		}
		
		if(pulseSwitch->Get() == 1)
		{
			lastPulse = true;
		}
		if(pulseSwitch->Get() == 0 && lastPulse)
		{
			lastPulse = false;
			launchState = STATE_COCKED;
		}
		break;
	case STATE_COCKED:
		
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
		if(armLauncherSwitch->Get() == 0) 
		{
			launchState = STATE_OFF;
		}
		
		if(lastPressed && !launchTrigger && !safetySwitch)
		{
			lastPressed = false;
		}
		if(launchTrigger && safetySwitch && !lastPressed && intakeArm->Get() == DoubleSolenoid::kForward)
		{
			launchState = STATE_FIRE;
		}
		break;
	case STATE_FIRE:
		
		if(armLauncherSwitch->Get() == 0) 
		{
			launchState = STATE_OFF;
		}
		
		if(init)
		{
			initTime = timer->Get();
			init = false;
		}
		currentTime = timer->Get();
		
		if(currentTime < LAUNCH_TIME + initTime)
		{
			launcherMotor->Set(1, SYNC_STATE_OFF);
		}
		else
		{
			launchState = STATE_HOLD;
		}
		break;
	default:
		launchState = STATE_OFF;
	}
}

//void AnesthesiologistLauncher::launchBall(bool launch)
//{	
//	if(launcherSwitch->Get() == 1)
//	{
//		launcherMotor->Set(0, SYNC_STATE_OFF);
//		isCocked = true;
//	}
//	else
//	{
//		launcherMotor->Set(.5, SYNC_STATE_OFF);
//		isCocked = false;
//	}
//	
//	if(isCocked)
//	{
//		if(launch && !isLastLaunch)
//		{
//			launcherMotor->Set(1, SYNC_STATE_OFF);
//			isLastLaunch = true;
//		}
//		else if(!launch && isLastLaunch)
//		{
//			isLastLaunch = false;
//			launcherMotor->Set(0, SYNC_STATE_OFF);
//		}
//	}
//	
//}

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
