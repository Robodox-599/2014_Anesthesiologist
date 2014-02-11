#ifndef VISION_H
#define VISION_H

#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include <Math.h>
#include "Math.h"
#include "Vision/Threshold.h"

//EVERYTHING SHOULD BE IN INCHES!!!! 
//AND DEGREES FOR ANY ANGLES

#define ANGLE									(23.5)//half of full view angle
#define FIELD_OF_VIEW_PIXELS_WIDTH				(0) //TODO
#define REFLECTOR_INCHES_WIDTH					(0) //TODO
#define NORMALIZED_TO_PIXEL						(FIELD_OF_VIEW_PIXELS_WIDTH/2) //TODO
#define WANTED_DISTANCE_FROM_SIDE				(69)
#define WANTED_DISTANCE_FROM_FRONT				(0)//TODO
#define AREA_MINIMUM							(150)


class Vision
{
public:
	Vision();
	~Vision();
	
	void getImage(HSLImage *image); //ues camera
	BinaryImage* getFilteredImage();
	BinaryImage* filterImageHSV(HSLImage *image); //takes out particles so only ones we want	
	BinaryImage* filterSmallParticles(BinaryImage *image);
	
	void setParticleAnalysisReport();
	ParticleAnalysisReport* getParticleAnalysisReport(int index); 
	void setReport(int index);
	
	double getDistance(); //camera to reflector tape, might be useless
	double getDistanceFromGoal();	
	double getDistanceFromSide();
	
	double getLinearMoveDistance(); //how much bot has to move forward
	double getSideMoveDistance(); //how much bot has to move to the left/right
								 //positive = right, negative = left;
								 //in inches, can be used with drive methods, hopefully
	
	double getYPixelOffset();
	double getXPixelOffset();
	
	double getPixelToFeetConversion();
	
	bool checkIfVertical(ParticleAnalysisReport *report);
	int setVertical();

	
private:
	vector<ParticleAnalysisReport> *reports;
	ParticleAnalysisReport *report;
	HSLImage *image;
	ParticleFilterCriteria2 criteria1[];
	Threshold *threshold;
	bool side; //if hotZone == left{side = false} else side = true
};

#endif
