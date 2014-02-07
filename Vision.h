#ifndef VISION_H
#define VISION_H

#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include "Math.h"

//EVERYTHING SHOULD BE IN INCHES!!!! 
//AND DEGREES FOR ANY ANGLES

#define REFLECTOR_TO_GOAL 						(0)//TODO: dummy number, may be unnecessary
#define THRESHOLD								(new Threshold (0,0,0,0,0,0))//TODO
#define CRITERIA								(ParticleFilterCriteria2[] = {{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}})
#define ANGLE									(45)//TODO
#define FIELD_OF_VIEW_PIXELS_WIDTH				(0) //TODO
#define FIELD_OF_VIEW_INCHES_WIDTH				(0) //TODO
#define REFLECTOR_INCHES_WIDTH					(0) //TODO
#define NORMALIZED_TO_PIXEL						(FIELD_OF_VIEW_PIXELS/2) //TODO
#define WANTED_DISTANCE_FROM_SIDE				(69)
#define WANTED_DISTANCE_FROM_FRONT				(0)//TODO


class Vision
{
public:
	static BinaryImage* filterImageHSV(ColorImage *image); //takes out particles so only ones we want
	static BinaryImage* filterImageSmallParticles(BinaryImage *image);
	static void setParticleAnalysisReport();
	static BinaryImage* getFilteredImage(ColorImage *image);
	static double getDistance(); //camera to reflector tape, might be useless
	static double getLinearMoveDistance(); //how much bot has to move forward
	static double getSideMoveDistance(); //how much bot has to move to the left/right
									 //positive = right, negative = left;
								     //in inches, can be used with drive methods, hopefully
	static double getDistanceFromGoal();
	static double getDistanceFromSide();
	static double getYPixelOffset();
	static double getXPixelOffset();
	static void getImage(); //ues camera
	static void setCamera(AxisCamera camera);
	static double getPixelToFeetConversion();
	
private:
	static vector<ParticleAnalysisReport> reports;
	static ColorImage *image;
	static AxisCamera camera;
	static bool side; //if hotZone == left{side = false} else side = true
};

#endif