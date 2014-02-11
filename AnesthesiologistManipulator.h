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
	
	void intakeBall(bool intake, bool outtake, bool toggleSpeed);
	
	void moveArm(bool isIntake, bool isStored);
	void moveStopper(bool shortShot, bool longShot);
	void toggleCameraPosition(bool isForward);
	
	bool getStopperPosition();
	bool getArmPosition();
	int getCameraPosition();
	
	double getRPM();
	
	AnalogChannel *pot;
	Victor *cameraMotor;
	Encoder *rollerEncoder;
	Timer *timer;
	
private:
	Victor *intakeRoller;
	DigitalInput *intakeSwitch;
	DoubleSolenoid *leftIntakeArm;
	DoubleSolenoid *rightIntakeArm;
	DoubleSolenoid *stopper;
	double rpm;
};
#endif
