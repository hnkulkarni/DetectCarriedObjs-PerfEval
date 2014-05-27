/*
 * GroundTruth.h
 *
 *  Created on: Jul 4, 2013
 *      Author: hrushi
 */

#ifndef GROUNDTRUTH_H_
#define GROUNDTRUTH_H_

#include "ProjectIncludes.h"

#include "Labels.h"
#include "CarryContour.h"
#include "AllDetectedCtrs.h"

const UINT GND_CATEGORIES = 3;

class GroundTruth
{

private:
	// Helper Function
	virtual int Copy( const GroundTruth& rhsGroundTruth );
	virtual int Allocate( const GroundTruth& rhsGroundTruth );
	virtual int Init_Members();
	virtual int Set_ConfusionMat( unsigned int Val);
	virtual int Set_RowHeaders();

	Labels m_AllLabels;
	Labels m_BagpackLabels;
	Labels m_SuitecaseLabels;
	vector<string> m_RowHeader;

	vector< pr_score > m_vScores;

	virtual int AddToScoreList(const AllDetectedCtrs& AllCtrs );
	virtual int PrintStats( const Args& args ) const;
	virtual int PrintStats(  const Args& args, const vector<double>& AllScores ) const;

	virtual int PrintAllVals(  const Args& args, cv::FileStorage& fScore,  const string Tag,  const vector<double>& AllScores) const;
	virtual const string GetSavePath( const Args& args ) const;

	static double PWR(double d);

protected:

	unsigned int m_ConfusionMat[GND_CATEGORIES][GND_CATEGORIES];

public:
	GroundTruth();
	GroundTruth(const Args& args);

	virtual ~GroundTruth();

	// Copy Constructor
	GroundTruth( const GroundTruth& rhsGroundTruth );

	// Assignment Operator
	virtual GroundTruth& operator=( const GroundTruth& rhsGroundTruth );


	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int Load( const Args& args);


	/**************************************************************
	 *           Accessors
	 **************************************************************/
	virtual int Print_ConfusionMat(const Args& args) const;

	/**************************************************************
	 *     Functions that use the data of this class.
	 **************************************************************/
	virtual bool isCorrect( const fs::path ProbeImgPath, const AllDetectedCtrs& AllCtrs );

	virtual vector<CarryContour> ReplaceWith_Gt(const fs::path ProbeImgPath, const vector<CarryContour>& vCC ) const;

};

#endif /* GROUNDTRUTH_H_ */
