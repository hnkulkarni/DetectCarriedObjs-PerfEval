/*
 * DetectByAppearance.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: hrushi
 */

#include "DetectByAppearance.h"


/*******************************************************************
 * Function Name: DetectByAppearance
 * Return Type 	: None
 * Created On	: Oct 31, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
DetectByAppearance::DetectByAppearance(  const ColorImg ProbeImg, const GrayImg BkImg, const ContourMap& Segments, const Args& args ):Detect(ProbeImg, BkImg, Segments, args)
{

	Init_Members(args.GetTrainFolderPath());

}


/*******************************************************************
 * Function Name: ~DetectByAppearance
 * Return Type 	: None
 * Created On	: Oct 31, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
DetectByAppearance::~DetectByAppearance()
{


}


/*****************************************************
 * Function	: DetectByAppearance Copy Constructor
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
DetectByAppearance::DetectByAppearance(const DetectByAppearance& rhs ):Detect(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
DetectByAppearance& DetectByAppearance:: operator=( const DetectByAppearance& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByAppearance::Allocate( const DetectByAppearance& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByAppearance::Copy( const DetectByAppearance& rhs )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: SetTrainingFolderPath
 * Return Type 	: int
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: Set the Training Folder path
 * Arguments	: const fs::path fsPath
 *******************************************************************/
int DetectByAppearance::SetTrainingFolderPath( const fs::path fsPath )
{
	m_TrainingFolderPath = fsPath;
	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetCarried
 * Return Type 	: vector<CarryContour>
 * Created On	: Nov 10, 2013
 * Created By 	: hrushi
 * Comments		: GetCarried function using Appearance
 * Arguments	:
 *******************************************************************/
vector<CarryContour> DetectByAppearance::GetCarried(const BOF& oBof,  const Args& args )
{
	vector<CarryContour> vCarriedCntrs;


	for(TYPE_MAP_ALL_CONTOUR::const_iterator itr = m_Segments.AllContourMap.begin(); itr != m_Segments.AllContourMap.end(); itr++ )
	{
		cout << "Checking for Contour with Label " << itr->second.GetLabel() << endl;

		Contour Ctr = itr->second;

		if( Ctr.GetLabel() == BACKGROUND_LABEL )
		{
			// Continue with the loop if the contour is a background contour
			continue;
		}

		ColorImg Chip = Ctr.GetImgChip(m_ProbeImg);
		Chip.Display(DISP_DELAY);

		vector<double> vAllScores;

		pr_score Score = isCarried(oBof, Chip, vAllScores, args);

		CarryContour TempContour = Ctr; // Copy the current contour
		TempContour.SetCarryTypeNScore(Score.first, Score.second);
		TempContour.SetAllScores(vAllScores);

		vCarriedCntrs.push_back(TempContour);

	}

	return vCarriedCntrs;
}


/*******************************************************************
 * Function Name: isCorrect
 * Return Type 	: int
 * Created On	: Nov 11, 2013
 * Created By 	: hrushi
 * Comments		: For the given image and the vocabulary, it checks if the given image chip is in which category
 * Arguments	: const BOF& oBof, const ColorImg& Img, const Args& args
 *******************************************************************/
pr_score DetectByAppearance::isCarried( const BOF& oBof, const ColorImg& Chip, vector<double>& vAllScores, const Args& args ) const
{
	pr_score Score = oBof.GetChipType(Chip, vAllScores, args);

	return Score;
}



/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Oct 11, 2013
 * Created By 	: hrushi
 * Comments		: Initializes the members
 * Arguments	:
 *******************************************************************/
int DetectByAppearance::Init_Members( const fs::path fsPath )
{

	SetTrainingFolderPath(fsPath);

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: CalAllCntrScore
 * Return Type 	: const TYPE_MAP_CNTRSCORE
 * Created On	: Jan 8, 2014
 * Created By 	: hrushi
 * Comments		: Calculate the confidence score for all the contours
 * Arguments	: const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args
 *******************************************************************/
const TYPE_MAP_CNTRSCORE DetectByAppearance::CalAllCntrScore( const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args ) const
{
	TYPE_MAP_CNTRSCORE Score;

	vector<double> vScore;

	for(TYPE_MAP_ALL_CONTOUR::const_iterator itr = m_Segments.AllContourMap.begin(); itr != m_Segments.AllContourMap.end(); itr++ )
	{
		cout << "Checking for Contour with Label " << itr->second.GetLabel() << endl;

		Contour Ctr = itr->second;

		if( Ctr.GetLabel() == BACKGROUND_LABEL )
		{
			// Continue with the loop if the contour is a background contour
			continue;
		}

		ColorImg Chip = Ctr.GetImgChip(m_ProbeImg);


	}

	return Score;
}
