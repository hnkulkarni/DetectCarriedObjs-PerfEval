/*
 * DetectionImg.h
 *
 *  Created on: Jul 7, 2013
 *      Author: hrushi
 */

#ifndef DETECTIONIMG_H_
#define DETECTIONIMG_H_

#include "ColorImg.h"
#include "AllDetectedCtrs.h"
#include "FileSystem.h"

class DetectionImg: public ColorImg
{

private:

	/**************************************************************
	 *           Variables
	 **************************************************************/

	/**************************************************************
	 *           Functions
	 **************************************************************/
	// Helper Function
	virtual int Copy( const DetectionImg& rhsDetectionImg );
	virtual int Allocate( const DetectionImg& rhsDetectionImg );

public:
	DetectionImg();
	virtual ~DetectionImg();

	// Copy Constructor
	DetectionImg( const DetectionImg& rhsDetectionImg );

	// Assignment Operator
	DetectionImg& operator=( const DetectionImg& rhsDetectionImg );

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int Overlay( const AllDetectedCtrs& AllCtrs, bool toDisplay, const Args& args );
	virtual ColorImg Overlay( const CarryContour& Ctr, bool toDisplay, const Args& args );

	/**************************************************************
	 *           Accessors
	 **************************************************************/



};

#endif /* DETECTIONIMG_H_ */
