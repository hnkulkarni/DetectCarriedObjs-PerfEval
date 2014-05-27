/*
 * Vector.h
 *
 *  Created on: Jan 25, 2013
 *      Author: hrushi
 */

#ifndef VECTOROP_H_
#define VECTOROP_H_

#include "CPPIncludes.h"
#include "MyIncludes.h"
#include "Boost.h"
#include "ImagePt.h"
#include "File.h"
#include "WriteList.h"

#include "StringOp.h"

template<typename T>

class VectorOp
{
	/**************************************************************
	 *           Private variables
	 **************************************************************/
private:



	/**************************************************************
	 *           Public Variables
	 **************************************************************/
public:
	int GetUniqueElem( vector<T>& Dest, const vector<T>& Src );
	vector<T> Normalize( const vector<T>& Src )const;
	T Dot(const vector<T>& V1, const vector<T>& V2 )const;
	static T GetMean(const vector<T>& Elem );
	double Length(const vector<T>& V) const;						//Finds the Length of the given vector
	vector<T> ZMUL(const vector<T> V) const;						//Zero Mean and Unit Length
	vector<T> GetZeroMean(const vector<T>& V) const;				// Return a zero Mean Data
	vector<T> GetUnitLength( const vector<T>& V) const;				// Returns a unit lenght data;
	int WriteVector(const string FilePath, const vector<T>& V, const unsigned int iNumRows, const unsigned int iNumCols ) const; // Writes the elements of the vector to a file
	static double Dist( const vector<T>& V1, const vector<T>& V2 ) ;
	static T GetMinVal( const vector<T>& V1);
	static T GetMaxVal( const vector<T>& V1);
	static T GetSTDev(const vector<T>& V1 );
	static int GetIndex( const vector<T>& V1, T Val);
	static int DeepCopy(vector< vector<T> >& lhs, const vector< vector<T> >& rhs);
	static int DeepCopy(vector<T>& lhs, const vector<T>& rhs);
	static T GetMedian( const vector<T>& V1);
	static int Archive(const vector<T>& eList, const fs::path ArchiveFilepath );
	static int SetAll(vector<T>& V1, const T SetVal);
};


/*******************************************************************
 * Function Name: SetAll
 * Return Type 	: int
 * Created On	: Apr 15, 2014
 * Created By 	: hrushi
 * Comments		: Sets all the elements in the vector as the given element
 * Arguments	: const T
 *******************************************************************/
template < typename T>
int VectorOp<T>::SetAll(vector<T>& V1,  const T SetVal)
{
	for(UINT i = 0; i < V1.size(); i++ )
	{
		V1.at(i) = SetVal;
	}

	return EXIT_SUCCESS;
}
/*******************************************************************
 * Function Name: GetMedian
 * Return Type 	: T
 * Created On	: Oct 27, 2013
 * Created By 	: hrushi
 * Comments		: Get the Median
 * Arguments	: const vector<T>& V1
 *******************************************************************/
template< typename T>
T VectorOp<T>::GetMedian( const vector<T>& V1)
{
	vector<T> V1Copy(V1);

	UINT CenterIdx = (double)V1.size() / 2;
	std::nth_element(V1Copy.begin(), V1Copy.begin() + CenterIdx, V1Copy.end() );

	T Median = *(V1Copy.begin() + CenterIdx);

	return Median;
}

/*******************************************************************
 * Function Name: GetSTDev
 * Return Type 	: T
 * Created On	: Oct 27, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Standard Deviation of the elements in a vector
 * Arguments	: const vector<T>& V1
 *******************************************************************/
template< typename T>
T VectorOp<T>::GetSTDev( const vector<T>& V1)
{
	T accum = 0.0;
	T mean = GetMean(V1);
	std::for_each (V1.begin(), V1.end(), [&](const T d) {
		accum += (d - mean) * (d - mean);
	});

	T Stdev = sqrt(accum / (V1.size()-1));

	return Stdev;
}

/*******************************************************************
 * Function Name: DeepCopy
 * Return Type 	: int
 * Created On	: Oct 11, 2013
 * Created By 	: hrushi
 * Comments		: Performs a deep copy
 * Arguments	: vector< vector<T> >& lhs, const vector< vector<T> >& rhs
 *******************************************************************/
