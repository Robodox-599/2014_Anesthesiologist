#ifndef ANESTHESIOLOGIST_MANIPULATOR_H
#define ANESTHESIOLOGIST_MANIPULATOR_H
#include "WPILib.h"
#include "Math.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistManipulator
{
public:
	AnesthesiologistManipulator();
	~AnesthesiologistManipulator();
	
	void intakeBall(bool intake, bool outtake, double speed);
	
	void moveArm(bool isIntake, bool isStored);
	void toggleCameraPosition(bool isForward);
	
	bool getArmPosition();
	int getCameraPosition();
	
	DigitalInput *intakeSwitch;
	Talon *intakeRoller;
	AnalogChannel *pot;
	Victor *cameraMotor;
	Timer *timer;
	int step;
	
private:
	DoubleSolenoid *intakeArm;
		
};
#endif
