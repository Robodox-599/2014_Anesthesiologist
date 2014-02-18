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
	
	void launchBall(bool launchTrigger, bool safetySwitch, bool killSwitchA, bool killSwitchB);
	void autoLaunch();	
	void autoReset();
	bool isIn();
	
	Ultrasonic *ultrasonicSensor;
	Talon *launcherMotor;
	int launchState;
	int autoLaunchState;
	Timer *timer;
	
private:
	DigitalInput *pulseSwitch;
	DigitalInput *armLauncherSwitch;
	AnesthesiologistManipulator *manipulator;
	
	double initTime; 	
	double currentTime; 
	bool init; 
	bool lastPulse;
	bool lastPressed;
	
	double resetStart;
	double resetEnd;
	
};
#endif