template < typename T >
int VectorOp<T>::DeepCopy( vector< vector<T> >& lhs, const vector< vector<T> >& rhs)
{

	lhs.resize(rhs.size());

	for(unsigned int i = 0; i < rhs.size(); i++ )
	{
		vector<T> vTemp;
		vTemp.resize(rhs.at(i).size() );

		for(unsigned int j = 0; j < rhs.at(i).size(); j++)
		{
			vTemp.at(j) = rhs.at(i).at(j);
		}

	}


	return EXIT_SUCCESS;
}




/*******************************************************************
 * Function Name: DeepCopy
 * Return Type 	: int
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Deep copies a function
 * Arguments	: vector<T>& lhs, const vector<T>& rhs
 *******************************************************************/
template<typename T>
int VectorOp<T>::DeepCopy( vector<T>& lhs, const vector<T>& rhs)
{
	lhs.resize(rhs.size());

	for(UINT i = 0; i < rhs.size(); ++i)
	{
		lhs.at(i) = rhs.at(i);
	}

	return EXIT_SUCCESS;
}
/*******************************************************************
 * Function Name: GetIndex
 * Return Type 	: unsigned int
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Returns the index of first occarance of the value provided
 * Arguments	: const vector<T>& V1, T Val
 *******************************************************************/
template < typename T >
int  VectorOp<T>::GetIndex( const vector<T>& V1, T Val)
{
	unsigned int Indx;

	typename vector<T>::const_iterator itr = std::find( V1.begin(), V1.end(), Val );

	if( itr == V1.end() )
	{
		Indx = -1;
	}
	else
	{
		Indx = itr - V1.begin();
	}

	return Indx;
}



/*******************************************************************
 * Function Name: GetMaxVal
 * Return Type 	: T
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Returns the element with the least value from the vector
 * Arguments	: const vector<T>& V1
 *******************************************************************/
template< typename T >
T VectorOp<T>::GetMaxVal( const vector<T>& V1)
{
	T MaxVal;

	MaxVal = *std::max_element( V1.begin(), V1.end() );

	return MaxVal;
}

/*******************************************************************
 * Function Name: GetMinVal
 * Return Type 	: T
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Returns the element with the least value from the vector
 * Arguments	: const vector<T>& V1
 *******************************************************************/
template< typename T >
T VectorOp<T>::GetMinVal( const vector<T>& V1)
{
	T MinVal;

	MinVal = *std::min_element(V1.begin(), V1.end());

	return MinVal;
}
/*******************************************************************
 * Function Name: Dist
 * Return Type 	: double
 * Created On	: May 22, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the distance between these two vectors; Both the vectors must be of the same dimension
 * Arguments	: const vector<T>& V1, const vector<T>& V2
 *******************************************************************/
template< typename T >
double VectorOp<T>::Dist( const vector<T>& V1, const vector<T>& V2)
{
	double vDist(0);
	double V1V2(0);

	if( V1.size() != V2.size() )
	{
		cerr << "The size of V1 and V2 should be same for calculating distance " << endl;
		throw ERR_DIMENSION_MISMATCH;
	}
	else
	{

		for(unsigned int i = 0; i < V1.size(); i++ )
		{
			V1V2 = V1.at(i) - V2.at(i);
			vDist += V1V2 * V1V2;
		}
	}

	vDist = sqrt( vDist );

	return vDist;
}

/*******************************************************************
 * Function Name: operator/
 * Return Type 	: vector<T>
 * Created On	: Mar 15, 2013
 * Created By 	: hrushi
 * Comments		: Divide the vector by a scalar
 * Arguments	: double d
 *******************************************************************/
template< typename T >
vector<T> operator/( const vector<T>& vec, double d)
{
	vector<T> RetVal;
	RetVal.resize( vec.size() );

	for(unsigned int i = 0; i < vec.size(); i++ )
	{
		RetVal.at(i) = vec.at(i)/d;
	}

	return RetVal;
}


/*******************************************************************
 * Function Name: operator*
 * Return Type 	: vector<T>
 * Created On	: Mar 15, 2013
 * Created By 	: hrushi
 * Comments		: Divide the vector by a scalar
 * Arguments	: double d
 *******************************************************************/
