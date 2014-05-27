/*
 * WritePoseFeature.h
 *
 *  Created on: Apr 10, 2013
 *      Author: hrushi
 */

#ifndef WRITEPOSEFEATURE_H_
#define WRITEPOSEFEATURE_H_


#include"ProjectIncludes.h"

#include "WriteFile.h"
#include "PoseData.h"
#include "Detect.h"


class WritePoseFeature: public WriteFile
{
private:
	vector<string> WriteQue; // String format converted features to write
	int WriteBanner();

protected:
	// Helper Function
	int Copy( const WritePoseFeature& rhsWritePoseFeature );
	int Allocate( const WritePoseFeature& rhsWritePoseFeature );

public:
	WritePoseFeature();
	WritePoseFeature(const string sPath);
	virtual ~WritePoseFeature();

	// Copy Constructor
	WritePoseFeature( const WritePoseFeature& rhsWritePoseFeature );

	// Assignment Operator
	WritePoseFeature& operator=( const WritePoseFeature& rhsWritePoseFeature );

	/**************************************************************
	 *           Relative Functions
	 **************************************************************/
	virtual int WriteOut();

	/**************************************************************
	 *				Mutators
	 **************************************************************/
	virtual int AddToWriteQue( const vector<double>& Feature  );


	/**************************************************************
	 *           Accessors
	 **************************************************************/


};

#endif /* WRITEPOSEFEATURE_H_ */
