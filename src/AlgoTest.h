/*
 * AlgoTest.h
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#ifndef ALGOTEST_H_
#define ALGOTEST_H_

#include "Algo.h"

#include "ProjectIncludes.h"

#include "AllDetectedCtrs.h"
#include "DetectionImg.h"
#include "Labels.h"
#include "PriorProb.h"
#include "Args.h"
#include "ReadPriorProb.h"
#include "WritePriorProbs.h"

#include "DetectByLocation.h"
#include "DetectByPose.h"
#include "DetectByShape.h"
#include "DetectByAppearance.h"

#include "HuMoments.h"

class AlgoTest: public Algo
{

protected:
	fs::path m_TrainFolderPath;
	vector<ProbImg> m_vProbImgs; 	// Vector containing all the Probability images
	PriorProb m_PriorProbs;			// Contains all the prior probabilities

	virtual const AllDetectedCtrs DetectionByAll( const fs::path ProbeImgPath, const fs::path BkImgPath, const ContourMap& Segments, const string AlgoType, const Args& args );
	virtual const vector<CarryContour> DetectbyVoting( const vector<CarryContour>& CrLoc, const vector<CarryContour>& CrShape, const vector<CarryContour>& CrPose, const vector<CarryContour>& CrAppr ) const;

public:
	AlgoTest( const Args& args );
	virtual ~AlgoTest();

	// Copy Constructor
	AlgoTest( const AlgoTest& rhsAlgoTest );

	// Assignment Operator
	AlgoTest& operator=( const AlgoTest& rhsAlgoTest );

	// Helper Function
	virtual int Copy( const AlgoTest& rhsAlgoTest );
	virtual int Allocate( const AlgoTest& rhsAlgoTest );

	/**************************************************************
	 *           Aux Functions
	 **************************************************************/
	virtual const AllDetectedCtrs DetectionAlgo(  const fs::path ProbeImgPath, const fs::path BkImgPath, const string AlgoType, const Args& args );
	virtual const ProbImg CalLocationPriorProb( const vector<ProbImg>& vProbImgs ) const;

	/**************************************************************
	 *           Load Functions
	 **************************************************************/
	virtual int LoadProbImgs( const fs::path TrainFolderPath );
	virtual int LoadTrainingPath( const fs::path TrainingFolderPath );
	virtual const PriorProb LoadPriorProbs( const fs::path TrainingFolderPath, const vector<ProbImg>& vProbImg, const Args& args );

	/**************************************************************
	 *           Accessors
	 **************************************************************/
	virtual ColorImg DisplayDetections(const fs::path ProbeImgPath, const vector<CarryContour>& vCrrCtr, const Args& args ) const;
	virtual ColorImg DisplayCarriedCtr( ColorImg ProbeImg, const CarryContour& CrrCtr, const Args& args ) const;

	virtual const TYPE_MAP_CNTRSCORE Product(const TYPE_MAP_CNTRSCORE& M1, const TYPE_MAP_CNTRSCORE& M2) const;
};

#endif /* ALGOTEST_H_ */
