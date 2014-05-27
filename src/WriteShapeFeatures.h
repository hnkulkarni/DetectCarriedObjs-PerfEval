/*
 * WriteShapeFeatures.h
 *
 *  Created on: Oct 6, 2013
 *      Author: hrushi
 */

#ifndef WRITESHAPEFEATURES_H_
#define WRITESHAPEFEATURES_H_

#include "WriteFile.h"
#include "ProjectIncludes.h"

class WriteShapeFeatures: public WriteFile
{

private:
	// Helper Function
	virtual int Copy( const WriteShapeFeatures& rhs );
	virtual int Allocate( const WriteShapeFeatures& rhs );


	/**************************************************************
	 *           Member Variables
	 **************************************************************/
	vector<string> m_Queue;

protected:


public:
	WriteShapeFeatures(const fs::path fsPath );
	virtual ~WriteShapeFeatures();

	// Copy Constructor
	WriteShapeFeatures( const WriteShapeFeatures& rhsWriteShapeFeatures );

	// Assignment Operator
	WriteShapeFeatures& operator=( const WriteShapeFeatures& rhsWriteShapeFeatures );


	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int WriteOut();
	virtual int WriteBanner();


	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int AddToWriteQue( const vector<double>& Feature  );


};

#endif /* WRITESHAPEFEATURES_H_ */
