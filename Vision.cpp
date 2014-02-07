/*#include "Vision.h"

static BinaryImage* Vision::getFilteredImage()
{
	return filterImageSmallParticles(filterImageHSV(image));
}

static BinaryImage* Vision::filterImageHSV(ColorImage *image)
{
	return image->ThresholdHSV(THRESHOLD);
}

static BinaryImage* Vision::filterSmallParitcles(BinaryImage *image)
{
	return image->ParticleFilter(CRITERA, 1);
}

static void Vision::setParticleAnalysisReport()
{
	reports = getFilteredImage()->GetOrderedParticleAnalysisReports();
}

static void Vision::setCamera(AxisCamera camera)
{
	this->camera = camera;
}

static void Vision::getImage()
{
	camera.GetImage();
}

static double Vision::getDistanceFromGoalWall()
{
	return (REFLECTOR_INCHES_WIDTH * FIELD_OF_VIEW_PIXELS_WIDTH)/(2 * reports->imageWidth * tan(ANGLE));	
}

static double Vision::getYPixelOffset()
{
	return abs(reports->center_mass_y_normalized * NORMALIZED_TO_PIXEL);
}

static double Vision::getXPixelOffset()
{
	double offset = reports->center_mass_x_normalized * NORMALIZED_TO_PIXEL;
	if (offset < 0)
	{
		side = false;
	}
	else
		side = true;
	return abs(offset);
}

static double Vision::getDistance()
{
	return sqrt(pow(getDistanceFromGoalWall, 2) + pow(getYPixelOffset*getPixelToFeetConversion(), 2) + pow(getPixelXOffset*getPixelToFeetConversion(), 2));
}

static double Vision::getPixelToFeetConversion()
{
	return REFLECTOR_INCHES_WIDTH/reports->imageWidth;
}

static double Vision::getDistanceFromSide()
{
	return getXPixelOffset() * getPixelToFeetConversion();
}

static double Vision::getLinearMoveDistance()
{
	return WANTED_DISTANCE_FROM_SIDE - getDistanceFromGoal(); 
}

static double Vision::getSideMoveDistance()
{
	double distance = WANTED_DISTANCE_FROM_SIDE - getDistanceFromSide();
	if (side)
		return distance;
	else
		return -distance;
}	
*/
