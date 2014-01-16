#include "AnesthesiologistDrive.h"

AnesthesiologistDrive::AnesthesiologistDrive(AnesthesiologistOperatorInterface *opInt)
{
	if (opInt) oi = opInt;
	linearVelocity = 0;
	turnSpeed = 0;
		
	isAtLeftTarget = false;
	isAtRightTarget = false;
	isAtLinearTarget = false;
	isAtTurnTarget = false;
	isAtSwivelTurnTarget = false;
	
	isAtTimeLinearTarget = false;
	isAtTimeTurnTarget = false;
	isAtTimeSwivelTarget = false;
	
	targetTicksRight = 0;
	targetTicksLeft = 0;
	
	isAtTarget = false;
	
	currentTicksLeft = 0;
	currentTicksRight = 0;

	frontLeftMotor = new Jaguar(1, CHANNEL1);
	rearLeftMotor = new Jaguar(1, CHANNEL2);
	frontRightMotor = new Jaguar(1, CHANNEL3);
	rearRightMotor = new Jaguar(1, CHANNEL4);
	
    shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B);   
    shifter->Set(DoubleSolenoid::kReverse);
	
	timer = new Timer();
	
	leftEncoder = new Encoder(LEFT_DRIVE_ENCODER_CHANNEL_A, LEFT_DRIVE_ENCODER_CHANNEL_B, true, Encoder::k1X);
	rightEncoder = new Encoder(RIGHT_DRIVE_ENCODER_CHANNEL_A, RIGHT_DRIVE_ENCODER_CHANNEL_B, true, Encoder::k1X);
}

AnesthesiologistDrive::~AnesthesiologistDrive()
{
	delete timer;
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
	delete shifter;
	
	shifter = NULL;	
	timer = NULL;
	frontLeftMotor = NULL;
	rearLeftMotor = NULL;
	frontRightMotor = NULL;
	rearRightMotor = NULL;
}

/*
 * param: 	button on joystick to indicate whether to shift up or down
 * @return:	whether gear was high or low before function 
 * 			true = high, false = low
 * will we use?
 */
bool AnesthesiologistDrive::shift(UINT8 highButton, UINT8 lowButton)
{
	 //static?
        bool lastGearWasHi = true;
        
        if(lowButton)
        {
                shifter->Set(DoubleSolenoid::kForward);
                lastGearWasHi = false;
        }
        else if(highButton)
        {
                shifter->Set(DoubleSolenoid::kReverse);
                lastGearWasHi = true;
        }
        
        return lastGearWasHi;  
}

/*
 * param: value wanted
 */
void AnesthesiologistDrive::setLinVelocity(double linVal) 
{
	if (linVal > DEADZONE || linVal < DEADZONE)
	{
		linearVelocity = linVal;
	}else
	{
		linearVelocity = 0;
	}
}
double AnesthesiologistDrive::getLinVelocity() //get-method
{
	return linearVelocity;
}

/*
 * param: 	decimal value
 * @return: 	original linV*param
 * 			ex: linV = 100  para = .5  return 50
 */
double AnesthesiologistDrive::reduceTurn(double reduceTo) 
{
	return turnSpeed*reduceTo;
}
/*
 * param: 	turn: Joystick returned value
 * 			turboButton: if pressed  must be pressed w/ Joystick to really move
 */
void AnesthesiologistDrive::setTurnSpeed(double turn, bool turboButton) 
{
	if (!turboButton && (turn > DEADZONE || turn < -DEADZONE))
	{
		turnSpeed = turn * REDUCTION;
	}else if (turn < DEADZONE && turn > -DEADZONE)
	{
		turnSpeed = 0;
	}else
	{
		turnSpeed = turn;
	}
}

double AnesthesiologistDrive::getTurnSpeed() //get-method
{
	return turnSpeed;
}
void AnesthesiologistDrive::setLeftMotors(double velocity) //set-method 
{
	frontLeftMotor->Set(-velocity, SYNC_STATE_OFF);
	rearLeftMotor->Set(-velocity, SYNC_STATE_OFF);
}
void AnesthesiologistDrive::setRightMotors(double velocity) //set-method
{
	frontRightMotor->Set(velocity, 0);
	frontRightMotor->Set(velocity, 0);
}
/*
 * (left,right)Cmd: velocity of both sides of the bot
 */
void AnesthesiologistDrive::drive() 
{
	leftCmd = linearVelocity + turnSpeed;
	rightCmd = linearVelocity - turnSpeed;
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}

