#include "WPILib.h"

#include "AnesthesiologistDrive.h"
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistPIDOutput.h"
#include "AnesthesiologistOperatorInterface.h"
#include "AnesthesiologistMacros.h"

class Anesthesiologist: public IterativeRobot
{
	AnesthesiologistDrive *drive;
	AnesthesiologistManipulator *manipulator;
	AnesthesiologistOperatorInterface *oi;
	Compressor *comp599;

public:	
	Anesthesiologist()
	{
		manipulator = new AnesthesiologistManipulator();
		drive = new AnesthesiologistDrive();
		oi = new AnesthesiologistOperatorInterface();
		comp599 = new Compressor(1, 1, 1, 1); 
		
		manipulator->timer->Start();
		
		oi->dashboard->init();
		comp599->Start();
	}
	
	void RobotInit()
	{
	
	}
	
	void DisabledInit()
	{
	
	}
	
	void AutonomousInit()
	{
	
	}
	
	void TeleopInit()
	{
		drive->setLinVelocity(0);
		drive->setTurnSpeed(0, false);
		drive->drive();
		manipulator->setVelocity(0);
	}
	
	void TestInit()
	{
	
	}
	
	void DisabledPeriodic()
	{
		smartDashboardPrint();
	}
	
	void AutonomousPeriodic()
	{
	
	
	}
	
	void TeleopPeriodic()
	{
		comp599->Start();
		
		while(IsOperatorControl())
		{
			oi->dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "Time: %f" , manipulator->timer->Get());
			 teleDrive();
			 smartDashboardPrint();
		}
	}
	
	void TestPeriodic()
	{
	
	}
	
	void teleDrive()
	{
		drive->setLinVelocity(-oi->getDriveJoystick()->GetY(Joystick::kRightHand));
		drive->setTurnSpeed(oi->getDriveJoystick()->GetX(Joystick::kRightHand), oi->getDriveJoystickButton(1));
		drive->drive();
		drive->shift(oi->getDriveJoystickButton(8), oi->getDriveJoystickButton(9));
		
		manipulator->setVelocity((oi->getManipJoystick()->GetThrottle()+1)/2);
		manipulator->intakeBall(oi->getManipJoystickButton(2));
		
		if(oi->getDriveJoystickButton(6))
		{
			comp599->Start();
		}
		else if(oi->getDriveJoystickButton(7))
		{
			comp599->Stop();
		}
	}
	
	void smartDashboardPrint()
	{
		oi->dashboard->PutNumber("Drive Linear Velocity: ", drive->getLinVelocity());
		oi->dashboard->PutNumber("Drive Turn Speed: ", drive->getTurnSpeed());
		oi->dashboard->PutNumber("Roller Velocity: ", drive->getLinVelocity());
		oi->dashboard->PutNumber("Arm Encoder Raw Value: ", manipulator->armEncoder->Get());
		oi->dashboard->PutNumber("timer test: ", manipulator->timer->Get());
	}
};	

START_ROBOT_CLASS(Anesthesiologist);
