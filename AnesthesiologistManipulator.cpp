#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	AnesthesiologistManipulator(INTAKE_ROLLER_VICTOR_CHANNEL);//, INTAKE_ARM_VICTOR_CHANNEL);
}

AnesthesiologistManipulator::AnesthesiologistManipulator(UINT8 intakeRollerVictorChannel)//, UINT8 intakeArmVictorChannel)
{
	intakeRoller = new Victor(intakeRollerVictorChannel);
	intakeSwitch = new DigitalInput(1, BALL_CRADLE_SWITCH_CHANNEL);
	//intakeArm = new Victor(intakeArmVictorChannel);
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	//delete intakeArm;
	
	intakeRoller = NULL;
	intakeSwitch = NULL;
	//intakeArm = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool intake)
{
	bool lastSwitchHit = false;
	
	if(intake && !lastSwitchHit && intakeSwitch->Get() == 1)//TODO: test for 0 or 1
	{
		intakeRoller->Set(0);
	}
	else
	{
		setRoller();
	}
	lastSwitchHit = intakeSwitch->Get();	
}

void AnesthesiologistManipulator::setRoller()
{
	intakeRoller->Set(targetVelocity * REDUCTION); 
}

void AnesthesiologistManipulator::setVelocity(double input)
{
	targetVelocity = input;
}

double AnesthesiologistManipulator::getVelocity()
{
	return targetVelocity;
}

