#include "AnesthesiologistLauncher.h"

AnesthesiologistLauncher::AnesthesiologistLauncher(AnesthesiologistManipulator* manip)
{
	manipulator = manip;//new AnesthesiologistManipulator();
	launcherMotor = new Talon(1, LAUNCHER_MOTOR_CHANNEL);	
	pulseSwitch = new DigitalInput(1, PULSE_SWITCH_CHANNEL);
	//stopper = new DoubleSolenoid(STOPPER_SOLENOID_CHANNEL_A, STOPPER_SOLENOID_CHANNEL_B);
	
	lastPulse = false;
	launchState = STATE_HOLD;
	autoLaunchState = STATE_COCKED;	
	
	init = true;
	autonInit1 = true;
	autonInit2 = true;
	lastPressed = true;
	
	timer = new Timer();
	timer->Start();
	initTime = 0;
	currentTime = 0;
}

AnesthesiologistLauncher::~AnesthesiologistLauncher()
{
	delete launcherMotor;
	delete pulseSwitch;
	delete timer;
	
	launcherMotor = NULL;
	pulseSwitch = NULL;
	timer = NULL;
}

void AnesthesiologistLauncher::launchBall(bool launchTrigger, bool safetySwitch, bool killSwitchA, bool killSwitchB)
{	
	switch(launchState)	
	{
	case STATE_OFF:	
		launcherMotor->Set(0, SYNC_STATE_OFF);
		if(lastPressed && !killSwitchA && !killSwitchB)
		{
			lastPressed = false;
		}
		if(killSwitchA && killSwitchB && !lastPressed)
		{
			lastPressed = true;
			launchState = STATE_HOLD;
		}
		break;
	case STATE_HOLD:
		
		if(killSwitchA && killSwitchB)
		{
			launchState = STATE_OFF;
		}
		
		init = true;
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
		if(lastPressed && !launchTrigger && !safetySwitch)
		{
			lastPressed = false;
		}
		if(launchTrigger && safetySwitch && !lastPressed)
		{
			lastPressed = true;
			launchState = STATE_RESET;
		}
		break;
	case STATE_RESET:
		
		if(killSwitchA && killSwitchB) 
		{
			launchState = STATE_OFF;
		}
		if(init)
		{
			initTime = timer->Get();
			init = false;
		}
		currentTime = timer->Get();
		
		if(currentTime < RESET_TIME + initTime)
		{
			launcherMotor->Set(-1, SYNC_STATE_OFF);
		}
		else
		{
			launcherMotor->Set(SLOW_SPEED, SYNC_STATE_OFF);
		}
		
		if(pulseSwitch->Get() == 1)
		{
			lastPulse = true;
		}
		if(pulseSwitch->Get() == 0 && lastPulse)
		{
			launchState = STATE_COCKED;
		}
		break;
	case STATE_COCKED:
		
		if(killSwitchA && killSwitchB) 
		{
			launchState = STATE_OFF;
		}
		init = true;
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
		if(lastPressed && !launchTrigger && !safetySwitch)
		{
			lastPressed = false;
		}
		if(launchTrigger && safetySwitch && !lastPressed && manipulator->getArmPosition() == true)//true?
		{
			lastPressed = true;
			launchState = STATE_FIRE;
		}
		break;
	case STATE_FIRE:
		if(killSwitchA && killSwitchB) 
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
			launcherMotor->Set(-1, SYNC_STATE_OFF);
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

void AnesthesiologistLauncher::autoFirstLaunch()
{	
	if(autonInit1)
	{
		initTime = timer->Get();
		autonInit1 = false;
	}
	currentTime = timer->Get();
	
	if(currentTime < LAUNCH_TIME + initTime)
	{
		launcherMotor->Set(-1, SYNC_STATE_OFF);
	}
	else
	{
		launcherMotor->Set(0);
	}
}

void AnesthesiologistLauncher::autoSecondLaunch()
{	
	if(autonInit2)
	{
		initTime = timer->Get();
		autonInit2 = false;
	}
	currentTime = timer->Get();
	
	if(currentTime < LAUNCH_TIME + initTime)
	{
		launcherMotor->Set(-1, SYNC_STATE_OFF);
	}
	else
	{
		launcherMotor->Set(0);
	}
}

void AnesthesiologistLauncher::autoReset()
{
	if(init)
	{
		initTime = timer->Get();
		init = false;
	}
	currentTime = timer->Get();
	
	if(currentTime < RESET_TIME + initTime)
	{
		launcherMotor->Set(-1, SYNC_STATE_OFF);
	}
	
	if(pulseSwitch->Get() == 1)
	{
		lastPulse = true;
	}
	if(pulseSwitch->Get() == 0 && lastPulse)
	{
		launcherMotor->Set(0, SYNC_STATE_OFF);
	}
}

//void AnesthesiologistLauncher::moveStopper(bool shortShot, bool longShot)
//{
//	if(launchState == STATE_COCKED) 
//	{
//		if(shortShot)
//		{
//			stopper->Set(DoubleSolenoid::kForward);
//		}
//		else if(longShot)
//		{
//			stopper->Set(DoubleSolenoid::kReverse);
//		}
//	}
//}
//
//bool AnesthesiologistLauncher::getStopperPosition()
//{
//	if(stopper->Get() == DoubleSolenoid::kForward)
//	{
//		return true;
//	}
//	return false;
//}

