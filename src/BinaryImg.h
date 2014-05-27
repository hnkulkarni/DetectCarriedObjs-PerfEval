/*
 * BinaryImg.h
 *
 *  Created on: Jun 18, 2013
 *      Author: hrushi
 */

#ifndef BINARYIMG_H_
#define BINARYIMG_H_

#include "GrayImg.h"

class BinaryImg: public GrayImg {
public:
	BinaryImg();
	BinaryImg(UINT numRows, UINT numCols);
	BinaryImg(const GrayImg& Img);
	BinaryImg(const cv::Size ImgSize );
	BinaryImg( const cv::Mat& ImgMat );

	virtual ~BinaryImg();

	// Copy Constructor
	BinaryImg( const BinaryImg& rhsBinaryImg );

	// Assignment Operator
	BinaryImg& operator=( const BinaryImg& rhsBinaryImg );

	// Helper Function
	virtual int Copy( const BinaryImg& rhsBinaryImg );
	virtual int Allocate( const BinaryImg& rhsBinaryImg );

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int SetImageType() { m_ImageType = IMAGE_TYPE_BINARY; return m_ImageType;}

	/**************************************************************
	 *           Aux Functions
	 **************************************************************/
	const BinaryImg Or( const BinaryImg& rhs ) const;
	const BinaryImg And( const BinaryImg& rhs ) const;

	const BinaryImg operator||( const BinaryImg& rhs ) const;
	const BinaryImg operator&&( const BinaryImg& rhs ) const;

	double Percentage_Overlap( const BinaryImg& rhs ) const;
	UINT CountNonZero() const;


	virtual const BinaryImg FillSolidBox( const cv::Rect Rt);
	virtual const BinaryImg FillSolidBox( const vector<cv::Rect>& Rt);

};

#endif /* BINARYIMG_H_ */
