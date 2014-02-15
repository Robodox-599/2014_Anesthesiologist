#include "AnesthesiologistLauncher.h"

AnesthesiologistLauncher::AnesthesiologistLauncher()
{
	launcherMotor = new Victor(LAUNCHER_MOTOR_VICTOR_CHANNEL);	
	pulseSwitch = new DigitalInput(1, PULSE_SWITCH_CHANNEL);
	armLauncherSwitch = new DigitalInput(1, ARM_LAUNCHER_SWITCH_CHANNEL);
	isCocked = false;
	lastPulse = false;
	launchState = STATE_OFF;
	
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
//		if(launchTrigger && safetySwitch && !lastPressed && getArmPosition())
//		{
//			launchState = STATE_FIRE;
//		}
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

