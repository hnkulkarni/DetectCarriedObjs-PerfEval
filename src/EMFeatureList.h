/*
 * EMFeatureList.h
 *
 *  Created on: Oct 8, 2013
 *      Author: hrushi
 */

#ifndef EMFEATURELIST_H_
#define EMFEATURELIST_H_

#include "EMLearning.h"
#include "ProjectIncludes.h"

class EMFeatureList: public EMLearning
{
private:
	// Helper Function
	virtual int Copy( const EMFeatureList& rhs );
	virtual int Allocate( const EMFeatureList& rhs );
	virtual int Init_Members( const VVDOUBLE& TrainingSamples );

protected:
	/**************************************************************
	 *           Pure - Virtual Functions
	 **************************************************************/
	virtual int LoadData(const VVDOUBLE& TrainingSamples);
	virtual int Populate_ColHeaders() = 0;

public:
	EMFeatureList(unsigned int NumClasses, const VVDOUBLE& TrainingSamples);
	EMFeatureList(UINT NumClasses, const Mat& Samples );
	virtual ~EMFeatureList();

	// Copy Constructor
	EMFeatureList( const EMFeatureList& rhsEMFeatureList );

	// Assignment Operator
	EMFeatureList& operator=( const EMFeatureList& rhsEMFeatureList );

	const cv::Vec2d Predict(const vector<double>& Feature) const;

};

#endif /* EMFEATURELIST_H_ */
