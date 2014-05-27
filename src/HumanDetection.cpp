/*
 * HumanDetection.cpp
 *
 *  Created on: Dec 5, 2013
 *      Author: hrushi
 */

#include "HumanDetection.h"

/*******************************************************************
 * Function Name: HumanDetection
 * Return Type 	: None
 * Created On	: Dec 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
HumanDetection::HumanDetection()
{
	  m_hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());


}


/*******************************************************************
 * Function Name: ~HumanDetection
 * Return Type 	: None
 * Created On	: Dec 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
HumanDetection::~HumanDetection()
{


}

/*****************************************************
 * Function	: HumanDetection Copy Constructor
 * Date		: Dec 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
HumanDetection::HumanDetection(const HumanDetection& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Dec 5, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
HumanDetection& HumanDetection:: operator=( const HumanDetection& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Dec 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int HumanDetection::Allocate( const HumanDetection& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Dec 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int HumanDetection::Copy( const HumanDetection& rhs )
{
	m_hog = rhs.m_hog;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Detect
 * Return Type 	: vector<cv::Rect>
 * Created On	: Dec 5, 2013
 * Created By 	: hrushi
 * Comments		: Performs human detection
 * Arguments	: const ColorImg& Img
 *******************************************************************/
vector<Rect> HumanDetection::Detect( const ColorImg& Img) const
{
	vector<Rect> found;

	cv::Mat ImgMat = Img.GetDataRef().clone();

	m_hog.detectMultiScale(ImgMat, found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);

	ColorImg HmDetect;
	HmDetect.SetImage(ImgMat);
	HmDetect.Overlay(found, COLOR_BLUE);

	HmDetect.Display(0);

	return found;
}
