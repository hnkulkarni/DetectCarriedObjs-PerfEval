/*
 * MapOp.h
 *
 *  Created on: Nov 17, 2013
 *      Author: hrushi
 */

#ifndef MAPOP_H_
#define MAPOP_H_

#include "CPPIncludes.h"
#include "VectorOp.h"

template<typename T>

class MapOp
{

	//---------- Private Variables ---------- //
private:


	//---------- Protected Variables ---------- //
protected:


	//---------- Public Variables  ---------- //
public:
	static int DeepCopy( T& mpLHS, const T& mpRHS);
	static int Print( const T& mp);

};

/*******************************************************************
 * Function Name: Print
 * Return Type 	: int
 * Created On	: Mar 10, 2014
 * Created By 	: hrushi
 * Comments		: Print Map Elements
 * Arguments	: const T& mp
 *******************************************************************/
template< typename T>
int MapOp<T>::Print( const T& mp)
{
	for(auto m : mp)
	{
		cout << m.first << " : " << m.second;
		cout << endl;
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: DeepCopy
 * Return Type 	: int
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Performs a Deep Copy of two maps
 * Arguments	: T& mpLHS, const T& mpRHS
 *******************************************************************/
template<typename T>
int MapOp<T>::DeepCopy( T& mpLHS, const T& mpRHS)
{

	for(auto srcEntry: mpRHS )
	{
		mpLHS[srcEntry.first] = srcEntry.second;
	}

	return EXIT_SUCCESS;
}



#endif /* MAPOP_H_ */
