/*
 * DetectByShape.h
 *
 *  Created on: Aug 10, 2013
 *      Author: hrushi
 */

#ifndef DETECTBYSHAPE_H_
#define DETECTBYSHAPE_H_

#include "Detect.h"
#include "ProjectIncludes.h"

#include "ReadFeatureList.h"
#include "ShapeEM.h"
#include "ContourMoments.h"
#include "PriorProb.h"
#include "ShapeFeaturesContainer.h"


class DetectByShape: public Detect
{
private:
	// Helper Function
	virtual int Copy( const DetectByShape& rhs );
	virtual int Allocate( const DetectByShape& rhs );
	virtual int Init_Members(const fs::path fsPath);
	virtual int LoadShapeFeatures(const fs::path TrainFolderPath );

	virtual pr_score isCarry( const ShapeEM& EMDragCarry, const ShapeEM& EMWornCarry, const ShapeEM& EMNoCarry, const Contour& Ctr, const ContourMoments& Mtm, vector<double>& vAllScores ) const;

	/**************************************************************
	 *           Private Member Variables
	 **************************************************************/
	static ShapeFeaturesContainer m_SFC;

protected:


public:
	DetectByShape( const ColorImg ProbeImg, const GrayImg BkImg,  const ContourMap& Segments,  const Args& args );
	virtual ~DetectByShape();


	// Copy Constructor
	DetectByShape( const DetectByShape& rhsDetectByShape );

	// Assignment Operator
	DetectByShape& operator=( const DetectByShape& rhsDetectByShape );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual vector<CarryContour>  GetCarried( const ContourMoments& Mtm );
	virtual int SetTrainingFolderPath( const fs::path fsPath );

	virtual const vector<double> CalScoreAtGivenCtr( const ShapeEM& EMDragCarry, const ShapeEM& EMWornCarry, const ShapeEM& EMNoCarry, const Contour& Ctr,  const ContourMoments& Mtm , PriorProb oPriorProb ) const;
	virtual const TYPE_MAP_CNTRSCORE  CalAllCntrScore( const TYPE_MAP_ALL_CONTOUR CtrMap,  const ContourMoments& Mtm, PriorProb oPriorProb ) const;
};


#endif /* DETECTBYSHAPE_H_ */
