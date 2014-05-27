/*
 * StringOp.h
 *
 *  Created on: Feb 4, 2013
 *      Author: hrushi
 */

#ifndef STRINGOP_H_
#define STRINGOP_H_

#include "CPPIncludes.h"
#include "MyIncludes.h"

template<typename T>

class StringOp
{
public:
	static T GetUpper( const T& element );
	static T GetNonWhiteSpace( const unsigned int index, const T& line );
	static const string GetString( const T& element );
	static const string GetString( const vector<T>& V1, const string dlimit);
	static const vector<string> GetString( const vector<T>& element );
	static const string GetString( const T& element, char cFill, UINT Width);
	static const vector<T> GetSplitParts(const string InputStr, const string SplitChars );
};

/*******************************************************************
 * Function Name: GetString
 * Return Type 	: const string
 * Created On	: Apr 15, 2014
 * Created By 	: hrushi
 * Comments		: Get the String equivalent
 * Arguments	: const vector<T>& V1, const string dlimit
 *******************************************************************/
template< typename T>
const string StringOp<T>::GetString( const vector<T>& V1, const string dlimit)
{
	string StrEq;

	std::stringstream ss;

	for(auto elem : V1)
	{
		ss << std::setw(12) << elem << dlimit;
	}

	StrEq = ss.str();

	ss.clear();
	ss.str("");

	return StrEq;
}


/*******************************************************************
 * Function Name: FirstNonWhiteSpace
 * Return Type 	: T
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Returns the <n>th non white space character
 * Arguments	: T
 *******************************************************************/
template<typename T>
T StringOp<T>::GetNonWhiteSpace(  const unsigned int index, const T& line )
{
	T NonWhiteSpace;
	std::istringstream iss;
	iss.str(line);

	for( unsigned int iCounter = 0; iCounter <= index; iCounter++ )
	{
		iss >> NonWhiteSpace;

		if( iCounter == index )
		{
			break;
		}

	}

	return NonWhiteSpace;
}


/*******************************************************************
 * Function Name: GetString
 * Return Type 	: string
 * Created On	: Feb 4, 2013
 * Created By 	: hrushi
 * Comments		: returns the string for the given recursive iterator
 * Arguments	: const T& type
 *******************************************************************/
template< typename T>
const string StringOp<T>::GetString( const T& element )
{
	std::stringstream ss;
	ss << element;
	string Temp = ss.str();

	return Temp;
}

/*******************************************************************
 * Function Name: GetString
 * Return Type 	: const vector<string>
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: Converts a vector of some elements into string
 * Arguments	: const vector<T>& elements
 *******************************************************************/
template<typename T>
const vector<string> StringOp<T>::GetString( const vector<T>& elements)
{
	vector<string> vStr;

	for(auto e : elements)
	{
		string str = GetString(e);
		vStr.push_back(str);
	}

	return vStr;
}




/*******************************************************************
 * Function Name: GetString
 * Return Type 	: const string
 * Created On	: Mar 8, 2014
 * Created By 	: hrushi
 * Comments		: Get the string in the format required
 * Arguments	: const T& element, char cFill, UINT Width
 *******************************************************************/
template< typename T>
const string StringOp<T>::GetString( const T& element, char cFill, UINT Width)
{
	std::stringstream ss;
	ss << std::setfill(cFill) << std::setw(Width) << element;
	string Temp = ss.str();
	return Temp;
}



/*******************************************************************
 * Function Name: GetUpper
 * Return Type 	: string
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Converts the given string to upper case
 * Arguments	: const T& element
 *******************************************************************/
template< typename T >
T StringOp<T>::GetUpper( const T& element)
{
	T Upper;
	Upper.resize( element.size() );
	std::transform(element.begin(), element.end(), Upper.begin(), ::toupper );

	return Upper;
}



/*******************************************************************
 * Function Name: GetValueInType
 * Return Type 	: RetType
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Extracts the type from the given string
 * Arguments	: const string& str, RetType& elem
 *******************************************************************/
 template<typename RetType>
 RetType GetValueInType(  const string& str)
 {
	 RetType elem;

	 std::istringstream iss;
	 iss.exceptions( std::ios::failbit | std::ios::badbit );

	 try
	 {
		 iss.str(str);
		 iss >> elem;
	 }
	 catch( const std::ios::failure &e )
	 {
		 cerr << "Cannot convert the string: " << str << " into the required datatype " << endl;
		 throw ERR_TYPE_MISMATCH;
	 }

	 return elem;
 }

 /*******************************************************************
  * Function Name: GetValueInType
  * Return Type 	: RetType
  * Created On	: Feb 24, 2013
  * Created By 	: hrushi
  * Comments		: Extracts the type from the given string
  * Arguments	: const string& str, RetType& elem
  *******************************************************************/
  template<typename RetType>
  RetType GetValueInType( unsigned int index,  const string& str)
  {
 	 const string Temp = StringOp<string>::GetNonWhiteSpace(index, str);
 	 RetType elem = GetValueInType<RetType>(Temp);

 	 return elem;
  }

  /*******************************************************************
   * Function Name: GetSplitParts
   * Return Type 	: const vector<string>
   * Created On	: Mar 7, 2014
   * Created By 	: hrushi
   * Comments		: Split the sptring into different parts using the SplitChars
   * Arguments	: const string InputStr, const string SplitChars
   *******************************************************************/
  template< typename T>
  const vector<T> StringOp<T>::GetSplitParts( const string InputStr, const string SplitChars)
  {
  	vector<string> strSplits;
  	boost::split(strSplits, InputStr, boost::is_any_of(SplitChars)  );

  	vector<T> RetSplits;
  	RetSplits.resize(strSplits.size());

  	for(UINT i = 0; i < strSplits.size(); i++ )
  	{
  		RetSplits.at(i) = GetValueInType<T>(strSplits.at(i));
  	}

  	return RetSplits;
  }

#endif /* STRINGOP_H_ */
