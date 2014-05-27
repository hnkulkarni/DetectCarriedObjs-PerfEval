/*
 * HuMoments.cpp
 *
 *  Created on: Oct 5, 2013
 *      Author: hrushi
 */

#include "HuMoments.h"

/*******************************************************************
 * Function Name: HuMoments
 * Return Type 	: None
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
HuMoments::HuMoments() {
	// TODO Auto-generated constructor stub

}



/*******************************************************************
 * Function Name: ~HuMoments
 * Return Type 	: None
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
HuMoments::~HuMoments() {
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: HuMoments Copy Constructor
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
HuMoments::HuMoments(const HuMoments& rhsHuMoments )
{
	Allocate( rhsHuMoments );
	Copy( rhsHuMoments );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
HuMoments& HuMoments:: operator=( const HuMoments& rhsHuMoments )
{
	Allocate( rhsHuMoments );
	Copy( rhsHuMoments );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int HuMoments::Allocate( const HuMoments& rhsHuMoments )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int HuMoments::Copy( const HuMoments& rhsHuMoments )
{
	ContourMoments::operator =( rhsHuMoments );

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: CalculateMoments
 * Return Type 	: int
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Calculates Hu Moments for the given contour
 * Arguments	: const Contour& Ctr
 *******************************************************************/
const VDOUBLE  HuMoments::CalculateMoments( const Contour& Ctr) const
{
	VDOUBLE Hu;

	ColorImg ClrMsk = Ctr.GetCtrBlackImg();
	GrayImg GryMsk = ClrMsk.Cvt2Gray();

	cv::Mat MskMat = GryMsk.GetDataRef().clone();
	vector<vector<cv::Point> > contours;
	vector<cv::Vec4i> hierarchy;

	cv::findContours(MskMat, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
	cv::Moments Mu2 = cv::moments(contours.at(0), false);

	cv::HuMoments(Mu2, Hu);

	return Hu;
}
