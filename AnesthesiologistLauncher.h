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
	void autoLaunch(bool launch);	
	
	bool isIn();
	
	bool isCocked;
	int launchState;
	int autoLaunchState;
	Timer *timer;
	
private:
	Victor *launcherMotor;
	DigitalInput *pulseSwitch;
	DigitalInput *armLauncherSwitch;
	AnesthesiologistManipulator *manipulator;
	
	Ultrasonic *ultrasonicSensor;
	
	bool lastPulse;
	double initTime; 
	double currentTime; 	
	
};
#endif
