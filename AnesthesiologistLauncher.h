#ifndef ANESTHESIOLOGIST_LAUNCHER_H
#define ANESTHESIOLOGIST_LAUNCHER_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistLauncher
{
public:
	AnesthesiologistLauncher();
	~AnesthesiologistLauncher();
	
	void launchBall(bool launch);
	
	bool isCocked;
	
private:
	Victor *launcherMotor;
	DigitalInput *launcherSwitch;
	
	bool isLastLaunch;

};
#endif
