/*
 * WriteEM.h
 *
 *  Created on: Jul 28, 2013
 *      Author: hrushi
 */

#ifndef WRITEEM_H_
#define WRITEEM_H_

#include "WriteFile.h"
#include "ProjectIncludes.h"

#include "EMLearning.h"

class WriteEM: public WriteFile
{

private:
	// Helper Function
	virtual int Copy( const WriteEM& rhsWriteEM );
	virtual int Allocate( const WriteEM& rhsWriteEM );

	virtual int Init_Members(const vector<string>& vColHeaders );


	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int WriteOut();
	virtual int WriteOut( const EMLearning& EML);
	virtual int WriteBanner();

protected:

	vector<string> m_vColHeaders;

public:
	WriteEM(const fs::path FilePath, const EMLearning& EML );
	virtual ~WriteEM();

	// Copy Constructor
	WriteEM( const WriteEM& rhsWriteEM );

	// Assignment Operator
	WriteEM& operator=( const WriteEM& rhsWriteEM );


};

#endif /* WRITEEM_H_ */
