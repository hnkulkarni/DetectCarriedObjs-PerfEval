/*
 * HuMoments.h
 *
 *  Created on: Oct 5, 2013
 *      Author: hrushi
 */

#ifndef HUMOMENTS_H_
#define HUMOMENTS_H_

#include "ContourMoments.h"
#include "ProjectIncludes.h"

class HuMoments: public ContourMoments
{

private:


	// Helper Function
	virtual int Copy( const HuMoments& rhsHuMoments );
	virtual int Allocate( const HuMoments& rhsHuMoments );

protected:


public:
	HuMoments();
	virtual ~HuMoments();

	// Copy Constructor
	HuMoments( const HuMoments& rhsHuMoments );

	// Assignment Operator
	HuMoments& operator=( const HuMoments& rhsHuMoments );


/**************************************************************
 *           Pure - Virtual Functions
 **************************************************************/
	virtual const VDOUBLE  CalculateMoments( const Contour& Ctr ) const;

};

#endif /* HUMOMENTS_H_ */
