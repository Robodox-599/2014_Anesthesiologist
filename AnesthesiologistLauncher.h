#ifndef ANESTHESIOLOGIST_LAUNCHER_H
#define ANESTHESIOLOGIST_LAUNCHER_H
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistMacros.h"
	
class AnesthesiologistLauncher
{
public:
	AnesthesiologistLauncher(AnesthesiologistManipulator* manip);
	~AnesthesiologistLauncher();
	
	void launchBall(bool launchTrigger, bool safetySwitch, bool killSwitchA, bool killSwitchB);
	
	void autoFirstLaunch();
	void autoSecondLaunch();
	void autoReset();
		
	Talon *launcherMotor;
	int launchState;
	int autoLaunchState;
	Timer *timer;
	
private:
	DigitalInput *pulseSwitch;
	AnesthesiologistManipulator *manipulator;
	
	double initTime;
	double currentTime;
	bool init;
	bool autonInit1;
	bool autonInit2;
	bool lastPulse;
	bool lastPressed;
	
};
#endif
