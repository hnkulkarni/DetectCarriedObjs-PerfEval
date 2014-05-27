/*
 * ReadHistLookup.h
 *
 *  Created on: Mar 9, 2013
 *      Author: hrushi
 */

#ifndef READHISTLOOKUP_H_
#define READHISTLOOKUP_H_

#include "ReadFile.h"
#include "KeyColor.h"
#include "ElevenSpaceHist.h"

const unsigned int LOOKUP_OCTET = 8;

class ElevenSpaceHist; // Partial Declaration
typedef std::map<string, ElevenSpaceHist> MapElevenSpc;

class ReadHistLookup: public ReadFile
{

protected:
	// Helper Function
	int Copy_ReadHistLookup( const ReadHistLookup& rhsReadHistLookup );
	int Allocate_ReadHistLookup( const ReadHistLookup& rhsReadHistLookup );

	int ReadLookUpLine(const string line );

	virtual int ReadIn();



public:

	/**************************************************************
	 *           Member Variables
	 **************************************************************/
	MapElevenSpc m_mapElHist;

	/**************************************************************
	 *           House Keeping Functions
	 **************************************************************/
	ReadHistLookup(string sPath);
	virtual ~ReadHistLookup();

	// Copy Constructor
	ReadHistLookup( const ReadHistLookup& rhsReadHistLookup );

	// Assignment Operator
	ReadHistLookup& operator=( const ReadHistLookup& rhsReadHistLookup );

	/**************************************************************
	 *           Member Functions
	 **************************************************************/



	/**************************************************************
	 *           Accessors
	 **************************************************************/
	MapElevenSpc GetMap() const{ return m_mapElHist; };
	ElevenSpaceHist GetVal( const Color& Clr ) const;
	Color GetEqKeyColor( const Color& Clr ) const;
	vector<double> GetHistVal(const Color& Clr ) const;

};


#endif /* READHISTLOOKUP_H_ */
