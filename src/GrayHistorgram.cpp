/*
 * Historgram.cpp
 *
 *  Created on: Jan 10, 2013
 *      Author: hrushi
 */

#include "GrayHistorgram.h"

GrayHistorgram::GrayHistorgram()
{
	Hist.resize(MAX_GRAY_VALUE + 1); // Added +1 because the number of gray values is 256


}

GrayHistorgram::~GrayHistorgram() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: Historgram
 * Date 		: Jan 10, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
GrayHistorgram::GrayHistorgram( const GrayHistorgram& rhsHistorgram )
{
	Allocate_Historgram( rhsHistorgram );
	Copy_Historgram( rhsHistorgram );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 10, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
GrayHistorgram& GrayHistorgram :: operator=( const GrayHistorgram & rhsHistorgram )
{
	Allocate_Historgram( rhsHistorgram );
	Copy_Historgram( rhsHistorgram );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Historgram
 * Date 		: Jan 10, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int GrayHistorgram:: Copy_Historgram(  const GrayHistorgram & rhsHistorgram  )
{
	Hist = rhsHistorgram.Hist;
	for( unsigned int i = 0; i < rhsHistorgram.Hist.size(); i++ )
	{
		Hist.at(i) = rhsHistorgram.Hist.at(i);
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Allocate_Historgram
 * Date 		: Jan 10, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int GrayHistorgram:: Allocate_Historgram(  const GrayHistorgram & rhsHistorgram  )
{
	Hist.resize( rhsHistorgram.Hist.size() );

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: IncrementCount
 * Return Type 	: int
 * Created On	: Jan 12, 2013
 * Created By 	: hrushi
 * Comments		: Increments counts of the given gray value
 * TODo			:
 *******************************************************************/
int GrayHistorgram::AddCount( const unsigned int GrayVal )
{
	Hist.at(GrayVal)++;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: std::ofstream&
 * Created On	: Jan 12, 2013
 * Created By 	: hrushi
 * Comments		: prints the histogram
 * TODo			:
 *******************************************************************/
std::ostream& operator<<( std::ostream& out, const GrayHistorgram& Hst )
{
	double BinCount = 0;

	for(const_HistItr itr = Hst.GetCountIteratorBegin(); itr != Hst.GetCountIteratorEnd(); itr++ )
	{
		out << *itr << " , ";
		BinCount++;
	}

	return out;
}


/*******************************************************************
 * Function Name: operator>>
 * Return Type 	: std::ostream&
 * Created On	: Feb 26, 2013
 * Created By 	: hrushi
 * Comments		: Read values into the histogram
 * Arguments	: std::ostream& in, Historgram& Hst
 *******************************************************************/
std::istream& operator>>( std::istream& in, GrayHistorgram& H)
{
	double dCount = 0;

	string str;
	StringOp<string> oStr;

	unsigned int iCurrentBin = 0;

	while(in.good())
	{
		string NonWhiteSpace;

		in >> str;
		NonWhiteSpace = oStr.GetNonWhiteSpace(0, str);

		if(NonWhiteSpace.size() > 0 )
		{
			char FirstChar = NonWhiteSpace.at(0);
			if( FirstChar == '#' )
			{
				continue;
			}
			else if( FirstChar == ',')
			{
				continue;
			}
			else
			{
				dCount = GetValueInType<double>(NonWhiteSpace);
				H.Hist.at(iCurrentBin) = dCount;

				iCurrentBin++;
			}
		}
	}

	return in;
}


/*******************************************************************
 * Function Name: NormalizeHist
 * Return Type 	: int
 * Created On	: Jan 13, 2013
 * Created By 	: hrushi
 * Comments		: Normalize the histogram from 0 to 1
 * TODo			:
 *******************************************************************/
int GrayHistorgram::Normalize()
{

	VectorOp <double>oVop;
	Hist = oVop.Normalize(Hist);

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Dot
 * Return Type 	: double
 * Created On	: Jan 13, 2013
 * Created By 	: hrushi
 * Comments		: Dot product of two histograms
 * TODo			:
 *******************************************************************/
double GrayHistorgram::Dot(const GrayHistorgram& rhsHist ) const
{

	VectorOp<double> oVop;
	double result = oVop.Dot(Hist, rhsHist.Hist);
	return result;
}



/*******************************************************************
 * Function Name: ZMUL
 * Return Type 	: int
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Zero Mean and Unit Length Histogram
 * Arguments	: const Args& args
 *******************************************************************/
int GrayHistorgram::ZMUL( )
{

	VectorOp<double> oVOP;
	vector<double> ZMULHist;
	ZMULHist.resize( Hist.size() );

	ZMULHist = oVOP.ZMUL(Hist);

	Hist.swap(ZMULHist);

	return EXIT_SUCCESS;
}
