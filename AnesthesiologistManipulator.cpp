#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	AnesthesiologistManipulator(INTAKE_ROLLER_VICTOR_CHANNEL);//, INTAKE_ARM_VICTOR_CHANNEL);
}

AnesthesiologistManipulator::AnesthesiologistManipulator(UINT8 intakeRollerVictorChannel)//, UINT8 intakeArmVictorChannel)
{
	intakeRoller = new Victor(intakeRollerVictorChannel);
	ballCradleSwitch = new DigitalInput(1, BALL_CRADLE_SWITCH_CHANNEL);
	//intakeArm = new Victor(intakeArmVictorChannel);
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete ballCradleSwitch;
	//delete intakeArm;
	
	intakeRoller = NULL;
	ballCradleSwitch = NULL;
	//intakeArm = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool intake)
{
	if(intake && ballCradleSwitch->Get() == 1)//TODO: test for 0 or 1
	{
		while (ballCradleSwitch->Get() == 1)
		{
			intakeRoller->Set(1.0);
		}
		intakeRoller->Set(0);
	}
	else
	{
		intakeRoller->Set(0);
	}
}

