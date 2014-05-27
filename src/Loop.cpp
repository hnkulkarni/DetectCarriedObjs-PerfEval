/*
 * Loop.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: hrushi
 */

#include "Loop.h"

Loop::Loop() {
	// TODO Auto-generated constructor stub

}

Loop::~Loop() {
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: Loop Copy Constructor
 * Date		: Mar 13, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
Loop::Loop(const Loop& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Mar 13, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
Loop& Loop:: operator=( const Loop& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Mar 13, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int Loop::Allocate( const Loop& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Mar 13, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int Loop::Copy( const Loop& rhs )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: LoopStatus
 * Return Type 	: int
 * Created On	: Mar 13, 2014
 * Created By 	: hrushi
 * Comments		: Prints the Loop Status
 * Arguments	: UINT uiCount, UINT Max
 *******************************************************************/
int Loop::PrintStatus( UINT uiCount, UINT MaxCount)
{
	int Fraction = (double)MaxCount/100;

	if(Fraction == 0)
	{
		Fraction = (double)MaxCount/10;
	}

	if((uiCount % Fraction) == 0 )
	{
		double PercentDone = ((double)uiCount/MaxCount) * 100;
		cout << "Done: " <<  PercentDone << "\r";
		std::flush(cout);
	}


	return EXIT_SUCCESS;
}
