/*
 * DetectionImg.cpp
 *
 *  Created on: Jul 7, 2013
 *      Author: hrushi
 */

#include "DetectionImg.h"

DetectionImg::DetectionImg():ColorImg()
{
	// TODO Auto-generated constructor stub

}

DetectionImg::~DetectionImg()
{
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: DetectionImg Copy Constructor
 * Date		: Jul 7, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
DetectionImg::DetectionImg(const DetectionImg& rhsDetectionImg ):ColorImg(rhsDetectionImg)
{
	Allocate( rhsDetectionImg );
	Copy( rhsDetectionImg );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 7, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
DetectionImg& DetectionImg:: operator=( const DetectionImg& rhsDetectionImg )
{
	Allocate( rhsDetectionImg );
	Copy( rhsDetectionImg );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 7, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectionImg::Allocate( const DetectionImg& rhsDetectionImg )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 7, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectionImg::Copy( const DetectionImg& rhsDetectionImg )
{
	ColorImg::operator =( rhsDetectionImg );

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Overlay
 * Arguments	: const AllDetectedCtrs& Ctrs, bool toDisplay
 *******************************************************************/
int DetectionImg::Overlay( const AllDetectedCtrs& AllCtrs, bool toDisplay, const Args& args)
{

	ColorImg Img;
	Img.SetImage(m_data);

	for( auto Cntur : AllCtrs.Get_vCtrs())
	{
		Img = Overlay(Cntur, false, args );
		SetImage( Img.GetDataRef() );
	}

	if( toDisplay )
	{
		if( args.GetRunMode() == OP_DEMO)
		{
			Display(0);
		}
		else
		{
			Display(DISP_DELAY);
		}
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Display a carry contour
 * Arguments	: const CarryContour& Ctr, bool toDisplay
 *******************************************************************/
ColorImg DetectionImg::Overlay( const CarryContour& CarryCtr, bool toDisplay, const Args& args)
{

	ColorImg ProbeImg = *this;

	switch(CarryCtr.GetCarryType())
	{
	case WORN_CARRY_LABEL:
		ProbeImg = ProbeImg.Overlay( CarryCtr, DISP_DELAY, COLOR_RED, args );
		break;

	case DRAG_CARRY_LABEL:
		ProbeImg = ProbeImg.Overlay( CarryCtr, DISP_DELAY, COLOR_GREEN, args );
		break;

	case PERSON_LABEL:
		ProbeImg = ProbeImg.Overlay( CarryCtr, DISP_DELAY, COLOR_BLUE, args );
		break;
	}

	if( toDisplay )
	{
		ProbeImg.Display(DISP_DELAY);
	}

	return ProbeImg;
}

