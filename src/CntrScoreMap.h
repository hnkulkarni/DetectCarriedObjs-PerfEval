/*
 * CntrScoreMap.h
 *
 *  Created on: Jan 13, 2013
 *      Author: hrushi
 */

#ifndef CNTRSCOREMAP_H_
#define CNTRSCOREMAP_H_


#include "CPPIncludes.h"
#include "MyIncludes.h"
#include "OpenCV_Includes.h"

class CntrScoreMap {

protected:
	Mat Scmat;

public:
	CntrScoreMap();
	CntrScoreMap(const unsigned int NumLabels);
	virtual ~CntrScoreMap();

	// Copy Constructor
	CntrScoreMap( const CntrScoreMap& rhsCntrScoreMap );

	// Assignment Operator
	CntrScoreMap& operator=( const CntrScoreMap& rhsCntrScoreMap );

	// Helper Function
	int Copy_CntrScoreMap( const CntrScoreMap& rhsCntrScoreMap );
	int Allocate_CntrScoreMap( const CntrScoreMap& rhsCntrScoreMap );

	/*
	 *  Member Functions
	 */
	int GetBestMatch( unsigned int ContourNum, double MatchThreshold ) const;
	bool CheckIfBestMatch( unsigned int Target, unsigned int Test ) const;
	double GetBestScore( unsigned int ContourNum ) const;
	int GetMatchContourWithScore( unsigned int ContourNum , double Score ) const;

	/*
	 * Mutators
	 */
	int Set(CUINT L1, CUINT L2, double Score);
	int Initialize(const unsigned int NumLabels);


	/*
	 * Accessors
	 */
	const Mat& GetMat() const {return Scmat;}

};

std::ostream& operator<<( std::ostream& out, const CntrScoreMap& rhsCntrScrMap );

#endif /* CNTRSCOREMAP_H_ */
