/*
 * PoseFeature.h
 *
 *  Created on: Apr 17, 2013
 *      Author: hrushi
 */

#ifndef POSEFEATURE_H_
#define POSEFEATURE_H_


#include "ProjectIncludes.h"
#include "VectorOp.h"
#include "ImagePt.h"


const unsigned int POSE_FEATURE_LENGTH = 2;

class PoseFeature {
public:
	PoseFeature();
	virtual ~PoseFeature();

	// Copy Constructor
	PoseFeature( const PoseFeature& rhsPoseFeature );

	// Assignment Operator
	PoseFeature& operator=( const PoseFeature& rhsPoseFeature );

	// Helper Function
	int Copy( const PoseFeature& rhsPoseFeature );
	int Allocate( const PoseFeature& rhsPoseFeature );


	/**************************************************************
	 *           Public Functions
	 **************************************************************/
	int ReadFromLine( const string line );
	int GetPoseAngles( const ImagePt &Pt ) const;

	/**************************************************************
	 *           Public Member Variables
	 **************************************************************/
	vector<double> feature;


	/**************************************************************
	 *           Get Functions
	 **************************************************************/
	virtual int Size() const{ return POSE_FEATURE_LENGTH; } // Returns size of the feature vector
	virtual double GetFeature_Angle() 	const { return feature.at(0); }
	virtual double GetFeature_Dist() 	const { return feature.at(1); }


};

#endif /* POSEFEATURE_H_ */
