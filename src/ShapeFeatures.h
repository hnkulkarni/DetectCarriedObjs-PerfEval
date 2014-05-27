/*
 * ShapeFeatures.h
 *
 *  Created on: Oct 5, 2013
 *      Author: hrushi
 */

#ifndef SHAPEFEATURES_H_
#define SHAPEFEATURES_H_
#include "ProjectIncludes.h"
#include "ContourMoments.h"
#include "WriteShapeFeatures.h"


class ShapeFeatures {

private:
	// Helper Function
	virtual int Copy( const ShapeFeatures& rhsShapeFeatures );
	virtual int Allocate( const ShapeFeatures& rhsShapeFeatures );

protected:


public:
	ShapeFeatures();
	virtual ~ShapeFeatures();

	// Copy Constructor
	ShapeFeatures( const ShapeFeatures& rhsShapeFeatures );

	// Assignment Operator
	ShapeFeatures& operator=( const ShapeFeatures& rhsShapeFeatures );

	const VDOUBLE AddShapeFeatures(const ContourMap& CtrMap, const ContourMoments& Mtm, int CarryLabel, WriteShapeFeatures& WFile_Carry, WriteShapeFeatures & WFile_NoCarry );

};

#endif /* SHAPEFEATURES_H_ */
