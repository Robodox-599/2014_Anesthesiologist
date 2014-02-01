#ifndef ANESTHESIOLOGIST_DRIVE_H
#define ANESTHESIOLOGIST_DRIVE_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"
#include "AnesthesiologistOperatorInterface.h"

class AnesthesiologistDrive
{
public:
	AnesthesiologistDrive(AnesthesiologistOperatorInterface *opInt = NULL);
	~AnesthesiologistDrive();
	
	bool shift(UINT8 highButton, UINT8 lowButton);
	
	void drive();
	
	void setLinVelocity(double linVal);
	double getLinVelocity();
	
	void setTurnSpeed(double turn, bool turboButton);		
	double getTurnSpeed();	
	
	double reduceTurn(double reduceBy);	
	
//	void setEncodersLinear(double target, double speed);
//	void autoLinear(double target, double speed);
	
	//encoder testing purposes
//	void setEncoderLeft(double target, double speed);
//	void setEncoderRight(double target, double speed);
//	void autoLeft(double target, double speed);
//	void autoRight(double target, double speed);
	
	DoubleSolenoid *shifter;
	
//	Encoder *leftDriveEncoder;
//	Encoder *rightDriveEncoder;
//	bool isAtLeftTarget;
//	bool isAtRightTarget;
//	bool isAtLinearTarget;
//	double currentTicksLeft;
//	double currentTicksRight;
	
private:
	Talon *frontLeftMotor;
	Talon *rearLeftMotor;
	Talon *frontRightMotor;
	Talon *rearRightMotor;
	
	void setLeftMotors(double velocity);
	void setRightMotors(double velocity);
	
	AnesthesiologistOperatorInterface *oi;
	
	double linearVelocity; 
	double turnSpeed; 
	
	double leftCmd;
	double rightCmd;
};
#endif
