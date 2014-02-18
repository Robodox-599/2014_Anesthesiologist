#include "AnesthesiologistLauncher.h"

AnesthesiologistLauncher::AnesthesiologistLauncher()
{
	manipulator = new AnesthesiologistManipulator();
	launcherMotor = new Talon(1, LAUNCHER_MOTOR_CHANNEL);	
	pulseSwitch = new DigitalInput(1, PULSE_SWITCH_CHANNEL);
	armLauncherSwitch = new DigitalInput(1, ARM_LAUNCHER_SWITCH_CHANNEL);
	ultrasonicSensor = new Ultrasonic(SONAR_OUTPUT, SONAR_INPUT, Ultrasonic::kInches);
	ultrasonicSensor->SetEnabled(1);
	ultrasonicSensor->SetAutomaticMode(1);
	
	lastPulse = false;
	launchState = STATE_HOLD;
	autoLaunchState = STATE_COCKED;	
	
	init = true;
	lastPressed = true;
	resetStart = 0;
	resetEnd = 0;
	
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
	delete ultrasonicSensor;
	delete timer;
	
	launcherMotor = NULL;
	pulseSwitch = NULL;
	armLauncherSwitch = NULL;
	ultrasonicSensor = NULL;
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
		if(launchTrigger && safetySwitch && !lastPressed && manipulator->getArmPosition() == false)
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



void AnesthesiologistLauncher::autoLaunch()
{	
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
		launcherMotor->Set(0);
	}
}

//void AnesthesiologistLauncher::autoReset()
//{
//	if(newCycle)
//	{
//		if(init)
//		{
//			initTime = timer->Get();
//			init = false;
//		}
//		currentTime = timer->Get();
//		
//		if(currentTime < RESET_TIME + initTime)
//		{
//			launcherMotor->Set(-1, SYNC_STATE_OFF);
//		}
//		else
//		{
//			launcherMotor->Set(SLOW_SPEED, SYNC_STATE_OFF);
//		}
//		
//		if(pulseSwitch->Get() == 1)
//		{
//			lastPulse = true;
//		}
//		if(pulseSwitch->Get() == 0 && lastPulse)
//		{
//			launcherMotor->Set(0, SYNC_STATE_OFF);
//		}
//	}
//	else
//	{
//		launcherMotor->Set(0, SYNC_STATE_OFF);
//	}
//}

bool AnesthesiologistLauncher::isIn()
{
	if (ultrasonicSensor->GetRangeInches() <= 0 || ultrasonicSensor->GetRangeInches() > 6)
	{
		return false;
	}
	else 
	{
		return true;
	}
}