template< typename T >
vector<T> operator*( const vector<T>& vec1, const vector<T>& vec2)
{
	if( vec1.size() != vec2.size() )
	{
		throw ERR_DIMENSION_MISMATCH;
	}


	vector<T> RetVal;
	RetVal.resize( vec1.size() );

	for(unsigned int i = 0; i < vec1.size(); i++ )
	{
		RetVal.at(i) = vec1.at(i) * vec2.at(i);
	}

	return RetVal;
}


/*******************************************************************
 * Function Name: operator+
 * Return Type 	: vector<T>
 * Created On	: Mar 15, 2013
 * Created By 	: hrushi
 * Comments		: Adds elements of two vectors
 * Arguments	: const vector<T>& v1, const vector<T>& v2
 *******************************************************************/
template<typename T>
vector<T> operator+( const vector<T>& v1, const vector<T>& v2 )
{
	vector<T> ResultVec;

	if( v1.size() != v2.size() )
	{
		cerr << "Size of two vectors needs to be equal to add them " << endl;
		throw ERR_DIMENSION_MISMATCH;
	}
	else
	{
		ResultVec.resize( v1.size() );

		for(unsigned int i = 0; i < v1.size(); i++ )
		{
			ResultVec.at(i) = v1.at(i) + v2.at(i);
		}
	}

	return ResultVec;
}

/*******************************************************************
 * Function Name: Write
 * Return Type 	: int
 * Created On	: Mar 2, 2013
 * Created By 	: hrushi
 * Comments		: Writes the values in the variable, defined by number of columns and rows
 * Arguments	: const string FilePath,
 *******************************************************************/
