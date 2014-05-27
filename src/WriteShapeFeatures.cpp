/*
 * WriteShapeFeatures.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: hrushi
 */

#include "WriteShapeFeatures.h"

/*******************************************************************
 * Function Name: WriteShapeFeatures
 * Return Type 	: None
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Default Constructor
 * Arguments	:
 *******************************************************************/
WriteShapeFeatures::WriteShapeFeatures(const fs::path fsPath ):WriteFile(fsPath)
{
	if( fs::exists(fsPath) )
	{
		WriteBanner();
	}
}


/*******************************************************************
 * Function Name: ~WriteShapeFeatures
 * Return Type 	: None
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Default Destructor
 * Arguments	: None
 *******************************************************************/
WriteShapeFeatures::~WriteShapeFeatures()
{

	WriteOut();

}


/*****************************************************
 * Function	: WriteShapeFeatures Copy Constructor
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
WriteShapeFeatures::WriteShapeFeatures(const WriteShapeFeatures& rhs ):WriteFile( rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
WriteShapeFeatures& WriteShapeFeatures:: operator=( const WriteShapeFeatures& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WriteShapeFeatures::Allocate( const WriteShapeFeatures& rhs )
{

	m_Queue.resize(rhs.m_Queue.size() );

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WriteShapeFeatures::Copy( const WriteShapeFeatures& rhs )
{

	for(unsigned int i = 0; i < rhs.m_Queue.size(); i++ )
	{
		m_Queue.at(i) = rhs.m_Queue.at(i);
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteOut
 * Return Type 	: int
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Writes the strings
 * Arguments	:
 *******************************************************************/
int WriteShapeFeatures::WriteOut( )
{

	for(unsigned int i = 0; i < m_Queue.size(); i++ )
	{
		WriteLine( m_Queue.at(i));
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Writes the Banner
 * Arguments	:
 *******************************************************************/
int WriteShapeFeatures::WriteBanner( )
{

	std::stringstream ss;

	ss << "# " << STARS << STARS ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Shape Features Feature File " ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Description: Contains Hu Moments for regions";
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	Time T;
	ss << "# Last Updated On : " << T.GetCurrentTime() ;
	WriteLine(ss.str() );

	ss << "# Column info" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 1: Hu0" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 2: Hu1" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 3: ..." ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");


	ss << "# Column 7: Hu6" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# " << STARS << STARS;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: AddToWriteQue
 * Return Type 	: int
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Adds the given feature to the write queue
 * Arguments	: const VDOUBLE& Feature
 *******************************************************************/
int WriteShapeFeatures::AddToWriteQue( const VDOUBLE& Feature)
{
	std::stringstream ss;
	ss << Feature;
	string TempLine = ss.str();

	m_Queue.push_back(TempLine);

	return EXIT_SUCCESS;
}
