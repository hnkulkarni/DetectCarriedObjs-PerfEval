/*
 * Time.h
 *
 *  Created on: Feb 10, 2013
 *      Author: hrushi
 */

#ifndef TIME_H_
#define TIME_H_

#include "MyIncludes.h"
#include "CPPIncludes.h"
#include "OpenCV_Includes.h"
#include "Boost.h"

class Time {
public:

	/***************************************************************************************
	 *  				Class Initialization
	 ***************************************************************************************/
	Time();
	virtual ~Time();

	// Copy Constructor
	Time( const Time& rhsTime );

	// Assignment Operator
	Time& operator=( const Time& rhsTime );

	// Helper Function
	int Copy_Time( const Time& rhsTime );
	int Allocate_Time( const Time& rhsTime );

	/***************************************************************************************
	 * 						Mutators
	 ***************************************************************************************/


	/***************************************************************************************
	 * 			     Aux. Member Functions
	 ****************************************************************************************/
	 string GetCurrentTime()const;

	/***************************************************************************************
	 * 						Accessors
	 ***************************************************************************************/


};

#endif /* TIME_H_ */
