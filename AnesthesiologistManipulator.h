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
	void moveArm(bool isIntake, bool isStored);
	
	void setRoller();	
	void setVelocity(double input);
	double getVelocity();
	
	bool getArmPosition();
	
private:
	Victor *intakeRoller;
	DigitalInput *intakeSwitch;
	DoubleSolenoid *leftIntakeArm;
	DoubleSolenoid *rightIntakeArm;
	double targetVelocity;
	
};
#endif
