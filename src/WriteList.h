/*
 * WriteList.h
 *
 *  Created on: Mar 12, 2014
 *      Author: hrushi
 */

#ifndef WRITELIST_H_
#define WRITELIST_H_

#include "WriteFile.h"
#include "Time.h"

template <class T>
class WriteList: public WriteFile
{

private:
	// Helper Function
	virtual int Copy( const WriteList& rhs );
	virtual int Allocate( const WriteList& rhs );

	vector<T> m_List;

protected:

public:
	WriteList(const vector<T>& List, const fs::path FilePath);
	virtual ~WriteList();


	// Copy Constructor
	WriteList( const WriteList<T>& rhsWriteList );

	// Assignment Operator
	WriteList<T>& operator=( const WriteList<T>& rhsWriteList );


	/**************************************************************
	 *           Virtual Functions
	 **************************************************************/
	virtual int WriteOut();
	virtual int WriteBanner();


};



/*******************************************************************
 * Function Name: WriteList
 * Return Type 	: None
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: const fs::path
 *******************************************************************/
template< typename T>
WriteList<T>::WriteList(const vector<T>& List, const fs::path FilePath):WriteFile(FilePath)
{

	m_List = List;

}


/*******************************************************************
 * Function Name: ~WriteList
 * Return Type 	: None
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
template< typename T>
WriteList<T>::~WriteList()
{
}

/*****************************************************
 * Function	: WriteList Copy Constructor
 * Date		: Mar 12, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
template< typename T>
WriteList<T>::WriteList(const WriteList<T>& rhs ):WriteFile(rhs)
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
template< typename T>
WriteList<T>& WriteList<T>:: operator=( const WriteList<T>& rhs )
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
template< typename T>
int WriteList<T>::Allocate( const WriteList& rhs )
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
template< typename T>
int WriteList<T>::Copy( const WriteList& rhs )
{

	WriteFile::operator =(rhs);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: WriteOut
 * Return Type 	: int
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Performs the Writeout function
 * Arguments	:
 *******************************************************************/
template< typename T>
int WriteList<T>::WriteOut( )
{

	WriteBanner();

	for(auto ListEntry : m_List)
	{
		string Str = StringOp<T>::GetString(ListEntry);
		WriteLine(Str);
	}

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Write the banner
 * Arguments	:
 *******************************************************************/
template< typename T>
int WriteList<T>::WriteBanner( )
{

	std::stringstream ss;
	Time TClass;

	ss << "# " << STARS << STARS << endl;
	ss << "# List file " << endl;
	ss << "# Description: Contains list of all elements in the vector" << endl;
	ss << "# Last Updated On : " << TClass.GetCurrentTime()  << endl;
	ss << "# " << STARS << STARS << endl;

	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	return EXIT_SUCCESS;
}



#endif /* WRITELIST_H_ */
