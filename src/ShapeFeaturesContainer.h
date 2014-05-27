/*
 * ShapeFeaturesContainer.h
 *
 *  Created on: Apr 20, 2014
 *      Author: hrushi
 */

#ifndef SHAPEFEATURESCONTAINER_H_
#define SHAPEFEATURESCONTAINER_H_

#include "ProjectIncludes.h"

class ShapeFeaturesContainer
{

private:
	// Helper Function
	virtual int Copy( const ShapeFeaturesContainer& rhs );
	virtual int Allocate( const ShapeFeaturesContainer& rhs );

public:
	ShapeFeaturesContainer();
	virtual ~ShapeFeaturesContainer();

	// Copy Constructor
	ShapeFeaturesContainer( const ShapeFeaturesContainer& rhsShapeFeaturesContainer );

	// Assignment Operator
	ShapeFeaturesContainer& operator=( const ShapeFeaturesContainer& rhsShapeFeaturesContainer );

	/**************************************************************
	 *           Member Variables
	 **************************************************************/
	VVDOUBLE  m_WornShapeFeature, m_DragShapeFeature, m_NoCarryFeature;


};

#endif /* SHAPEFEATURESCONTAINER_H_ */
