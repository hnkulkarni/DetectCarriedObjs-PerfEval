/*
 * File.h
 *
 *  Created on: Mar 9, 2013
 *      Author: hrushi
 *
 *      Abstract Base Class for reading and writing files.
 */

#ifndef FILE_H_
#define FILE_H_


#include "MyIncludes.h"
#include "CPPIncludes.h"
#include "OpenCV_Includes.h"
#include "Boost.h"
#include "StringOp.h"

const string SKIP_CHARS	= ",#";

class File {

protected:
	fs::path m_FilePath;

	File( const fs::path Path ); // This avoids all the base classed to be created without giving the name
	virtual ~File();

	// Copy Constructor
	File( const File& rhsFile );

	// Assignment Operator
	File& operator=( const File& rhsFile );

	// Helper Function
	int Copy_File( const File& rhsFile );
	int Allocate_File( const File& rhsFile );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int Open()  = 0; 	// Pure Virtual Function to Open a file
	virtual int Close() = 0; 	// Pure Virtual Function to Close a file.

public:

};

bool isSkipChar( const string Elem);




#endif /* FILE_H_ */
