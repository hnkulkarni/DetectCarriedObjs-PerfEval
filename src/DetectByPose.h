/*
 * DetectByPose.h
 *
 *  Created on: Jul 21, 2013
 *      Author: hrushi
 */

#ifndef DETECTIONBYPOSE_H_
#define DETECTIONBYPOSE_H_

#include "ProjectIncludes.h"
#include "Detect.h"
#include "ColorImg.h"
#include "GrayImg.h"
#include "ProbImg.h"
#include "PoseData.h"
#include "PoseFile.h"
#include "PoseEM.h"
#include "PoseFeature.h"
#include "WriteEM.h"
#include "PriorProb.h"

typedef std::map<string, PoseEM> mp_str_poseEM;

class DetectByPose: public Detect
{
private:

	PoseData m_Pose;
	vector<ProbImg> m_vProbImgs;

	// Helper Function
	virtual int Copy( const DetectByPose& rhsDetectByPose );
	virtual int Allocate( const DetectByPose& rhsDetectByPose );

	// Get Pose for the given probe image
	virtual int Init_Members(const fs::path ProbeImgPath, const fs::path TrainFolderPath, vector<ProbImg> ProbImgs );
	virtual int ReadPose( const fs::path ProbeImgPath );
	virtual int LoadAllPoseFeatures( const fs::path TrainingFolderPath);

	virtual pr_score isArmCarry( const string PartType, const Contour& Ctr, vector<double>& vAllScore ) const;
	virtual double GetRatio( const VDOUBLE& PoseFeature, const PoseEM& CarryEM, const PoseEM& NoCarryEM, double& LogCarry_Prob, double& LogNoCarry_Prob ) const;
	virtual const pr_score MakeDecision( const pr_score& LeftScore, const pr_score& RightScore ) const;

protected:


	mp_PoseFeature 	m_Map_Posefeature;
	mp_str_poseEM	m_Map_strPoseEM;

public:
	DetectByPose(const ColorImg ProbeImg, const GrayImg BkImg, const vector<ProbImg> m_vProbImgs, const ContourMap& Segments, const Args& args);
	virtual ~DetectByPose();

	// Copy Constructor
	DetectByPose( const DetectByPose& rhsDetectByPose );

	// Assignment Operator
	DetectByPose& operator=( const DetectByPose& rhsDetectByPose );

	virtual CarryContour Check_if_Cntr_Carry( const Contour& Ctr, double& dLike ) const;
	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual vector<CarryContour>  GetCarried();
	virtual int SetTrainingFolderPath( const fs::path fsPath );

	const TYPE_MAP_CNTRSCORE CalAllCntrScore( const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args ) const;
};

#endif /* DETECTIONBYPOSE_H_ */
