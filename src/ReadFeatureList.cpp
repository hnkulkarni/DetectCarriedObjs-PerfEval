/*
 * ReadFeatureList.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: hrushi
 */

#include "ReadFeatureList.h"

/*******************************************************************
 * Function Name: ReadFeatureList
 * Return Type 	: None
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Default Constructor
 * Arguments	:
 *******************************************************************/
ReadFeatureList::ReadFeatureList( const fs::path fsPath):ReadFile(fsPath)
{


}

/*******************************************************************
 * Function Name: ~ReadFeatureList
 * Return Type 	: None
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Default Destructor
 * Arguments	: None
 *******************************************************************/
ReadFeatureList::~ReadFeatureList()
{

}

/*****************************************************
 * Function	: ReadFeatureList Copy Constructor
 * Date		: Oct 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ReadFeatureList::ReadFeatureList(const ReadFeatureList& rhs ):ReadFile(rhs)
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
ReadFeatureList& ReadFeatureList:: operator=( const ReadFeatureList& rhs )
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
int ReadFeatureList::Allocate( const ReadFeatureList& rhs )
{

	m_FeatureList.resize( rhs.m_FeatureList.size() );

	for(unsigned int i = 0; i < rhs.m_FeatureList.size(); i++ )
	{
		m_FeatureList.at(i).resize( m_FeatureList.at(i).size());
	}

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
int ReadFeatureList::Copy( const ReadFeatureList& rhs )
{
	ReadFile::operator =( rhs );

	for(unsigned int i = 0; i < rhs.m_FeatureList.size(); i++ )
	{
		for( unsigned int j = 0; j < rhs.m_FeatureList.at(i).size(); j++ )
		{
			m_FeatureList.at(i).at(j) = rhs.m_FeatureList.at(i).at(j);
		}

	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadIn
 * Return Type 	: int
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Reads the list of features from the file and puts them into a vector< vector< double > >
 * Arguments	:
 *******************************************************************/
int ReadFeatureList::ReadIn( )
{
	SkipComments(); // Skips the comment lines.

	UINT uiLineNum(0);

	while(isGood() )
	{
		string line = GetLine();
		std::stringstream ss;
		ss.clear();
		ss.str("");

		ss.str(line);

		if(line.length() == 0 )
		{
			continue;
		}

		vector<double> TempFeature;
		ss >> TempFeature;

		uiLineNum++;

		// Create space for an empty vector
		m_FeatureList.push_back(TempFeature);

		cout << ".";
		std::flush(cout);

		if( (uiLineNum % 100) == 0 )
		{
			cout << "\n Line " << uiLineNum  << endl;
		}

	}

	return EXIT_SUCCESS;
}



