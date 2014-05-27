/*
 * ViperGroundTruth.h
 *
 *  Created on: Mar 16, 2014
 *      Author: hrushi
 */

#ifndef VIPERGROUNDTRUTH_H_
#define VIPERGROUNDTRUTH_H_

#include "ProjectIncludes.h"
#include "TrackXML.h"
#include "ViperXML.h"
#include "AllDetectedCtrs.h"
#include "Args.h"
#include "RectOp.h"

#include "DetectionImg.h"

class ViperGroundTruth
{

private:
	// Helper Function
	virtual int Copy( const ViperGroundTruth& rhs );
	virtual int Allocate( const ViperGroundTruth& rhs );

	UINT m_TP, m_TN, m_FP, m_FN;

	virtual int Init();

protected:

public:
	ViperGroundTruth();
	virtual ~ViperGroundTruth();

	// Copy Constructor
	ViperGroundTruth( const ViperGroundTruth& rhsViperGroundTruth );

	// Assignment Operator
	ViperGroundTruth& operator=( const ViperGroundTruth& rhsViperGroundTruth );

	const vector<bool> isCorrect(const AllDetectedCtrs& allDCs, const fs::path TrkPath, const Args& args) ;
	const vector<bool> Add2ConfMat(const AllDetectedCtrs& allDCs, const cv::Rect TrackBx, const vector<cv::Rect>& GndTruth);

	int Print_ConfusionMat( const Args& args) const;

	const vector<cv::Rect> GetGndTruthinTrack( const cv::Rect TrackBx, const vector<cv::Rect>& GndTruth ) const;

	const vector<bool> AnalyzeGnd_NoDetection(const AllDetectedCtrs& allDC );
	const vector<bool> AnalyzeGnd_PosDetection( const AllDetectedCtrs& allDC, const cv::Rect TrackBx, const vector<cv::Rect>& GndTruth );
};

#endif /* VIPERGROUNDTRUTH_H_ */
