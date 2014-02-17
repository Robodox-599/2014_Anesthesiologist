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
	10 - 
	11 - 
Manip Joystick:
	1 - 
	2 - intake 
	3 - outtake
	4 - 
	5 - 
	6 - set arm to intake position
	7 - set arm to stored position 
	8 - set camera position to back
	9 - set camera position to forward
	10 - toggle shot range to short 
	11 - toggle shot range to long
	throttle -  roller speed
*/

	//Slots
#define PNEUMATICS_24V_SLOT						(1)//TODO: dummy number

	//Talons
#define DRIVE_FRONT_LEFT_MOTOR_CHANNEL          (1)
#define DRIVE_REAR_LEFT_MOTOR_CHANNEL           (2)
#define DRIVE_FRONT_RIGHT_MOTOR_CHANNEL         (3)
#define DRIVE_REAR_RIGHT_MOTOR_CHANNEL          (4)
#define LAUNCHER_MOTOR_CHANNEL          		(5)
#define INTAKE_ROLLER_CHANNEL					(6)
#define CAMERA_VICTOR_CHANNEL					(7)

	//Sensor Channels
#define POT_CHANNEL 							(1)
#define INTAKE_SWITCH_CHANNEL					(2)
#define PULSE_SWITCH_CHANNEL					(3)
#define ARM_LAUNCHER_SWITCH_CHANNEL				(4)//TODO: dummy number
#define SONAR_OUTPUT 							(5)
#define SONAR_INPUT 							(6)

	//Pneumatics
#define SHIFTER_SOLENOID_CHANNEL_A				(1)
#define SHIFTER_SOLENOID_CHANNEL_B				(2)
#define INTAKE_ARM_SOLENOID_CHANNEL_A			(3)
#define INTAKE_ARM_SOLENOID_CHANNEL_B			(4)
#define STOPPER_SOLENOID_CHANNEL_A				(5)
#define STOPPER_SOLENOID_CHANNEL_B				(6)

	//Encoders
#define LEFT_DRIVE_ENCODER_CHANNEL_A			(4)//TODO: dummy number
#define LEFT_DRIVE_ENCODER_CHANNEL_B			(5)//TODO: dummy number
#define RIGHT_DRIVE_ENCODER_CHANNEL_A			(6)//TODO: dummy number
#define RIGHT_DRIVE_ENCODER_CHANNEL_B			(7)//TODO: dummy number

	//Potentiometer
#define POT_DEADZONE_HIGH						(.3)
#define POT_DEADZONE_LOW						(.3)
#define POT_UPPER_LIMIT							(4.3)
#define POT_LOWER_LIMIT							(.47)

	//Choo-Choo Launcher 
#define STATE_OFF								(0)
#define STATE_HOLD								(1)
#define STATE_RESET								(2)
#define STATE_COCKED							(3)
#define STATE_FIRE								(4)
#define LAUNCH_TIME 							(.1)
#define TIME_TO_SLOW_SPEED						(2)//TODO: dummy number
#define LAUNCHER_MOTOR_SLOW_SPEED				(-.5)//TODO: dummy number (must be negative)
														
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

	//Camera, in Inches and Degrees
#define ANGLE									(23.5 *PI/180)	//half of full view angle
#define FIELD_OF_VIEW_PIXELS_WIDTH				(640) 	//TODO
#define REFLECTOR_INCHES_WIDTH					(4) 	//TODO
#define AREA_MINIMUM							(150)
#define RANGE_MINIMUM							(204)	//TODO
#define RANGE_MAXIMUM							(240)	//TODO

#endif
