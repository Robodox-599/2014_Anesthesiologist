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
	int getVerticalIndex();
	
	bool update(HSLImage *image);

	//void print(int index, AnesthesiologistOperatorInterface *oi);
	std::string join(std::string str, int i);
	
	ParticleAnalysisReport* getReport();
private:
	vector<ParticleAnalysisReport> *reports;
	ParticleAnalysisReport *report;
	HSLImage *image;
	ParticleFilterCriteria2 *criteria;
	Threshold *threshold;
	bool side; //if hotZone == left{side = false} else side = true
};

#endif


/*	
	struct itemScores
	{
		double rectangularity;
		double aspectRatioVertical;
		double aspectRatioHorizontal;
	};
	
	struct reportOnTarget
	{
		int verticalIndex;
		int horizontalIndex;
		bool isHot;
		double totalScore;
		double leftScore;
		double rightScore;
		double tapeWidthScore;
		double verticalScore;
	};
 	void track()
	{
		Threshold threshold(105, 137, 230, 255, 133, 183);	//HSV threshold criteria, ranges are in that order ie. Hue is 60-100
		ParticleFilterCriteria2 criteria[] = {{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}};
		
		AxisCamera &camera = AxisCamera::GetInstance();
		ColorImage *image = camera.GetImage();
		BinaryImage *thresholdedImage = image->ThresholdHSV(threshold);
		BinaryImage *filteredImage = thresholdedImage->ParticleFilter(criteria, 1);

		itemScores scores[MAX_PARTICLES];
		reportOnTarget target;
		int verticalTarget[MAX_PARTICLES];//will contain potential targets
		int horizontalTarget[MAX_PARTICLES];
		int verticalTargetCount = 0; //num of potential targets
		int horizontalTargetCount = 0; //num of potential targets
		vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();//dat report
		
		if(reports->size() > 0)
		{
			ParticleAnalysisReport *report;
			//dat forloop
			for(UINT8 count = 0; count < MAX_PARTICLES && count < reports->size(); count++)
			{
				report = &(reports->at(count));
				
				scores[count].rectangularity = scoreRectangularity(report);
				scores[count].aspectRatioVertical = scoreAspectRatio(filteredImage, report, true);
				scores[count].aspectRatioHorizontal = scoreAspectRatio(filteredImage, report, false);
			
				if(scoreCompare(scores[count], false))
				{
					horizontalTarget[horizontalTargetCount] = count;
					horizontalTargetCount += 1;
				}
				else if(scoreCompare(scores[count], true))
				{
					verticalTarget[verticalTargetCount] = count;
					verticalTargetCount += 1;
				}
				else
				{
					//lay down, try not to cry, cry a lot
				}
			}
			
			target.totalScore = 0;
			target.leftScore = 0;
			target.rightScore = 0;
			target.tapeWidthScore = 0;
			target.verticalScore = 0;
			target.verticalIndex = verticalTarget[0];
			
			for(int i = 0; i < verticalTargetCount; i++) //dat forloop again
			{
				ParticleAnalysisReport *verticalReport = &(reports->at(verticalTarget[i]));
				
				for (int j = 0; j < horizontalTargetCount; j++) //dat nested forloop thooooooo
				{
					ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTarget[j]));
					double horizontalWidth; 
					double horizontalHeight;
					double verticalWidth; 
					
					imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizontalWidth);
					imaqMeasureParticle(filteredImage->GetImaqImage(), verticalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &verticalWidth);
					imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizontalHeight); //measures rectangular sides
					
					double leftScore = ratioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizontalWidth);
					double rightScore = ratioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizontalWidth);
					double tapeWidthScore = ratioToScore(verticalWidth/horizontalHeight);
					double verticalScore = ratioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizontalHeight));
					
					double total = tapeWidthScore + verticalScore;
					if(leftScore > rightScore)
					{
						total += leftScore;
					}
					else
					{
						total += rightScore;
					}
					
					if(total > target.totalScore)
					{
						target.horizontalIndex = horizontalTarget[j];
						target.verticalIndex = verticalTarget[i];
						target.totalScore = total;
						target.leftScore = leftScore;
						target.rightScore = rightScore;
						target.tapeWidthScore = tapeWidthScore;
						target.verticalScore = verticalScore;
					}
				}
				target.isHot = hotOrNot(target);
			}
		}
		
		delete filteredImage;
		delete thresholdedImage;
		delete image;
		delete reports;	
	}
	
	double computeDistance (BinaryImage *image, ParticleAnalysisReport *report) 
	{
		double rectLong;
		double height;
		int targetHeight;
		
		imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
		height = min(report->boundingRect.height, rectLong);
		targetHeight = 32;
		
		return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
	}
	
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical)
	{
		double rectLong, rectShort, idealAspectRatio, aspectRatio;
		
		if(vertical)
		{
			idealAspectRatio = (4.0/32);
		}
		else
		{
			idealAspectRatio = (23.5/4);
		}
		
		imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
		imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
		
		if(report->boundingRect.width > report->boundingRect.height) //calculate aspect ratio
		{
			aspectRatio = ratioToScore(((rectLong/rectShort)/idealAspectRatio));
		} 
		else
		{
			aspectRatio = ratioToScore(((rectShort/rectLong)/idealAspectRatio));
		}
		
		return aspectRatio; //range 0-100
	}
	
	bool scoreCompare(itemScores scores, bool vertical)
	{
		bool isTarget = true;
	
		isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
		if(vertical)
		{
			isTarget &= scores.aspectRatioVertical > ASPECT_RATIO_LIMIT;
		}
		else 
		{
			isTarget &= scores.aspectRatioHorizontal > ASPECT_RATIO_LIMIT;
		}
	
		return isTarget;
	}
	
	double scoreRectangularity(ParticleAnalysisReport *report)
	{
		if(report->boundingRect.width*report->boundingRect.height !=0)
		{
			return 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
		}
		else 
		{
			return 0;
		}	
	}	
	
	double ratioToScore(double ratio)
	{
		return (max(0, min(100*(1 - fabs(1-ratio)), 100)));
	}
	
	bool hotOrNot(reportOnTarget target)
	{
		bool isHot = true;
		
		isHot &= target.tapeWidthScore >= TAPE_WIDTH_LIMIT;
		isHot &= target.verticalScore >= VERTICAL_SCORE_LIMIT;
		isHot &= (target.leftScore > LR_SCORE_LIMIT) | (target.rightScore > LR_SCORE_LIMIT);
		
		return isHot;
	}
 
 */
