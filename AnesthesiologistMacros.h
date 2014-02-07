#ifndef ANESTHESIOLOGIST_MACROS_H
#define ANESTHESIOLOGIST_MACROS_H

/*Joystick button mapping (for reference)
Drive Joystick:
	1 - turbo turning
	2 - 
	3 - 
	4 - 
	5 - 
	6 - start compressor
	7 - stop compressor
	8 - shift up
	9 - shift down
	10 - timer wait
	11 - 
Manip Joystick:
	1 - shoot ball
	2 - shooter safety switch
	3 - start rollers, intake ball
	4 - set arm to intake position
	5 - set arm to stored position
	6 - 
	7 - 
	8 - set camera position to back
	9 - set camera position to forward
	10 - 
	11 - 
*/

	//Slots
#define PNEUMATICS_24V_SLOT						(1)//TODO: dummy number

	//Motors
#define DRIVE_FRONT_LEFT_MOTOR_CHANNEL          (1)//TODO: dummy number
#define DRIVE_REAR_LEFT_MOTOR_CHANNEL           (2)//TODO: dummy number
#define DRIVE_FRONT_RIGHT_MOTOR_CHANNEL         (3)//TODO: dummy number
#define DRIVE_REAR_RIGHT_MOTOR_CHANNEL          (4)//TODO: dummy number
#define LAUNCHER_MOTOR_VICTOR_CHANNEL           (5)//TODO: dummy number
#define INTAKE_ROLLER_VICTOR_CHANNEL			(6)//TODO: dummy number
#define CAMERA_VICTOR_CHANNEL					(7)//TODO: dummy number

	//Sensor Channels
#define INTAKE_SWITCH_CHANNEL					(1)//TODO: dummy number
#define LAUNCHER_SWITCH_CHANNEL					(2)//TODO: dummy number

	//Pneumatics
#define SHIFTER_SOLENOID_CHANNEL_A				(1)//TODO: dummy number
#define SHIFTER_SOLENOID_CHANNEL_B				(2)//TODO: dummy number
#define LAUNCHER_SOLENOID_CHANNEL				(3)//TODO: dummy number
#define LEFT_INTAKE_ARM_SOLENOID_CHANNEL_A		(4)//TODO: dummy number
#define LEFT_INTAKE_ARM_SOLENOID_CHANNEL_B		(5)//TODO: dummy number
#define RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_A		(6)//TODO: dummy number
#define RIGHT_INTAKE_ARM_SOLENOID_CHANNEL_B		(7)//TODO: dummy number

	//Encoders
#define LEFT_DRIVE_ENCODER_CHANNEL_A			(4)//TODO: dummy number
#define LEFT_DRIVE_ENCODER_CHANNEL_B			(5)//TODO: dummy number
#define RIGHT_DRIVE_ENCODER_CHANNEL_A			(6)//TODO: dummy number
#define RIGHT_DRIVE_ENCODER_CHANNEL_B			(7)//TODO: dummy number

	//Misc
#define SYNC_STATE_OFF          		        (0)
#define REDUCTION							    (.75)
#define DEADZONE								(.1)
#define TICKS_DEADZONE							(10)
#define POT_DEADZONE							(.2)
#define POT_UPPER_LIMIT							(5)
#define POT_LOWER_LIMIT							(0)
#define INCHES_PER_TICK                			(0.075398)   // circumference of wheel / total 


#endif
