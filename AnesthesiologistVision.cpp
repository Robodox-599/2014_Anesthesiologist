#include "AnesthesiologistVision.h"
/*
AnesthesiologistVision::AnesthesiologistVision()
{
	threshold = new Threshold(61, 255, 50, 255, 69, 255);//TODO: dummy numbers
	criteria->parameter = IMAQ_MT_AREA;
	criteria->lower = AREA_MINIMUM;
	criteria->upper = 65535;
	criteria->calibrated = false;
	criteria->exclude = false;
}

AnesthesiologistVision::~AnesthesiologistVision()
{
	delete reports;
	delete report;
	delete image;

	reports = NULL;
	report = NULL;
	image = NULL;
}
BinaryImage* AnesthesiologistVision::getFilteredImage() {
	return filterSmallParticles(filterImageHSV(image));
}
BinaryImage* AnesthesiologistVision::filterImageHSV(HSLImage *image) {
	return image->ThresholdHSV(threshold->plane1Low, threshold->plane2High,
			threshold->plane2Low, threshold->plane2High, threshold->plane3Low,
			threshold->plane3High);
}

void AnesthesiologistVision::setImage(HSLImage *img) {
	image = img;
}

BinaryImage* AnesthesiologistVision::filterSmallParticles(BinaryImage *image) {
	return image->ParticleFilter(criteria, 1);
}

void AnesthesiologistVision::setParticleAnalysisReport() {
	BinaryImage *img = getFilteredImage();
	reports = img->GetOrderedParticleAnalysisReports();
}

double AnesthesiologistVision::getDistanceFromGoal() {
	return (REFLECTOR_INCHES_WIDTH * FIELD_OF_VIEW_PIXELS_WIDTH) / (2
			* report->imageWidth * tan(ANGLE));
}

bool AnesthesiologistVision::checkIfVertical(ParticleAnalysisReport *report) {
	if (report->imageHeight > report->imageWidth) {
		return true;
	}
	return false;
}

ParticleAnalysisReport* AnesthesiologistVision::getParticleAnalysisReport(int index) {
	return &reports->at(index);
}

ParticleAnalysisReport* AnesthesiologistVision::getReport()
{
	return report;
}

int AnesthesiologistVision::getVerticalIndex() {
	for (unsigned int i = 0; i < reports->size(); i++) {
		report = getParticleAnalysisReport(i);
		if (checkIfVertical(report))
			return i;
	}
	return 0;
}

void AnesthesiologistVision::setReport(int index) {
	report = &reports->at(index);
}

bool AnesthesiologistVision::update(HSLImage* image)
{
	setImage(image);
	setParticleAnalysisReport();
	print(0, oi);
	/*if (getDistanceFromGoal() > RANGE_MINIMUM && getDistanceFromGoal() < RANGE_MAXIMUM)
	{
		oi->dashboard->PutString("Range", "Good To Shoot");
	}
	else if(getDistanceFromGoal() < RANGE_MINIMUM)
=======
	setReport(getVerticalIndex());	
	if (getDistanceFromGoal() > RANGE_MINIMUM && getDistanceFromGoal() < RANGE_MAXIMUM)
	{
		return true;
	}
	return false;
}


std::string AnesthesiologistVision::join(std::string str, int i) {
	std::ostringstream oss;
	oss << str << i;
	return oss.str();
}

void AnesthesiologistVision::print(int i, AnesthesiologistOperatorInterface *oi)
{
	oi->dashboard->PutString("Test", "Yellow");
	
	setReport(i);
	oi->dashboard->PutNumber("Distance ", getDistanceFromGoal());
	oi->dashboard->PutNumber(join("Pixel Of Target Width ", i), report->imageWidth);
	oi->dashboard->PutNumber(join("Pixel Of Target Height ", i), report->imageHeight);
	oi->dashboard->PutNumber(join("Field Of View Pixel ", i), FIELD_OF_VIEW_PIXELS_WIDTH);
	oi->dashboard->PutNumber(join("ANGLE ", i), ANGLE);
	oi->dashboard->PutNumber(join("TAN (ANGL) ", i), tan(ANGLE));
	
}
*/
