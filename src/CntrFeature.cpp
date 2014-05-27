/*
 * CntrFeature.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: hrushi
 */

#include "CntrFeature.h"

CntrFeature::CntrFeature() {
	// TODO Auto-generated constructor stub

	Label = -1;

}

CntrFeature::~CntrFeature() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: CntrFeature
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
CntrFeature::CntrFeature( const CntrFeature& rhsCntrFeature )
{
	Allocate_CntrFeature( rhsCntrFeature );
	Copy_CntrFeature( rhsCntrFeature );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
CntrFeature& CntrFeature :: operator=( const CntrFeature & rhsCntrFeature )
{
	Allocate_CntrFeature( rhsCntrFeature );
	Copy_CntrFeature( rhsCntrFeature );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_CntrFeature
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int CntrFeature:: Copy_CntrFeature(  const CntrFeature & rhsCntrFeature  )
{
	Hst 	= rhsCntrFeature.Hst;
	Label 	= rhsCntrFeature.Label;

	return EXIT_SUCCESS;
}





/**********************************************************************
 * Function Name: Allocate_CntrFeature
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int CntrFeature:: Allocate_CntrFeature(  const CntrFeature & rhsCntrFeature  )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ZMUL
 * Return Type 	: int
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Zero Means and Unit Lengths all the data
 * Arguments	: const Args& args
 *******************************************************************/
int CntrFeature::ZMUL( const Args& args)
{
	Hst.ZMUL();

	return EXIT_SUCCESS;
}


