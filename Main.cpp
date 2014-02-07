#include "WPILib.h"
#include "Vision.h"

class Main
{
public:
	Main()
	{
		autonomous();
	}
private:
	void autonomous()
	{
		Vision::setCamera(AxisCamera::GetInstance());
		Vision::getImage();
		setParticleAnalysisReport();
		Vision::getLinearMoveDistance();
		Vision::getSideMoveDistance();
		
		//shoot
	}
};