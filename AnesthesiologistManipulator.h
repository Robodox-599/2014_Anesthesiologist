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
	
	void intakeBall(bool intakeSlow, bool intakeFast);
	void moveArm(bool isIntake, bool isStored);
	void moveStopper(bool shortShot, bool longShot);
	void toggleCameraPosition(bool isForward, bool isBack);
	
	bool getStopperPosition();
	bool getArmPosition();
	int getCameraPosition();
	
	AnalogChannel *pot;
	Victor *cameraMotor;
private:
	Victor *intakeRoller;
	DigitalInput *intakeSwitch;
	DoubleSolenoid *leftIntakeArm;
	DoubleSolenoid *rightIntakeArm;
	DoubleSolenoid *stopper;
	//Victor *cameraMotor;
	double targetVelocity;
	
};
#endif
