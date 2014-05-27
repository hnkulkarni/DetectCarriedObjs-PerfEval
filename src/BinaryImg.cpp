/*
 * BinaryImg.cpp
 *
 *  Created on: Jun 18, 2013
 *      Author: hrushi
 */

#include "BinaryImg.h"

BinaryImg::BinaryImg():GrayImg()
{

}


/*******************************************************************
 * Function Name: BinaryImg
 * Return Type 	:
 * Created On	: Dec 29, 2013
 * Created By 	: hrushi
 * Comments		: Overloaded constructor for the image
 * Arguments	: UINT numRows, UINT numCols
 *******************************************************************/
BinaryImg::BinaryImg( UINT numRows, UINT numCols):GrayImg(numRows, numCols)
{
	SetImageType();
}


/*******************************************************************
 * Function Name: BinaryImg
 * Return Type 	:
 * Created On	: Jan 2, 2014
 * Created By 	: hrushi
 * Comments		: Constructor with Size Argument
 * Arguments	: const cv::Size ImgSize
 *******************************************************************/
 BinaryImg::BinaryImg( const cv::Size ImgSize ):GrayImg(ImgSize)
{
	 SetImageType();
}


 /*******************************************************************
 * Function Name: BinaryImg
 * Return Type 	:
 * Created On	: Jan 4, 2014
 * Created By 	: hrushi
 * Comments		: Constructor for the Binary Image with the cv::Mat type
 * Arguments	: const cv::Mat& rhsMat
 *******************************************************************/
 BinaryImg::BinaryImg( const cv::Mat& rhsMat):GrayImg(rhsMat)
{
	 SetImageType();
}

/*******************************************************************
 * Function Name: BinaryImg
 * Return Type 	:
 * Created On	: Dec 30, 2013
 * Created By 	: hrushi
 * Comments		: Converts a GrayImg into a Binary Image
 * Arguments	: const GrayImg& Img
 *******************************************************************/
BinaryImg::BinaryImg( const GrayImg& Img)
{
	// Copy the RHS into the current class; since it derives from GrayImg
	GrayImg::operator =( Img );

	// Copy current data into a Mat
	cv::Mat DispImg;
	copyTo(DispImg);

	cv::threshold(DispImg, DispImg, GRAY_VALUE, MAX_GRAY_VALUE, cv::THRESH_BINARY );

	// Copy back the thresholded data into the current class
	SetImage(DispImg);
}



BinaryImg::~BinaryImg()
{
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: BinaryImg Copy Constructor
 * Date		: Jun 18, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
BinaryImg::BinaryImg(const BinaryImg& rhsBinaryImg ):GrayImg(rhsBinaryImg)
{
	Allocate( rhsBinaryImg );
	Copy( rhsBinaryImg );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jun 18, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
BinaryImg& BinaryImg:: operator=( const BinaryImg& rhsBinaryImg )
{
	Allocate( rhsBinaryImg );
	Copy( rhsBinaryImg );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jun 18, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int BinaryImg::Allocate( const BinaryImg& rhsBinaryImg )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jun 18, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int BinaryImg::Copy( const BinaryImg& rhsBinaryImg )
{
	GrayImg::operator =( rhsBinaryImg );

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: operator||
 * Return Type 	: BinaryImg
 * Created On	: Dec 29, 2013
 * Created By 	: hrushi
 * Comments		: Overloading ||
 * Arguments	: const BinaryImg& rhs
 *******************************************************************/
const BinaryImg BinaryImg::operator||( const BinaryImg& rhs) const
{
	//Create a Binary Image with the same number of rows and columns
	BinaryImg retOr = Or( rhs );

	return retOr;
}


/*******************************************************************
 * Function Name: Or
 * Return Type 	: const BinaryImg
 * Created On	: Dec 30, 2013
 * Created By 	: hrushi
 * Comments		: Oring of two binary Images
 * Arguments	: const BinaryImg& rhs
 *******************************************************************/
const BinaryImg BinaryImg::Or( const BinaryImg& rhs) const
{
	//Create a Binary Image with the same number of rows and columns
	BinaryImg retOr(GetNumRows(), GetNumRows());

	cv::Mat DestMat;
	retOr.copyTo(DestMat);

	cv::bitwise_or(m_data, rhs.m_data, DestMat, cv::noArray() );

	retOr.SetImage(DestMat);

	return retOr;
}


/*******************************************************************
 * Function Name: operator&&
 * Return Type 	: const BinaryImg
 * Created On	: Dec 29, 2013
 * Created By 	: hrushi
 * Comments		: Binary Image And Operation
 * Arguments	: const BinaryImg& rhs
 *******************************************************************/
const BinaryImg BinaryImg::operator&&( const BinaryImg& rhs) const
{
	BinaryImg retAnd = And( rhs );

	return retAnd;
}

/*******************************************************************
 * Function Name: And
 * Return Type 	: const BinaryImg
 * Created On	: Dec 30, 2013
 * Created By 	: hrushi
 * Comments		: Anding of the current image with the passed image
 * Arguments	: const BinaryImg& Img
 *******************************************************************/
const BinaryImg BinaryImg::And( const BinaryImg& rhs) const
{
	BinaryImg retAnd(GetNumRows(), GetNumRows());

	cv::Mat DestMat;
	retAnd.copyTo(DestMat);

	cv::bitwise_and(m_data, rhs.m_data, DestMat, cv::noArray() );

	retAnd.SetImage(DestMat);

	return retAnd;
}

/*******************************************************************
 * Function Name: Percentage_Overlap
 * Return Type 	: double
 * Created On	: Dec 30, 2013
 * Created By 	: hrushi
 * Comments		: Finds out the overlap of the given image with the current image
 * Arguments	: const BinaryImg& rhs
 *******************************************************************/
double BinaryImg::Percentage_Overlap( const BinaryImg& rhs) const
{
	BinaryImg AndImg = And(rhs);


	UINT uiMainCount	= CountNonZero();
	UINT uiAndCount 	= AndImg.CountNonZero();

	double Overlap = (double)uiAndCount/uiMainCount;

	return Overlap;
}



/*******************************************************************
 * Function Name: CountNonZero
 * Return Type 	: UINT
 * Created On	: Dec 30, 2013
 * Created By 	: hrushi
 * Comments		: Count the number of non zero pixels
 * Arguments	:
 *******************************************************************/
UINT BinaryImg::CountNonZero( ) const
{
	cv::Mat TempMat;
	copyTo(TempMat);

	UINT uiCount = cv::countNonZero(TempMat);

	return uiCount;

}


/*******************************************************************
 * Function Name: FillSolidBox
 * Return Type 	: BinaryImg
 * Created On	: Mar 10, 2014
 * Created By 	: hrushi
 * Comments		: Fill the gray image with a solid box
 * Arguments	: const cv::Rect Rt
 *******************************************************************/
const BinaryImg BinaryImg::FillSolidBox( const cv::Rect Rt)
{
	cv::rectangle(m_data, Rt, GRAY_WHITE, CV_FILLED, CV_AA, 0);

	return *this;
}



/*******************************************************************
 * Function Name: FillSolidBox
 * Return Type 	: const BinaryImg
 * Created On	: Mar 10, 2014
 * Created By 	: hrushi
 * Comments		: Fill the gray image with all the boxes in the vector
 * Arguments	: const vector<cv::Rect>& Rt
 *******************************************************************/
const BinaryImg BinaryImg::FillSolidBox( const vector<cv::Rect>& Rt)
{

	for(auto r : Rt)
	{
		FillSolidBox(r);
	}

	return *this;
}
