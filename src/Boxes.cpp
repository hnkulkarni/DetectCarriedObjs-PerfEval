/*
 * Boxes.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#include "Boxes.h"

Boxes::Boxes() {
	// TODO Auto-generated constructor stub

}

Boxes::~Boxes() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: Boxes
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
Boxes::Boxes( const Boxes& rhsBoxes )
{
	Allocate_Boxes( rhsBoxes );
	Copy_Boxes( rhsBoxes );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
Boxes& Boxes :: operator=( const Boxes & rhsBoxes )
{
	Allocate_Boxes( rhsBoxes );
	Copy_Boxes( rhsBoxes );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Boxes
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int Boxes:: Copy_Boxes(  const Boxes & rhsBoxes  )
{
	TopLeft 	= rhsBoxes.TopLeft;
	BottomRight = rhsBoxes.BottomRight;
	RectDetect 	= rhsBoxes.RectDetect;
	Center		= rhsBoxes.Center;

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function Name: Allocate_Boxes
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int Boxes:: Allocate_Boxes(  const Boxes & rhsBoxes  )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: SetBoxRect
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Sets the Rect for the Box
 * Arguments	: const ImagePt Pt_TopLeft, const ImagePt Pt_BottomRight
 *******************************************************************/
int Boxes::SetBoxRect( const ImagePt Pt_TopLeft, const ImagePt Pt_BottomRight)
{
	TopLeft = Pt_TopLeft;
	BottomRight = Pt_BottomRight;

	RectDetect.x 		= TopLeft.GetX();
	RectDetect.y 		= TopLeft.GetY();
	RectDetect.height 	= BottomRight.GetY() - TopLeft.GetY();
	RectDetect.width 	= BottomRight.GetX() - TopLeft.GetX();

	Center = TopLeft + BottomRight;
	Center = Center/2;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: operator>>
 * Return Type 	: std::istream&
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Reads a box from the string
 * Arguments	: std::istream& in, Boxes& bx
 *******************************************************************/
std::istream& operator>>( std::istream& in, Boxes& bx)
{
	ImagePt TL, BR;

	in >> TL;
	in >> BR;

	bx.SetBoxRect(TL, BR);

	return in;
}

/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: CImage
 * Created On	: Apr 30, 2013
 * Created By 	: hrushi
 * Comments		: Overlays this box on the Image
 * Arguments	: const CImage& img
 *******************************************************************/
ColorImg Boxes::Overlay( const CImage& Img, const cv::Scalar Clr) const
{
	ColorImg Orlay;
	Orlay.SetImage( Img.GetDataRef() );

	Mat tempMat;
	Img.copyTo( tempMat );

	cv::rectangle(tempMat, RectDetect, Clr, 1, CV_AA, 0);
	Orlay.SetImage( tempMat );

	return Orlay;
}

