/*
 * Color.cpp
 *
 *  Created on: Jan 9, 2013
 *      Author: hrushi
 */

#include "Color.h"

Color::Color() {
	// TODO Auto-generated constructor stub

}

Color::~Color() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: Color
 * Date 		: Jan 9, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
Color::Color( const Color& rhsColor )
{
	Allocate_Color( rhsColor );
	Copy_Color( rhsColor );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 9, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
Color& Color :: operator=( const Color & rhsColor )
{
	Allocate_Color( rhsColor );
	Copy_Color( rhsColor );

	return *this;
}

/*******************************************************************
 * Function Name: operator=
 * Return Type 	: Color&
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Assignes the Vec3b from the image to the color
 * Arguments	: const cv::Vec3b vec
 *******************************************************************/
Color& Color::operator=( const cv::Vec3b vec)
{
	Set(vec.val[0], vec.val[1], vec.val[2] );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Color
 * Date 		: Jan 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int Color:: Copy_Color(  const Color & rhsColor  )
{
	RGB = rhsColor.RGB;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_Color
 * Date 		: Jan 9, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int Color:: Allocate_Color(  const Color & rhsColor  )
{


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Set
 * Return Type 	: int
 * Created On	: Mar 15, 2013
 * Created By 	: hrushi
 * Comments		: Sets the RGB color
 * Arguments	: const cv::Vec3d& vec
 *******************************************************************/
int Color::Set( const cv::Vec3d& vec)
{
	return Set(vec[0], vec[1], vec[2] );
}

/*******************************************************************
 * Function Name: Set
 * Return Type 	: int
 * Created On	: Mar 10, 2013
 * Created By 	: hrushi
 * Comments		: Sets the RGB Color
 * Arguments	: unsigned int R, unsigned int G, unsigned int B
 *******************************************************************/
int Color::Set( double R, double G, double B)
{
	RGB.val[0] = R;
	RGB.val[1] = G;
	RGB.val[2] = B;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: operator>>
 * Return Type 	: std::istream
 * Created On	: Mar 10, 2013
 * Created By 	: hrushi
 * Comments		: Reads the RGB Values from the iStream Pointer
 * Arguments	: std::istream& in, Color& C
 *******************************************************************/
std::istream& operator>>( std::istream& in, Color& C )
{

	vector<double> ColorVal;
	ColorVal.resize(3);

	try
	{
		in >> ColorVal;
	}
	catch(int err )
	{
		if( err == ERR_CANNOT_READ_VALUE )
		{
			cerr << "Cannot read Color Values from File " << endl;
			exit(ERR_CANNOT_READ_VALUE);
		}
		else
		{
			throw err;
		}

	}

	C.Set(ColorVal.at(0), ColorVal.at(1), ColorVal.at(2) );

	return in;
}




/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: std::ostream&
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Color values on the screen
 * Arguments	: std::ostream& out, const Color& C
 *******************************************************************/
std::ostream&  operator<<( std::ostream& out, const Color& C )
{

	Vec3d Val = C.getRgb();

	out << "RGB: ";

	for( unsigned int i = 0; i < 3; i++ )
	{
		out << Val.val[i] << " ";
	}

	return out;
}


/*******************************************************************
 * Function Name: operator%
 * Return Type 	: Color&
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Performs the Modulus operator on the Color
 * Arguments	: const double d
 *******************************************************************/
Color Color::operator%( int d) const
{
	Color RetColor;

	int ChVal;

	for( unsigned int i = 0; i < 3; i++ )
	{
		ChVal = RGB.val[i]; // Converting from double to int, because modulus operator is defined only over ints
		RetColor.RGB.val[i] = ChVal % d;
	}

	return RetColor;
}



/*******************************************************************
 * Function Name: operator-
 * Return Type 	: Color
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Performs Subtraction of Two Colors
 * Arguments	: const Color& Clr
 *******************************************************************/
Color Color::operator-( const Color& Clr) const
{
	Color RetColor;

	for(unsigned int i = 0; i < 3; i++)
	{
		RetColor.RGB.val[i] = RGB.val[i] - Clr.RGB.val[i];
	}

	return RetColor;
}

/*******************************************************************
 * Function Name: operator-
 * Return Type 	: Color
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Subtracts a fixed value from all three channels
 * Arguments	: const double d
 *******************************************************************/
Color Color::operator-( const double d) const
{
	Color RetColor;

	for( unsigned int i = 0; i < 3; i++ )
	{
		RetColor.RGB.val[i] = RGB.val[i] - d;
	}

	return RetColor;
}

/*******************************************************************
 * Function Name: operator+
 * Return Type 	: Color
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Adds two Colors
 * Arguments	: const Color& Clr
 *******************************************************************/
Color Color::operator+( const Color& Clr) const
{
	Color RetColor;

	for( unsigned int i = 0; i < 3; i++ )
	{
		RetColor.RGB.val[i] = RGB.val[i] + Clr.RGB.val[i];
	}

	return RetColor;
}


/*******************************************************************
 * Function Name: operator+
 * Return Type 	: Color
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Adds a fixed value to the Color
 * Arguments	: const double d
 *******************************************************************/
Color Color::operator+( const double d) const
{
	Color RetColor;

	for(unsigned int i = 0; i < 3; i++ )
	{
		RetColor.RGB.val[i] = RGB.val[i] + d;
	}

	return RetColor;
}
