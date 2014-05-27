/*
 * ApprEM.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: hrushi
 */

#include "ApprEM.h"

/*******************************************************************
 * Function Name: ApprEM
 * Return Type 	: None
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Constructor
 * Arguments	:
 *******************************************************************/
ApprEM::ApprEM(UINT uiNumClasses, const Mat& TrainingSamples):EMFeatureList(uiNumClasses, TrainingSamples)
{

	Populate_ColHeaders();

}


/*******************************************************************
 * Function Name: ApprEM
 * Return Type 	: None
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
ApprEM::ApprEM():EMFeatureList(DEFAULT_NUM_CLASSES, Mat())
{

}


/*******************************************************************
 * Function Name: ~ApprEM
 * Return Type 	: None
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
ApprEM::~ApprEM()
{

}

/*****************************************************
 * Function	: ApprEM Copy Constructor
 * Date		: Nov 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ApprEM::ApprEM(const ApprEM& rhs ):EMFeatureList(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Nov 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ApprEM& ApprEM:: operator=( const ApprEM& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Nov 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ApprEM::Allocate( const ApprEM& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Nov 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ApprEM::Copy( const ApprEM& rhs )
{

	EMFeatureList::operator =(rhs);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Populate_ColHeaders
 * Return Type 	: int
 * Created On	: Oct 8, 2013
 * Created By 	: hrushi
 * Comments		: Populates Headers
 * Arguments	:
 *******************************************************************/
int ApprEM::Populate_ColHeaders( )
{

	std::stringstream ss;
	ss.clear();
	ss.str("");

	for(unsigned int i = 0; i <  m_FeatureLength; i++ )
	{
		ss << i;
		m_ColHeader.push_back(ss.str());
		ss.str("");
		ss.clear();
	}

	m_ColHeader.push_back("Likelihood");
	m_ColHeader.push_back("Mix_Component");

	return EXIT_SUCCESS;
}
