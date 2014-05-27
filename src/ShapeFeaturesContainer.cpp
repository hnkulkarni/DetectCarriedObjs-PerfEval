/*
 * ShapeFeaturesContainer.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: hrushi
 */

#include "ShapeFeaturesContainer.h"


/*******************************************************************
 * Function Name: ShapeFeaturesContainer
 * Return Type 	: None
 * Created On	: Apr 20, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
ShapeFeaturesContainer::ShapeFeaturesContainer()
{

}


/*******************************************************************
 * Function Name: ~ShapeFeaturesContainer
 * Return Type 	: None
 * Created On	: Apr 20, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
ShapeFeaturesContainer::~ShapeFeaturesContainer()
{


}

/*****************************************************
 * Function	: ShapeFeaturesContainer Copy Constructor
 * Date		: Apr 20, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ShapeFeaturesContainer::ShapeFeaturesContainer(const ShapeFeaturesContainer& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Apr 20, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ShapeFeaturesContainer& ShapeFeaturesContainer:: operator=( const ShapeFeaturesContainer& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Apr 20, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ShapeFeaturesContainer::Allocate( const ShapeFeaturesContainer& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Apr 20, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ShapeFeaturesContainer::Copy( const ShapeFeaturesContainer& rhs )
{

	VectorOp<VDOUBLE>::DeepCopy(m_WornShapeFeature, rhs.m_WornShapeFeature);
	VectorOp<VDOUBLE>::DeepCopy(m_DragShapeFeature, rhs.m_DragShapeFeature);
	VectorOp<VDOUBLE>::DeepCopy(m_NoCarryFeature, rhs.m_NoCarryFeature);

	return EXIT_SUCCESS;
}


