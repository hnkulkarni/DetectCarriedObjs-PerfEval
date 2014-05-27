/*
 * DetectionScoreFile.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: hrushi
 */

#include "DetectionScoreFile.h"

/*******************************************************************
 * Function Name: DetectionScoreFile
 * Return Type 	: None
 * Created On	: Apr 15, 2014
 * Created By 	: hrushi
 * Comments		:
 * Arguments	: const fs::path
 *******************************************************************/
DetectionScoreFile::DetectionScoreFile(const fs::path fsPath):WriteFile(fsPath)
{

	if( fs::exists(fsPath) )
	{
		WriteBanner();
	}

}


/*******************************************************************
 * Function Name: ~DetectionScoreFile
 * Return Type 	: None
 * Created On	: Apr 15, 2014
 * Created By 	: hrushi
 * Comments		:
 * Arguments	: None
 *******************************************************************/
DetectionScoreFile::~DetectionScoreFile()
{

}

/*****************************************************
 * Function	: DetectionScoreFile Copy Constructor
 * Date		: Apr 15, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
DetectionScoreFile::DetectionScoreFile(const DetectionScoreFile& rhs ):WriteFile( rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Apr 15, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
DetectionScoreFile& DetectionScoreFile:: operator=( const DetectionScoreFile& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Apr 15, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectionScoreFile::Allocate( const DetectionScoreFile& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Apr 15, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectionScoreFile::Copy( const DetectionScoreFile& rhs )
{

	m_ScoreLine = rhs.m_ScoreLine;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: WriteOut
 * Return Type 	: int
 * Created On	: April 15, 2014
 * Created By 	: hrushi
 * Comments		: Writes the strings
 * Arguments	:
 *******************************************************************/
int DetectionScoreFile::WriteOut( )
{
	WriteLine( m_ScoreLine );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: April 15, 2014
 * Created By 	: hrushi
 * Comments		: Writes the Banner
 * Arguments	:
 *******************************************************************/
int DetectionScoreFile::WriteBanner( )
{

	std::stringstream ss;

	ss << "# " << STARS << STARS ;
	WriteLine( ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Detection Score File File " ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Contains the Image, ground truth and scores";
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	Time T;
	ss << "# Last Updated On : " << T.GetCurrentTime() ;
	WriteLine(ss.str() );

	ss << "# Column info" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 1: ImgName" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 2: isGroundTruthTrue" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# " << STARS << STARS;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");


	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: AddToScoreLine
 * Return Type 	: int
 * Created On	: Apr 15, 2014
 * Created By 	: hrushi
 * Comments		: Add To Score Line
 * Arguments	: const fs::path ImgPath, const bool isGndTruthTrue, const vector<double>& Score
 *******************************************************************/
int DetectionScoreFile::AddToScoreLine( const fs::path fsImgPath, const bool isGndTruthTrue, const vector<double>& Score)
{
	std::stringstream ss;
	string dLimit = " ";

	ss << fsImgPath.stem().string() << dLimit << isGndTruthTrue << dLimit;

	string TempScoreStr = StringOp<double>::GetString(Score, dLimit);

	ss << TempScoreStr;

	m_ScoreLine = ss.str();

	ss.clear();
	ss.str();

	WriteOut();

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: AddToScoreLine
 * Return Type 	: int
 * Created On	: Apr 15, 2014
 * Created By 	: hrushi
 * Comments		: Writes the contours sscores and detections
 * Arguments	: const fs::path ImgPath, const vector<bool> isGndTruthTrue, const AllDetectedCtrs& CarryDetection
 *******************************************************************/
int DetectionScoreFile::AddToScoreLine( const fs::path ImgPath, const vector<bool> isGndTruthTrue, const AllDetectedCtrs& CarryDetection)
{

	for(UINT i = 0; i < CarryDetection.Get_NumvCntrs(); i++ )
	{
		AddToScoreLine(ImgPath, isGndTruthTrue.at(i), CarryDetection.Get_vCtrs().at(i).GetAllScores());
	}

	return EXIT_SUCCESS;
}
