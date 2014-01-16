#ifndef ANESTHESIOLOGIST_OPERATOR_INTERFACE_H
#define ANESTHESIOLOGIST_OPERATOR_INTERFACE_H

#include "WPILib.h"
#include "AnesthesiologistMacros.h"

#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/NamedSendable.h"
#include "SmartDashboard/Sendable.h"
#include "SmartDashboard/SendableChooser.h"

class AnesthesiologistOperatorInterface
{
public:
	AnesthesiologistOperatorInterface();
	~AnesthesiologistOperatorInterface();
	
	//enum?
	
	bool getDriveJoystickButton(UINT8 button);
	Joystick* getManipJoystick();
	Joystick* getDriveJoystick();
	bool getManipJoystickButton(UINT8 button);
	
	SmartDashboard 			*dashboard;
	
	
private:
	Joystick 				*joyDrive;
	Joystick 				*joyManip;
	DriverStationEnhancedIO *ds;
	DriverStation 			*dsSimple;
	DriverStationLCD		*dsLCD;
	
};
#endif
