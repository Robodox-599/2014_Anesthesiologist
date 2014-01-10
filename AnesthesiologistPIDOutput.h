#ifndef ANESTHESIOLOGIST_PID_OUTPUT_H
#define ANESTHESIOLOGIST_PID_OUTPUT_H
#include "WPILib.h"
#include "AnesthesiologistMacros.h"

class AnesthesiologistPIDOutput : public PIDOutput
{
public:
	AnesthesiologistPIDOutput();
	virtual ~AnesthesiologistPIDOutput();
};
#endif
