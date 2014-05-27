/*
 * PoseEM.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: hrushi
 */

#include "PoseEM.h"

/*******************************************************************
 * Function Name: PoseEM
 * Return Type 	: None
 * Created On	: Oct 21, 2013
 * Created By 	: hrushi
 * Comments		: Default Constructor
 * Arguments	:
 *******************************************************************/
PoseEM::PoseEM():EMLearning(DEFAULT_NUM_CLASSES)
{
	/*
	 * Do nothing constructor, required by C++ map
	 */

	//cout << "Do Nothing PoseEM with " << DEFAULT_NUM_CLASSES << " Classes " << endl;

}

/*******************************************************************
 * Function Name: Default Constructor
 * Return Type 	:
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Constructor for the PoseEM
 * Arguments	:
 *******************************************************************/
PoseEM::PoseEM(unsigned int NumClasses, const vector<PoseFeature>& vPF ):EMLearning(NumClasses)
{

	Init_Members(vPF);
	LoadData();
	Train();

}

/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Initalize All Member Variables
 * Arguments	:
 *******************************************************************/
int PoseEM::Init_Members( const vector<PoseFeature>& vPF )
{
	m_vPF = vPF;
	m_NumSamples = m_vPF.size();
	SetFeatureLength(POSE_FEATURE_LENGTH);

	m_Samples = Mat::zeros(m_NumSamples, m_FeatureLength, CV_32FC1);

	Populate_ColHeaders();



	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Populate_ColHeaders
 * Return Type 	: int
 * Created On	: Jul 28, 2013
 * Created By 	: hrushi
 * Comments		: Populate the vector of column headers
 * Arguments	:
 *******************************************************************/
int PoseEM::Populate_ColHeaders( )
{
	//Column 1
	m_ColHeader.push_back("Carry_Angle");
	m_ColHeader.push_back("Carry_dist");
	m_ColHeader.push_back("Rgn_Y");
	m_ColHeader.push_back("Likelihood");
	m_ColHeader.push_back("Mix_Component");

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Default Destructor
 * Return Type 	:
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Destructor for the PoseEM
 * Arguments	:
 *******************************************************************/
PoseEM::~PoseEM()
{


}

/*****************************************************
 * Function	: PoseEM Copy Constructor
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
PoseEM::PoseEM(const PoseEM& rhsPoseEM ):EMLearning(rhsPoseEM)
{
	Allocate( rhsPoseEM );
	Copy( rhsPoseEM );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
PoseEM& PoseEM:: operator=( const PoseEM& rhsPoseEM )
{
	Allocate( rhsPoseEM );
	Copy( rhsPoseEM );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int PoseEM::Allocate( const PoseEM& rhsPoseEM )
{
	m_vPF.resize( rhsPoseEM.m_vPF.size() );
	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int PoseEM::Copy( const PoseEM& rhsPoseEM )
{

	EMLearning::operator =(rhsPoseEM);

	for(unsigned int i = 0; i< rhsPoseEM.m_vPF.size(); i++)
	{
		m_vPF.at(i) = rhsPoseEM.m_vPF.at(i);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: LoadData
 * Return Type 	: int
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Loads the Pose Data as required by the EM
 * Arguments	:
 *******************************************************************/
int PoseEM::LoadData( )
{
	for( unsigned int i = 0; i < m_NumSamples; i++ )
	{
		for(unsigned int j = 0; j < m_vPF.at(i).feature.size(); j++ )
		{
			m_Samples.at<float>(i,j) = m_vPF.at(i).feature.at(j);
		}
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Predict
 * Return Type 	: cv::Vec2d
 * Created On	: Jul 27, 2013
 * Created By 	: hrushi
 * Comments		: Returns the sample and the log normal probabilities using the trained EM
 * Arguments	: double CarryAngle, double CarryDist
 *******************************************************************/
cv::Vec2d PoseEM::Predict( const vector<double>& Feature ) const
{

	cv::Mat Sample(1, Feature.size(), CV_32FC1 );

	for( unsigned int i = 0; i < Feature.size(); i++ )
	{
		Sample.at<float>(i) = Feature.at(i);
	}

	cv::Vec2d Response = EMLearning::Predict( Sample );

	return Response;
}




