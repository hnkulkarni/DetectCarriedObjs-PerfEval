/*
 * ShapeEM.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: hrushi
 */

#include "ShapeEM.h"

/*******************************************************************
 * Function Name: ShapeEM
 * Return Type 	: None
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Default Constructor
 * Arguments	: UINT
 *******************************************************************/
ShapeEM::ShapeEM(UINT uiNumClasses, const VVDOUBLE& TrainingSamples):EMFeatureList(uiNumClasses, TrainingSamples)
{
	Populate_ColHeaders();
}


/*******************************************************************
 * Function Name: ~ShapeEM
 * Return Type 	: None
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Default Destructor
 * Arguments	: None
 *******************************************************************/
ShapeEM::~ShapeEM()
{


}


/*****************************************************
 * Function	: ShapeEM Copy Constructor
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ShapeEM::ShapeEM(const ShapeEM& rhs ):EMFeatureList(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ShapeEM& ShapeEM:: operator=( const ShapeEM& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ShapeEM::Allocate( const ShapeEM& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ShapeEM::Copy( const ShapeEM& rhs )
{
	EMFeatureList::operator =(rhs);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Populate_ColHeaders
 * Return Type 	: int
 * Created On	: Oct 8, 2013
 * Created By 	: hrushi
 * Comments		: Populates Headers
 * Arguments	:
 *******************************************************************/
int ShapeEM::Populate_ColHeaders( )
{

	std::stringstream ss;
	ss.clear();
	ss.str("");

	const UINT NUM_HU_MOMENTS = 7;

	for(unsigned int i = 0; i <  NUM_HU_MOMENTS; i++ )
	{
		ss << "HU_" << i;
		m_ColHeader.push_back(ss.str());
		ss.str("");
		ss.clear();
	}

	m_ColHeader.push_back("Likelihood");
	m_ColHeader.push_back("Mix_Component");

	return EXIT_SUCCESS;
}




