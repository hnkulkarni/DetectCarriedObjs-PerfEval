/*
 * WritePriorProbs.h
 *
 *  Created on: Jul 15, 2013
 *      Author: hrushi
 */

#ifndef WRITEPRIORPROBS_H_
#define WRITEPRIORPROBS_H_

#include "WriteFile.h"
#include "PriorProb.h"

class WritePriorProbs: public WriteFile
{

private:

	// Helper Function
	virtual int Copy( const WritePriorProbs& rhsWritePriorProbs );
	virtual int Allocate( const WritePriorProbs& rhsWritePriorProbs );

	virtual int WriteBanner();

	PriorProb m_PP;

public:
	WritePriorProbs(const string FilePath );
	virtual ~WritePriorProbs();

	// Copy Constructor
	WritePriorProbs( const WritePriorProbs& rhsWritePriorProbs );

	// Assignment Operator
	WritePriorProbs& operator=( const WritePriorProbs& rhsWritePriorProbs );

	/**************************************************************
	 *           Virtual Functions
	 **************************************************************/
	virtual int WriteOut();


	/**************************************************************
	 *           Set Functions
	 **************************************************************/
	inline int Set_PriorProb( const PriorProb& PP ){ m_PP = PP; return EXIT_SUCCESS;}

};

#endif /* WRITEPRIORPROBS_H_ */