template< typename T >
int VectorOp<T>::WriteVector(const string FilePath, const vector<T>& V, const unsigned int iNumRows, const unsigned int iNumCols ) const
{
	fs::path bPath = FilePath;
	if( fs::exists(bPath) )
	{
		cerr << "File " << bPath.string() << " Exists " << endl;
		cerr << "Overwriting the File " << endl;
	}

	std::ofstream fPtr;
	fPtr.open( FilePath.c_str() );

	if( fPtr.is_open() )
	{
		cout << "File Opening Success " << endl;

		vector<int>::const_iterator itr = V.begin();
		for( unsigned int i = 0; i < iNumRows; i++ )
		{
			for( unsigned int j = 0; j < iNumCols; j++ )
			{
				fPtr <<  std::setw(2) << (*itr) << " ";
				itr++;
			}

			fPtr << endl;
		}
	}
	else
	{
		cerr << "Cannot Open File " << bPath.string() << endl;
		exit(ERR_CANNOT_OPEN_FILE);
	}

	if( fPtr.is_open() )
	{
		fPtr.close();
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetUnitLength
 * Return Type 	: vector<T>
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Unit Lenght version of the data
 * Arguments	: const vector<T> & V
 *******************************************************************/
template<typename T>
vector<T> VectorOp<T>::GetUnitLength( const vector<T> & V) const
{
	vector<T> vUL;
	vUL.resize(V.size());

	double Len = Length(V);
	for(unsigned int i = 0; i < V.size(); i++ )
	{
		vUL.at(i) = (double)V.at(i)/Len;
	}

	return vUL;
}
/*******************************************************************
 * Function Name: ZeroMean
 * Return Type 	: vector<T>
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Makes the data Zero Mean
 * Arguments	: const vector<T>& V
 *******************************************************************/
template< typename T >
vector<T> VectorOp<T>::GetZeroMean( const vector<T>& V) const
{
	vector<T> vZM;
	vZM.resize(V.size());

	// Make Data Zero mean
	double MeanVal = GetMean(V);
	for(unsigned int i = 0; i < V.size(); i++)
	{
		vZM.at(i) = V.at(i) - MeanVal;
	}

	return vZM;
}


/*******************************************************************
 * Function Name: ZMUL
 * Return Type 	: vector<T>
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Finds the Zero Meand and Unit Length of the given vector
 * Arguments	: const vector<T>& V
 *******************************************************************/
template< typename T >
vector<T> VectorOp<T>::ZMUL( const vector<T> V) const

{
	// Make Data Zero Mean
	vector<T> vZM;
	vZM.resize(V.size() );
	vZM = GetZeroMean(V);

	// Make Data Unit Length
	vector<T> vZMUL;
	vZMUL.resize(V.size());
	vZMUL = GetUnitLength(vZM);

	return vZMUL;
}


/*******************************************************************
 * Function Name: Length
 * Return Type 	: T
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Finds the Length of the vector
 * Arguments	: const vector<T>& V
 *******************************************************************/
template< typename T>
double VectorOp<T>::Length( const vector<T>& V) const
{
	double VectorLength = 0;

	for( unsigned int i = 0; i < V.size(); i++)
	{
		VectorLength += V.at(i) * V.at(i);
	}

	VectorLength = sqrt(VectorLength);

	return VectorLength;
}


/*************************************************************************************
 ********************* Functors ******************************************************
 *************************************************************************************/
template<typename T>
class FnGetMean{
protected:
	/**************************************************************
	 *           Protected Variables
	 **************************************************************/
	T CentroidVal;
	T SumVal;
	unsigned int Count;

public:

	/**************************************************************
	 *           Public Variables
	 **************************************************************/
	//Constructor
	FnGetMean(){
		CentroidVal = 0;
		SumVal = 0;
		Count = 0;
	}

	/*******************************************************************
	 * Function Name: operator()
	 * Return Type 	: T
	 * Created On	: Feb 20, 2013
	 * Created By 	: hrushi
	 * Comments		: Does the actual work of finding the Mean
	 * Arguments	: T Elem
	 *******************************************************************/
	T operator()( const T Elem)
	{
		Count = Count + 1;

		SumVal = SumVal + Elem;
		CentroidVal = SumVal / Count;

		return CentroidVal;

	}

	T GetVal()const {return CentroidVal;}

};

/*******************************************************************
 * Function Name: GetMean
 * Return Type 	: T
 * Created On	: Feb 20, 2013
 * Created By 	: hrushi
 * Comments		: Finds the Centoid. If the elemnt is a vector of
 * 				ImagePt then it will find the centroid of the contour defined.
 * Arguments	: const vector<T>& Elem
 *******************************************************************/
template<typename T>
T VectorOp<T>::GetMean( const vector<T>& Elem)
{
	FnGetMean<T> oFnGetMean;
	FnGetMean <T> oFnRet = std::for_each( Elem.begin(), Elem.end(), oFnGetMean);

	return oFnRet.GetVal();
}


/*******************************************************************
 * Function Name: Dot
 * Return Type 	: T
 * Created On	: Feb 11, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Dot Product of the Vector
 * Arguments	: const vector<T>& V1, const vector<T>& V2
 *******************************************************************/
template<typename T>
T VectorOp<T>::Dot( const vector<T>& V1, const vector<T>& V2 ) const
{
	if( V1.size() != V2.size() )
	{
		cout << "The two vectors are not of the same length " << endl;
		exit(ERR_DIMENSION_MISMATCH);
	}

	T Result = 0;
	typename vector<T>::const_iterator itr1, itr2;

	for(itr1 = V1.begin(), itr2 = V2.begin(); itr1 != V1.end(), itr2 != V2.end(); itr1++, itr2++ )
	{
		Result += (*itr1) * (*itr2);
	}

	return Result;
}


/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: std::ostream&
 * Created On	: Jan 26, 2013
 * Created By 	: hrushi
 * Comments		: Overloaded Operator for printing any vector on the screen
 * Arguments	: std::ostream& out, const vector<T>& vec
 *******************************************************************/
template<typename T>
std::ostream& operator<<( std::ostream& out, const vector<T>& vec)
{
	typename vector<T>::const_iterator itr;

	if( vec.size() > 100 ) //Length of string greater than 100 characters then hit enter
	{
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(out, "\n"));
	}
	else
	{
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(out, ", "));
	}

	return out;
}


/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: std::ostream&
 * Created On	: Oct 8, 2013
 * Created By 	: hrushi
 * Comments		: Operator for printing a vector of vectors
 * Arguments	: std::ostream& out, const vector< vector< T > >& vec
 *******************************************************************/
