/*
 * ApprEM.h
 *
 *  Created on: Nov 17, 2013
 *      Author: hrushi
 */

#ifndef APPREM_H_
#define APPREM_H_

#include "EMFeatureList.h"

class ApprEM; // Partial Declaration

typedef std::map<string, ApprEM> mp_Str_ApprEM;

class ApprEM: public EMFeatureList
{


private:
	// Helper Function
	virtual int Copy( const ApprEM& rhs );
	virtual int Allocate( const ApprEM& rhs );


protected:
	/**************************************************************
	 *           Pure - Virtual Functions
	 **************************************************************/
	virtual int Populate_ColHeaders();


public:
	ApprEM(UINT uiNumClasses, const Mat& TrainingSamples);
	ApprEM(); // Empty constructor for using std::Maps
	virtual ~ApprEM();



	// Copy Constructor
	ApprEM( const ApprEM& rhsApprEM );

	// Assignment Operator
	ApprEM& operator=( const ApprEM& rhsApprEM );

};

#endif /* APPREM_H_ */
