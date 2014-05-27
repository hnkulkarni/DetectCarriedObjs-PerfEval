/*
 * Learning.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: hrushi
 */

#include "MLearning.h"

/*******************************************************************
 * Function Name: Default Constructor
 * Return Type 	:
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Constructor for the EM Class
 * Arguments	:
 *******************************************************************/
MLearning::MLearning()
{

	Init_Members();

}



/*******************************************************************
 * Function Name: Default Destructor
 * Return Type 	:
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Destructor for the EM Class
 * Arguments	:
 *******************************************************************/
MLearning::~MLearning()
{


}

/*****************************************************
 * Function	: MLearning Copy Constructor
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
MLearning::MLearning(const MLearning& rhsMLearning )
{
	Allocate( rhsMLearning );
	Copy( rhsMLearning );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
MLearning& MLearning:: operator=( const MLearning& rhsMLearning )
{
	Allocate( rhsMLearning );
	Copy( rhsMLearning );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int MLearning::Allocate( const MLearning& rhsMLearning )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int MLearning::Copy( const MLearning& rhsMLearning )
{

	m_NumSamples = rhsMLearning.m_NumSamples;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Initalize All Member Variables
 * Arguments	:
 *******************************************************************/
int MLearning::Init_Members( )
{
	m_NumSamples = 0;

	return EXIT_SUCCESS;
}
