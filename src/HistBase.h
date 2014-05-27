/*
 * HistBase.h
 *
 *  Created on: Mar 13, 2013
 *      Author: hrushi
 */

#ifndef HISTBASE_H_
#define HISTBASE_H_

class HistBase {

private:

	/**************************************************************
	 *           Private Member Functions
	 **************************************************************/
	int Copy_HistBase( const HistBase& rhsHistBase );
	int Allocate_HistBase( const HistBase& rhsHistBase );


public:

	/**************************************************************
	 *           House Keeping
	 **************************************************************/
	HistBase();
	virtual ~HistBase();

	// Copy Constructor
	HistBase( const HistBase& rhsHistBase );

	// Assignment Operator
	HistBase& operator=( const HistBase& rhsHistBase );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int AddCount() = 0;
};

#endif /* HISTBASE_H_ */
