/*
 * ReadFile.h
 *
 *  Created on: Mar 9, 2013
 *      Author: hrushi
 */

#ifndef READFILE_H_
#define READFILE_H_

#include "File.h"

class ReadFile: public File
{

private:
	std::ifstream m_ifPtr;

protected:


	ReadFile(const fs::path sPath);
	virtual ~ReadFile();

	// Copy Constructor
	ReadFile( const ReadFile& rhsReadFile );

	// Assignment Operator
	ReadFile& operator=( const ReadFile& rhsReadFile );

	// Helper Function
	int Copy_ReadFile( const ReadFile& rhsReadFile );
	int Allocate_ReadFile( const ReadFile& rhsReadFile );

	/**************************************************************
	 *           Relative Functions
	 **************************************************************/
	virtual int Open();
	virtual int Close();
	virtual string GetLine();
	virtual int SkipComments();

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int ReadIn() = 0;

	/**************************************************************
	 *           Accessors
	 **************************************************************/
	bool isGood() const { return m_ifPtr.good(); }

public:

};


#endif /* READFILE_H_ */
