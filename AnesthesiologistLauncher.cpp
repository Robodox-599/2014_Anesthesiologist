#include "AnesthesiologistLauncher.h"

AnesthesiologistLauncher::AnesthesiologistLauncher()
{
	AnesthesiologistLauncher(LAUNCHER_MOTOR_VICTOR_CHANNEL, LAUNCHER_SOLENOID_CHANNEL);	
}

AnesthesiologistLauncher::AnesthesiologistLauncher(UINT8 launcherVictorChannel, UINT8 launcherSolenoid)
{
	launcherMotor = new Victor(launcherVictorChannel);	
	launcherPiston = new Solenoid(launcherSolenoid);
}

AnesthesiologistLauncher::~AnesthesiologistLauncher()
{
	delete launcherMotor;
	delete launcherPiston;

	launcherMotor = NULL;
	launcherPiston = NULL;
}

void AnesthesiologistLauncher::launchBall(bool launch)
{
	if(launch && launcherPiston->Get() == 0) // This'll possibly create a logical error, since if you pass launch==true but the piston is already up, it'll flip positions
	{
		launcherPiston->Set(1);
	} 
	else
	{
		launcherPiston->Set(0);
	}
	
}
