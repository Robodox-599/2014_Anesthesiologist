#ifndef ANESTHESIOLOGIST_DRIVE_H
#define ANESTHESIOLOGIST_DRIVE_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"
#include "AnesthesiologistOperatorInterface.h"

class AnesthesiologistDrive
{
public:
	/*
	 * Constructors:
	 */
	AnesthesiologistDrive(AnesthesiologistOperatorInterface *oiInt = NULL);
	~AnesthesiologistDrive();//Destructor
	
	/*
	 * param: 	button on joystick to indicate whether to shift up or down
	 * @return:	whether gear was high or low before function 
	 * 			true = high, false = low
	 */
	bool shift(UINT8 highButton, UINT8 lowButton);
	
	/*
	 * param: value wanted
	 */
	void setLinVelocity(double linVal);
	
	double getLinVelocity();//get-method
	
	/*
	 * param: 	decimal value
	 * @return: 	original linV*param
	 * 			ex: linV = 100; para = .5; return 50
	 */
	double reduceTurn(double reduceTo);
	
	/*
	 * param: 	turn: Joystick returned value
	 * 			turboButton: if pressed; must be pressed w/ Joystick to really move
	 */
	void setTurnSpeed(double turn, bool turboButton);
	
	double getTurnSpeed();//get-method

	void setLeftMotors(double velocity);//set-method 
	
	void setRightMotors(double velocity);//set-method
	
	/*
	 * (left,right)Cmd: velocity of both sides of the bot
	 */
	void drive();
	
	void moveLeftEncoder(double target, double speed);//idk...
	void moveRightEncoder(double target, double speed);//idk...
	
	/*
	 * param: 	target: where you want to go
	 * 			speed: how fast you want to go
	 * (moves forward, turns) in auto
	 */
	void autoLinear(double target, double speed);
	void autoTurn(double target, double speed, bool clockwise);
	
	/*
	 * uses time rather than encoders to measure how far you move
	 */
	void timeLinear(double speed, double targetTime_ms);
	
	void resetAtTarget();
	void resetTimers();
	
    DoubleSolenoid *shifter;

    Encoder *leftEncoder;
    Encoder *rightEncoder;
    double currentTicksLeft ; //average of encoder values; used in auton
    double targetTicksLeft;  //target encoder values; used in auton
    //double deltaTicksLeft;   //change in encoder values; used in auton
    //double errorLeft;        //the offset of target ticks relative to current ticks; used in auton
    
    double currentTicksRight; //average of encoder values; used in auton
    double targetTicksRight;  //target encoder values; used in auton
    //double deltaTicksRight;   //change in encoder values; used in auton
    //double errorRight;        //the offset of target ticks relative to current ticks; used in auton
    
    double currentTicksLinear ; //average of encoder values; used in auton
    double targetTicksLinear;  //target encoder values; used in auton
    double deltaTicksLinear;   //change in encoder values; used in auton
    //double errorLinear;        //the offset of target ticks relative to current ticks; used in auton

    double currentTicksTurn; //average of encoder values; used in auton
    double targetTicksTurn;  //target encoder values; used in auton
    double deltaTicksTurn;   //change in encoder values; used in auton
    //double errorTurn;        //the offset of target ticks relative to current ticks; used in auton
/*
    double currentTicksSwivelTurn; //average of encoder values; used in auton
    double targetTicksSwivelTurn;  //target encoder values; used in auton
    double deltaTicksSwivelTurn;   //change in encoder values; used in auton
    //double errorSwivelTurn;        //the offset of target ticks relative to current ticks; used in auton
   */ 
    Timer *timer;
   /* 
    double currentTimeLinear;
    double targetTimeLinear;
    double deltaTimeLinear;
    double errorTimeLinear;
    
    double currentTimeTurn;
    double targetTimeTurn;
    double deltaTimeTurn;
    double errorTimeTurn;
    
    double currentTimeSwivel;
    double targetTimeSwivel;
    double deltaTimeSwivel;
    double errorTimeSwivel;
    */
    bool isAtLeftTarget;
    bool isAtRightTarget;
    bool isAtLinearTarget;
    bool isAtTurnTarget;
    bool isAtSwivelTurnTarget;
    
    bool isAtTimeLinearTarget;
    bool isAtTimeTurnTarget;
    bool isAtTimeSwivelTarget;

    bool isAtTarget;
    void moveDriveEncoder(double deltaTicks, double speed);
    void moveTurnEncoder(double deltaTicks, double speed, bool clockwise);
    bool inBetweenEncoder(double currentTicks, double deltaTicks);
    void resetEncoders();
    
    
private:
	Jaguar *frontLeftMotor;
	Jaguar *rearLeftMotor;
	Jaguar *frontRightMotor;
	Jaguar *rearRightMotor;
	
	AnesthesiologistOperatorInterface *oi;
	
	double linearVelocity;
	double turnSpeed;
	
	double leftCmd;
	double rightCmd;
	
	
	
};
#endif
