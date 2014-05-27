/*
 * ReadLists.h
 *
 *  Created on: Mar 12, 2014
 *      Author: hrushi
 */

#ifndef READLISTS_H_
#define READLISTS_H_

#include "ReadFile.h"

template<typename T>
class ReadLists: public ReadFile
{
private:
	// Helper Function
	virtual int Copy( const ReadLists& rhs );
	virtual int Allocate( const ReadLists& rhs );

protected:
	vector<T> m_List;

public:
	ReadLists(const fs::path& FilePath );
	virtual ~ReadLists();

	// Copy Constructor
	ReadLists( const ReadLists<T>& rhsReadLists );

	// Assignment Operator
	ReadLists<T>& operator=( const ReadLists<T>& rhsReadLists );


	/**************************************************************
	 *           Pure Virtual Function
	 **************************************************************/
	int ReadIn( );

	/**************************************************************
	 *           Get Methods
	 **************************************************************/
	vector<T> GetList() const {return m_List;}


};

/*******************************************************************
 * Function Name: ReadLists
 * Return Type 	: None
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
template<typename T>
ReadLists<T>::ReadLists(const fs::path& FilePath ):ReadFile(FilePath)
{
	ReadIn();
}



/*******************************************************************
 * Function Name: ~ReadLists
 * Return Type 	: None
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
template<typename T>
ReadLists<T>::~ReadLists()
{

}


/*****************************************************
 * Function	: ReadLists Copy Constructor
 * Date		: Mar 12, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
template<typename T>
ReadLists<T>::ReadLists(const ReadLists& rhs ):ReadFile(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Mar 12, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
template<typename T>
ReadLists<T>& ReadLists<T>:: operator=( const ReadLists& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Mar 12, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
template<typename T>
int ReadLists<T>::Allocate( const ReadLists& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Mar 12, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
template<typename T>
int ReadLists<T>::Copy( const ReadLists& rhs )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadIn
 * Return Type 	: int
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Read in the list in from the vector
 * Arguments	:
 *******************************************************************/
template<typename T>
int ReadLists<T>::ReadIn( )
{
	UINT uiLineNum(0);

	while(isGood() )
	{
		string line = GetLine();

		const string NewWhiteSpace = StringOp<string>::GetNonWhiteSpace(0, line);

		if( NewWhiteSpace.length() == 0 )
		{
			continue;
		}

		char FirstChar = NewWhiteSpace.at(0);

		if( FirstChar == '#' )
		{
			cout << line << endl;
			continue;
		}
		else if( isGood() )
		{
			T Elem = GetValueInType<T>(line);
			m_List.push_back(Elem);
			uiLineNum++;

		}
	}

	return EXIT_SUCCESS;
}


#endif /* READLISTS_H_ */
