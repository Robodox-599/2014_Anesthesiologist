#ifndef ANESTHESIOLOGIST_MANIPULATOR_H
#define ANESTHESIOLOGIST_MANIPULATOR_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistManipulator
{
public:
	AnesthesiologistManipulator();
	AnesthesiologistManipulator(UINT8 intakeRollerVictorChannel);//, UINT8 intakeArmVictorChannel);
	~AnesthesiologistManipulator();
	
	void intakeBall(bool intake);
	
	
private:
	Victor *intakeRoller;
	DigitalInput *ballCradleSwitch;
	//Victor *intakeArm;
	
	
};
#endif
