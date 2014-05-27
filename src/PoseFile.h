/*
 * PoseFile.h
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#ifndef POSEFILE_H_
#define POSEFILE_H_

#include"ProjectIncludes.h"

#include "ReadFile.h"
#include "PoseData.h"
#include "WritePoseFeature.h"

class WritePoseFeature; //Partial Declaration

typedef boost::shared_ptr<WritePoseFeature> shptr_WrPF;
typedef std::map<char, shptr_WrPF > Map_WrtPoseFeature;


class PoseFile: public ReadFile
{

private:
	// Helper Function
	int Copy_PoseFile( const PoseFile& rhsPoseFile );
	int Allocate_PoseFile( const PoseFile& rhsPoseFile );

protected:



public:

	/**************************************************************
	 *           House Keeping Functions
	 **************************************************************/
	PoseFile( const fs::path sPath );
	virtual ~PoseFile();


	// Copy Constructor
	PoseFile( const PoseFile& rhsPoseFile );

	// Assignment Operator
	PoseFile& operator=( const PoseFile& rhsPoseFile );


	/**************************************************************
	 *           Virtual Functions
	 **************************************************************/
	virtual int ReadIn();


	/**************************************************************
	 *           Aux Functions
	 **************************************************************/
	virtual int ReadLine(const string line, const unsigned int uiLineCnt );

	/**************************************************************
	 *           Public Member Functions
	 **************************************************************/
	static const fs::path GetBoxFilePath( const fs::path ImgPath );
	virtual int AddPoseFeatures(const ColorImg& WorkImg, const ContourMap& Segments, int Label,const vector<char> vPartKey,  Map_WrtPoseFeature& Carry, Map_WrtPoseFeature& No_Carry, const Args& args ) const;


	/**************************************************************
	 *           Public Member Variables
	 **************************************************************/
	PoseData m_Pose;

};

#endif /* POSEFILE_H_ */
