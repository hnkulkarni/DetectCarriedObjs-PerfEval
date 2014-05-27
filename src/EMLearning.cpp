/*
 * EMLearning.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: hrushi
 */

#include "EMLearning.h"

/*******************************************************************
 * Function Name: Default Constructor
 * Return Type 	:
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Constructor for the EM Class
 * Arguments	:
 *******************************************************************/
EMLearning::EMLearning(unsigned int NumClasses): MLearning(), m_EM(NumClasses, cv::EM::COV_MAT_GENERIC )
{
	Init_Members(NumClasses);

}


/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Initalize All Member Variables
 * Arguments	:
 *******************************************************************/
int EMLearning::Init_Members( unsigned int NumClasses )
{
	m_NumClasses = NumClasses;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Default Destructor
 * Return Type 	:
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Destructor for the EM Class
 * Arguments	:
 *******************************************************************/
EMLearning::~EMLearning()
{


}

/*****************************************************
 * Function	: EMLearning Copy Constructor
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
EMLearning::EMLearning(const EMLearning& rhsEMLearning ):MLearning( rhsEMLearning )
{
	Allocate( rhsEMLearning );
	Copy( rhsEMLearning );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 22, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
EMLearning& EMLearning:: operator=( const EMLearning& rhsEMLearning )
{
	Allocate( rhsEMLearning );
	Copy( rhsEMLearning );

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
int EMLearning::Allocate( const EMLearning& rhsEMLearning )
{

	m_ColHeader.resize( rhsEMLearning.m_ColHeader.size() );
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
int EMLearning::Copy( const EMLearning& rhsEMLearning )
{

	m_NumClasses	= rhsEMLearning.m_NumClasses;
	m_EM			= rhsEMLearning.m_EM;
	m_Labels 		= rhsEMLearning.m_Labels;
	m_LogLike 		= rhsEMLearning.m_LogLike;
	m_ProbMat 		= rhsEMLearning.m_ProbMat;
	m_Samples 		= rhsEMLearning.m_Samples;
	m_ColHeader 	= rhsEMLearning.m_ColHeader;
	m_FeatureLength	= rhsEMLearning.m_FeatureLength;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Train
 * Return Type 	: int
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Train the EM Class
 * Arguments	:
 *******************************************************************/
int EMLearning::Train( )
{
	m_Samples.convertTo(m_Samples, CV_32FC1);
	m_EM.train(m_Samples, m_LogLike, m_Labels, m_ProbMat);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Predict
 * Return Type 	: const cv::Vec2d
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Perform Prediction using the trained data
 * Arguments	: const cv::Mat Sample
 *******************************************************************/
const cv::Vec2d EMLearning::Predict( const cv::Mat Sample) const
{
	cv::Vec2d Response = m_EM.predict(Sample);

	return Response;
}


/*******************************************************************
 * Function Name: Write
 * Return Type 	: int
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Writes the EM Parameters
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
int EMLearning::Write( const fs::path fsPath) const
{
	fs::path ParentPath = fsPath.parent_path();

	if( fs::exists(ParentPath))
	{
		cv::FileStorage fStore;
		fStore.open( fsPath.string(), cv::FileStorage::WRITE);

		m_EM.write(fStore);

		fStore.release();
	}
	else
	{
		cerr << "Folder Path: " << ParentPath << " does not exist" << endl;
		throw ERR_INVALID_PATH;
	}


	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Load
 * Return Type 	: int
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Load the EM contains from the file
 * Arguments	: const fs::path fsPath
 *******************************************************************/
int EMLearning::Load( const fs::path fsPath)
{
	fs::path ParentPath = fsPath.parent_path();

	if( fs::exists(ParentPath))
	{
		const cv::FileStorage fStore( fsPath.string(), cv::FileStorage::READ);

		if(fStore.isOpened() )
		{
			const cv::FileNode &fn = fStore["StatModel.EM"];
			m_EM.read(fn);
		}
	}

	return EXIT_SUCCESS;
}