/*
 * param: 	target - tick you want
 * 			speed - speed you want
 * moves robot to tick you want, method use in autoLinear to moves forward inches
 *
void AnesthesiologistDrive::moveLeftEncoder(double target, double speed)
{
	isAtLeftTarget = false;
	double deltaTicksLeft;
	while (!isAtLeftTarget)
	{
		currentTicksLeft = leftEncoder->Get();
		deltaTicksLeft = -target - currentTicksLeft; //-target as left encoder is backwards
		if(deltaTicksLeft < -TICKS_DEADZONE)
		{
			setLeftMotors(speed);
			isAtLeftTarget = false;
		}
		else if(deltaTicksLeft > TICKS_DEADZONE)
		{
			setLeftMotors(-speed);
			isAtLeftTarget = false;
		}
		else
		{
			setLeftMotors(0);
			isAtLeftTarget = true;
		}
		if(isAtLeftTarget)
		{
			setLeftMotors(0);
		}
	}
}

void AnesthesiologistDrive::moveRightEncoder(double target, double speed) //idk...
{
	isAtRightTarget = false;
	int deltaTicksRight;
	while (!isAtRightTarget)
	{
		currentTicksRight = rightEncoder->Get();
		deltaTicksRight = target - currentTicksRight;
		if(deltaTicksLeft < -TICKS_DEADZONE)
		{
			setRightMotors(-speed);
			isAtRightTarget = false;
		}
		else if(deltaTicksLeft > TICKS_DEADZONE)
		{
			setRightMotors(speed);
			isAtRightTarget = false;
		}
		else
		{
			setRightMotors(0);
			isAtRightTarget = true;
		}
		if(isAtRightTarget)
		{
			setRightMotors(0);
		}
	}
}
*/
void AnesthesiologistDrive::moveDriveEncoder(double deltaTicks, double speed)
{	
	currentTicksRight 	= rightEncoder->Get();
	currentTicksLeft 	= leftEncoder->Get();
	
	targetTicksRight 	= currentTicksRight + deltaTicks;
	targetTicksLeft 	= currentTicksLeft 	+ deltaTicks;

	currentTicksRight 	= rightEncoder->Get();
	currentTicksLeft	= leftEncoder->Get();
	
	if (currentTicksRight < targetTicksRight - TICKS_DEADZONE)
	{
		setRightMotors(speed);
	}else{
		if (currentTicksRight > targetTicksRight + TICKS_DEADZONE)
		{
			setRightMotors(-speed);
		}
	}
	if (currentTicksLeft < targetTicksLeft - TICKS_DEADZONE)
	{
		setLeftMotors(speed);
	}else{
		if (currentTicksLeft > targetTicksLeft + TICKS_DEADZONE)
		{
			setRightMotors(-speed);
		}
	}
	currentTicksRight 	= rightEncoder->Get();
	currentTicksLeft	= leftEncoder->Get();
	if (inBetweenEncoder(currentTicksLeft, targetTicksLeft) && inBetweenEncoder(currentTicksRight, targetTicksRight))
	{
		setRightMotors(0);
		setLeftMotors(0);
		isAtTarget = true;
	}
}
 
/*
 * param: 	deltaTicks:	converted from degrees to ticks, how many ticks you want to move
 * 			speed:		speed
 * 			clockwise:	if (true)
 * 							turn clockwise
 * 						else
 * 							turn counterclockwise
 */
void AnesthesiologistDrive::moveTurnEncoder(double deltaTicks, double speed, bool clockwise)
{
	currentTicksRight 	= rightEncoder->Get();
	currentTicksLeft 	= leftEncoder->Get();

	if (clockwise) //left moves forward, right moves backward
	{
		targetTicksRight 	= currentTicksRight - deltaTicks;
		targetTicksLeft 	= currentTicksLeft 	+ deltaTicks;
		while (!isAtTarget)
		{
			currentTicksRight 	= rightEncoder->Get();
			currentTicksLeft 	= leftEncoder->Get();
			if (inBetweenEncoder(currentTicksRight, targetTicksRight) && inBetweenEncoder(currentTicksLeft, targetTicksLeft))
			{
				setRightMotors(0);
				setLeftMotors(0);
				isAtTarget = true;
			}
			setLeftMotors(speed);
			setRightMotors(-speed);
		}
	}
	else
	{
		targetTicksRight 	= currentTicksRight + deltaTicks;
		targetTicksLeft 	= currentTicksLeft 	- deltaTicks;
		while(!isAtTarget)
		{
			currentTicksRight	= rightEncoder->Get();
			currentTicksLeft	= leftEncoder->Get();
			if (inBetweenEncoder(currentTicksRight, targetTicksRight) && inBetweenEncoder(currentTicksLeft, targetTicksLeft))
			{
				setRightMotors(0);
				setLeftMotors(0);
				isAtTarget = true;
			}
		}
	}
	
	
}

bool AnesthesiologistDrive::inBetweenEncoder(double currentTicks, double targetTicks)
{
	if (currentTicks < targetTicks + TICKS_DEADZONE && currentTicks > targetTicks - TICKS_DEADZONE)
	{
		return true;
	}
	return false;
}

/*
 * param: 	target: where you want to go in inches
 * 			speed: how fast you want to go
 * (moves forward, turns) in auto
 */
void AnesthesiologistDrive::autoLinear(double target, double speed) 
{
	isAtTarget = false;
	target = target/INCHES_PER_TICK;
	resetEncoders();
	while (!isAtTarget){
		moveDriveEncoder(target, speed);
	}
}

void AnesthesiologistDrive::autoTurn(double target, double speed, bool clockwise) 
{
	target = target * TICKS_PER_DEGREE;
	isAtTarget = false;
	moveTurnEncoder(target, speed, clockwise);
}

void AnesthesiologistDrive::resetEncoders()
{
	leftEncoder->Reset();
	rightEncoder->Reset();
}

void AnesthesiologistDrive::resetAtTarget() 
{
    isAtLeftTarget = false;
    isAtRightTarget = false;
    isAtLinearTarget = false;
    isAtTurnTarget = false;
    isAtSwivelTurnTarget = false;
    isAtTimeLinearTarget = false;
    isAtTimeTurnTarget = false;
    isAtTimeSwivelTarget = false;
}
