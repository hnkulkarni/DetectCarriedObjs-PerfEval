/*
 * DetectByAppearance.h
 *
 *  Created on: Oct 31, 2013
 *      Author: hrushi
 */

#ifndef DETECTBYAPPEARANCE_H_
#define DETECTBYAPPEARANCE_H_

#include "Detect.h"
#include "ProjectIncludes.h"

#include "BOF.h"

class DetectByAppearance: public Detect
{

private:
	// Helper Function
	virtual int Copy( const DetectByAppearance& rhs );
	virtual int Allocate( const DetectByAppearance& rhs );

protected:

	/**************************************************************
	 *           Variables
	 **************************************************************/



	/**************************************************************
	 *           Functions
	 **************************************************************/
	virtual pr_score isCarried(const BOF& oBof, const ColorImg& Img, vector<double>& vAllScores, const Args& args ) const;



public:
	DetectByAppearance(  const ColorImg ProbeImg, const GrayImg BkImg, const ContourMap& Segments, const Args& args );
	virtual ~DetectByAppearance();

	// Copy Constructor
	DetectByAppearance( const DetectByAppearance& rhsDetectByAppearance );

	// Assignment Operator
	DetectByAppearance& operator=( const DetectByAppearance& rhsDetectByAppearance );


	virtual vector<CarryContour> GetCarried(const BOF& oBof, const Args& args );
	virtual int Init_Members( const fs::path fsPath );

	const TYPE_MAP_CNTRSCORE CalAllCntrScore( const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args ) const;

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int SetTrainingFolderPath( const fs::path fsPath );


};

#endif /* DETECTBYAPPEARANCE_H_ */
