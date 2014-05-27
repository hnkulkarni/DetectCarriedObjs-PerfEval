/*
 * ElevenSpaceHist.cpp
 *
 *  Created on: Mar 8, 2013
 *      Author: hrushi
 */

#include "ElevenSpaceHist.h"

ElevenSpaceHist::ElevenSpaceHist()
{

	m_Hist.resize(ELEVEN_HIST_SIZE);
}

ElevenSpaceHist::~ElevenSpaceHist()
{
	// TODO Auto-generated destructor stub
}


/**********************************************************************
 * Function Name: ElevenSpaceHist
 * Date 		: Mar 8, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ElevenSpaceHist::ElevenSpaceHist( const ElevenSpaceHist& rhsElevenSpaceHist )
{
	Allocate_ElevenSpaceHist( rhsElevenSpaceHist );
	Copy_ElevenSpaceHist( rhsElevenSpaceHist );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Mar 8, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
ElevenSpaceHist& ElevenSpaceHist :: operator=( const ElevenSpaceHist & rhsElevenSpaceHist )
{
	Allocate_ElevenSpaceHist( rhsElevenSpaceHist );
	Copy_ElevenSpaceHist( rhsElevenSpaceHist );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_ElevenSpaceHist
 * Date 		: Mar 8, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int ElevenSpaceHist:: Copy_ElevenSpaceHist(  const ElevenSpaceHist & rhsElevenSpaceHist  )
{

	vector<double>::iterator itrLHS = m_Hist.begin() ;

	for(vector<double>::const_iterator itrRHS (rhsElevenSpaceHist.m_Hist.begin() ); 	itrRHS != rhsElevenSpaceHist.m_Hist.end(); itrRHS++, itrLHS++ )
	{
		*itrLHS = *itrRHS;

	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Allocate_ElevenSpaceHist
 * Date 		: Mar 8, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int ElevenSpaceHist:: Allocate_ElevenSpaceHist(  const ElevenSpaceHist & rhsElevenSpaceHist  )
{

	m_Hist.resize(rhsElevenSpaceHist.m_Hist.size() );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: operator>>
 * Return Type 	: std::istream&
 * Created On	: Mar 11, 2013
 * Created By 	: hrushi
 * Comments		: Copies the 11 elements from the stream into the Eleven Space
 * Arguments	: std::istream& in, ElevenSpaceHist& ElSpc
 *******************************************************************/
std::istream& operator>>( std::istream& in, ElevenSpaceHist& ElSpc )
{
	ElSpc.m_Hist.resize(ELEVEN_HIST_SIZE);

	try
	{
		in >> ElSpc.m_Hist;
	}
	catch( unsigned int err )
	{
		cerr << "Cannot read values from file for Eleven Space Histogram " << endl;
		throw err;
	}

	return in;
}


/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: std::ostream&
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Histogram Values on the text
 * Arguments	: std::ostream& out, const ElevenSpaceHist& ElSpc
 *******************************************************************/
std::ostream& operator<<( std::ostream& out, const ElevenSpaceHist& ElSpc )
{
	out << ElSpc.m_Hist;
	return out;
}

/*******************************************************************
 * Function Name: AddCount
 * Return Type 	: int
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: const Color& Clr
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
int ElevenSpaceHist::AddCount( const Color& Clr, const ReadHistLookup& Lookup  )
{

	Color EqClr = Lookup.GetEqKeyColor(Clr);
	vector<double> ElHist = Lookup.GetHistVal(EqClr);

	m_Hist = m_Hist + ElHist;

	return EXIT_SUCCESS;
}




/*******************************************************************
 * Function Name: GetMatchScore
 * Return Type 	: double
 * Created On	: Mar 15, 2013
 * Created By 	: hrushi
 * Comments		: Get the MatchScore between two 11 space histograms: Pradyumna's algo
 * Arguments	: const ElevenSpaceHist& E2
 *******************************************************************/
double ElevenSpaceHist::GetMatchScore( const ElevenSpaceHist& E2) const
{


	double score(0);

	score = MatchScore_ClrMinMax(E2);

	return score;
}


/*******************************************************************
 * Function Name: MatchScore_ClrMinMax
 * Return Type 	: double
 * Created On	: Mar 30, 2013
 * Created By 	: hrushi
 * Comments		: Uses Pradyumna's Algo
 * Arguments	: const ElevenSpaceHist& E2
 *******************************************************************/
double ElevenSpaceHist::MatchScore_ClrMinMax( const ElevenSpaceHist& E2) const
{
	double score(0);

	double Numerator(0), Denominator(0);

	for( int i = 0; i < ELEVEN_HIST_SIZE; i++ )
	{
		Numerator   += MIN( m_Hist.at(i) , E2.m_Hist.at( i ));
		Denominator += MAX( m_Hist.at(i) , E2.m_Hist.at( i ));
	}

	score = Numerator/Denominator;

	return score;
}


/*******************************************************************
 * Function Name: ZMUL
 * Return Type 	: int
 * Created On	: Apr 2, 2013
 * Created By 	: hrushi
 * Comments		: Zero Mean and Unit Length Data
 * Arguments	:
 *******************************************************************/
int ElevenSpaceHist::ZMUL( )
{

	VectorOp<double> oVOP;
	vector<double> ZMULHist;
	ZMULHist.resize( m_Hist.size() );

	ZMULHist = oVOP.ZMUL(m_Hist);

	m_Hist.swap(ZMULHist);

	return EXIT_SUCCESS;
}
