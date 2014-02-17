#include "WPILib.h"
//Vision includes
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include "Math.h"

#include "AnesthesiologistDrive.h"
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistLauncher.h"
#include "AnesthesiologistPIDOutput.h"
#include "AnesthesiologistOperatorInterface.h"
#include "AnesthesiologistVision.h"
#include "AnesthesiologistMacros.h"

int step = 0;
	//timer wait
bool isWait = false;
bool bTimerInit = true;
double initWaitTime = 0;
double currentWaitTime = 0;
	//Latches
bool bTimerLatch = false;
bool bCameraLatch = false;

class Anesthesiologist: public IterativeRobot
{
	AnesthesiologistDrive *drive;
	AnesthesiologistManipulator *manipulator;
	AnesthesiologistLauncher *launcher;
	AnesthesiologistOperatorInterface *oi;
	Compressor *comp599;
	//Relay *relay599;
	Timer *timer;
	//AnesthesiologistVision *vision;
public:	
	Anesthesiologist()
	{
		manipulator = new AnesthesiologistManipulator();
		launcher = new AnesthesiologistLauncher();
		drive = new AnesthesiologistDrive();
		oi = new AnesthesiologistOperatorInterface();
		comp599 = new Compressor(1, 1, 1, 2); 
		//relay599 = new Relay(1, 2);
		timer = new Timer();
		//vision = new AnesthesiologistVision();
		
		drive->leftDriveEncoder->Start();
		drive->rightDriveEncoder->Start();
		
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
	}
	
	void AutonomousInit()
	{
		step = 0;
		timer->Start();
		drive->leftDriveEncoder->Reset();
		drive->rightDriveEncoder->Reset();
	}
	
	void TeleopInit()
	{
		step = 0;
		drive->setLinVelocity(0);
		drive->setTurnSpeed(0, false);
		drive->drive();
		comp599->Start();
		timer->Start();		
		drive->leftDriveEncoder->Start();
		drive->rightDriveEncoder->Start();
	}
	
	void TestInit()
	{
	
	}
	
	void DisabledPeriodic()
	{
		step = 0;
		drive->leftDriveEncoder->Reset();
		drive->rightDriveEncoder->Reset();
		smartDashboardPrint();
	}
	
	void AutonomousPeriodic()
	{		
		smartDashboardPrint();
		
		//TODO: dummy speeds & times
		if(timer->Get() > 0 && timer->Get() < 2)
		{
			drive->setLinVelocity(1);
		}
		else if(timer->Get() > 2 && timer->Get() < 3)
		{
			drive->setLinVelocity(0);
			step = 1;
			//launcher->autoLaunch(true);
		}
		else if(timer->Get() > 3 && timer->Get() < 6)
		{
			drive->setLinVelocity(-1);	
		}
		else if(timer->Get() > 6 && timer->Get() < 7)
		{
			drive->setLinVelocity(0);
			step = 2;
			//manipulator->intakeBall(true, false, 1);
		}
		else if(timer->Get() > 7 && timer->Get() < 10)
		{
			drive->setLinVelocity(1);
		}
		else if(timer->Get() > 10 && timer->Get() < 11)
		{
			drive->setLinVelocity(0);
			//launcher->autoLaunch(true);
		}
		drive->drive();
		
//		smartDashboardPrint();
//		setEncodersLinear(1,1); //TODO: Dummy Numbers (target, speed)
//		launcher->launchBall(true);
//		setEncodersLinear(-1,-1); //TODO: Dummy Numbers (target, speed) for moving backwards
//		manipulator->intakeBall(true,false,true);
//		setEncodersLinear(2,2); //TODO: Dummy Numbers (target, speed) for moving forwards
//		launcher->launchBall(true);
	}
	
	void TeleopPeriodic()
	{
		//while(IsOperatorControl())
		//{
			teleDrive();
			smartDashboardPrint();
		//}
	}
	
	void TestPeriodic()
	{
	
	}
	
	void teleDrive()
	{
		if(!isWait)
		{
			drive->setLinVelocity(-oi->getDriveJoystick()->GetY(Joystick::kRightHand));
			drive->setTurnSpeed(oi->getDriveJoystick()->GetX(Joystick::kRightHand), oi->getDriveJoystickButton(3));
			drive->drive();
		}
		
		drive->shift(oi->getDriveJoystickButton(8), oi->getDriveJoystickButton(9));
		manipulator->moveArm(oi->getManipJoystickButton(6), oi->getManipJoystickButton(7));
		manipulator->moveStopper(oi->getManipJoystickButton(10), oi->getManipJoystickButton(11));	
		//manipulator->intakeBall(oi->getManipJoystickButton(3), oi->getManipJoystickButton(2), drive->getShiftState() ? (drive->getLinVelocity()*1.54) : (drive->getLinVelocity()*6.2)); //dribbling 
		manipulator->intakeBall(oi->getManipJoystickButton(3), oi->getManipJoystickButton(2), (oi->getManipJoystick()->GetThrottle()+1)/2);
		launcher->launchBall(oi->getDriveJoystickButton(1), oi->getDriveJoystickButton(2));
		toggleCompressor(oi->getDriveJoystickButton(6), oi->getDriveJoystickButton(7));
		
			//camera motor mount
		if(oi->getManipJoystickButton(8))
		{
			bCameraLatch = true;
		}
		else if(oi->getManipJoystickButton(9))
		{
			bCameraLatch = false;
		}	
		manipulator->toggleCameraPosition(bCameraLatch);
		
			//timer wait
//		if(oi->getDriveJoystickButton(10))
//		{
//			bTimerLatch = true;
//		}
//		if(bTimerLatch)
//		{
//			wait(5.0);
//		}

	}
	
