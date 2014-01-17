#include "WPILib.h"

#include "AnesthesiologistDrive.h"
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistPIDOutput.h"
#include "AnesthesiologistOperatorInterface.h"
#include "AnesthesiologistMacros.h"

int step = 0;

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
		
		//manipulator->timer->Start();
		
		oi->dashboard->init();
		comp599->Start();
	}
	
	void RobotInit()
	{
	
	}
	
	void DisabledInit()
	{
		drive->leftDriveEncoder->Start();
		drive->rightDriveEncoder->Start();
		//manipulator->armEncoder->Start();
	}
	
	void AutonomousInit()
	{
		step = 0;
		drive->leftDriveEncoder->Reset();
		drive->rightDriveEncoder->Reset();
		//manipulator->armEncoder->Reset();
		drive->isAtLinearTarget = false;
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
		step = 0;
		drive->leftDriveEncoder->Reset();
		drive->rightDriveEncoder->Reset();
		//manipulator->armEncoder->Reset();
		drive->isAtLinearTarget = false;
		smartDashboardPrint();
	}
	
	void AutonomousPeriodic()
	{
		smartDashboardPrint();
		
		/*if(step == 0)
		{
			drive->autoLeft(20, .25);
			step++;
		}*/
		if(step == 0)
		{
			drive->autoRight(-20, .25);
			step++;
		}
		
		/*auto test
		if(step == 0)
		{
			drive->autoLinear(25, .50);
			manipulator->timer->wait(1000);
			step++;
		}
		if(step == 1)
		{
			drive->autoLinear(25, -.50);
			manipulator->timer->wait(1000);
			step++;
		}
		if(step == 2)
		{
			drive->autoLinear(-25, .50);
			manipulator->timer->wait(1000);
			step++;
		}
		if(step == 3)
		{
			drive->autoLinear(-25, -.50);
			manipulator->timer->wait(1000);
			step++;
		}*/
	}
	
	void TeleopPeriodic()
	{
		comp599->Start();
		
		while(IsOperatorControl())
		{
			 oi->dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "EncoderL: %f" , drive->leftDriveEncoder->Get());
			 oi->dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "EncoderR: %f" , drive->rightDriveEncoder->Get());
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
		//oi->dashboard->PutNumber("Arm Encoder Raw Value: ", manipulator->armEncoder->Get());
		oi->dashboard->PutNumber("Left Encoder Raw Value: ", drive->leftDriveEncoder->Get());
		oi->dashboard->PutNumber("Right Encoder Raw Value: ", drive->rightDriveEncoder->Get());
		//oi->dashboard->PutNumber("Timer: ", manipulator->timer->Get());
	}
};	

START_ROBOT_CLASS(Anesthesiologist);
