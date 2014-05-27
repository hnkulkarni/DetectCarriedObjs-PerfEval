/*
 * PoseFeature.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: hrushi
 */

#include "PoseFeature.h"

PoseFeature::PoseFeature() {
	// TODO Auto-generated constructor stub

}

PoseFeature::~PoseFeature() {
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: PoseFeature Copy Constructor
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
PoseFeature::PoseFeature(const PoseFeature& rhsPoseFeature )
{
	Allocate( rhsPoseFeature );
	Copy( rhsPoseFeature );

}

/*****************************************************
 * Function	: operator =
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
PoseFeature& PoseFeature:: operator=( const PoseFeature& rhsPoseFeature )
{
	Allocate( rhsPoseFeature );
	Copy( rhsPoseFeature );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int PoseFeature::Allocate( const PoseFeature& rhsPoseFeature )
{
	feature.resize( rhsPoseFeature.feature.size() );
	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int PoseFeature::Copy( const PoseFeature& rhsPoseFeature )
{

	for( unsigned int i = 0; i < rhsPoseFeature.feature.size(); i++ )
	{
		feature.at(i) = rhsPoseFeature.feature.at(i);
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadFromLine
 * Return Type 	: int
 * Created On	: Apr 17, 2013
 * Created By 	: hrushi
 * Comments		: Populates the features from the line
 * Arguments	: const string line
 *******************************************************************/
int PoseFeature::ReadFromLine( const string line)
{

	feature.resize( Size() );

	std::stringstream ss;
	ss.str( line );

	ss >> feature;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetPoseAngles
 * Return Type 	: int
 * Created On	: Apr 17, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Pose angles for the give centroid
 * Arguments	: const ImagePt & pt
 *******************************************************************/
int PoseFeature::GetPoseAngles( const ImagePt & pt) const
{


	return EXIT_SUCCESS;
}
