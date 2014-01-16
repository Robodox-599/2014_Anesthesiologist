#include "AnesthesiologistOperatorInterface.h"

AnesthesiologistOperatorInterface::AnesthesiologistOperatorInterface()
{
	joyDrive = new Joystick(1);
	joyManip = new Joystick(2);
	dsSimple = DriverStation::GetInstance();
	ds = &dsSimple->GetEnhancedIO();
	dsLCD = DriverStationLCD::GetInstance();
	dashboard->init();
}

AnesthesiologistOperatorInterface::~AnesthesiologistOperatorInterface()
{
	delete dsLCD;
	delete joyDrive;
	delete joyManip;
	
	dsLCD = NULL;
	joyDrive = NULL;
	joyManip = NULL;
}

Joystick* AnesthesiologistOperatorInterface::getManipJoystick()
{
	return joyManip;
}

Joystick* AnesthesiologistOperatorInterface::getDriveJoystick()
{
	return joyDrive;
}

bool AnesthesiologistOperatorInterface::getDriveJoystickButton(UINT8 button)
{
	return joyDrive->GetRawButton(button);
	/*
	bool pressed = false;
	if (joyDrive->GetRawButton(button))
	{
		
	}*/
}

bool AnesthesiologistOperatorInterface::getManipJoystickButton(UINT8 button)
{
	return joyManip->GetRawButton(button);
}


