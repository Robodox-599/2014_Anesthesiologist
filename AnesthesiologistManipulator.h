#ifndef ANESTHESIOLOGIST_MANIPULATOR_H
#define ANESTHESIOLOGIST_MANIPULATOR_H
#include "WPILib.h"
#include "RobodoxTimer.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistManipulator
{
public:
	AnesthesiologistManipulator();
	~AnesthesiologistManipulator();
	
	void intakeBall(bool intake);
	
	void setRoller();	
	void setVelocity(double input);
	double getVelocity();
	
	void moveArmEncoder(double target, double speed);
	
	Encoder *armEncoder;
	
private:
	Victor *intakeRoller;
	DigitalInput *intakeSwitch;
	Victor *intakeArm;
	double targetVelocity;
	double currentTicks;	
	
};
#endif
