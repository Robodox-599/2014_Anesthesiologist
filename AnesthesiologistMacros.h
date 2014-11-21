#ifndef ANESTHESIOLOGIST_MACROS_H
#define ANESTHESIOLOGIST_MACROS_H

/*Joystick button mapping (for reference)
Drive Joystick:
	1 - shoot ball
	2 - safety switch
	3 - turbo turning
	4 - 
	5 - 
	6 - start compressor
	7 - stop compressor
	8 - shift up
	9 - shift down
	10 - kill switch A  
	11 - kill switch B
Manip Joystick:
	1 - 
	2 - intake 
	3 - outtake
	4 - 
	5 - 
	6 - set arm to intake position
	7 - set arm to stored position 
	8 - 
	9 - 
	10 - set camera position to back  
	11 - set camera position to forward 
	throttle -  roller speed
*/

	//Slots
#define PNEUMATICS_24V_SLOT						(1)

	//Talons
#define DRIVE_FRONT_LEFT_MOTOR_CHANNEL          (1)
#define DRIVE_REAR_LEFT_MOTOR_CHANNEL           (2)
#define DRIVE_FRONT_RIGHT_MOTOR_CHANNEL         (3)
#define DRIVE_REAR_RIGHT_MOTOR_CHANNEL          (4)
#define LAUNCHER_MOTOR_CHANNEL          		(5)
#define INTAKE_ROLLER_CHANNEL					(6)
#define CAMERA_VICTOR_CHANNEL					(7)

	//Sensor Channels
#define INTAKE_SWITCH_CHANNEL					(2)
#define PULSE_SWITCH_CHANNEL					(3)

	//Analog
#define POT_CHANNEL 							(1)

	//Pneumatics
#define SHIFTER_SOLENOID_CHANNEL_A				(1)
#define SHIFTER_SOLENOID_CHANNEL_B				(2)
#define INTAKE_ARM_SOLENOID_CHANNEL_A			(3)
#define INTAKE_ARM_SOLENOID_CHANNEL_B			(4)

	//Potentiometer
#define POT_DEADZONE_HIGH						(.3)
#define POT_DEADZONE_LOW						(.4)
#define POT_UPPER_LIMIT							(4.4)
#define POT_LOWER_LIMIT							(.5)

	//Choo-Choo Launcher 
#define STATE_OFF								(0)
#define STATE_HOLD								(1)
#define STATE_RESET								(2)
#define STATE_COCKED							(3)
#define STATE_FIRE								(4)
#define LAUNCH_TIME 							(.17)
#define RESET_TIME								(1)
#define SLOW_SPEED								(-1)
														
	//RPM
#define TIME_COMPARISON							(.25)
#define MINUTE_CONVERSION						(240)
#define TICKS_PER_ROTATION						(250)

	//Misc
#define SYNC_STATE_OFF          		        (0)
#define REDUCTION							    (.5)
#define DEADZONE								(.1)
#define TICKS_DEADZONE							(10)
#define INCHES_PER_TICK                			(0.075398)   // circumference of wheel / total 
#define PI										(3.14159265358979323846264338327950288)
#define INCHES_PER_VOLT							(1/.0098)// 1 / (9.8mV / 1000)

#endif
