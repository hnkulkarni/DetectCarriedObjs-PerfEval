/*
 * ReadFile.cpp
 *
 *  Created on: Mar 9, 2013
 *      Author: hrushi
 */

#include "ReadFile.h"



/*******************************************************************
 * Function Name: Default Constructor
 * Return Type 	:
 * Created On	: Mar 9, 2013
 * Created By 	: hrushi
 * Comments		: This is the default constructor. Also initlaizes the base class
 * Arguments	: Boost Path to the FilePath
 *******************************************************************/
ReadFile::ReadFile(const fs::path sPath):File(sPath)
{

	Open();

}


/*******************************************************************
 * Function Name: Default Destructor
 * Return Type 	:
 * Created On	: Mar 9, 2013
 * Created By 	: hrushi
 * Comments		: This is the default destructor.
 * Arguments	:
 *******************************************************************/
ReadFile::~ReadFile()
{
	Close();
}


/**********************************************************************
 * Function Name: ReadFile
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ReadFile::ReadFile( const ReadFile& rhsReadFile ):File( rhsReadFile)   // It is necessary to add the base class in the Initializer List
{
	Allocate_ReadFile( rhsReadFile );
	Copy_ReadFile( rhsReadFile );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
ReadFile& ReadFile :: operator=( const ReadFile & rhsReadFile )
{
	Allocate_ReadFile( rhsReadFile );
	Copy_ReadFile( rhsReadFile );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_ReadFile
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int ReadFile:: Copy_ReadFile(  const ReadFile & rhsReadFile  )
{


	return EXIT_SUCCESS;
}





/**********************************************************************
 * Function Name: Allocate_ReadFile
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int ReadFile:: Allocate_ReadFile(  const ReadFile & rhsReadFile  )
{

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Open
 * Return Type 	: int
 * Created On	: Mar 9, 2013
 * Created By 	: hrushi
 * Comments		: Opens the file
 * Arguments	:
 *******************************************************************/
int ReadFile::Open( )
{

	m_ifPtr.exceptions( std::ifstream::failbit | std::ifstream::badbit );

	try
	{
		m_ifPtr.open(m_FilePath.string().c_str(), std::ifstream::in);
	}
	catch(std::ifstream::failure &e )
	{
		cerr << "Error Opening the File " << m_FilePath << " : " << e.what() << endl;
		throw ERR_CANNOT_OPEN_FILE ;
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Close
 * Return Type 	: int
 * Created On	: Mar 9, 2013
 * Created By 	: hrushi
 * Comments		: Close the File
 * Arguments	:
 *******************************************************************/
int ReadFile::Close( )
{
	if( m_ifPtr.is_open() )
	{

		m_ifPtr.exceptions(std::ifstream::failbit );
		try
		{
			m_ifPtr.close();
		}
		catch(std::ifstream::failure & e)
		{
			cerr << "Error Closing File " << m_FilePath << " : " << e.what() << endl;
			throw ERR_CLOSING_FILE;
		}

		//cout << "File: " << m_sPath << " Closed with success " << endl;
	}
	else
	{
		cout << "File not open to close " << endl;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetLine
 * Return Type 	: string
 * Created On	: Mar 10, 2013
 * Created By 	: hrushi
 * Comments		: Reads the line from the given file pointer
 * Arguments	:
 *******************************************************************/
string ReadFile::GetLine( )
{
	string line;

	try
	{
		getline( m_ifPtr, line);
	}
	catch(std::ifstream::failure &e )
	{
		if( m_ifPtr.eof() )
		{
			cout << "End of File Reached for: " << m_FilePath << endl;
			m_ifPtr.clear(std::ifstream::eofbit); // Clearning up this state, so that the pointer can be used by other functions
		}
		else
		{
			cerr << "Cannot read line from file " << m_FilePath << endl;
			throw(ERR_CANNOT_READ_VALUE);
		}
	}

	return line;
}

/*******************************************************************
 * Function Name: SkipComments
 * Return Type 	: int
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Skips empty lines and comments
 * Arguments	:
 *******************************************************************/
int ReadFile::SkipComments( )
{

	string line;
	bool bCommentStart 	= false;

	while(isGood() )
	{
		line = GetLine();
		const string NewWhiteSpace = StringOp<string>::GetNonWhiteSpace(0, line);

		if( NewWhiteSpace.length() == 0 )
		{
			continue;
		}

		char FirstChar = NewWhiteSpace.at(0);

		if( FirstChar == '#' )
		{
			cout << line << endl;

			char SecondChar = StringOp<string>::GetNonWhiteSpace(1, line).at(0);
			if( SecondChar == '*' )
			{
				if( bCommentStart == false )
				{
					bCommentStart = true;
				}
				else
				{
					break;
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
