/*
 * RectOp.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: hrushi
 */

#include "RectOp.h"

RectOp::RectOp() {
	// TODO Auto-generated constructor stub

}

RectOp::~RectOp() {
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: RectOp Copy Constructor
 * Date		: Mar 9, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
RectOp::RectOp(const RectOp& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Mar 9, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
RectOp& RectOp:: operator=( const RectOp& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Mar 9, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int RectOp::Allocate( const RectOp& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Mar 9, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int RectOp::Copy( const RectOp& rhs )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: isInside
 * Return Type 	: bool
 * Created On	: Mar 9, 2014
 * Created By 	: hrushi
 * Comments		: Checks if the smaller rectangle is inside the bigger rectangle
 * Arguments	: const cv::Rect& BigRect, const cv::Rect& SmallRect
 *******************************************************************/
bool RectOp::Contains( const cv::Rect& BigRect, const cv::Rect& SmallRect )
{
	if( BigRect.contains(SmallRect.tl() ) && BigRect.contains( SmallRect.br() ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*******************************************************************
 * Function Name: GetContaining
 * Return Type 	: vector<cv::Rect>
 * Created On	: Mar 9, 2014
 * Created By 	: hrushi
 * Comments		: Return a vector of containing small rects in the given rect
 * Arguments	: const cv::Rect& BigRect, const vector<cv::Rect>& SmallRects
 *******************************************************************/
const vector<cv::Rect> RectOp::GetContaining( const cv::Rect& BigRect, const vector<cv::Rect>& SmallRects)
{
	vector<cv::Rect> vRect;

	for(auto R : SmallRects)
	{
		if(Contains(BigRect, R))
		{
			vRect.push_back(R);
		}
	}

	return vRect;
}

/*******************************************************************
 * Function Name: GetIntersection
 * Return Type 	: const cv::Rect
 * Created On	: Mar 9, 2014
 * Created By 	: hrushi
 * Comments		: Returns the intersecting rectangle between the two
 * Arguments	: const cv::Rect& BigRect, const cv::Rect& SmallRect
 *******************************************************************/
const cv::Rect RectOp::GetIntersection( const cv::Rect& BigRect, const cv::Rect& SmallRect )
{
	const cv::Rect IntersectRect = BigRect & SmallRect;

	return IntersectRect;
}


/*******************************************************************
 * Function Name: GetOverlappingRect
 * Return Type 	: const vector<cv::Rect>
 * Created On	: Mar 9, 2014
 * Created By 	: hrushi
 * Comments		: From the given list of small rectangles, select the rectangles that are overlapping
 * Arguments	: const cv::Rect& BigRect,  const vector<cv::Rect>& SmallRects, double OverlapThreshold
 *******************************************************************/
const vector<cv::Rect> RectOp::GetOverlappingRect( const cv::Rect& BigRect,  const vector<cv::Rect>& SmallRects, double OverlapThreshold )
{
	vector<cv::Rect> OverlapRects;

	for(auto r : SmallRects)
	{
		cv::Rect ir = GetIntersection(BigRect, r);

		double OverlapAreaRatio = (double)ir.area()/r.area();

		if(OverlapAreaRatio >= OverlapThreshold )
		{
			OverlapRects.push_back(r);
		}
	}


	return OverlapRects;
}

/*******************************************************************
 * Function Name: MakeRelativeToBigRect
 * Return Type 	: const vector<cv::Rect>
 * Created On	: Mar 9, 2014
 * Created By 	: hrushi
 * Comments		: Make all the smaller rectangles relative to the top left of the big rectangle
 * Arguments	: const cv::Rect& BigRect,  const vector<cv::Rect>& SmallRects
 *******************************************************************/
const vector<cv::Rect> RectOp::MakeRelativeToBigRect( const cv::Rect& BigRect,  const vector<cv::Rect>& SmallRects)
{
	vector<cv::Rect> RelativeRects;

	for(auto s : SmallRects)
	{
		s.x = s.x - BigRect.x;
		s.y = s.y - BigRect.y;

		RelativeRects.push_back(s);
	}

	return RelativeRects;
}


/*******************************************************************
 * Function Name: MaskeMasks
 * Return Type 	: const GrayImg
 * Created On	: Mar 10, 2014
 * Created By 	: hrushi
 * Comments		: Make the masks of the given size using the rects
 * Arguments	: const size_t MaskSize, const vector<cv::Rect>& Rt
 *******************************************************************/
const BinaryImg RectOp::MakeMasks( const cv::Size MaskSize, const vector<cv::Rect>& Rt)
{
	BinaryImg MskImg(MaskSize);
	MskImg.FillSolidBox(Rt);

	return MskImg;
}
