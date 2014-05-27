/*
 * DetectByLocation.h
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#ifndef DETECTBYLOCATION_H_
#define DETECTBYLOCATION_H_

#include "ProjectIncludes.h"

#include "Detect.h"
#include "ProbImg.h"
#include "PriorProb.h"
#include "PoseFile.h"
#include "PoseData.h"

class DetectByLocation: public Detect
{

private:
	// Helper Function
	int Copy( const DetectByLocation& rhsDetectByLocation );
	int Allocate( const DetectByLocation& rhsDetectByLocation );
	int Init_Members( const fs::path TrainFolderPath );

protected:
	vector<ProbImg> m_vProbImgs;
	PriorProb m_PriorProb;

public:

	/**************************************************************
	 *           Housekeeping Functions
	 **************************************************************/
	DetectByLocation(const ColorImg ProbeImg, const GrayImg BkImg, vector<ProbImg> ProbImgs, PriorProb oPriorProb, const ContourMap& Segments,  const Args& args);

	virtual ~DetectByLocation();

	// Copy Constructor
	DetectByLocation( const DetectByLocation& rhsDetectByLocation );

	// Assignment Operator
	DetectByLocation& operator=( const DetectByLocation& rhsDetectByLocation );


	/**************************************************************
	 *           Abstract Methods
	 **************************************************************/
	virtual vector<CarryContour> GetCarried( const Args& args );


	/**************************************************************
	 *           Modifiers
	 **************************************************************/
	virtual int SetTrainingFolderPath( const fs::path fsPath );

	/**************************************************************
	 *           Accessors
	 **************************************************************/

	virtual const vector<double> CalScoreAtGivenCtr( const Contour& ctr ) const;
	virtual const TYPE_MAP_CNTRSCORE CalAllCntrScore(const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args) const;


};

#endif /* DETECTBYLOCATION_H_ */
