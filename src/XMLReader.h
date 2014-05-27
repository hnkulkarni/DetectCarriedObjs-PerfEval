/*
 * XMLReader.h
 *
 *  Created on: Mar 3, 2014
 *      Author: hrushi
 */

#ifndef XMLREADER_H_
#define XMLREADER_H_

#include "pugixml.hpp"
#include "ProjectIncludes.h"

class XMLReader
{

private:
	// Helper Function
	virtual int Copy( const XMLReader& rhs );
	virtual int Allocate( const XMLReader& rhs );

protected:
	fs::path m_FilePath;
	pugi::xml_document m_XMLFile;

public:
	XMLReader(const fs::path FilePath);
	virtual ~XMLReader();

	// Copy Constructor
	XMLReader( const XMLReader& rhsXMLReader );

	// Assignment Operator
	XMLReader& operator=( const XMLReader& rhsXMLReader );


/**************************************************************
 *           Static Functions
 **************************************************************/

/**************************************************************
 *           Get Functions
 **************************************************************/
	const fs::path GetFilePath() const { return m_FilePath; }
};

#endif /* XMLREADER_H_ */
