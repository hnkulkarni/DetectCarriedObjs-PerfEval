/*
 * WriteFile.h
 *
 *  Created on: Apr 10, 2013
 *      Author: hrushi
 */

#ifndef WRITEFILE_H_
#define WRITEFILE_H_

#include "File.h"
#include "Time.h"

class WriteFile: public File
{

private:
	std::ofstream m_ofPtr;

protected:
	/**************************************************************
	 *           Virtual Functions
	 **************************************************************/
	virtual int Open();
	virtual int Close();

	int WriteLine(const string line );
	int WriteBanner_Time();


public:
	WriteFile(const fs::path fsPath);
	virtual ~WriteFile();

	// Copy Constructor
	WriteFile( const WriteFile& rhsWriteFile );

	// Assignment Operator
	WriteFile& operator=( const WriteFile& rhsWriteFile );

	// Helper Function
	int Copy( const WriteFile& rhsWriteFile );
	int Allocate( const WriteFile& rhsWriteFile );



	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int WriteOut() = 0;
	virtual int WriteBanner() = 0;


	/**************************************************************
	 *           Accessors
	 **************************************************************/
	bool isGood() const { return m_ofPtr.good(); }

};

#endif /* WRITEFILE_H_ */