template<typename T>
std::ostream& operator<<( std::ostream& out, const vector< vector< T > >& vec)
{

	typename vector< vector<T> >::const_iterator itr;

	for( itr = vec.begin(); itr != vec.end(); itr++ )
	{
		out << (*itr);
		out << endl;
	}

	return out;
}


/*******************************************************************
 * Function Name: operator>>
 * Return Type 	: std::istream&
 * Created On	: Mar 11, 2013
 * Created By 	: hrushi
 * Comments		: Reads into the vector from the stream
 * Arguments	: std::istream& in, vector<T>& vec
 *******************************************************************/

template< typename T >
std::istream& operator>>( std::istream& in, vector<T>& vec)
{

	in.exceptions(std::istream::badbit | std::istream::failbit );
	string TempStr;
	unsigned int iValidField = 0;
	unsigned int RequiredFileds = vec.size();

	bool bTillEoFLine = false;

	if( RequiredFileds == 0 )
	{
		bTillEoFLine = true;
	}


	while(( iValidField < RequiredFileds ) || bTillEoFLine )
	{

		try
		{
			in >> TempStr;

			bool b = isSkipChar(TempStr);

			if(TempStr == "\n")
			{
				break;
			}

			if( b == true )
			{
				continue;
			}
			else
			{
				double Val = GetValueInType<double>( TempStr );

				try
				{
					vec.at(iValidField) = Val;
				}
				catch(const std::out_of_range& oor )
				{
					vec.push_back(Val);
				}

				iValidField++;
			}
		}
		catch(std::istream::failure &e)
		{
			if(in.eof() )
			{
				return in;
			}
			else
			{
				cout << "Cannot Read Value from File " <<  e.what() << endl;
				throw ERR_CANNOT_READ_VALUE;
			}
		}
	}

	return in;
}


/*******************************************************************
 * Function Name: GetUniqueElem
 * Return Type 	: int VectorOp<T>
 * Created On	: Jan 26, 2013
 * Created By 	: hrushi
 * Comments		: Returns the unique elements in the vector
 * Arguments	: vector<T>& Dest, const vector<T>& Src
 *******************************************************************/
template<typename T>
int VectorOp<T>::GetUniqueElem( vector<T>& Dest, const vector<T>& Src )
{

	vector<T> Temp;
	typename vector<T>::iterator it;

	Dest.resize( Src.size() );
	Temp.resize( Src.size() );

	std::copy(Src.begin(), Src.end(), Temp.begin() );
	std::sort(Temp.begin(), Temp.end() );

	it = std::unique_copy(Temp.begin(), Temp.end(), Dest.begin() );

	size_t NewSize = it - Dest.begin();

	Dest.resize(NewSize);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Normalize
 * Return Type 	: int
 * Created On	: Feb 11, 2013
 * Created By 	: hrushi
 * Comments		: Normalizes the length of the vector
 * Arguments	: const vector<T>& Src
 *******************************************************************/
template <typename T>
vector<T> VectorOp<T>::Normalize( const vector<T>& Src) const
{
	vector<T> Nrm;

	Nrm.resize( Src.size() );

	T max = *std::max_element( Src.begin(), Src.end() );

	typename vector<T>::iterator itrNrm = Nrm.begin();
	for(typename vector<T>::const_iterator itrSrc = Src.begin(); itrSrc != Src.end(); itrSrc++, itrNrm++)
	{
		*itrNrm = (T)*itrSrc/max;
	}

	return Nrm;
}


/*******************************************************************
 * Function Name: Archive
 * Return Type 	: T
 * Created On	: Mar 12, 2014
 * Created By 	: hrushi
 * Comments		: Save the list in a archive
 * Arguments	: const fs::path& FilePath
 *******************************************************************/
template<typename T>
int VectorOp<T>::Archive( const vector<T>& eList, const fs::path ArchiveFilepath)
{

	cout << "Saving List at " << ArchiveFilepath << endl;
	WriteList<T> WL(eList, ArchiveFilepath);
	WL.WriteOut();

	return EXIT_SUCCESS;
}


#endif /* VECTOR_H_ */
