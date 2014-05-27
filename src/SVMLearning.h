/*
 * SVMLearning.h
 *
 *  Created on: Nov 10, 2013
 *      Author: hrushi
 */

#ifndef SVMLEARNING_H_
#define SVMLEARNING_H_

#include "MLearning.h"
#include "ProjectIncludes.h"

class SVMLearning; //Partial Declaration

typedef std::map<string, SVMLearning> mp_Str_SVML;


class SVMLearning: public MLearning
{

private:
	// Helper Function
	virtual int Copy( const SVMLearning& rhs );
	virtual int Allocate( const SVMLearning& rhs );

	//---------- Aux functions ---------- //
	virtual int Check(const Mat Samples, const Mat ActLabels) const;

protected:

	cv::SVM m_SVM;
	cv::SVMParams m_SVMParam;

public:
	SVMLearning();
	virtual ~SVMLearning();


	// Copy Constructor
	SVMLearning( const SVMLearning& rhsSVMLearning );

	// Assignment Operator
	SVMLearning& operator=( const SVMLearning& rhsSVMLearning );

	virtual unsigned int Train( const pr_Mat_Mat& Pr);
	virtual int Save(const fs::path fs) const;
	virtual int Load(const fs::path fs);


	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual const cv::Vec2d Predict(const cv::Mat Sample) const ; 	// Get prediction response

};

#endif /* SVMLEARNING_H_ */
