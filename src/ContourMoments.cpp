/*
 * ContourMoments.cpp
 *
 *  Created on: Oct 5, 2013
 *      Author: hrushi
 */

#include "ContourMoments.h"


/*******************************************************************
 * Function Name: ContourMoments
 * Return Type 	: None
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
ContourMoments::ContourMoments()
{

}

/*******************************************************************
 * Function Name: ~ContourMoments
 * Return Type 	: None
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
ContourMoments::~ContourMoments()
{


}

/*****************************************************
 * Function	: ContourMoments Copy Constructor
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ContourMoments::ContourMoments(const ContourMoments& rhsContourMoments )
{
	Allocate( rhsContourMoments );
	Copy( rhsContourMoments );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ContourMoments& ContourMoments:: operator=( const ContourMoments& rhsContourMoments )
{
	Allocate( rhsContourMoments );
	Copy( rhsContourMoments );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ContourMoments::Allocate( const ContourMoments& rhsContourMoments )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ContourMoments::Copy( const ContourMoments& rhsContourMoments )
{

	return EXIT_SUCCESS;
}




