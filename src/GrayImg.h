/*
 * GrayImg.h
 *
 *  Created on: Jan 20, 2013
 *      Author: hrushi
 */

#ifndef GRAYIMG_H_
#define GRAYIMG_H_

#include "ProjectIncludes.h"

#include "CImage.h"
#include "ImagePt.h"
#include "ContourMap.h"
#include "ColorImg.h"
#include "Args.h"

class ContourMap; 	// Partial Declaration - Overlay Contour
class ColorImg;		// Partial Declaration - Return copied values of gray in place of RGB
class Contour; 		// Partial Declaration - For Overlaying a single contour on the image.

class GrayImg: public CImage
{
private:
	virtual int Initializer();
	virtual int Constructor(UINT numRows, UINT numCols);

public:

	/**********************************************
	 * 			Code House Keeping
	 **********************************************/
	GrayImg();
	GrayImg(UINT numRows, UINT numCols);
	GrayImg( const cv::Size ImgSize );
	GrayImg( const cv::Mat& rhsMat );

	virtual ~GrayImg();

	// Copy Constructor
	GrayImg( const GrayImg& rhsGrayImg );


	// Copy Constructor for String
	GrayImg( const fs::path FilePath );

	// Assignment Operator
	virtual const GrayImg& operator=( const GrayImg& rhsGrayImg );
	virtual const GrayImg operator+( const GrayImg& rhsGrayImg ) const;


	// Helper Function
	virtual int Copy_GrayImg( const GrayImg& rhsGrayImg );
	virtual int Allocate_GrayImg( const GrayImg& rhsGrayImg );


	/**********************************************
	 * 				Accessors
	 **********************************************/
	virtual uchar at( unsigned int i, unsigned int j ) const;
	virtual uchar at( const ImagePt ImgPt ) const;


	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int SetImageType() { m_ImageType = IMAGE_TYPE_GRAY; return m_ImageType;}
	virtual const GrayImg Threshold( const char ThresholdVal );
	virtual const GrayImg Fill();


	/**********************************************
	 * 			 Generic Functions
	 **********************************************/
	virtual ColorImg Overlay( const ContourMap& Ctr, const int Delay,  cv::Scalar DrwColor, bool OverlayNums, const Args& args ) const;
	virtual ColorImg Overlay( const ContourMap& Ctr, const int Delay,  cv::Scalar DrwColor, const Args& args ) const;
	virtual ColorImg Overlay( const Contour& Cntr, const int Delay, cv::Scalar DrwColor, const Args& args ) const;
	virtual ColorImg Cvt2ColorCompatible() const;
	virtual UINT SumAllPixVals() const;

};

#endif /* GRAYIMG_H_ */
