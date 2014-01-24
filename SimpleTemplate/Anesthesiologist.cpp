#include "WPILib.h"

//Vision includes
//#include "Vision/RGBImage.h"
//#include "Vision/BinaryImage.h"
//#include "Math.h"

#include "AnesthesiologistDrive.h"
//#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistPIDOutput.h"
#include "AnesthesiologistOperatorInterface.h"
#include "AnesthesiologistMacros.h"

//Vision defines
//Camera constants used for distance calculation
#define Y_IMAGE_RES 			(480)	//X Image resolution in pixels, should be 120, 240 or 480
#define VIEW_ANGLE 				(49)	//Axis M1013

#define PI 						(3.141592653)

//Score limits used for target identification
#define RECTANGULARITY_LIMIT 	(40)
#define ASPECT_RATIO_LIMIT 		(55)

//Score limits used for hot target determination
#define TAPE_WIDTH_LIMIT 		(50)
#define VERTICAL_SCORE_LIMIT 	(50)
#define LR_SCORE_LIMIT 			(50)
	
//Minimum area of particles to be considered
#define AREA_MINIMUM 			(150)

//Maximum number of particles to process
#define MAX_PARTICLES 			(8)


int step = 0;

bool isWait = false;
bool bInit = true;
bool bLatch = false;
double initTime = 0;
double currentTime = 0;

class Anesthesiologist: public IterativeRobot
{
	AnesthesiologistDrive *drive;
	//AnesthesiologistManipulator *manipulator;
	AnesthesiologistOperatorInterface *oi;
	Compressor *comp599;
	//Encoder *leftDriveEncoder;
	Timer *timer;
	//Encoder *rightDriveEncoder;
	//AxisCamera &camera;
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
*/
public:	
	Anesthesiologist()
	{
		//manipulator = new AnesthesiologistManipulator();
		drive = new AnesthesiologistDrive();
		oi = new AnesthesiologistOperatorInterface();
		comp599 = new Compressor(1, 1, 1, 1); 
		//leftDriveEncoder = new Encoder(1, LEFT_DRIVE_ENCODER_CHANNEL_A, 1, LEFT_DRIVE_ENCODER_CHANNEL_B, true, Encoder::k1X);
		//rightDriveEncoder = new Encoder(1, RIGHT_DRIVE_ENCODER_CHANNEL_A, 1, RIGHT_DRIVE_ENCODER_CHANNEL_B, false, Encoder::k1X);
		
		//manipulator->timer->Start();
		//leftDriveEncoder->Start();
		//rightDriveEncoder->Start();
		oi->dashboard->init();
		comp599->Start();
		//Vision(accent)
		//camera = AxisCamera::GetInstance();
		//isWait = false;
		//bInit = true;
		//bLatch = false;
	}
	
	void RobotInit()
	{
	
	}
	
	void DisabledInit()
	{
		//manipulator->armEncoder->Start();
		//leftDriveEncoder->Start();
		//rightDriveEncoder->Start();
	}
	
	void AutonomousInit()
	{
		step = 0;
		//manipulator->armEncoder->Reset();
		//leftDriveEncoder->Reset();
		//rightDriveEncoder->Reset();
	}
	
	void TeleopInit()
	{
		drive->setLinVelocity(0);
		drive->setTurnSpeed(0, false);
		drive->drive();
		//manipulator->setVelocity(0);
		//leftDriveEncoder->Start();
		//rightDriveEncoder->Start();
	}
	
	void TestInit()
	{
	
	}
	
	void DisabledPeriodic()
	{
		step = 0;
		//manipulator->armEncoder->Reset();
		//drive->isAtLinearTarget = false;
		//leftDriveEncoder->Reset();
		//rightDriveEncoder->Reset();
		smartDashboardPrint();
	}
	
	void AutonomousPeriodic()
	{
		//timer->Start();
		smartDashboardPrint();
	}
	
	void TeleopPeriodic()
	{
		comp599->Start();
		//leftDriveEncoder->Start();
		//rightDriveEncoder->Start();
		//manipulator->timer->Start();
		timer->Start();
		while(IsOperatorControl())
		{
			teleDrive();
			smartDashboardPrint();
		}
	}
	
	void TestPeriodic()
	{
	
	}
	
