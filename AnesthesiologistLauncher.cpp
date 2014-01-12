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

bool AnesthesiologistLauncher::checkIfCocked()
{
	
}

void AnesthesiologistLauncher::launchBall()
{
	
}
