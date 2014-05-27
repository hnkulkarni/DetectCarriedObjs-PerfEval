/*
 * ReadPoseFeature.h
 *
 *  Created on: Apr 17, 2013
 *      Author: hrushi
 */

#ifndef READPOSEFEATURE_H_
#define READPOSEFEATURE_H_
#include "ProjectIncludes.h"

#include "ReadFile.h"
#include "PoseFeature.h"
#include "PoseFile.h"

const 	vector<string> ALL_POSE_FEATURE_FILES = {
		LEFT_WORN_POSE_FEATURE_FILE,
		LEFT_DRAG_POSE_FEATURE_FILE,
		LEFT_NOCARRY_POSE_FEATURE_FILE,
		RIGHT_WORN_POSE_FEATURE_FILE,
		RIGHT_DRAG_POSE_FEATURE_FILE,
		RIGHT_NOCARRY_POSE_FEATURE_FILE };

typedef std::map<string, vector<PoseFeature> > mp_PoseFeature;

class ReadPoseFeature: public ReadFile
{
private:
	// Helper Function
	int Copy( const ReadPoseFeature& rhsReadPoseFeature );
	int Allocate( const ReadPoseFeature& rhsReadPoseFeature );


protected:

	vector<PoseFeature> m_vPoseFeature;


public:
	ReadPoseFeature(const fs::path sPath);
	virtual ~ReadPoseFeature();

	// Copy Constructor
	ReadPoseFeature( const ReadPoseFeature& rhsReadPoseFeature );

	// Assignment Operator
	ReadPoseFeature& operator=( const ReadPoseFeature& rhsReadPoseFeature );

	virtual int ReadIn();

	bool isCarryPose() const;

	/**************************************************************
	 *           Get Functions
	 **************************************************************/
	const vector<PoseFeature> GetVectorOfPoseFeatures() const { return m_vPoseFeature; }
	static mp_PoseFeature GetMap_String_PoseFeature(const string TrainFolderPath, const vector<string> PoseFeatureFileList);

};

#endif /* READPOSEFEATURE_H_ */
