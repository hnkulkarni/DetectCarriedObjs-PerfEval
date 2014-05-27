/*
 * EMLearning.h
 *
 *  Created on: Jul 22, 2013
 *      Author: hrushi
 */

#ifndef EMLEARNING_H_
#define EMLEARNING_H_

#include "MLearning.h"

class EMLearning: public MLearning
{
private:
	// Helper Function
	virtual int Copy( const EMLearning& rhsEMLearning );
	virtual int Allocate( const EMLearning& rhsEMLearning );
	virtual int Init_Members( unsigned int NumClasses );


protected:
	UINT m_NumClasses;
	cv::EM m_EM;
	Mat m_Labels;
	Mat m_LogLike;
	Mat m_ProbMat;
	Mat m_Samples;
	vector<string> m_ColHeader;
	UINT m_FeatureLength;

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int Train(); 		// Train the Specific Algo
	virtual int Populate_ColHeaders() = 0;

public:
	EMLearning(unsigned int NumClasses);
	virtual ~EMLearning();

	// Copy Constructor
	EMLearning( const EMLearning& rhsEMLearning );

	// Assignment Operator
	EMLearning& operator=( const EMLearning& rhsEMLearning );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual const cv::Vec2d Predict(const cv::Mat Sample) const; 	// Get prediction response



	/**************************************************************
	 *           Accessors
	 **************************************************************/
	virtual const vector<string> GetColHeader() const { return m_ColHeader; }
	virtual const Mat GetSamples() const { return m_Samples.clone(); }
	virtual const Mat GetLabels() const { return m_Labels.clone(); }
	virtual const Mat GetPostProbs() const { return m_ProbMat.clone(); }
	virtual const UINT GetFeatureLength() const { return m_FeatureLength; }
	virtual const bool isTrained() const { return m_EM.isTrained(); }
	virtual int Write( const fs::path fsPath) const;
	virtual int Load( const fs::path fsPath );

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	const UINT SetFeatureLength(UINT Length){ m_FeatureLength = Length; return m_FeatureLength;}


};

#endif /* EMLEARNING_H_ */
