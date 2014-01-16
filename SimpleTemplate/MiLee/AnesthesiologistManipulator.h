#ifndef ANESTHESIOLOGIST_MANIPULATOR_H
#define ANESTHESIOLOGIST_MANIPULATOR_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistManipulator
{
	public:
		AnesthesiologistManipulator();
		AnesthesiologistManipulator(UINT8 intakeRollerChannel);
		~AnesthesiologistManipulator();
		
		void intake(bool intakeNow);
		
	private:
		Victor *intakeRoller;
	
};
#endif
