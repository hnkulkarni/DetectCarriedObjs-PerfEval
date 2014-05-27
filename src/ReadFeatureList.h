/*
 * ReadFeatureList.h
 *
 *  Created on: Oct 6, 2013
 *      Author: hrushi
 */

#ifndef READFEATURELIST_H_
#define READFEATURELIST_H_

#include "ProjectIncludes.h"
#include "ReadFile.h"

class ReadFeatureList: public ReadFile
{

private:
	// Helper Function
	virtual int Copy( const ReadFeatureList& rhs );
	virtual int Allocate( const ReadFeatureList& rhs );


protected:

	VVDOUBLE m_FeatureList;

public:
	ReadFeatureList( const fs::path fsPath);
	virtual ~ReadFeatureList();

	// Copy Constructor
	ReadFeatureList( const ReadFeatureList& rhsReadFeatureList );

	// Assignment Operator
	ReadFeatureList& operator=( const ReadFeatureList& rhsReadFeatureList );


	/**************************************************************
	 *           Pure Virtual Function
	 **************************************************************/

	virtual int ReadIn();


	/**************************************************************
	 *           Accessors
	 **************************************************************/

	const VVDOUBLE GetFeatureList() const { return m_FeatureList; }
};

#endif /* READFEATURELIST_H_ */
