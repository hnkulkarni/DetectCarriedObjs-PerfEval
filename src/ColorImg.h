/*
 * ColorImg.h
 *
 *  Created on: Jan 20, 2013
 *      Author: hrushi
 */

#ifndef COLORIMG_H_
#define COLORIMG_H_

#include "ProjectIncludes.h"

#include "CImage.h"
#include "GrayImg.h"
#include "ContourMap.h"

#include "Args.h"


class ContourMap; //Partial Declaration.
class GrayImg; // Partial Declaration
class Contour; // Partial Declaration

class ColorImg: public CImage {

private:
	ColorImg Overlay( cv::Mat& Img, const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, bool bPutText, const Args& args ) const;
	virtual int Initializer();

	virtual int BuildImage(UINT nrows, UINT ncols, cv::Scalar InitColor);

public:

	/***********************************************************
	 * 					House Keeping Functions
	 ***********************************************************/
	ColorImg();
	ColorImg(const cv::Mat& rhsMat );
	ColorImg(UINT nrows, UINT ncols);
	ColorImg(UINT nrows, UINT ncols, cv::Scalar InitColor);
	virtual ~ColorImg();

	// Copy Constructor
	ColorImg( const ColorImg& rhsColorImg );

	//
	ColorImg( const fs::path FilePath );

	// Assignment Operator
	ColorImg& operator=( const ColorImg& rhsColorImg );

	// Helper Function
	int Copy_ColorImg( const ColorImg& rhsColorImg );
	int Allocate_ColorImg( const ColorImg& rhsColorImg );


	/***********************************************************
	 * 				   Modifiers
	 ***********************************************************/
	//Loads a Image in Color
	virtual int SetImageType() { m_ImageType = IMAGE_TYPE_COLOR; return m_ImageType;}
	virtual int Mask( const GrayImg& Msk );

	/**************************************************************
	 *           Accessors
	 **************************************************************/
	// Convert the data to Gray
	virtual GrayImg Cvt2Gray() const;
	virtual cv::Vec3b at(const unsigned int i, const unsigned int j) const;
	virtual int at(unsigned int i, unsigned int j, char B, char G, char R);
	virtual int at(unsigned int i, unsigned int j, const cv::Vec3b& BGR ); // Sets the Value at the given pixel

	virtual ColorImg Overlay( const ContourMap& Ctr, const int Delay, cv::Scalar Color, const Args& args ) const;
	virtual ColorImg Overlay( const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, const Args& args ) const;
	virtual ColorImg Overlay( const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, bool bPutText, const Args& args ) const;
	virtual ColorImg Overlay( const vector<ImagePt> vPt,  const int Delay, cv::Scalar DrwColor, const Args& args ) const;
	virtual ColorImg Overlay( const ImagePt Pt, const int Delay, cv::Scalar DrwColor, const Args& args ) const;
	virtual int Overlay(const vector<cv::Rect>& Rt, const cv::Scalar RectColor);
	virtual int Overlay(const cv::Rect& Rt, const cv::Scalar RectColor);

};

#endif /* COLORIMG_H_ */
