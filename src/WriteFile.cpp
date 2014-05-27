/*
 * WriteFile.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: hrushi
 *
 *      Abstract Class for Writing the File
 */

#include "WriteFile.h"

/*******************************************************************
 * Function Name: WriteFile
 * Return Type 	:
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Default Constructor
 * Arguments	: const string
 *******************************************************************/
WriteFile::WriteFile(const fs::path fsPath):File(fsPath)
{

	if( fsPath.empty() )
	{
		cout << "Path Empty: " << fsPath << endl;

	}
	else
	{
		//Set the Exceptions for the File Pointer
		m_ofPtr.exceptions( std::ofstream::failbit | std::ofstream::badbit);
		Open();
	}
}

/*******************************************************************
 * Function Name: WriteFile
 * Return Type 	:
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Default Destructor
 * Arguments	:
 *******************************************************************/
WriteFile::~WriteFile()
{
	Close();
}

/*****************************************************
 * Function	: WriteFile Copy Constructor
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
WriteFile::WriteFile(const WriteFile& rhsWriteFile ):File(rhsWriteFile )
{
	Allocate( rhsWriteFile );
	Copy( rhsWriteFile );

}

/*****************************************************
 * Function	: operator =
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
WriteFile& WriteFile:: operator=( const WriteFile& rhsWriteFile )
{

	// Coping the parent class member variables.
	File::operator =(rhsWriteFile);

	Allocate( rhsWriteFile );
	Copy( rhsWriteFile );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WriteFile::Allocate( const WriteFile& rhsWriteFile )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WriteFile::Copy( const WriteFile& rhsWriteFile )
{

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Open
 * Return Type 	: int
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Opens the file
 * Arguments	:
 *******************************************************************/
int WriteFile::Open( )
{

	try
	{
		m_ofPtr.open( m_FilePath.string().c_str() );
		cout << "Success Opening " << m_FilePath << endl;
	}
	catch(const std::ofstream::failure & e)
	{
		cerr << "Error Opening File: " << endl;
		cerr << "Location: " << m_FilePath << endl;

		throw ERR_CANNOT_OPEN_FILE;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Close
 * Return Type 	: int
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Closes the File
 * Arguments	:
 *******************************************************************/
int WriteFile::Close( )
{

	if( m_ofPtr.is_open() )
	{
		try
		{
			m_ofPtr.close();
			cout << "Success Closing " << m_FilePath << endl;

		}
		catch( std::ofstream::failure &e )
		{
			cerr << "Error Closing File " << endl;
			cerr << "Location: " << m_FilePath << endl;

			throw ERR_CLOSING_FILE;
		}
	}
	else
	{
		cerr << "File not Open to Close " << endl;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteLine
 * Return Type 	: int
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Writes the line to the file
 * Arguments	: const string line
 *******************************************************************/
int WriteFile::WriteLine( const string line)
{

	try
	{
		m_ofPtr << line;
		m_ofPtr << endl;
	}
	catch(std::ofstream::failure &e)
	{
		cerr << "Cannot write line to file " << endl;
		cerr << "Line: " << line << endl;

		throw ERR_WRITING_TO_FILE;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteBanner_Time
 * Return Type 	: int
 * Created On	: Jul 18, 2013
 * Created By 	: hrushi
 * Comments		: Writes the Banner and the Time of file update
 * Arguments	:
 *******************************************************************/
int WriteFile::WriteBanner_Time( )
{

	Time T;
	std::stringstream ss;

	ss << "# " << STARS << STARS ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Last Updated On : " << T.GetCurrentTime() ;
	WriteLine(ss.str() );


	return EXIT_SUCCESS;
}
