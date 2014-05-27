/*
 * Boxes.h
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#ifndef BOXES_H_
#define BOXES_H_

#include "MyIncludes.h"
#include "CPPIncludes.h"
#include "OpenCV_Includes.h"
#include "Boost.h"
#include "Args.h"
#include "OpenCV_Includes.h"
#include "ImagePt.h"
#include "ColorImg.h"

class Boxes {

public:
	ImagePt TopLeft;
	ImagePt BottomRight;
	cv::Rect RectDetect;
	ImagePt Center;


	Boxes();
	virtual ~Boxes();

	// Copy Constructor
	Boxes( const Boxes& rhsBoxes );

	// Assignment Operator
	Boxes& operator=( const Boxes& rhsBoxes );

	// Helper Function
	int Copy_Boxes( const Boxes& rhsBoxes );
	int Allocate_Boxes( const Boxes& rhsBoxes );

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	int SetBoxRect(const ImagePt Pt_TopLeft, const ImagePt Pt_BottomRight );


	/**************************************************************
	 *           Accessors
	 **************************************************************/
	ColorImg Overlay( const CImage& Img, const cv::Scalar Clr ) const;
};

std::istream& operator>>( std::istream& in, Boxes& Bx);

#endif /* BOXES_H_ */
