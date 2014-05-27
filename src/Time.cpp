/*
 * Time.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: hrushi
 */

#include "Time.h"

Time::Time() {
	// TODO Auto-generated constructor stub

}

Time::~Time() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: Time
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
Time::Time( const Time& rhsTime )
{
	Allocate_Time( rhsTime );
	Copy_Time( rhsTime );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
Time& Time :: operator=( const Time & rhsTime )
{
	Allocate_Time( rhsTime );
	Copy_Time( rhsTime );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Time
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int Time:: Copy_Time(  const Time & rhsTime  )
{

	return EXIT_SUCCESS;
}





/**********************************************************************
 * Function Name: Allocate_Time
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int Time:: Allocate_Time(  const Time & rhsTime  )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetCurrentTime
 * Return Type 	: string
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Returns the current time in text format
 * Arguments	:
 *******************************************************************/
string Time::GetCurrentTime( ) const
{
	string sTime;

	time_t rawTime;
	struct tm *timeinfo;
	time(&rawTime);

	timeinfo = localtime(& rawTime );
	sTime = asctime(timeinfo);

	return sTime;
}

