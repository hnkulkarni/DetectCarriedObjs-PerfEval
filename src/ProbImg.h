/*
 * ProbImg.h
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#ifndef PROBIMG_H_
#define PROBIMG_H_

#include "GrayImg.h"
#include "Contour.h"
#include "BinaryImg.h"

class ProbImg: public GrayImg
{

private:
	// Helper Function
	virtual int Copy( const ProbImg& rhsProbImg );
	virtual int Allocate( const ProbImg& rhsProbImg );

public:
	ProbImg();
	ProbImg( const fs::path FilePath);
	virtual ~ProbImg();


	// Copy Constructor
	ProbImg( const ProbImg& rhsProbImg );
	ProbImg( const GrayImg& rhsGrayImg );

	// Assignment Operator
	ProbImg& operator=( const ProbImg& rhsProbImg );



	/**************************************************************
	 *           Accessors
	 **************************************************************/
	const double GetLocScore( const Contour& Ctr ) const;

};

#endif /* PROBIMG_H_ */
