/*
 * WritePriorProbs.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: hrushi
 */

#include "WritePriorProbs.h"

WritePriorProbs::WritePriorProbs(const string FilePath ):WriteFile( FilePath )
{

	WriteBanner();

}

WritePriorProbs::~WritePriorProbs()
{

}

/*****************************************************
 * Function	: WritePriorProbs Copy Constructor
 * Date		: Jul 15, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
WritePriorProbs::WritePriorProbs(const WritePriorProbs& rhsWritePriorProbs ):WriteFile( rhsWritePriorProbs )
{
	Allocate( rhsWritePriorProbs );
	Copy( rhsWritePriorProbs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 15, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
WritePriorProbs& WritePriorProbs:: operator=( const WritePriorProbs& rhsWritePriorProbs )
{
	Allocate( rhsWritePriorProbs );
	Copy( rhsWritePriorProbs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 15, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WritePriorProbs::Allocate( const WritePriorProbs& rhsWritePriorProbs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 15, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WritePriorProbs::Copy( const WritePriorProbs& rhsWritePriorProbs )
{
	WriteFile::operator =( rhsWritePriorProbs );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteOut
 * Return Type 	: int
 * Created On	: Jul 15, 2013
 * Created By 	: hrushi
 * Comments		: Writes the Prior Probabilites at the given file location
 * Arguments	:
 *******************************************************************/
int WritePriorProbs::WriteOut( )
{

	if( m_PP.isValid() )
	{
		cout << "Writing Prior Probabilities " << endl;
		cout << m_PP;

		std::stringstream ss;
		ss << m_PP;
		WriteLine(ss.str() );
		ss.clear();
		ss.str("");



	}
	else
	{
		cerr << "Prior Probabilities do not sum to 1: See Below " << endl;
		cerr << m_PP;
		cerr << "Returning an Error" << endl;
		throw ERR_INVALID_ARGS;
	}


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: Jul 18, 2013
 * Created By 	: hrushi
 * Comments		: Writes the Banner for this Prior Prob File
 * Arguments	:
 *******************************************************************/
int WritePriorProbs::WriteBanner( )
{

	Time T;
	std::stringstream ss;

	ss << "# " << STARS << STARS ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Prior Probability " ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Description: Contains the Prior probability for Location based calculation. " << endl;
	ss << "\t This avoids the efforts of calculating values over and over."  << endl;
	ss << "\t If this file is accidently deleted it will force calculation " << endl;
	ss << "\t of the prior probabilites again, and write the file"           << endl;

	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Last Updated On : " << T.GetCurrentTime() ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# " << STARS << STARS ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	return EXIT_SUCCESS;
}
