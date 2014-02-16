#ifndef AnesthesiologistVision_H
#define AnesthesiologistVision_H

#include <sstream>
#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include <Math.h>
#include "Math.h"
#include "Vision/Threshold.h"
#include "AnesthesiologistOperatorInterface.h"

//EVERYTHING SHOULD BE IN INCHES!!!! 
//AND DEGREES FOR ANY ANGLES

#define ANGLE									(23.5)	//half of full view angle
#define FIELD_OF_VIEW_PIXELS_WIDTH				(640) 	//TODO
#define REFLECTOR_INCHES_WIDTH					(4) 	//TODO
#define WANTED_DISTANCE_FROM_SIDE				(69)
#define WANTED_DISTANCE_FROM_FRONT				(0)//TODO
#define AREA_MINIMUM							(150)
#define RANGE_MINIMUM							(204)//TODO
#define RANGE_MAXIMUM							(240)//TODO


class AnesthesiologistVision
{
public:
	AnesthesiologistVision();
	~AnesthesiologistVision();
	
	void setImage(HSLImage *image); //ues camera
	BinaryImage* getFilteredImage();
	BinaryImage* filterImageHSV(HSLImage *image); //takes out particles so only ones we want	
	BinaryImage* filterSmallParticles(BinaryImage *image);
	
	void setParticleAnalysisReport();
	ParticleAnalysisReport* getParticleAnalysisReport(int index); 
	void setReport(int index);
	
	//double getDistance(); //camera to reflector tape, might be useless
	double getDistanceFromGoal();	//really wanted...
	//double getDistanceFromSide();	//useless?
	
	//double getLinearMoveDistance(); //how much bot has to move forward
	//double getSideMoveDistance(); //how much bot has to move to the left/right
								 //positive = right, negative = left;
								 //in inches, can be used with drive methods, hopefully
								//but this class will only return true or false, so maybe not needed
	
	//double getYPixelOffset();
	//double getXPixelOffset();
	
	//double getPixelToFeetConversion();
	
	bool checkIfVertical(ParticleAnalysisReport *report);
	int setVertical();
	
	void update(HSLImage *image, AnesthesiologistOperatorInterface *oi);

	void print(int index, AnesthesiologistOperatorInterface *oi);
	std::string join(std::string str, int i);
private:
	vector<ParticleAnalysisReport> *reports;
	ParticleAnalysisReport *report;
	HSLImage *image;
	ParticleFilterCriteria2 *criteria;
	Threshold *threshold;
	bool side; //if hotZone == left{side = false} else side = true
};

#endif
