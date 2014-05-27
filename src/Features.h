/*
 * Features.h
 *
 *  Created on: Feb 11, 2013
 *      Author: hrushi
 */

#ifndef FEATURES_H_
#define FEATURES_H_


#include "MyIncludes.h"
#include "CPPIncludes.h"
#include "OpenCV_Includes.h"
#include "Boost.h"
#include "Time.h"
#include "Args.h"
#include "StringOp.h"
#include "Detect.h"
#include "ColorImg.h"
#include "ContourMap.h"
#include "CntrFeature.h"
#include "GrayHistorgram.h"


const unsigned int WRITE_MODE 	= 1;
const unsigned int READ_MODE	= 2;

class Features {

protected:

	fs::path FilePath;
	std::fstream fPtr;
	vector<CntrFeature> ImgFeature;
	bool bWBanner;

	/***************************************************************************************
	 *  							Private Functions
	 ***************************************************************************************/
	// Helper Function
	int Copy_Features( const Features& rhsFeatures );
	int Allocate_Features( const Features& rhsFeatures );
	int WriteBanner();
	int Open(const Args& args, const unsigned int Mode );
	int Close();
	int ReadLine( const Args& args, string line);
	int ZMUL( const Args& args ); // Zero Mean- Unit Length
	vector< pair<double, int> > GetAllDistances( const ElevenSpaceHist& Hst ) const;
	vector< pair<double, int> > SortByDistances( const vector< pair<double, int> > &AllDistPairs) const;
	int MakeWeightedDecision( const vector< pair<double, int> >& AllDistPairs, unsigned int K) const;
	double EditVote( int SampleLabel, double SampleDist, double MinDist, double MaxDist ) const;

public:
	/***************************************************************************************
	 *  							House Keeping
	 ***************************************************************************************/
	Features(const Args& args, const unsigned int Mode);
	virtual ~Features();

	// Copy Constructor
	Features( const Features& rhsFeatures );

	// Assignment Operator
	Features& operator=( const Features& rhsFeatures );

	/***************************************************************************************
	 *  							Aux Functions
	 ***************************************************************************************/
	int Write( const Args& args, const int CurrentLabel, const ContourMap& Segments );
	int WriteFeatures( const Args& args, const int CurrentLabel, const ContourMap& Segments );
	int Add( const fs::path& ImPath, const int CurrentLabel, const ContourMap& Segments, const Args& args ); // Adds features to the feature map
	int Read( const Args& args);
	int NearestNeighbour(const ElevenSpaceHist& Hst, unsigned int K) const;


};

bool CompairPair( const pair<double, int>& lhs, const pair<double, int>& rhs );

#endif /* FEATURES_H_ */