	void wait(double secToWait)
	{
		currentWaitTime = timer->Get();
		if(bTimerInit)
		{
			initWaitTime = currentWaitTime;
			bTimerInit = false;
			isWait = true;
		}
		if(currentWaitTime < secToWait + initWaitTime)
		{
			isWait = true;
		}
		else
		{
			isWait = false;
			bTimerInit = true;
			bTimerLatch = false;
		}
		currentWaitTime = timer->Get();
	}
	
	void toggleCompressor(bool start, bool stop)
	{
		if(start)
		{
			comp599->Start();
			//relay599->Set(Relay::kForward);
		}
		else if(stop)
		{
			comp599->Stop();
			//relay599->Set(Relay::kOff);
		}
	}
	
	void smartDashboardPrint()
	{
		oi->dashboard->PutNumber("Drive Linear Speed: ", drive->getLinVelocity());
		oi->dashboard->PutNumber("Drive Turn Speed: ", drive->getTurnSpeed());
		oi->dashboard->PutNumber("Left Encoder Raw Value: ", drive->leftDriveEncoder->GetRaw());
		oi->dashboard->PutNumber("Right Encoder Raw Value: ", drive->rightDriveEncoder->GetRaw());
		oi->dashboard->PutNumber("Timer: ", timer->Get());
		oi->dashboard->PutNumber("Pot Raw Value: ", manipulator->pot->GetVoltage());
		oi->dashboard->PutBoolean(" Wait (Motors Disabled)", isWait);
		oi->dashboard->PutBoolean(" Compressor", comp599->Enabled());
		oi->dashboard->PutString("Shot Range: ", manipulator->getStopperPosition() ? "Short" : "Long");
		oi->dashboard->PutString("Arm Position: ", manipulator->getArmPosition() ? "Stored" : "Intake");
		oi->dashboard->PutString("Shift State: ", drive->getShiftState() ? "High" : "Low");
		oi->dashboard->PutString("Launch State: ", launcher->launchState > 0 ? (launcher->launchState == 1 ? "HOLD" : (launcher->launchState == 2 ? "RESET" : (launcher->launchState == 3 ? "COCKED" : "FIRE"))) : "OFF");
		oi->dashboard->PutString("Camera Position: ", manipulator->getCameraPosition() > 0 ? ((manipulator->getCameraPosition() == 2) ? "Forward" : "Back") : "Inbetween");
		oi->dashboard->PutBoolean(" Ready to Fire", launcher->launchState == STATE_COCKED ? true : false);
		oi->dashboard->PutBoolean(" Ball is Stored", launcher->isIn());
		oi->dashboard->PutNumber("Sonar Raw Value: ", launcher->ultrasonicSensor->GetRangeInches());
		//oi->dashboard->PutNumber("Roller Value: ", manipulator->intakeRoller->Get());
		//oi->dashboard->PutNumber("Throttle: ", (oi->getManipJoystick()->GetThrottle()+1)/2);
		//oi->dashboard->PutNumber("Intake Switch: ", manipulator->intakeSwitch->Get());
		//oi->dashboard->PutNumber("Step: ", manipulator->step);		

		//AxisCamera &camera = AxisCamera::GetInstance("10.5.99.11");
		
//		oi->dashboard->PutBoolean("Can Shoot", vision->update(new HSLImage("2014 Vision Target/Center_18ft_On.jpg")));
//		SendableChooser *sc = new SendableChooser();
//		sc->AddObject("Filtered Image", vision->filterImageHSV(new HSLImage("2014 Vision Target/Center_18ft_on.jpg")));
//		oi->dashboard->PutData("Filtered", sc);
//		sc->AddObject("Filtered Imaeg of Particles", vision->getFilteredImage());
//		oi->dashboard->PutNumber("ImageHeight", vision->getReport()->imageWidth);
//		oi->dashboard->PutNumber("ImageWidth", vision->getReport()->imageHeight);
	}	
};

START_ROBOT_CLASS(Anesthesiologist);
