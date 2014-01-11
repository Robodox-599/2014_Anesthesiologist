#ifndef ANESTHESIOLOGIST_LAUNCHER_H
#define ANESTHESIOLOGIST_LAUNCHER_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistLauncher
{
public:
	AnesthesiologistLauncher();
	AnesthesiologistLauncher(UINT8 launcherVictorChannel, UINT8 launcherSolenoid);
	~AnesthesiologistLauncher();
	
	bool checkIfCocked();
	void launchBall();
	
private:
	Victor *launcherMotor;
	Solenoid *launcherPiston;

};
#endif
