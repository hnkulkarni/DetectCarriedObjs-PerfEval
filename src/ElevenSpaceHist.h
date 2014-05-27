/*
 * ElevenSpaceHist.h
 *
 *  Created on: Mar 8, 2013
 *      Author: hrushi
 */

#ifndef ELEVENSPACEHIST_H_
#define ELEVENSPACEHIST_H_

#include "CPPIncludes.h"
#include "MyIncludes.h"
#include "OpenCV_Includes.h"
#include "VectorOp.h"
#include "StringOp.h"

#include "Args.h"
#include "KeyColor.h"
#include "ReadHistLookup.h"


const int ELEVEN_HIST_SIZE = 11;
const double ELEVEN_HIST_MATCH_THRESHOLD = 0.75;


class ReadHistLookup; // Partial Declaration

class ElevenSpaceHist
{
private:



public:

	/**************************************************************
	 *           Member Variables
	 **************************************************************/
	vector<double> m_Hist;


	/**************************************************************
	 *           Member functions
	 **************************************************************/

	ElevenSpaceHist();
	virtual ~ElevenSpaceHist();

	// Copy Constructor
	ElevenSpaceHist( const ElevenSpaceHist& rhsElevenSpaceHist );

	// Assignment Operator
	ElevenSpaceHist& operator=( const ElevenSpaceHist& rhsElevenSpaceHist );

	// Helper Function
	int Copy_ElevenSpaceHist( const ElevenSpaceHist& rhsElevenSpaceHist );
	int Allocate_ElevenSpaceHist( const ElevenSpaceHist& rhsElevenSpaceHist );

	int AddCount(const Color& Clr, const ReadHistLookup& Lookup );

	double GetMatchScore(const ElevenSpaceHist& E2 ) const;
	double MatchScore_ClrMinMax(const ElevenSpaceHist& E2 ) const;

	int ZMUL();



};




std::istream& operator>>( std::istream& in, ElevenSpaceHist& ElSpc );
std::ostream& operator<<( std::ostream& out, const ElevenSpaceHist& ElSpc );


#endif /* ELEVENSPACEHIST_H_ */
