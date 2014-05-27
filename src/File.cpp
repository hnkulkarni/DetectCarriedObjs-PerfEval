/*
 * File.cpp
 *
 *  Created on: Mar 9, 2013
 *      Author: hrushi
 */

#include "File.h"





File::File( const fs::path Path )
{
	m_FilePath  = Path;
}

File::~File()
{
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: File
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
File::File( const File& rhsFile )
{
	Allocate_File( rhsFile );
	Copy_File( rhsFile );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
File& File :: operator=( const File & rhsFile )
{
	Allocate_File( rhsFile );
	Copy_File( rhsFile );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_File
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int File:: Copy_File(  const File & rhsFile  )
{

	m_FilePath = rhsFile.m_FilePath;

	return EXIT_SUCCESS;
}





/**********************************************************************
 * Function Name: Allocate_File
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int File:: Allocate_File(  const File & rhsFile  )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: isSkipChar
 * Return Type 	: bool
 * Created On	: Mar 10, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given string belong to the list of ckipchars
 * Arguments	: const T& Elem
 *******************************************************************/
bool isSkipChar( const string Elem)
{
	string CmprStr;

	for(unsigned int i = 0; i < SKIP_CHARS.length(); i++ )
	{
		CmprStr = SKIP_CHARS.at(i);

		if( CmprStr.compare(Elem) == 0 )
		{
			return true;
		}
	}

	return false;
}




