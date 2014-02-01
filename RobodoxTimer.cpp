#include "RobodoxTimer.h"

RobodoxTimer::RobodoxTimer()
{
	
}

RobodoxTimer::~RobodoxTimer()
{
	
}

void RobodoxTimer::wait(double timeToWaitMs)
{
	Start();
	double init = Get();
	while(Get() < timeToWaitMs/1000 + init)
	{
		
	}
	Stop();
}
