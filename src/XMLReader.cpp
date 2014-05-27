/*
 * XMLReader.cpp
 *
 *  Created on: Mar 3, 2014
 *      Author: hrushi
 */

#include "XMLReader.h"

/*******************************************************************
 * Function Name: XMLReader
 * Return Type 	: None
 * Created On	: Mar 3, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: const fs::path
 *******************************************************************/
XMLReader::XMLReader(const fs::path FilePath)
{
	m_FilePath = FilePath;

	pugi::xml_parse_result result = m_XMLFile.load_file(FilePath.string().c_str());

	if(!result)
	{
		cerr << "XML " << m_FilePath << " Could not be loaded" << result.description() << endl;
		exit(ERR_CANNOT_OPEN_FILE);
	}

}

/*******************************************************************
 * Function Name: ~XMLReader
 * Return Type 	: None
 * Created On	: Mar 3, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
XMLReader::~XMLReader()
{

}

/*****************************************************
 * Function	: XMLReader Copy Constructor
 * Date		: Mar 3, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
XMLReader::XMLReader(const XMLReader& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Mar 3, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
XMLReader& XMLReader:: operator=( const XMLReader& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Mar 3, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int XMLReader::Allocate( const XMLReader& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Mar 3, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int XMLReader::Copy( const XMLReader& rhs )
{

	m_FilePath	= rhs.m_FilePath;

	return EXIT_SUCCESS;
}


