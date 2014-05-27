/*
 * Loop.h
 *
 *  Created on: Mar 13, 2014
 *      Author: hrushi
 */

#ifndef LOOP_H_
#define LOOP_H_

#include "MyIncludes.h"

class Loop
{


private:
	// Helper Function
	virtual int Copy( const Loop& rhs );
	virtual int Allocate( const Loop& rhs );

protected:

public:
	Loop();
	virtual ~Loop();

	// Copy Constructor
	Loop( const Loop& rhsLoop );

	// Assignment Operator
	Loop& operator=( const Loop& rhsLoop );

	static int PrintStatus(UINT uiCount, UINT Max );

};

#endif /* LOOP_H_ */
