/*
 * CntrFeature.h
 *
 *  Created on: Feb 11, 2013
 *      Author: hrushi
 */

#ifndef CNTRFEATURE_H_
#define CNTRFEATURE_H_


#include "MyIncludes.h"
#include "CPPIncludes.h"
#include "OpenCV_Includes.h"
#include "Boost.h"
#include "Args.h"
#include "Time.h"
#include "ElevenSpaceHist.h"

class CntrFeature {

public:
	/**************************************************************
	 *           Public Functions
	 **************************************************************/
	CntrFeature();
	virtual ~CntrFeature();

	// Copy Constructor
	CntrFeature( const CntrFeature& rhsCntrFeature );

	// Assignment Operator
	CntrFeature& operator=( const CntrFeature& rhsCntrFeature );

	// Helper Function
	int Copy_CntrFeature( const CntrFeature& rhsCntrFeature );
	int Allocate_CntrFeature( const CntrFeature& rhsCntrFeature );

	int ZMUL(const Args& args);

	/**************************************************************
	 *            Public Variables
	 **************************************************************/
	ElevenSpaceHist Hst;
	int Label;


};

#endif /* CNTRFEATURE_H_ */
