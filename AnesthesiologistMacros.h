#ifndef ANESTHESIOLOGIST_MACROS_H
#define ANESTHESIOLOGIST_MACROS_H

//fake for Drive; encoders + jaguars
#define CHANNEL1										(8)//TODO: dummy number
#define CHANNEL2										(8)//TODO: dummy number
#define CHANNEL3										(8)//TODO: dummy number
#define CHANNEL4										(8)//TODO: dummy number
#define LEFT_DRIVE_ENCODER_CHANNEL_A					(8)//TODO: dummy number
#define LEFT_DRIVE_ENCODER_CHANNEL_B					(8)//TODO: dummy number
#define RIGHT_DRIVE_ENCODER_CHANNEL_A					(8)//TODO: dummy number
#define RIGHT_DRIVE_ENCODER_CHANNEL_B					(8)//TODO: dummy number

#define SYNC_STATE_OFF	(0)

#define PNEUMATICS_24V_SLOT                             (1)//TODO: dummy number

        //Motors
#define DRIVE_FRONT_LEFT_MOTOR_CHANNEL          		(1)//TODO: dummy number
#define DRIVE_REAR_LEFT_MOTOR_CHANNEL           		(2)//TODO: dummy number
#define DRIVE_FRONT_RIGHT_MOTOR_CHANNEL         		(3)//TODO: dummy number
#define DRIVE_REAR_RIGHT_MOTOR_CHANNEL          		(4)//TODO: dummy number
#define LAUNCHER_MOTOR_VICTOR_CHANNEL           		(5)//TODO: dummy number

        //Pneumatics
#define SHIFTER_SOLENOID_CHANNEL_A                      (1)//TODO: dummy number
#define SHIFTER_SOLENOID_CHANNEL_B                      (2)//TODO: dummy number
#define LAUNCHER_SOLENOID_CHANNEL                       (3)//TODO: dummy number

        //Manipulators
#define INTAKE_ROLLER_VICTOR_CHANNEL                    (1)//TODO: dummy number
#define INTAKE_SWITCH_CHANNEL                           (2)//TODO: dummy number
#define INTAKE_ARM_VICTOR_CHANNEL                       (3)//TODO: dummy number

        //Encoders
#define ARM_ENCODER_CHANNEL_A                           (1)//TODO: dummy number
#define ARM_ENCODER_CHANNEL_B                           (2)//TODO: dummy number
#define TICKS_DEADZONE									(5)	//TODO: dummy number
#define INCHES_PER_TICK									(6)	//TODO: dummy number
															//wheelCircumference/totalTicksPerRev
#define TICKS_PER_DEGREE								(7)	//TODO: dummy number
															//widthWheelToWheel*ticks*DEGREES_TO_RADIANS

        //Misc
#define SYNC_STATE_OFF                                  (0)
#define REDUCTION                                       (.75)
#define DEADZONE                                        (.1)


#endif
