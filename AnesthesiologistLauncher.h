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
	
	Ultrasonic *ultrasonicSensor;
	Talon *launcherMotor;
	bool isCocked;
	int launchState;
	int autoLaunchState;
	Timer *timer;
	
private:
	DigitalInput *pulseSwitch;
	DigitalInput *armLauncherSwitch;
	AnesthesiologistManipulator *manipulator;
	
	bool lastPulse;
	double initTime; 
	double resetTime;
	double currentTime; 
	bool init; 
	bool lastPressed; 
		
	
};
#endif
