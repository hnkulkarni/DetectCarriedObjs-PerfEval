/*
 * DetectionScoreFile.h
 *
 *  Created on: Apr 15, 2014
 *      Author: hrushi
 */

#ifndef DETECTIONSCOREFILE_H_
#define DETECTIONSCOREFILE_H_

#include "WriteFile.h"
#include "AllDetectedCtrs.h"

class DetectionScoreFile: public WriteFile
{
private:
	// Helper Function
	virtual int Copy( const DetectionScoreFile& rhs );
	virtual int Allocate( const DetectionScoreFile& rhs );


	string m_ScoreLine;

public:
	DetectionScoreFile(const fs::path fsPath);
	virtual ~DetectionScoreFile();

	// Copy Constructor
	DetectionScoreFile( const DetectionScoreFile& rhsDetectionScoreFile );

	// Assignment Operator
	DetectionScoreFile& operator=( const DetectionScoreFile& rhsDetectionScoreFile );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int WriteOut();
	virtual int WriteBanner();


	/**************************************************************
	 *           Add
	 **************************************************************/
	virtual int AddToScoreLine(const fs::path ImgPath, const bool isGndTruthTrue, const vector<double>& Score);
	virtual int AddToScoreLine(const fs::path ImgPath, const vector<bool> isGndTruthTrue, const AllDetectedCtrs& CarryDetection);
};

#endif /* DETECTIONSCOREFILE_H_ */
