/*
 * ShapeFeatures.cpp
 *
 *  Created on: Oct 5, 2013
 *      Author: hrushi
 */

#include "ShapeFeatures.h"


/*******************************************************************
 * Function Name: ShapeFeatures
 * Return Type 	: None
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
ShapeFeatures::ShapeFeatures() {
	// TODO Auto-generated constructor stub

}

/*******************************************************************
 * Function Name: ~ShapeFeatures
 * Return Type 	: None
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
ShapeFeatures::~ShapeFeatures() {
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: ShapeFeatures Copy Constructor
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ShapeFeatures::ShapeFeatures(const ShapeFeatures& rhsShapeFeatures )
{
	Allocate( rhsShapeFeatures );
	Copy( rhsShapeFeatures );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 5, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ShapeFeatures& ShapeFeatures:: operator=( const ShapeFeatures& rhsShapeFeatures )
{
	Allocate( rhsShapeFeatures );
	Copy( rhsShapeFeatures );

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
int ShapeFeatures::Allocate( const ShapeFeatures& rhsShapeFeatures )
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
int ShapeFeatures::Copy( const ShapeFeatures& rhsShapeFeatures )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: AddShapeFeatures
 * Return Type 	: const VDOUBLE
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Adds a vector of doubles
 * Arguments	: const ContourMoments& Mtm
 *******************************************************************/
const VDOUBLE ShapeFeatures::AddShapeFeatures( const ContourMap& CtrMap, const ContourMoments& Mtm, int CarryLabel, WriteShapeFeatures& WFile_Carry, WriteShapeFeatures & WFile_NoCarry)
{

	VDOUBLE Features;

	for( TYPE_MAP_ALL_CONTOUR::const_iterator itr = CtrMap.AllContourMap.begin(); itr != CtrMap.AllContourMap.end(); itr++ )
	{
		int CtrNum = itr->first;
		if( CtrNum == (int)BACKGROUND_LABEL )
		{
			continue;
		}

		Features = Mtm.CalculateMoments( itr->second );

		if( CarryLabel == NO_CARRIED_OBJECT )
		{
			WFile_NoCarry.AddToWriteQue(Features);
		}
		else
		{
			if( CtrNum == CarryLabel)
			{
				WFile_Carry.AddToWriteQue(Features);
			}
			else
			{
				WFile_NoCarry.AddToWriteQue(Features);
			}
		}
	}

	return Features;
}
