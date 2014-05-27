/*
 * ReadPriorProb.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: hrushi
 */

#include "ReadPriorProb.h"

ReadPriorProb::ReadPriorProb(const fs::path FilePath):ReadFile(FilePath.string())
{
	try
	{
		ReadIn();
	}
	catch(unsigned int err )
	{
		cerr << "Cannot read the Prob file: " << m_FilePath << endl;
		throw err;
	}
}

ReadPriorProb::~ReadPriorProb()
{


}


/*****************************************************
 * Function	: ReadPriorProb Copy Constructor
 * Date		: Jul 15, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ReadPriorProb::ReadPriorProb(const ReadPriorProb& rhsReadPriorProb ):ReadFile( rhsReadPriorProb )
{
	Allocate( rhsReadPriorProb );
	Copy( rhsReadPriorProb );
}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 15, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ReadPriorProb& ReadPriorProb:: operator=( const ReadPriorProb& rhsReadPriorProb )
{
	Allocate( rhsReadPriorProb );
	Copy( rhsReadPriorProb );

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
int ReadPriorProb::Allocate( const ReadPriorProb& rhsReadPriorProb )
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
int ReadPriorProb::Copy( const ReadPriorProb& rhsReadPriorProb )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ReadIn
 * Return Type 	: int
 * Created On	: Jul 15, 2013
 * Created By 	: hrushi
 * Comments		: Reads in the Prior Probability values
 * Arguments	:
 *******************************************************************/
int ReadPriorProb::ReadIn( )
{
	unsigned int iLineCount = 0;
	string line;

	while( isGood() )
	{
		line = GetLine();
		iLineCount++;

		Readline( line );
	}
	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Readline
 * Return Type 	: int
 * Created On	: Jul 18, 2013
 * Created By 	: hrushi
 * Comments		: Reads bits from the string
 * Arguments	: const string line
 *******************************************************************/
int ReadPriorProb::Readline( const string line)
{
	string FirstWord = StringOp<string>::GetNonWhiteSpace(0, line);

	if(FirstWord.size() < 1 )
	{
		return EXIT_SUCCESS;
	}

	if(!FirstWord.compare("#") )
	{
		cout << line << endl;
		return EXIT_SUCCESS;
	}
	else if( !FirstWord.compare("Dragged_Obj") )
	{
		double Temp = GetValueInType<double>(1, line );
		m_PP.Set_PriorProb_DraggedObj(Temp);
	}
	else if(!FirstWord.compare("WornObj"))
	{
		double Temp = GetValueInType<double>(1, line );
		m_PP.Set_PriorProb_WornObj(Temp);

	}
	else if( !FirstWord.compare("Person"))
	{
		double Temp = GetValueInType<double>(1, line );
		m_PP.Set_PriorProb_PersonRgn(Temp);
	}
	else if( !FirstWord.compare("Location_Prior_ImgName"))
	{
		const string ImgName = StringOp<string>::GetNonWhiteSpace(1, line);
		const fs::path ProbImgFilepath = m_FilePath.parent_path().string() + "/" + ImgName;

		ProbImg pImgTemp(ProbImgFilepath);
		m_PP.Set_LocationPriorProb( pImgTemp );
	}

	return EXIT_SUCCESS;
}
