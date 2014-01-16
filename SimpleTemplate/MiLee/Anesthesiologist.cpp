#include "WPILib.h"

#include "AnesthesiologistDrive.h"
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistOperatorInterface.h"
#include "AnesthesiologistMacros.h"

int step;

class Anesthesiologist: public IterativeRobot
{
        AnesthesiologistManipulator *manipulator;
        AnesthesiologistOperatorInterface *oi;
        AnesthesiologistDrive *drive;
        Compressor *comp599;
        //AnalogChannel *pot;
        //AnalogChannel *magazineBottomCounter;
        //AnalogChannel *spoilerCounter;
        //AnalogChannel *intakeCounter;
        //AnalogChannel *magazineInputCounter;
        //Counter *shooterIRCount2;
        //Victor *elevatorMotor;
        //Victor *shooterWheel;
        //Victor *shooterMiniWheel;
        //DoubleSolenoid *feeder;
        //DoubleSolenoid *cameraAngle;
        //Solenoid *rpmSensor;
        //DigitalInput *rpmIRSensor;
        
        Timer *timer;

public:

	Anesthesiologist()
	{
		oi = new AnesthesiologistOperatorInterface();
		drive = new AnesthesiologistDrive();
		//shooter = new AnesthesiologistShooter();
		comp599 = new Compressor(1, 1, 1, 1);//TODO: add real values
		//pot = new AnalogChannel(1,1);
		//magazineBottomCounter = new AnalogChannel(1, 2);
		//magazineInputCounter = new AnalogChannel(1, 3);
		//spoilerCounter = new AnalogChannel(1, 4);
		//intakeCounter = new AnalogChannel(1,5);
		//shooterIRCount2 = new Counter(new DigitalInput(4));
		//elevatorMotor = new Victor(8);
		//shooterWheel = new Victor(10);
		//shooterMiniWheel = new Victor(9);
		//feeder = new DoubleSolenoid(2, 5, 6);
		//cameraAngle = new DoubleSolenoid(PNEUMATICS_24V_SLOT, 3, 4);
	//	rpmSensor = new Solenoid(PNEUMATICS_24V_SLOT, 5);
	//	rpmIRSensor = new DigitalInput(1, SHOOTER_WHEEL_IR_CHANNEL);
		
		oi->dashboard->init();
		comp599->Start();
		timer = new Timer();
		//shooterIRCount2->Start();
		
	
	}
	
	void RobotInit()
	{
			
	}
	
	void DisabledInit()
	{
			drive->leftEncoder->Start();
			drive->rightEncoder->Start();                
	}
	
	void AutonomousInit()
	{
			step = 0;
			drive->leftEncoder->Reset();
			drive->rightEncoder->Reset();
			drive->isAtLinearTarget = false;
	}
	
	void TeleopInit()
	{
			drive->setLinVelocity(0);
			drive->setTurnSpeed(0, false);
			drive->drive();
	}
	
	void TestInit()
	{
			
	}
	
	void DisabledPeriodic()
	{
			step = 0;
			drive->leftEncoder->Reset();
			drive->rightEncoder->Reset();
			drive->isAtTimeLinearTarget = false;
			smartDashboardPrint();
	
	}
	
	void AutonomousPeriodic()
	{
		//shoot(true);                                        //shoot preloads
		
		//drive->autoTurn(55, TURN_SPEED); 
		
		step = 0;
		smartDashboardPrint();
	
		if (step == 0){
			drive->moveDriveEncoder(25, .25);
			step++;
		}
		if (step == 1)
		{
			drive->moveDriveEncoder(-25, .25);
			step++;
		}
		if (step == 2){
			drive->moveDriveEncoder(25, -.25);
			step++;
		}
		if (step == 3)
		{
			drive->moveDriveEncoder(-25, -.25);
			step++;
		}
		if (step == 4){
			drive->moveTurnEncoder(25, .25, true);
			step++;
			}
		if (step == 5){
			drive->moveTurnEncoder(-25, .25, true);
			step++;
			}
		if (step == 6){
			drive->moveTurnEncoder(25, -.25, true);
			step++;
			}
		if (step == 7){
			drive->moveTurnEncoder(-25, -.25, true);
			step++;
			}
		if (step == 8){
			drive->moveTurnEncoder(25, .25, false);
			step++;
			}
		if (step == 9){
			drive->moveTurnEncoder(-25, .25, false);
			step++;
			}
		if (step == 10){
			drive->moveTurnEncoder(25, -.25, false);
			step++;
			}
		if (step == 11){
			drive->moveTurnEncoder(-25, -.25, false);
			step++;
			}
	
	
			
		
		
	}
	
	void smartDashboardPrint()
	{
		oi->dashboard->PutNumber("Linear Velocity", drive->getLinVelocity());
		oi->dashboard->PutNumber("Left Encoder", drive->leftEncoder->Get());
		oi->dashboard->PutNumber("Right Encoder", drive->rightEncoder->Get());
		oi->dashboard->PutBoolean("isAtTargetD", drive->isAtTarget);
		oi->dashboard->PutNumber("Step", step);
	}
};

