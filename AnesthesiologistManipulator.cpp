#include "AnesthesiologistManipulator.h"

AnesthesiologistManipulator::AnesthesiologistManipulator()
{
	intakeRoller = new Victor(INTAKE_ROLLER_VICTOR_CHANNEL);
	intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	leftIntakeArm = new DoubleSolenoid(LEFT_INTAKE_ARM_SOLENOID_CHANNEL_A, LEFT_INTAKE_ARM_SOLENOID_CHANNEL_B);
	rightIntakeArm = new DoubleSolenoid(RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_A, RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_B);
	stopper = new DoubleSolenoid(STOPPER_SOLENOID_CHANNEL_A, STOPPER_SOLENOID_CHANNEL_B);
	cameraMotor = new Victor(CAMERA_VICTOR_CHANNEL);
	pot = new AnalogChannel(1, 1);
	rollerEncoder = new Encoder(ROLLER_ENCODER_CHANNEL_A, ROLLER_ENCODER_CHANNEL_B, false, Encoder::k1X);	
	timer = new Timer();
	
	timer->Start();
	rpm = 0;
}

AnesthesiologistManipulator::~AnesthesiologistManipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	delete leftIntakeArm;
	delete rightIntakeArm;
	delete stopper;
	delete cameraMotor;
	delete pot;
	delete rollerEncoder;
	
	intakeRoller = NULL;
	intakeSwitch = NULL;
	leftIntakeArm = NULL;
	rightIntakeArm = NULL;
	stopper = NULL;
	cameraMotor = NULL;
	pot = NULL;
	rollerEncoder = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool intake, bool outtake, bool toggleSpeed)
{
	bool lastSwitchHit = false;
	bool lastPressed = true;
	
	if(!lastSwitchHit && intakeSwitch->Get() == 0)
	{
		if(intake)
		{
			if(toggleSpeed)
			{
				intakeRoller->Set(.5, SYNC_STATE_OFF);
			}
			else
			{
				intakeRoller->Set(1, SYNC_STATE_OFF);
			}
		}
		else if(outtake)
		{
			if(toggleSpeed)
			{
				intakeRoller->Set(-.5, SYNC_STATE_OFF);
			}
			else
			{
				intakeRoller->Set(-1, SYNC_STATE_OFF);
			}
		}
	}
	
	if(!lastSwitchHit && intakeSwitch->Get() == 1)//TODO: test for 0 or 1
	{
		intakeRoller->Set(0, SYNC_STATE_OFF);
		lastSwitchHit = true;
	}
	
	if(lastSwitchHit && intakeSwitch->Get() == 1)
	{
		if(lastPressed && (!intake && !outtake))
		{
			lastPressed = false;
		}
		if(!lastPressed && ( intake || outtake))
		{
			if(intake)
			{
				if(toggleSpeed)
				{
					intakeRoller->Set(.5, SYNC_STATE_OFF);
				}
				else
				{
					intakeRoller->Set(1, SYNC_STATE_OFF);
				}
			}
			else if(outtake)
			{
				if(toggleSpeed)
				{
					intakeRoller->Set(-.5, SYNC_STATE_OFF);
				}
				else 
				{
					intakeRoller->Set(-1, SYNC_STATE_OFF);
				}
			}
		}
	}		
}

void AnesthesiologistManipulator::moveArm(bool isIntake, bool isStored)
{
	if(isIntake)
	{
		leftIntakeArm->Set(DoubleSolenoid::kForward);
		rightIntakeArm->Set(DoubleSolenoid::kForward);
	}
	else if(isStored)
	{
		leftIntakeArm->Set(DoubleSolenoid::kReverse);
		rightIntakeArm->Set(DoubleSolenoid::kReverse);	
	}
}

void AnesthesiologistManipulator::moveStopper(bool shortShot, bool longShot)
{
	if(shortShot)
	{
		stopper->Set(DoubleSolenoid::kForward);
	}
	else if(longShot)
	{
		stopper->Set(DoubleSolenoid::kReverse);
	}
}

void AnesthesiologistManipulator::toggleCameraPosition(bool isForward)
{
	bool isForwardLimit = false;
	bool isBackLimit = false;
	
	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
	{
		isBackLimit = true;
	}
	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
	{
		isForwardLimit = true;
	}
	else
	{
		isForwardLimit = false;
		isBackLimit = false;
	}
	
	if(isForwardLimit || isBackLimit)
	{
		cameraMotor->Set(0, SYNC_STATE_OFF);
	}
	if(isForward && !isForwardLimit)
	{
		cameraMotor->Set(-1, SYNC_STATE_OFF);
	}
	if(!isForward && !isBackLimit)
	{
		cameraMotor->Set(1, SYNC_STATE_OFF);
	}
	
}

bool AnesthesiologistManipulator::getStopperPosition()
{
	if(stopper->Get() == DoubleSolenoid::kForward)
	{
		return true;
	}
	return false;
}

bool AnesthesiologistManipulator::getArmPosition()
{
	if(leftIntakeArm->Get() == DoubleSolenoid::kForward)
	{
		return true;
	}
	return false;
}

int AnesthesiologistManipulator::getCameraPosition()
{
	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
	{
		return 2;
	}
	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
	{
		return 1;
	}
	return 0;
}

double AnesthesiologistManipulator::getRPM()
{
	static bool init = true;
	double initTime = 0;
	double deltaTime = 0;
	double initTicks = 0;
	double deltaTicks = 0;
	double ticksPerMinute = 0;
	
	if(init)
	{
		initTime = timer->Get();
		initTicks = rollerEncoder->Get();
		init = false;
	}
	
	deltaTime = timer->Get() - initTime;
	deltaTicks = rollerEncoder->Get() - initTicks;
	
	if(deltaTime == TIME_COMPARISON)
	{
		ticksPerMinute = deltaTicks * TIME_COMPARISON * MINUTE_CONVERSION;
		rpm = ticksPerMinute / TICKS_PER_ROTATION;
	}
	return rpm;
}
