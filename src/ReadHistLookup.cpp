/*
 * ReadHistLookup.cpp
 *
 *  Created on: Mar 9, 2013
 *      Author: hrushi
 */

#include "ReadHistLookup.h"



/**********************************************************************
 * Function Name: Default Constructor
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		:
 * Args			:
 **********************************************************************/
ReadHistLookup::ReadHistLookup(string sPath) : ReadFile(sPath)
{

	try
	{
		ReadIn();
	}
	catch(unsigned int err )
	{
		cerr << "Error Reading Look Up File" << endl;
		throw err;
	}

}


/**********************************************************************
 * Function Name: Comman distructor
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		:
 * Args			:
 **********************************************************************/
ReadHistLookup::~ReadHistLookup()
{

}


/**********************************************************************
 * Function Name: ReadHistLookup
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ReadHistLookup::ReadHistLookup( const ReadHistLookup& rhsReadHistLookup ): ReadFile(rhsReadHistLookup)
{
	Allocate_ReadHistLookup( rhsReadHistLookup );
	Copy_ReadHistLookup( rhsReadHistLookup );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
ReadHistLookup& ReadHistLookup :: operator=( const ReadHistLookup & rhsReadHistLookup )
{
	Allocate_ReadHistLookup( rhsReadHistLookup );
	Copy_ReadHistLookup( rhsReadHistLookup );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_ReadHistLookup
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int ReadHistLookup:: Copy_ReadHistLookup(  const ReadHistLookup & rhsReadHistLookup  )
{

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Allocate_ReadHistLookup
 * Date 		: Mar 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int ReadHistLookup:: Allocate_ReadHistLookup(  const ReadHistLookup & rhsReadHistLookup  )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ReadIn
 * Return Type 	: int
 * Created On	: Mar 9, 2013
 * Created By 	: hrushi
 * Comments		: Reads in the Lookup for the Histogram
 * Arguments	:
 *******************************************************************/
int ReadHistLookup::ReadIn( )
{

	cout << "Reading the Lookup File Now " << endl;
	Color RGB;

	string line;

	unsigned int iLineCount = 0;

	while( isGood() )
	{
		line = GetLine();
		iLineCount++;

		try
		{
			ReadLookUpLine(line);
		}
		catch( unsigned int err )
		{

			cerr << "Error Reading Line " << iLineCount  <<  " from " << m_FilePath << endl;
			throw( err );
		}
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ReadLookUpLine
 * Return Type 	: int
 * Created On	: Mar 10, 2013
 * Created By 	: hrushi
 * Comments		: Extracts the Color and Histogram information from the line,
 * 					and adds that to the Map
 * Arguments	: const string line
 *******************************************************************/
int ReadHistLookup::ReadLookUpLine( const string line )
{

	string NonWhiteSpace;
	NonWhiteSpace = StringOp<string>::GetNonWhiteSpace(0, line);

	KeyColor TempKey;
	ElevenSpaceHist ElevenSpc;

	if(NonWhiteSpace.size() > 0 )
	{
		char FirstChar = NonWhiteSpace.at(0);

		if( FirstChar == '#' )
		{
			cout << line << endl;
			return EXIT_SUCCESS;
		}
		else
		{
			std::istringstream iss;
			iss.str(line);

			try
			{
				iss >> TempKey;
				iss >> ElevenSpc;

				string strColor = TempKey.GetString();
				m_mapElHist[strColor] = ElevenSpc;
			}
			catch(unsigned int err )
			{
				cerr << "Error Reading Line from Look Up File " << endl;
				throw err;
			}
		}
	}
	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: GetVal
 * Return Type 	: ElevenSpaceHist
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: For the given color value, it will return its hist value
 * Arguments	: const Color& Img
 *******************************************************************/
ElevenSpaceHist ReadHistLookup::GetVal( const Color& Clr) const
{
	ElevenSpaceHist Val;

	Color EqClr = GetEqKeyColor( Clr );

	return Val;
}


/*******************************************************************
 * Function Name: GetEqKeyColor
 * Return Type 	: Color
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Returns the equivalent key color
 *
 * The lookup table has been arranged in such a way that every key value
 * is seprated by an OCTET ( 8 ), and it is offset by the value of 3.5.
 * This color conversion algorithm has been written by Pradyumna Kumar
 *
 * Arguments	: const Color& Clr
 *******************************************************************/
Color ReadHistLookup::GetEqKeyColor( const Color& Clr) const
{

	Color EqColor = ( Clr - ( Clr % LOOKUP_OCTET ) ) + 3.5; // See Comments above


	return EqColor;
}


/*******************************************************************
 * Function Name: GetHistVal
 * Return Type 	: vector<double>
 * Created On	: Mar 15, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: const Color& Clr
 *******************************************************************/
vector<double> ReadHistLookup::GetHistVal( const Color& Clr) const
{
	vector<double> RetHist;

	KeyColor TempClr;
	TempClr.Set(Clr.getRgb());

	string KeyStr = TempClr.GetString();

	try
	{
	ElevenSpaceHist ElHist =  m_mapElHist.at(KeyStr);
	RetHist = ElHist.m_Hist;
	}
	catch( const std::out_of_range &oor)
	{
		cerr << "Caught an Out of Range Exception when polling the map " << endl;
		cerr << "Check if the given color is an Equivalent Key Color " << endl;

		cerr << "Error in ReadHistLookup::GetHistVal" << endl;

		throw oor;
	}



	return RetHist;
}
