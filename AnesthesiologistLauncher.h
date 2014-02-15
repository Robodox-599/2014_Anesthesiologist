#ifndef ANESTHESIOLOGIST_LAUNCHER_H
#define ANESTHESIOLOGIST_LAUNCHER_H
#include "WPILib.h"
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistMacros.h"
	
class AnesthesiologistLauncher
{
public:
	AnesthesiologistLauncher();
	~AnesthesiologistLauncher();
	
	void launchBall(bool launchTrigger, bool safetySwitch);
	
	bool isCocked;
	int launchState;
	Timer *timer;
	
private:
	Victor *launcherMotor;
	DigitalInput *pulseSwitch;
	DigitalInput *armLauncherSwitch;
	
	bool lastPulse;
	double initTime; 
	double currentTime; 
	
};
#endif
