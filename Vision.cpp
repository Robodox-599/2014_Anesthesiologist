#include "Vision.h"

Vision::Vision() {
	threshold = new Threshold(105, 137, 230, 255, 133, 183);//TODO: dummy numbers
	ParticleFilterCriteria2 criteria1[] = { { IMAQ_MT_AREA, AREA_MINIMUM,
			65535, false, false } };
}
Vision::~Vision() {
	delete reports;
	delete report;
	delete image;

	reports = NULL;
	report = NULL;
	image = NULL;
}
BinaryImage* Vision::getFilteredImage() {
	return filterSmallParticles(filterImageHSV(image));
}
BinaryImage* Vision::filterImageHSV(HSLImage *image) {
	return image->ThresholdHSV(threshold->plane1Low, threshold->plane2High,
			threshold->plane2Low, threshold->plane2High, threshold->plane3Low,
			threshold->plane3High);
}

void Vision::getImage(HSLImage *img) {
	image = img;
}

BinaryImage* Vision::filterSmallParticles(BinaryImage *image) {
	return image->ParticleFilter(criteria1, 1);
}

void Vision::setParticleAnalysisReport() {
	BinaryImage *img = getFilteredImage();
	reports = img->GetOrderedParticleAnalysisReports();
}

double Vision::getDistanceFromGoal() {
	return (REFLECTOR_INCHES_WIDTH * FIELD_OF_VIEW_PIXELS_WIDTH) / (2
			* report->imageWidth * tan(ANGLE));
}

double Vision::getYPixelOffset() {
	double offset = report->center_mass_y_normalized
			* (double) NORMALIZED_TO_PIXEL;
	if (offset < 0)
		offset *= -1;
	return offset;
}

double Vision::getXPixelOffset() {
	double offset = report->center_mass_x_normalized
			* (double) NORMALIZED_TO_PIXEL;
	if (offset < 0) {
		side = false;
		offset *= -1;
	} else
		side = true;
	return offset;
}

double Vision::getDistance() {
	return sqrt(
			pow(getDistanceFromGoal(), 2) + pow(
					getYPixelOffset() * getPixelToFeetConversion(), 2) + pow(
					getXPixelOffset() * getPixelToFeetConversion(), 2));
}

double Vision::getPixelToFeetConversion() {
	return (double) REFLECTOR_INCHES_WIDTH / (double) report->imageWidth;
}

double Vision::getDistanceFromSide() {
	return getXPixelOffset() * getPixelToFeetConversion() + 8 + 23.5 + 9.12;
}

double Vision::getLinearMoveDistance() {
	return WANTED_DISTANCE_FROM_SIDE - getDistanceFromGoal();
}

double Vision::getSideMoveDistance() {
	double distance = WANTED_DISTANCE_FROM_SIDE - getDistanceFromSide();
	if (side)
		return distance;
	else
		return -distance;
}

bool Vision::checkIfVertical(ParticleAnalysisReport *report) {
	if (report->imageHeight > report->imageWidth) {
		return true;
	}
	return false;
}

ParticleAnalysisReport* Vision::getParticleAnalysisReport(int index) {
	return &reports->at(index);
}

int Vision::setVertical() {
	for (unsigned int i = 0; i < reports->size(); i++) {
		report = getParticleAnalysisReport(i);
		if (checkIfVertical(report))
			return i;
	}
	return 0;
}

void Vision::setReport(int index) {
	report = &reports->at(index);
}

