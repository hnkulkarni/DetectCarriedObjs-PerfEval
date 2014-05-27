/*
 * WriteEM.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: hrushi
 */

#include "WriteEM.h"

WriteEM::WriteEM(const fs::path FilePath,  const EMLearning& EML ):WriteFile(FilePath)
{

	Init_Members(EML.GetColHeader());


	if( fs::exists(FilePath) )
	{
		WriteBanner();
	}


	WriteOut(EML);

}

WriteEM::~WriteEM()
{
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: WriteEM Copy Constructor
 * Date		: Jul 28, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
WriteEM::WriteEM(const WriteEM& rhsWriteEM ):WriteFile(rhsWriteEM)
{
	Allocate( rhsWriteEM );
	Copy( rhsWriteEM );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 28, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
WriteEM& WriteEM:: operator=( const WriteEM& rhsWriteEM )
{
	Allocate( rhsWriteEM );
	Copy( rhsWriteEM );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 28, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WriteEM::Allocate( const WriteEM& rhsWriteEM )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 28, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WriteEM::Copy( const WriteEM& rhsWriteEM )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: Initialize Member Variables
 * Arguments	: const vector<string>& vColHeaders
 *******************************************************************/
int WriteEM::Init_Members( const vector<string>& vColHeaders)
{

	m_vColHeaders = vColHeaders;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteOut
 * Return Type 	: int
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: This is a depricated function, and does not take any arguments
 * Arguments	:
 *******************************************************************/
int WriteEM::WriteOut( )
{

	cerr << "Please use the WriteOut( const EMLearning& EML) version " << endl;
	throw ERR_INVALID_ARGS;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteOut
 * Return Type 	: int
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: Writes the EM
 * Arguments	: const EMLearning& EML
 *******************************************************************/
int WriteEM::WriteOut( const EMLearning& EML)
{

	Mat Samples = EML.GetSamples().clone();
	Mat Labels = EML.GetLabels().clone();
	Mat PostProb = EML.GetPostProbs().clone();

	std::stringstream ss;

	for( int i = 0; i < Samples.rows; i++ )
	{
		ss << std::setprecision(5) << std::setw(7) <<  std::fixed << std::right;

		for( UINT j = 0; j < EML.GetFeatureLength(); j++)
		{
			ss << Samples.at<float>(i,j) << " \t ";
		}

		ss << Labels.at<int>(i) << " \t " << PostProb.at<double>(i);
		WriteLine(ss.str() );
		ss.str("");
		ss.clear();
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: Writes the Banner
 * Arguments	:
 *******************************************************************/
int WriteEM::WriteBanner( )
{

	std::stringstream ss;
	ss.str("");

	ss << "# " <<  STARS ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "EM Train File, contains the EM training information";
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");


	Time T;
	ss << "# Last Updated On : " << T.GetCurrentTime() ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column info" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	for( UINT i = 0; i < m_vColHeaders.size(); i++ )
	{
		ss << "Column " << i << ": " << m_vColHeaders.at(i);
		WriteLine(ss.str() );
		ss.clear();
		ss.str("");
	}

	ss << "# " << STARS << endl;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# ";
	for( auto Header : m_vColHeaders )
	{
		ss  << Header << " \t ";
	}

	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	return EXIT_SUCCESS;
}


