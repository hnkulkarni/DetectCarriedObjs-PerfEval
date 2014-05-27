/*
 * ContourMoments.h
 *
 *  Created on: Oct 5, 2013
 *      Author: hrushi
 */

#ifndef CONTOURMOMENTS_H_
#define CONTOURMOMENTS_H_

#include "ProjectIncludes.h"
#include "Contour.h"

class ContourMoments
{
private:

	// Helper Function
	virtual int Copy( const ContourMoments& rhsContourMoments );
	virtual int Allocate( const ContourMoments& rhsContourMoments );


protected:


public:
	ContourMoments();
	virtual ~ContourMoments();

	// Copy Constructor
	ContourMoments( const ContourMoments& rhsContourMoments );

	// Assignment Operator
	ContourMoments& operator=( const ContourMoments& rhsContourMoments );


	virtual const VDOUBLE CalculateMoments( const Contour& Ctr ) const = 0;

/**************************************************************
 *           Accessors
 **************************************************************/


};

#endif /* CONTOURMOMENTS_H_ */
