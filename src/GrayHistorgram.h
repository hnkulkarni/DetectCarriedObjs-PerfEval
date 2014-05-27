/*
 * Historgram.h
 *
 *  Created on: Jan 10, 2013
 *      Author: hrushi
 */

#ifndef HISTORGRAM_H_
#define HISTORGRAM_H_

#include "CPPIncludes.h"
#include "MyIncludes.h"
#include "OpenCV_Includes.h"
#include "VectorOp.h"
#include "StringOp.h"

#include "Args.h"

typedef vector<double>::const_iterator const_HistItr;
typedef vector<double>::iterator HistItr;

class GrayHistorgram {

protected:



public:
	GrayHistorgram();
	virtual ~GrayHistorgram();


	// Copy Constructor
	GrayHistorgram( const GrayHistorgram& rhsHistorgram );

	// Assignment Operator
	GrayHistorgram& operator=( const GrayHistorgram& rhsHistorgram );

	// Helper Function
	int Copy_Historgram( const GrayHistorgram& rhsHistorgram );
	int Allocate_Historgram( const GrayHistorgram& rhsHistorgram );

	/**************************************************************
	 *           Accessors
	 **************************************************************/

	const_HistItr GetCountIteratorBegin()const { return Hist.begin();};
	const_HistItr GetCountIteratorEnd()const { return Hist.end();};


	/**************************************************************
	 *           Public Members
	 **************************************************************/

	// Record Count
	int AddCount(const unsigned int GrayVal);

	// Normalize the histogram
	int Normalize();

	double Dot( const GrayHistorgram& rhsHist ) const;

	int ZMUL(  );

	/**************************************************************
	 *           Public Variables
	 **************************************************************/
	vector<double> Hist;

};

std::ostream& operator<<( std::ostream& out, const GrayHistorgram& Hst );
std::istream& operator>>( std::istream& in,        GrayHistorgram& Hst );

#endif /* HISTORGRAM_H_ */
