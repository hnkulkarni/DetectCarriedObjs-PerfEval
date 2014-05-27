/*
 * Algo.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#include "Algo.h"

Algo::Algo()
{
	// TODO Auto-generated constructor stub

}

Algo::~Algo() {
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: Algo Copy Constructor
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
Algo::Algo(const Algo& rhsAlgo )
{
	Allocate( rhsAlgo );
	Copy( rhsAlgo );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
Algo& Algo:: operator=( const Algo& rhsAlgo )
{
	Allocate( rhsAlgo );
	Copy( rhsAlgo );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int Algo::Allocate( const Algo& rhsAlgo )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int Algo::Copy( const Algo& rhsAlgo )
{

	return EXIT_SUCCESS;
}




