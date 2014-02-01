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
	
	Joystick *getDriveJoystick();
	bool getDriveJoystickButton(UINT8 button);
	bool getDriveJoystickButtonReleased(UINT8 button);

	Joystick *getManipJoystick();		
	bool getManipJoystickButton(UINT8 button);		
	bool getManipJoystickButtonReleased(UINT8 button);
	
	float getBatteryVoltage();
	
	DriverStation *getDriverStation();
	DriverStationLCD *dsLCD;
	SmartDashboard *dashboard;
	
private:
	Joystick *joyDrive;
	Joystick *joyManip;
	DriverStationEnhancedIO *ds;
	DriverStation *dsSimple;
};
#endif
	
