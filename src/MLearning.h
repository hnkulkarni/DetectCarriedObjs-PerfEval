/*
 * Learning.h
 *
 *  Created on: Jul 22, 2013
 *      Author: hrushi
 *
 *  About: Abstract Machine Learning Class.
 */

#ifndef LEARNING_H_
#define LEARNING_H_

#include "ProjectIncludes.h"


/**************************************************************
 *           Machine Learning Constants
 **************************************************************/
const unsigned int DEFAULT_NUM_CLASSES = 3;


class MLearning
{

private:
	// Helper Function
	virtual int Copy( const MLearning& rhsMLearning );
	virtual int Allocate( const MLearning& rhsMLearning );
	virtual int Init_Members();

protected:

	unsigned int m_NumSamples;

public:
	MLearning();
	virtual ~MLearning();

	// Copy Constructor
	MLearning( const MLearning& rhsMLearning );

	// Assignment Operator
	MLearning& operator=( const MLearning& rhsMLearning );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual const cv::Vec2d Predict(const cv::Mat Sample) const = 0; 	// Get prediction response


};

#endif /* LEARNING_H_ */
