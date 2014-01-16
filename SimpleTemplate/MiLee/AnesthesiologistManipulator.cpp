#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	AnesthesiologistManipulator(INTAKE_ROLLER_CHANNEL);
}

AnesthesiologistManipulator::AnesthesiologistManipulator(UINT8 intakeRollerChannel)
{
	intakeRoller = new Victor(intakeRollerChannel);
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	//delete kicker;
	delete intakeRoller;
	
	//kicker = NULL;
	intakeRoller = NULL;
}
void AnesthesiologistManipulator::intake(bool intakeNow)
{
	if (intakeNow) intakeRoller->Set(1);
	else intakeRoller->Set(0);
}
