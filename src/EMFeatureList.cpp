/*
 * EMFeatureList.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: hrushi
 */

#include "EMFeatureList.h"

/*******************************************************************
 * Function Name: EMFeatureList
 * Return Type 	: None
 * Created On	: Oct 8, 2013
 * Created By 	: hrushi
 * Comments		:
 * Arguments	:
 *******************************************************************/
EMFeatureList::EMFeatureList(unsigned int NumClasses, const VVDOUBLE& TrainingSamples):EMLearning(NumClasses)
{

	Init_Members(TrainingSamples);
	LoadData( TrainingSamples );

	Train();

}

/*******************************************************************
 * Function Name: EMFeatureList
 * Return Type 	:
 * Created On	: Nov 16, 2013
 * Created By 	: hrushi
 * Comments		: Creates the EMFeature list class for the given samples
 * Arguments	: unsigned int NumClasses, const VVDOUBLE& TrainingSamples
 *******************************************************************/
EMFeatureList::EMFeatureList( unsigned int NumClasses, const Mat& Samples ):EMLearning(NumClasses)
{
	UINT NumCols = Samples.cols;
	SetFeatureLength(NumCols);

	m_Samples = Samples.clone();
	m_NumSamples = Samples.rows;

	//---------- This is a safety, because maps require a empty constructor ---------- //
	if(m_NumSamples > 0 )
	{
		Train();
	}
}
/*******************************************************************
 * Function Name: ~EMFeatureList
 * Return Type 	: None
 * Created On	: Oct 8, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
EMFeatureList::~EMFeatureList()
{

}

/*****************************************************
 * Function	: EMFeatureList Copy Constructor
 * Date		: Oct 8, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
EMFeatureList::EMFeatureList(const EMFeatureList& rhs ):EMLearning(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 8, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
EMFeatureList& EMFeatureList:: operator=( const EMFeatureList& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 8, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int EMFeatureList::Allocate( const EMFeatureList& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 8, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int EMFeatureList::Copy( const EMFeatureList& rhs )
{
	EMLearning::operator =( rhs );


	return EXIT_SUCCESS;
}/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Oct 8, 2013
 * Created By 	: hrushi
 * Comments		: Initializes the member variables
 * Arguments	: const VVDOUBLE& TrainingSamples
 *******************************************************************/
int EMFeatureList::Init_Members( const VVDOUBLE& TrainingSamples)
{

	m_NumSamples = TrainingSamples.size();

	UINT Length = TrainingSamples.at(0).size();
	SetFeatureLength(Length);

	m_Samples = Mat::zeros(m_NumSamples, m_FeatureLength , CV_32FC1);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: LoadData
 * Return Type 	: int
 * Created On	: Oct 8, 2013
 * Created By 	: hrushi
 * Comments		: Loads the Vector of Vector in the specific format
 * Arguments	:
 *******************************************************************/
int EMFeatureList::LoadData( const VVDOUBLE& TrainingSamples )
{

	for( unsigned int i = 0; i < m_NumSamples; i++ )
	{
		for(unsigned int j = 0; j < TrainingSamples.at(i).size(); j++ )
		{
			m_Samples.at<float>(i,j) = (float)TrainingSamples.at(i).at(j);
		}
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Predict
 * Return Type 	: const cv::Vec2d
 * Created On	: Oct 12, 2013
 * Created By 	: hrushi
 * Comments		: Preform prediction
 * Arguments	: const vector<double>& Feature
 *******************************************************************/
const cv::Vec2d EMFeatureList::Predict( const vector<double>& Feature) const
{
	cv::Mat Sample(1, Feature.size(), CV_32FC1 );

	for( unsigned int i = 0; i < Feature.size(); i++ )
	{
		Sample.at<float>(i) = Feature.at(i);
	}

	cv::Vec2d Response = EMLearning::Predict( Sample );

	return Response;
}
