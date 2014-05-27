/*
 * Detect.h
 *
 *  Created on: Dec 31, 2012
 *      Author: hrushi
 *
 *      This performs the action of Detection
 */

#ifndef DETECT_H_
#define DETECT_H_


#include "ProjectIncludes.h"
#include "GrayImg.h"
#include "ColorImg.h"
#include "Segmentation.h"
#include "ContourMap.h"
#include "Args.h"
#include "Boost.h"
#include "Features.h"
#include "ReadPoseFeature.h"
#include "CarryContour.h"
#include "Labels.h"
#include "PoseData.h"
#include "BinaryImg.h"


typedef std::map<int, vector<double> >  TYPE_MAP_CNTRSCORE;
typedef std::tuple<int, int, double > TYPE_TUPLE_RGN_TYPE;

const UINT LOCATION_DETECT 	= 0;
const UINT SHAPE_DETECT		= 1;
const UINT POSE_DETECT		= 2;
const UINT APPR_DETECT		= 3;

class Detect
{

private:

	int SetDefaults();


protected:
	// Helper Function
	int Copy_Detect( const Detect& rhsDetect );
	int Allocate_Detect( const Detect& rhsDetect );

	virtual int LoadPoseData( const Args& args);

	ContourMap m_Segments;
	ColorImg m_ProbeImg;
	GrayImg m_BkImg;

	fs::path m_TrainingFolderPath;
	bool m_PoseInfoAvailable;
	PoseData m_PoseData;

	vector<double> m_Default_Person_Score;

public:
	Detect(  const ColorImg ProbeImg, const GrayImg BkImg, const ContourMap& Segments, const Args& args  );
	virtual ~Detect();

	// Copy Constructor
	Detect( const Detect& rhsDetect );

	// Assignment Operator
	Detect& operator=( const Detect& rhsDetect );

	static const pr_score GetFinalScore(double dWorn, double dDrag, double dNoCarry, vector<double>& vAllScores );

	static ContourMap GetSegments( const ColorImg ProbeImg, const GrayImg BkImg, bool ifSaveOutput, const Args& args );
	static const fs::path GiveSegImgPath( const fs::path& ImgPath, const string Suffix );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int SetTrainingFolderPath( const fs::path fsPath ) = 0;

	static int GetType(const string ImgPath, const Args& args );

	virtual int PrintScoreMap(TYPE_MAP_CNTRSCORE ScoreMap ) const;
	virtual const vector<TYPE_TUPLE_RGN_TYPE> FormatCarryScores( const TYPE_MAP_CNTRSCORE& CtrMap ) const;
	virtual const vector<CarryContour> MakeDetectionContours( const vector<TYPE_TUPLE_RGN_TYPE>& vRgnType, const TYPE_MAP_CNTRSCORE ScoreMap  ) const;
	virtual int PrintScoreTuple( const vector<TYPE_TUPLE_RGN_TYPE>& vScoreTuple ) const;
	virtual const vector<double> LogToProb(const vector<double>& vLogScore ) const;
};


#endif /* DETECT_H_ */
