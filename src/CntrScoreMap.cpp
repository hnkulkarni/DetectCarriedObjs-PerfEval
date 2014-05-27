/*
 * CntrScoreMap.cpp
 *
 *  Created on: Jan 13, 2013
 *      Author: hrushi
 */

#include "CntrScoreMap.h"

/**********************************************************************
 * Function Name: CntrScoreMap
 * Date 		: Jan 13, 2013
 * Author		: hrushi
 * Comments		: Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
CntrScoreMap::CntrScoreMap( )
{

}

/**********************************************************************
 * Function Name: CntrScoreMap
 * Date 		: Jan 13, 2013
 * Author		: hrushi
 * Comments		: Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
CntrScoreMap::CntrScoreMap( const unsigned int NumLabels)
{
	// TODO Auto-generated constructor stub

	Initialize(NumLabels);

}

/*******************************************************************
 * Function Name: Initialize
 * Return Type 	: int
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: Initializes the variables
 * Arguments	: const unsigned int NumLabels
 *******************************************************************/
int CntrScoreMap::Initialize( const unsigned int NumLabels)
{
	Scmat.release();
	Mat Initmat = Mat::zeros(NumLabels, NumLabels, CV_64F);
	Scmat = Initmat.clone();

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: CntrScoreMap
 * Date 		: Jan 13, 2013
 * Author		: hrushi
 * Comments		: Default Destructor
 * Args			:
 * ToDo			:
 **********************************************************************/
CntrScoreMap::~CntrScoreMap()
{
	// TODO Auto-generated destructor stub
}


/**********************************************************************
 * Function Name: CntrScoreMap
 * Date 		: Jan 13, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
CntrScoreMap::CntrScoreMap( const CntrScoreMap& rhsCntrScoreMap )
{
	Allocate_CntrScoreMap( rhsCntrScoreMap );
	Copy_CntrScoreMap( rhsCntrScoreMap );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 13, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
CntrScoreMap& CntrScoreMap :: operator=( const CntrScoreMap & rhsCntrScoreMap )
{
	Allocate_CntrScoreMap( rhsCntrScoreMap );
	Copy_CntrScoreMap( rhsCntrScoreMap );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_CntrScoreMap
 * Date 		: Jan 13, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int CntrScoreMap:: Copy_CntrScoreMap(  const CntrScoreMap & rhsCntrScoreMap  )
{

	Scmat = rhsCntrScoreMap.Scmat.clone();

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_CntrScoreMap
 * Date 		: Jan 13, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int CntrScoreMap:: Allocate_CntrScoreMap(  const CntrScoreMap & rhsCntrScoreMap  )
{


	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: std::ostream&
 * Created On	: Jan 13, 2013
 * Created By 	: hrushi
 * Comments		: Prints the score Map
 * TODo			:
 *******************************************************************/
std::ostream& operator<<( std::ostream& out, const CntrScoreMap& rhsCntrScrMap )
{

	Mat TempMap = rhsCntrScrMap.GetMat();

	for(  int i = 0; i < TempMap.rows; i++)
	{
		out << "{" << std::setw(2) << i << "} ";
		for(  int j = 0; j < TempMap.cols; j++ )
		{
			out << "[" << j << "] " << std::setw(6) << std::setprecision(2) << TempMap.at<double>(i,j) << " ";
		}

		out << endl;
	}

	return out;
}



/*******************************************************************
 * Function Name: Set
 * Return Type 	: int
 * Created On	: Jan 13, 2013
 * Created By 	: hrushi
 * Comments		: Sets the Score Mat for the given Label (L1) with L2
 * TODo			:
 *******************************************************************/
int CntrScoreMap::Set(CUINT L1, CUINT L2, double Score)
{

	Scmat.at<double>(L1, L2) = Score;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: GetBestMatch
 * Return Type 	: unsigned int
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: Returns the best match for the given contour
 * 					 0	= No match
 * 					<n> = ID of the matching contour
 * Arguments	: unsigned int ContourNum
 *******************************************************************/
int  CntrScoreMap::GetBestMatch( unsigned int ContourNum, double MatchThreshold ) const
{
	int  MatchContour = -1;
	double MaxScore = -1;

	MaxScore = GetBestScore( ContourNum );

	if( MaxScore > MatchThreshold ) // The maximum score should be atleast more than one.
	{
		MatchContour = GetMatchContourWithScore( ContourNum, MaxScore );
	}

	return MatchContour;
}

/*******************************************************************
 * Function Name: GetBestScore
 * Return Type 	: double
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: Gets the best score match for this contour
 * Arguments	: unsigned int ContourNum
 *******************************************************************/
double CntrScoreMap::GetBestScore( unsigned int ContourNum) const
{
	double MaxScore = -1;
	double Score = -1;
	unsigned int NumCols = Scmat.cols;

	for( unsigned int j = 0; j < NumCols; j++) // 0 is the Background contour. We do want to compare only foreground
	{
		if( j != ContourNum ) // We do not want to match the contour to itself
		{
			Score = Scmat.at<double>( ContourNum, j );

			if( Score > MaxScore )
			{
				MaxScore = Score;
			}
		}
	}


	return MaxScore;
}



/*******************************************************************
 * Function Name: GetContourWithScore
 * Return Type 	: unsigned int
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: returns the first contour with the given score
 * Arguments	: double Score
 *******************************************************************/
int CntrScoreMap::GetMatchContourWithScore( unsigned int ContourNum , double MatchScore) const
{
	int MatchingContour = -1;

	double Score = 0;
	unsigned int NumCols = Scmat.cols;

	for( unsigned int j = 0; j < NumCols; j++) // 0 is the Background contour. We do want to compare only foreground
	{
		if( j != ContourNum )
		{
			Score = Scmat.at<double>( ContourNum, j );

			if( MatchScore == Score )
			{
				MatchingContour = j;
			}
		}

	}

	return MatchingContour;
}

/*******************************************************************
 * Function Name: CheckIfBestMatch
 * Return Type 	: bool
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: Many times, multiple contours will have the same score. This function will check, if the given contour, has the maximum score.
 * 					Checks if the Test has the maximum score in the score table for Target
 * Arguments	: unsigned int ContourNum
 *******************************************************************/
bool CntrScoreMap::CheckIfBestMatch( unsigned int Target, unsigned int Test) const
{
	bool isMatch = 0;

	double MaxScore = GetBestScore(Target);
	double Score = 0;
	unsigned int NumCols = Scmat.cols;

	for( unsigned int j = 1; j < NumCols; j++) // 0 is the Background contour. We do want to compare only foreground
	{
		if( j != Target )
		{
			Score = Scmat.at<double>( Target, j );

			if( Score == MaxScore )
			{
				if( Test == j )
				{
					isMatch = true;
					return isMatch;
				}
			}
		}
	}

	return isMatch;
}
