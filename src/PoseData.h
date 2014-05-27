/*
 * PoseData.h
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#ifndef POSEDATA_H_
#define POSEDATA_H_

#include"ProjectIncludes.h"

#include "PartOfPose.h"
#include "Contour.h"
#include "CImage.h"
#include "PoseFeature.h"
#include "BinaryImg.h"


typedef std::map<char, PartOfPose>  MapPartOfPose;

const char PartColor[64] = {'g','g','y','m','m','m','m','y','y','y','r','r','r','r','y','c','c','c','c','y','y','y','b','b','b','b'};
const double ARM_EXTN_DIST = 10; // Draws an extension line along with the arm.
const double POSE_BELIEVE_THRLD = 0.70; // Base of the calculation of the Pose data only if the data is above this threshold.
const double POSE_PART_BELIEVE_THRLD = 0.5; // Believe the poase part overlap score only if there is a 50 percent overlap

class PoseData
{

private:

	bool ShouldOverlayPose( string PartType, string sOpt ) const;



protected:
	MapPartOfPose m_PosePartMap;
	const ImagePt GetExtensionPt(char MapKey) const;


public:

	/**************************************************************
	 *           	House Keeping
	 **************************************************************/
	PoseData();
	virtual ~PoseData();

	// Copy Constructor
	PoseData( const PoseData& rhsPoseData );

	// Assignment Operator
	PoseData& operator=( const PoseData& rhsPoseData );

	// Helper Function
	int Copy_PoseData( const PoseData& rhsPoseData );
	int Allocate_PoseData( const PoseData& rhsPoseData );

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	int Add(char cPartClr, const Boxes& Bx);
	int CalculatePartAngles();
	double CalcCarryAngles(char PartKey, const ImagePt& Pt) const;
	double CalcCarryDist( char PartKey, const Contour& Ct ) const;
	int SetCarryAngle(const double Val);

	/**************************************************************
	 *           Accessors
	 **************************************************************/
	int GetNumParts() 		const {	return m_PosePartMap.size();}
	MapPartOfPose GetPosePartMap()	const { return m_PosePartMap; }
	ColorImg Overlay( const CImage& img, string sOpt ) const;
	ColorImg Overlay( const ColorImg & Img, const string PartType,  const Contour& Ctr ) const;
	ColorImg Overlay( const ColorImg& Img, char Mapkey, const Contour& Ctr ) const;
	ColorImg OverlayExtn( const ColorImg& Img, char Mapkey, const Contour& Ctr ) const;

	const vector<double> CalcPoseFeature( char PartKey, const Contour& Ctr ) const;
	const vector<double> GetPoseFeature(ColorImg& DispImg, bool isCarryRgn,  char PartKey, const Contour& Ctr, const Args& args) const;

	const string GetLegendString( const string ArmName, const vector<double>& Feature) const;
	const BinaryImg PoseMask( const cv::Size ImgSize, const string sOpt, const Args& args ) const;
	double GetOverlapPercentage(const BinaryImg& Img, const string sPart, bool bDisp,  const Args& args) const;
	bool PoseOverlapDetectScore(const BinaryImg& MskImg,  const Contour& Ctr, const string sPosePart, vector<double>& Score, const Args& args) const;

	/**************************************************************
	 *           Aux Functions
	 **************************************************************/


};

#endif /* POSEDATA_H_ */
