#include "AnesthesiologistPIDOutput.h"

AnesthesiologistPIDOutput::AnesthesiologistPIDOutput()
{
	
}

AnesthesiologistPIDOutput::~AnesthesiologistPIDOutput()
{
	
}

void AnesthesiologistPIDOutput::PIDWrite(float output)
{
	result = output;
}

double AnesthesiologistPIDOutput::readOutput()
{
	return result;
}
