/*
 * CarryContour.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: hrushi
 */

#include "CarryContour.h"

CarryContour::CarryContour()
{
	Init();

}

CarryContour::~CarryContour()
{

}

/*****************************************************
 * Function	: CarryContour Copy Constructor
 * Date		: Jun 20, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
CarryContour::CarryContour(const CarryContour& rhsCarryContour )
{
	Allocate( rhsCarryContour );
	Copy( rhsCarryContour );

}


/*******************************************************************
 * Function Name: CarryContour
 * Return Type 	:
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Constructor when called with its parent
 * Arguments	: const Contour& rhsContour
 *******************************************************************/
CarryContour::CarryContour( const Contour& rhsContour)
{
	Contour::operator =( rhsContour );
	Init();
}
/*****************************************************
 * Function	: operator =
 * Date		: Jun 20, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
CarryContour& CarryContour:: operator=( const CarryContour& rhsCarryContour )
{
	Allocate( rhsCarryContour );
	Copy( rhsCarryContour );

	return *this;
}




/*******************************************************************
 * Function Name: Init
 * Return Type 	: int
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Initializes the Member Variables
 * Arguments	:
 *******************************************************************/
int CarryContour::Init( )
{
	SetCarryTypeNScore( -1, 0 ); // Carry Type = -1 indicates not initialized, hence Score is set to zero

	return EXIT_SUCCESS;
}
/*****************************************************
 * Function	: Allocate
 * Date		: Jun 20, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int CarryContour::Allocate( const CarryContour& rhsCarryContour )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jun 20, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int CarryContour::Copy( const CarryContour& rhsCarryContour )
{
	// Copy Elements from the Base Class.
	Contour::operator =( rhsCarryContour );

	// Copy Elements from this class
	m_CarryType = rhsCarryContour.m_CarryType;
	m_CarryScore = rhsCarryContour.m_CarryScore;

	VectorOp<double>::DeepCopy(m_AllScores, rhsCarryContour.m_AllScores);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: SetCarryTypeNScore
 * Return Type 	: int
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Sets the Carry Score and Type
 * Arguments	: int CarryType, double CarryScore
 *******************************************************************/
int CarryContour::SetCarryTypeNScore( int CarryType, double CarryScore)
{
	m_CarryType = CarryType;
	m_CarryScore = CarryScore;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: OtherScores
 * Return Type 	: int
 * Created On	: Apr 14, 2014
 * Created By 	: hrushi
 * Comments		: Sets scores for Worn Carry, Drag Carry and Person Carry
 * Arguments	: const vector<double>& OtherScores
 *******************************************************************/
int CarryContour::SetAllScores( const vector<double>& AllScores)
{
	VectorOp<double>::DeepCopy(m_AllScores, AllScores);
	return EXIT_SUCCESS;
}