	void teleDrive()
	{
		//leftDriveEncoder->Start();
		//rightDriveEncoder->Start();
		if(!isWait)
		{
			drive->setLinVelocity(-oi->getDriveJoystick()->GetY(Joystick::kRightHand));
			drive->setTurnSpeed(oi->getDriveJoystick()->GetX(Joystick::kRightHand), oi->getDriveJoystickButton(1));
			drive->drive();
		}
		drive->shift(oi->getDriveJoystickButton(8), oi->getDriveJoystickButton(9));
		
		//manipulator->setVelocity((oi->getManipJoystick()->GetThrottle()+1)/2);
		//manipulator->intakeBall(oi->getManipJoystickButton(2));
		
		if(oi->getDriveJoystickButton(6))
		{
			comp599->Start();
		}
		else if(oi->getDriveJoystickButton(7))
		{
			comp599->Stop();
		}
		
		//timer wait test
		if(oi->getDriveJoystickButton(10))
		{
			bLatch = true;
		}
		if(bLatch)
		{
			wait(10.0);
		}
	}
	
	void smartDashboardPrint()
	{
		oi->dashboard->PutNumber("Drive Linear Speed: ", drive->getLinVelocity());
		oi->dashboard->PutNumber("Drive Turn Speed: ", drive->getTurnSpeed());
		//oi->dashboard->PutNumber("Arm Encoder Raw Value: ", manipulator->armEncoder->Get());
		//oi->dashboard->PutNumber("encoder raw value: ", leftDriveEncoder->Get());
		//oi->dashboard->PutNumber("Left Encoder Raw Value: ", leftDriveEncoder->Get());
		//oi->dashboard->PutNumber("Right Encoder Raw Value: ", rightDriveEncoder->Get());
		//oi->dashboard->PutNumber("Timer: ", manipulator->timer->Get());
		oi->dashboard->PutNumber("Timer: ", timer->Get());
		oi->dashboard->PutBoolean("Wait?: ", isWait);
		oi->dashboard->PutBoolean("BLATCH BLATCH BLATCH!?: ", bLatch);
	}
	
	void wait(double secToWait)
	{
		currentTime = timer->Get();
		if(bInit)
		{
			initTime = currentTime;
			bInit = false;
			isWait = true;
		}
		if(currentTime < secToWait+initTime)
		{
			isWait = true;
		}
		else
		{
			isWait = false;
			bInit = true;
			bLatch = false;
		}
		currentTime = timer->Get();
	}
	
	/*
	void track()
	{
		itemScores *scores;
		reportOnTarget target;
		int verticalTarget[MAX_PARTICLES];//will contain potential targets
		int horizontalTarget[MAX_PARTICLES];
		int verticalTargetCount;//num of potential targets
		int horizontalTargetCount;//num of potential targets
		Threshold threshold(105, 137, 230, 255, 133, 183);	//HSV threshold criteria, ranges are in that order ie. Hue is 60-100
		ParticleFilterCriteria2 criteria[] = {{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}};
		ColorImage *image; //image to analyze
		
		//image = camera.GetImage();
		BinaryImage *thresholdedImage = image->ThresholdHSV(threshold);
		BinaryImage *filteredImage = thresholdedImage->ParticleFilter(criteria, 1);
		vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();//dat report
		
		verticalTargetCount = 0;
		horizontalTargetCount = 0;
		
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
					horizontalTarget[horizontalTargetCount++] = count;
				}
				else if(scoreCompare(scores[count], true))
				{
					verticalTarget[verticalTargetCount++] = count;
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
				ParticleAnalysisReport *verticalReport = reports->at(verticalTarget[i]);
				
				for (int j = 0; j < horizontalTargetCount; j++) //dat nested forloop thooooooo
				{
					ParticleAnalysisReport *horizontalReport = reports->at(horizontalTarget[j]);
					double horizontalWidth; 
					double horizontalHeight;
					double verticalWidth; 
					double leftScore; 
					double rightScore;
					double tapeWidthScore; 
					double verticalScore; 
					double total;
					
					imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizontalWidth);
					imaqMeasureParticle(filteredImage->GetImaqImage(), verticalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &verticalWidth);
					imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizontalHeight); //measures rectangular sides
					
					leftScore = ratioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizontalWidth);				
					rightScore = ratioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizontalWidth);
					tapeWidthScore = ratioToScore(verticalWidth/horizontalHeight);
					verticalScore = ratioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizontalHeight));
					
					if(leftScore > rightScore)
					{
						total = leftScore;
					}
					else
					{
						total = rightScore;
					}
					total += tapeWidthScore + verticalScore;
					
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
		delete scores;
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
		return (max(0, min(100*(1-fabs(1-ratio)), 100)));
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
};	

START_ROBOT_CLASS(Anesthesiologist);
