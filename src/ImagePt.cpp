/*
 * ImagePt.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: hrushi
 */

#include "ImagePt.h"

ImagePt::ImagePt() {
	// TODO Auto-generated constructor stub

	Init();

}

ImagePt::~ImagePt() {
	// TODO Auto-generated destructor stub
}

/*******************************************************************
 * Function Name: ImagePt
 * Return Type 	:
 * Created On	: Sep 22, 2013
 * Created By 	: hrushi
 * Comments		: Overloaded constructor, to define a point
 * Arguments	: double x, double y
 *******************************************************************/
 ImagePt::ImagePt( double x, double y)
{
	 Pt.x = x;
	 Pt.y = y;
}

/*******************************************************************
 * Function Name: Init
 * Return Type 	: int
 * Created On	: Feb 20, 2013
 * Created By 	: hrushi
 * Comments		: Initializes
 * Arguments	:
 *******************************************************************/
int ImagePt::Init( )
{
	Pt.x = 0;
	Pt.y = 0;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: ImagePt
 * Date 		: Jan 4, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ImagePt::ImagePt( const ImagePt& rhsImagePt )
{
	Allocate_ImagePt( rhsImagePt );
	Copy_ImagePt( rhsImagePt );
}

/*******************************************************************
 * Function Name: ImagePt
 * Return Type 	:
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Copy constructor for the Image Pt
 * Arguments	: const cv::Point& Pt
 *******************************************************************/
 ImagePt::ImagePt( const cv::Point& rhsPt)
{
	 SetPoint(rhsPt);
}

/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 4, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
ImagePt& ImagePt :: operator=( const ImagePt & rhsImagePt )
{
	Allocate_ImagePt( rhsImagePt );
	Copy_ImagePt( rhsImagePt );

	return *this;
}

/*******************************************************************
 * Function Name: operator=
 * Return Type 	: ImagePt&
 * Created On	: Feb 20, 2013
 * Created By 	: hrushi
 * Comments		: Initializes the class if the rhs equal to zero
 * Arguments	: const int rhs
 *******************************************************************/
ImagePt& ImagePt::operator=( const int rhs)
{
	if( rhs == 0)
	{
		Init();
	}
	else
	{
		cout << "No function initialized for initializing ImagePt to " << rhs << endl;
		cout << "Please check" << endl;

		exit(ERR_TYPE_MISMATCH);
	}

	return *this;
}



/*******************************************************************
 * Function Name: operator=
 * Return Type 	: ImagePt&
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Assigns a Image Point from a given cv::Point
 * Arguments	: const cv::Point& rhsPt
 *******************************************************************/
ImagePt& ImagePt::operator=( const cv::Point& rhsPt)
{
	SetPoint(rhsPt);

	return *this;
}

/**********************************************************************
 * Function Name: Copy_ImagePt
 * Date 		: Jan 4, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int ImagePt:: Copy_ImagePt(  const ImagePt & rhsImagePt  )
{
	Pt = rhsImagePt.Pt;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_ImagePt
 * Date 		: Jan 4, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int ImagePt:: Allocate_ImagePt(  const ImagePt & rhsImagePt  )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: operator+
 * Return Type 	: return_type
 * Created On	: Jan 4, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
ImagePt ImagePt::operator+( const ImagePt& rhsImagePt ) const
{
	ImagePt TempPt;

	TempPt.Pt = Pt  + rhsImagePt.Pt;

	return TempPt;
}


/*******************************************************************
 * Function Name: operator+
 * Return Type 	: ImagePt
 * Created On	: May 1, 2013
 * Created By 	: hrushi
 * Comments		: Adds the given scalar to both X and Y co-ordinates
 * Arguments	: const double d
 *******************************************************************/
ImagePt ImagePt::operator+( const double d) const
{
	ImagePt TempPt;

	TempPt.Pt.x = TempPt.Pt.x + d;
	TempPt.Pt.y = TempPt.Pt.y + d;

	return TempPt;
}

/*******************************************************************
 * Function Name: operator+
 * Return Type 	: ImagePt
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Adds the given point with the given cv::Point
 * Arguments	: const cv::Point& rhsPt
 *******************************************************************/
ImagePt ImagePt::operator+( const cv::Point& rhsPt) const
{
	return Offset(rhsPt);
}

/*******************************************************************
 * Function Name: operator-
 * Return Type 	: ImagePt
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Subtracts two Image Point
 * Arguments	: const ImagePt& rhsImagePt
 *******************************************************************/
ImagePt ImagePt::operator-( const ImagePt& rhsImagePt) const
{
	ImagePt TempPt;

	TempPt.Pt = Pt - rhsImagePt.Pt;

	return TempPt;
}


/*******************************************************************
 * Function Name: operator-
 * Return Type 	: ImagePt
 * Created On	: May 1, 2013
 * Created By 	: hrushi
 * Comments		: Subtracts the scalar from the both co-ordinates X and Y
 * Arguments	: const double d
 *******************************************************************/
ImagePt ImagePt::operator-( const double d) const
{
	ImagePt TempPt;

	TempPt.Pt.x = (double)Pt.x - d;
	TempPt.Pt.y = (double)Pt.y - d;

	return TempPt;
}

/*******************************************************************
 * Function Name: operator/=
 * Return Type 	: int
 * Created On	: Jan 24, 2013
 * Created By 	: hrushi
 * Comments		: Divides and updates the pointer
 * Arguments	: const double d
 *******************************************************************/
ImagePt ImagePt::operator/( const double d) const
{
	ImagePt TempPt;

	TempPt.Pt.x = (double)Pt.x / d;
	TempPt.Pt.y = (double)Pt.y / d;

	return TempPt;
}



/*******************************************************************
 * Function Name: operator*
 * Return Type 	: ImagePt
 * Created On	: Sep 22, 2013
 * Created By 	: hrushi
 * Comments		: Multiplies Vector by that value
 * Arguments	: const double d
 *******************************************************************/
ImagePt ImagePt::operator*( const double d) const
{
	ImagePt TempPt;

	TempPt.Pt.x = (double)Pt.x * d;
	TempPt.Pt.y = (double)Pt.y * d;

	return TempPt;
}
/*******************************************************************
 * Function Name: operator ==
 * Return Type 	: bool
 * Created On	: May 5, 2013
 * Created By 	: hrushi
 * Comments		: Compares two Image Points and checkes if they are equal
 * Arguments	: const ImagePt& rhsImagePt
 *******************************************************************/
bool ImagePt::operator ==( const ImagePt& rhsImagePt) const
{
	bool decision(false);

	if( rhsImagePt.Pt.x == Pt.x )
	{
		if( rhsImagePt.Pt.y == Pt.y )
		{
			decision = true;
		}
		else
		{
			decision = false;
		}

	}
	else
	{
		decision = false;
	}

	return decision;
}


/*******************************************************************
 * Function Name: SwapXY
 * Return Type 	: int
 * Created On	: Feb 21, 2013
 * Created By 	: hrushi
 * Comments		: Swaps the value of X and Y
 * Arguments	:
 *******************************************************************/
int ImagePt::SwapXY( )
{

	cv::Point TempPt;
	TempPt.x	= Pt.x;
	Pt.x 		= Pt.y;
	Pt.y		= TempPt.x;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: std::ostream&
 * Created On	: Feb 21, 2013
 * Created By 	: hrushi
 * Comments		: For Overloading cout
 * Arguments	: const ImagePt& RHS
 *******************************************************************/
std::ostream& operator<<(std::ostream& out, const ImagePt& RHS )
{
	cv::Point TempPoint;
	TempPoint = RHS.GetPoint();
	out << "X: " << TempPoint.x << " Y: " << TempPoint.y;
	return out;
}


/*******************************************************************
 * Function Name: operator>>
 * Return Type 	: std::istream&
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Reads an Image Point from the file stream
 * Arguments	: std::istream& in, ImagePt& RHS
 *******************************************************************/
std::istream& operator>>( std::istream& in, ImagePt& RHS)
{

	vector<double> dPt;
	dPt.resize(2);

	in >> dPt;

	// If element is less than zero, set it to zero, else keep as it is; Images do not have values less than zero
	if( dPt.at(0) < 0 )
	{
		dPt.at(0) = 0;
	}

	if( dPt.at(1) < 0 )
	{
		dPt.at(1) = 0;
	}


	RHS.Set_X( int(dPt.at(0)) );
	RHS.Set_Y( int(dPt.at(1)) );

	return in;
}
/*******************************************************************
 * Function Name: Distance
 * Return Type 	: double
 * Created On	: Jan 7, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the distance of the current point to the given point
 * Arguments	: const ImagePt& Pt2
 *******************************************************************/
double ImagePt::Distance( const ImagePt& Pt2 ) const
{
	double dist = 0;

	dist = pow((double)(Pt.x - Pt2.Pt.x), 2 ) + pow((double)(Pt.y - Pt2.Pt.y), 2 );
	dist = sqrt(dist);

	return dist;
}


/*******************************************************************
 * Function Name: Dot
 * Return Type 	: double
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Dot Product between two points
 * Arguments	: const ImagePt& Pt2
 *******************************************************************/
double ImagePt::Dot ( const ImagePt& Pt2) const
{
	double DotProd(0);

	DotProd = Pt.dot( Pt2.Pt );

	return DotProd;
}

/*******************************************************************
 * Function Name: Slope
 * Return Type 	: double
 * Created On	: Apr 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the slope of the line connecting the given point to this point.
 * Arguments	: const ImagePt& Pt2
 *******************************************************************/
double ImagePt::Slope( const ImagePt& Pt2) const
{
	return (double)( Pt2.GetY() - Pt.y ) / ( Pt2.GetX() - Pt.x );
}


/*******************************************************************
 * Function Name: SlopeAngle
 * Return Type 	: double
 * Created On	: Apr 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the angle subtended by this line with the positive x-axis
 * Arguments	:
 *******************************************************************/
double ImagePt::SlopeAngle( const ImagePt& Pt2 ) const
{
	return atan( Slope(Pt2) );
}

/*******************************************************************
 * Function Name: GetUnit
 * Return Type 	: const ImagePt
 * Created On	: Aug 5, 2013
 * Created By 	: hrushi
 * Comments		: Returns the unit vector
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
const ImagePt ImagePt::GetUnit( const ImagePt& Pt ) const
{
	ImagePt DiffPt = Pt - *this;
	double dDist = Distance(Pt);
	ImagePt Unit = DiffPt / dDist;

	return Unit;
}


/*******************************************************************
 * Function Name: YCompliment
 * Return Type 	: int
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: Compliments the value of Y from the number or Rows
 * Arguments	: int NumRows
 *******************************************************************/
int  ImagePt::YCompliment( int NumRows)
{

	Pt.y = NumRows - Pt.y;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: XCompliment
 * Return Type 	: int
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: Compliments the value of X from the number of cols
 * Arguments	: int NumCols
 *******************************************************************/
int ImagePt::XCompliment( int NumCols)
{

	Pt.x = NumCols - Pt.x;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Offset
 * Return Type 	: int
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Offset the given point with respect to the other
 * Arguments	: const cv::Point& rhsPt
 *******************************************************************/
const ImagePt ImagePt::Offset( const cv::Point& rhsPt) const
{
	ImagePt TempPt(rhsPt);
	TempPt = TempPt + *this;

	return TempPt;
}
