/*
 * HumanDetection.h
 *
 *  Created on: Dec 5, 2013
 *      Author: hrushi
 */

#ifndef HUMANDETECTION_H_
#define HUMANDETECTION_H_

#include "ProjectIncludes.h"
#include "ColorImg.h"

class HumanDetection
{

private:
	// Helper Function
	virtual int Copy( const HumanDetection& rhs );
	virtual int Allocate( const HumanDetection& rhs );

protected:

    cv::HOGDescriptor m_hog;


public:
	HumanDetection();
	virtual ~HumanDetection();

	// Copy Constructor
	HumanDetection( const HumanDetection& rhsHumanDetection );

	// Assignment Operator
	HumanDetection& operator=( const HumanDetection& rhsHumanDetection );


/**************************************************************
 *           Working Functions
 **************************************************************/
	vector<Rect> Detect( const ColorImg& Img ) const;

};

#endif /* HUMANDETECTION_H_ */
