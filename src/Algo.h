/*
 * Algo.h
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#ifndef ALGO_H_
#define ALGO_H_

#include "ProjectIncludes.h"
#include "Contour.h"
#include "ColorImg.h"
#include "GrayImg.h"
#include "DetectByLocation.h"

class Algo
{

private:
	// Helper Function
	int Copy( const Algo& rhsAlgo );
	int Allocate( const Algo& rhsAlgo );

public:
	Algo();
	virtual ~Algo();

	// Copy Constructor
	Algo( const Algo& rhsAlgo );

	// Assignment Operator
	Algo& operator=( const Algo& rhsAlgo );

};

#endif /* ALGO_H_ */
