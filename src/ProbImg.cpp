/*
 * ProbImg.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 *
 *      Contains all the functions required / related to the Probabilty Image
 *
 */

#include "ProbImg.h"

ProbImg::ProbImg():GrayImg()
{

}

ProbImg::~ProbImg()
{

}


/*******************************************************************
 * Function Name: ProbImg
 * Return Type 	:
 * Created On	: Jul 19, 2013
 * Created By 	: hrushi
 * Comments		: Constructor for file path
 * Arguments	: const fs::path FilePath
 *******************************************************************/
 ProbImg::ProbImg( const fs::path FilePath):GrayImg(FilePath)
{

}

/*****************************************************
 * Function	: ProbImg Copy Constructor
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ProbImg::ProbImg(const ProbImg& rhsProbImg ):GrayImg(rhsProbImg)
{
	Allocate( rhsProbImg );
	Copy( rhsProbImg );
}

/*******************************************************************
 * Function Name: ProbImg
 * Return Type 	:
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Copy Constructor for copying form the base class; GrayImg
 * Arguments	: const GrayImg& rhsGrayImg
 *******************************************************************/
 ProbImg::ProbImg( const GrayImg& rhsGrayImg)
{
	 GrayImg::operator =(rhsGrayImg);
}

/*****************************************************
 * Function	: operator =
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ProbImg& ProbImg:: operator=( const ProbImg& rhsProbImg )
{
	Allocate( rhsProbImg );
	Copy( rhsProbImg );

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
int ProbImg::Allocate( const ProbImg& rhsProbImg )
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
int ProbImg::Copy( const ProbImg& rhsProbImg )
{
	GrayImg::operator =( rhsProbImg );

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetLocScore
 * Return Type 	: const double
 * Created On	: Jun 18, 2013
 * Created By 	: hrushi
 * Comments		: Get the Average Location score for the given contour
 * Arguments	: const Contour& Ctr
 *******************************************************************/
const double ProbImg::GetLocScore( const Contour& Ctr ) const
{
	double Score(0);
	unsigned int CntrNumPixels(0);

	BinaryImg CtrMask;
	CtrMask.SetImage(Ctr.GetCtrMask());
	CtrMask.Resize( m_nrows, m_ncols );

	//Overlay(Ctr, DISP_DELAY, COLOR_RED, Args() ).Display(DISP_DELAY);

	for( unsigned int i = 0; i < m_nrows; i++ )
	{
		for( unsigned int j = 0; j < m_ncols; j++ )
		{
			if( CtrMask.at(i,j) == MAX_GRAY_VALUE ) // Check out why this Round Over is present
			{
				CntrNumPixels++;
				Score += (double) at(i,j)/MAX_GRAY_VALUE;
			}
		}
	}

	Score = Score / CntrNumPixels;
	return Score;
}



