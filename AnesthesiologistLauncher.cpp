#include "AnesthesiologistLauncher.h"

AnesthesiologistLauncher::AnesthesiologistLauncher()
{
	manipulator = new AnesthesiologistManipulator();
	launcherMotor = new Talon(1, LAUNCHER_MOTOR_CHANNEL);	
	pulseSwitch = new DigitalInput(1, PULSE_SWITCH_CHANNEL);
	armLauncherSwitch = new DigitalInput(1, ARM_LAUNCHER_SWITCH_CHANNEL);
	ultrasonicSensor = new Ultrasonic(SONAR_INPUT, SONAR_OUTPUT);
	
	isCocked = false;
	lastPulse = false;
	launchState = STATE_HOLD;
	autoLaunchState = STATE_HOLD;	
	
	init = true;
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
	delete armLauncherSwitch;
	delete timer;
	
	launcherMotor = NULL;
	pulseSwitch = NULL;
	armLauncherSwitch = NULL;
	timer = NULL;
}

void AnesthesiologistLauncher::launchBall(bool launchTrigger, bool safetySwitch)
{	
	switch(launchState)	
	{
	case STATE_OFF:
		
		if(armLauncherSwitch->Get() == 1) 
		{
			launchState = STATE_HOLD;
		}
		break;
	case STATE_HOLD:
		init = true;
			
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
//		if(armLauncherSwitch->Get() == 0) 
//		{
//			launchState = STATE_OFF;
//		}
		if(lastPressed && !launchTrigger && !safetySwitch)
		{
			lastPressed = false;
		}
		if(launchTrigger && safetySwitch && !lastPressed)
		{
			lastPressed = true;
			launchState = STATE_RESET;
			resetTime = timer->Get();
		}
		break;
	case STATE_RESET:
		if (resetTime < TIME_TO_SLOW_SPEED)
			launcherMotor->Set(-1, SYNC_STATE_OFF);
		else
			launcherMotor->Set(LAUNCHER_MOTOR_SLOW_SPEED, SYNC_STATE_OFF);
//		if(armLauncherSwitch->Get() == 0) 
//		{
//			launchState = STATE_OFF;
//		}
		
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
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
//		if(armLauncherSwitch->Get() == 0) 
//		{
//			launchState = STATE_OFF;
//		}
		
		if(lastPressed && !launchTrigger && !safetySwitch)
		{
			lastPressed = false;
		}
		if(launchTrigger && safetySwitch && !lastPressed) //&& manipulator->getArmPosition())
		{
			lastPressed = true;
			launchState = STATE_FIRE;
		}
		break;
	case STATE_FIRE:
		
//		if(armLauncherSwitch->Get() == 0) 
//		{
//			launchState = STATE_OFF;
//		}
		
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
void AnesthesiologistLauncher::autoLaunch(bool launch)
{	
	static bool init = true;
	
	switch(autoLaunchState)	
	{
	case STATE_HOLD:
		
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
		if(launch)
		{
			autoLaunchState = STATE_RESET;
		}
		break;
	case STATE_RESET:
		
		launcherMotor->Set(1, SYNC_STATE_OFF);
			
		if(pulseSwitch->Get() == 1)
		{
			lastPulse = true;
		}
		if(pulseSwitch->Get() == 0 && lastPulse)
		{
			lastPulse = false;
			autoLaunchState = STATE_COCKED;
		}
		break;
	case STATE_COCKED:
		
		launcherMotor->Set(0, SYNC_STATE_OFF);
		
		if(launch && manipulator->getArmPosition() == true)
		{
			autoLaunchState = STATE_FIRE;
		}
		break;
	case STATE_FIRE:
			
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
			autoLaunchState = STATE_HOLD;
		}
		break;
	default:
		autoLaunchState = STATE_HOLD;
	}
}

bool AnesthesiologistLauncher::isIn()
{
	if (ultrasonicSensor->GetRangeInches() < 0 || ultrasonicSensor->GetRangeInches() > 6)
	{
		return false;
	}
	else 
	{
		return true;
	}
}
