#include "AnesthesiologistLauncher.h"

AnesthesiologistLauncher::AnesthesiologistLauncher()
{
	launcherMotor = new Victor(LAUNCHER_MOTOR_VICTOR_CHANNEL);	
	launcherSwitch = new DigitalInput(1, LAUNCHER_SWITCH_CHANNEL);

	isCocked = false;
	isLastLaunch = false;
}

AnesthesiologistLauncher::~AnesthesiologistLauncher()
{
	delete launcherMotor;

	launcherMotor = NULL;
}

void AnesthesiologistLauncher::launchBall(bool launch)
{	
	if(launcherSwitch->Get() == 1)
	{
		launcherMotor->Set(0, SYNC_STATE_OFF);
		isCocked = true;
	}
	else
	{
		launcherMotor->Set(.5, SYNC_STATE_OFF);
		isCocked = false;
	}
	
	if(isCocked)
	{
		if(launch && !isLastLaunch)
		{
			launcherMotor->Set(1, SYNC_STATE_OFF);
			isLastLaunch = true;
		}
		else if(!launch && isLastLaunch)
		{
			isLastLaunch = false;
			launcherMotor->Set(0, SYNC_STATE_OFF);
		}
	}
	
}
