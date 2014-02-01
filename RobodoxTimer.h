#ifndef ROBODOX_TIMER_H
#define ROBODOX_TIMER_H

#include "WPILib.h"

class RobodoxTimer : public Timer
{
public:
	RobodoxTimer();
	~RobodoxTimer();
	
	void wait(double timeToWaitMs);
};
#endif
