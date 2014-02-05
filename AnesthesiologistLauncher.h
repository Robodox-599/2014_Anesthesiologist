#ifndef ANESTHESIOLOGIST_LAUNCHER_H
#define ANESTHESIOLOGIST_LAUNCHER_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistLauncher
{
public:
	AnesthesiologistLauncher();
	AnesthesiologistLauncher(UINT8 launcherVictorChannel);//, UINT8 launcherSolenoid);
	~AnesthesiologistLauncher();
	
	void launchBall(bool launch);
	
	bool isCocked;
	
private:
	Victor *launcherMotor;
	//Solenoid *launcherPiston;
	DigitalInput *launcherSwitch;

};
#endif
