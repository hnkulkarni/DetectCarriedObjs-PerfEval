/*
 * ShapeEM.h
 *
 *  Created on: Oct 6, 2013
 *      Author: hrushi
 */

#ifndef SHAPEEM_H_
#define SHAPEEM_H_

#include "ProjectIncludes.h"
#include "EMFeatureList.h"

class ShapeEM: public EMFeatureList
{

private:

	// Helper Function
	virtual int Copy( const ShapeEM& rhs );
	virtual int Allocate( const ShapeEM& rhs );



protected:
	/**************************************************************
	 *           Pure - Virtual Functions
	 **************************************************************/
	virtual int Populate_ColHeaders();


public:
	ShapeEM(UINT uiNumClasses, const VVDOUBLE& TrainingSamples);
	virtual ~ShapeEM();

	// Copy Constructor
	ShapeEM( const ShapeEM& rhsShapeEM );

	// Assignment Operator
	ShapeEM& operator=( const ShapeEM& rhsShapeEM );


};

#endif /* SHAPEEM_H_ */
