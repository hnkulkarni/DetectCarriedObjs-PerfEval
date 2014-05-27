/*
 * DetectByLocation.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#include "DetectByLocation.h"

/*******************************************************************
 * Function Name: Default Constructor
 * Return Type 	:
 * Created On	: Jun 18, 2013
 * Created By 	: hrushi
 * Comments		: This is the that takes arguments of the probe images and background images.
 * Arguments	: const ColorImg ProbeImg, const GrayImg BkImg, const Args& args
 *******************************************************************/
DetectByLocation::DetectByLocation(const ColorImg ProbeImg, const GrayImg BkImg, vector<ProbImg> ProbImgs, PriorProb oPriorProb, const ContourMap& Segments,  const Args& args):Detect(ProbeImg, BkImg, Segments, args)
{
	m_vProbImgs = ProbImgs;
	m_PriorProb	= oPriorProb;

	Init_Members( args.GetTrainFolderPath() );
}

DetectByLocation::~DetectByLocation()
{
}

/*****************************************************
 * Function	: DetectByLocation Copy Constructor
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
DetectByLocation::DetectByLocation(const DetectByLocation& rhsDetectByLocation ):Detect(rhsDetectByLocation)
{
	Allocate( rhsDetectByLocation );
	Copy( rhsDetectByLocation );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
DetectByLocation& DetectByLocation:: operator=( const DetectByLocation& rhsDetectByLocation )
{
	Allocate( rhsDetectByLocation );
	Copy( rhsDetectByLocation );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByLocation::Allocate( const DetectByLocation& rhsDetectByLocation )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByLocation::Copy( const DetectByLocation& rhsDetectByLocation )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 15, 2013
 * Created By 	: hrushi
 * Comments		: Initializes the member variables
 * Arguments	:
 *******************************************************************/
int DetectByLocation::Init_Members( const fs::path TrainFolderPath  )
{
	SetTrainingFolderPath(TrainFolderPath);
	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetCarried
 * Return Type 	: vector<Contour>
 * Created On	: Jun 17, 2013
 * Created By 	: hrushi
 * Comments		: Main function to get the Carried Objects
 * Arguments	:
 *******************************************************************/
vector<CarryContour> DetectByLocation::GetCarried( const Args& args )
{
	TYPE_MAP_CNTRSCORE mapCntrProbScore;

	m_ProbeImg.Overlay( m_Segments, DISP_DELAY, COLOR_BLUE,  Args() ).Display(DISP_DELAY);

	mapCntrProbScore = CalAllCntrScore( m_Segments.AllContourMap, args);
	PrintScoreMap(mapCntrProbScore);

	vector<TYPE_TUPLE_RGN_TYPE> vRgnNType = FormatCarryScores( mapCntrProbScore );
	vector<CarryContour> CarriedCntrs = MakeDetectionContours( vRgnNType, mapCntrProbScore );

	return CarriedCntrs;
}


/*******************************************************************
 * Function Name: GetCntrScore
 * Return Type 	: TYPE_MAP_CNTRSCORE
 * Created On	: Jun 18, 2013
 * Created By 	: hrushi
 * Comments		: Gets the Contour probability score for each Probability image, and updates the Member variable m_mapCntrScore
 * Arguments	:
 *******************************************************************/
const TYPE_MAP_CNTRSCORE DetectByLocation::CalAllCntrScore( const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args ) const
{
	TYPE_MAP_CNTRSCORE mpScore;

	for(auto Cntr : CtrMap)
	{
		if( Cntr.first > BACKGROUND_LABEL ) //Region 0 is a Background Region. Hence skipping this.
		{
			bool bUsePoseOverlap = args.isUsePoseOverlap();
			vector<double> Score;
			bool bFromTorsoOverlap = false;
			bool bFromLegsOverlap  = false;

			if( m_PoseInfoAvailable && bUsePoseOverlap )
			{
				bFromTorsoOverlap = m_PoseData.PoseOverlapDetectScore(m_BkImg, Cntr.second, "torso-head", Score, args);

				if( bFromTorsoOverlap )
				{
					mpScore.insert(std::pair<int, vector<double> >( Cntr.first, Score ));
				}
				else
				{
					bFromLegsOverlap = m_PoseData.PoseOverlapDetectScore(m_BkImg, Cntr.second, "legs", Score, args);

					if( bFromLegsOverlap )
					{
						mpScore.insert(std::pair<int, vector<double> >( Cntr.first, Score));
					}
					else
					{
						mpScore.insert(std::pair<int, vector<double> >( Cntr.first, CalScoreAtGivenCtr(Cntr.second) ));
					}
				}

			}
			else
			{
				mpScore[Cntr.first] = CalScoreAtGivenCtr(Cntr.second);
			}

		}
	}

	return mpScore;
}


/*******************************************************************
 * Function Name: CalGivenCtrScore
 * Return Type 	: const vector<double>
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Calculate Given Contour Score
 * Arguments	: const Contour& Ctr
 *******************************************************************/
const vector<double>  DetectByLocation::CalScoreAtGivenCtr( const Contour& Ctr) const
{
	vector<double> vScore;
	vScore.reserve( m_vProbImgs.size()); // Create a vector of double, for each element to probability image
	double ProbScore = 0;

	//double LocPriorScore = m_PriorProb.Get_LocationPrior().GetLocScore(Ctr);

	for( unsigned int i = 0; i < m_vProbImgs.size(); i++)
	{
		ProbImg PrImg = m_vProbImgs.at(i);
		double LocScore = PrImg.GetLocScore( Ctr );

		switch(i)
		{
		case WORN_CARRY_LABEL:
			ProbScore = LocScore;// * m_PriorProb.Get_WornObjPrior() ;
			break;

		case DRAG_CARRY_LABEL:
			ProbScore = LocScore;//  * m_PriorProb.Get_DraggedObjPrior() ;
			break;

		case PERSON_LABEL:
			ProbScore = LocScore;// * m_PriorProb.Get_PersonPrior();
			break;

		}

		//Commenting this because earlier the number was small since it was multipled by the Prior. hence
		// Had to also divide by the prior. But now it is not needed.
		//ProbScore = ProbScore / LocPriorScore;
		vScore.push_back(ProbScore);
	}

	return vScore;
}



/*******************************************************************
 * Function Name: SetTrainingFolderPath
 * Return Type 	: int
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: Set the Training Folder path
 * Arguments	: const fs::path fsPath
 *******************************************************************/
int DetectByLocation::SetTrainingFolderPath( const fs::path fsPath )
{
	m_TrainingFolderPath = fsPath;

	return EXIT_SUCCESS;
}

