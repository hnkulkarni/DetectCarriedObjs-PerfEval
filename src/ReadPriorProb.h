/*
 * ReadPriorProb.h
 *
 *  Created on: Jul 15, 2013
 *      Author: hrushi
 */

#ifndef READPRIORPROB_H_
#define READPRIORPROB_H_

#include "ReadFile.h"
#include "PriorProb.h"
#include "StringOp.h"

class ReadPriorProb: public ReadFile
{

private:

	// Helper Function
	virtual int Copy( const ReadPriorProb& rhsReadPriorProb );
	virtual int Allocate( const ReadPriorProb& rhsReadPriorProb );
	virtual int Readline( const string line);

	PriorProb m_PP;

public:
	ReadPriorProb(const fs::path FilePath);
	virtual ~ReadPriorProb();

	// Copy Constructor
	ReadPriorProb( const ReadPriorProb& rhsReadPriorProb );

	// Assignment Operator
	ReadPriorProb& operator=( const ReadPriorProb& rhsReadPriorProb );

	virtual int ReadIn( );

	/**************************************************************
	 *           Get Functions
	 **************************************************************/
	const PriorProb Get_PriorProb() const { return m_PP; }

};

#endif /* READPRIORPROB_H_ */
