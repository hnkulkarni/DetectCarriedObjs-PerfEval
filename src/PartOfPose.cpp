/*
 * PartOfPose.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#include "PartOfPose.h"

PartOfPose::PartOfPose()
{
	// TODO Auto-generated constructor stub

	ElbowAngle = 0;
	WristAngle = 0;
	ShoulderAngle = 0;
	PartClr = 'w';

}

PartOfPose::~PartOfPose()
{

}

/**********************************************************************
 * Function Name: PartOfPose
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 **********************************************************************/
PartOfPose::PartOfPose( const PartOfPose& rhsPartOfPose )
{
	Allocate_PartOfPose( rhsPartOfPose );
	Copy_PartOfPose( rhsPartOfPose );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 **********************************************************************/
PartOfPose& PartOfPose :: operator=( const PartOfPose & rhsPartOfPose )
{
	Allocate_PartOfPose( rhsPartOfPose );
	Copy_PartOfPose( rhsPartOfPose );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_PartOfPose
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 **********************************************************************/
int PartOfPose:: Copy_PartOfPose(  const PartOfPose & rhsPartOfPose  )
{

	for(unsigned int i = 0; i < PartBoxes.size(); i++ )
	{
		PartBoxes.at(i) = rhsPartOfPose.PartBoxes.at(i);
	}

	ShoulderAngle 	= rhsPartOfPose.ShoulderAngle;
	ElbowAngle 		= rhsPartOfPose.ElbowAngle;
	WristAngle		= rhsPartOfPose.WristAngle;
	PartClr			= rhsPartOfPose.PartClr;
	RgbPartClr		= rhsPartOfPose.RgbPartClr;
	PartType		= rhsPartOfPose.PartType;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_PartOfPose
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 **********************************************************************/
int PartOfPose:: Allocate_PartOfPose(  const PartOfPose & rhsPartOfPose  )
{

	PartBoxes.resize( rhsPartOfPose.PartBoxes.size() );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Add
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Adds the box for the part
 * Arguments	: const Boxes& Bx
 *******************************************************************/
int PartOfPose::Add( const Boxes& Bx)
{
	PartBoxes.push_back(Bx);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetElbowAngle
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Elbow Angle
 * Arguments	:
 *******************************************************************/
int PartOfPose::CalcAngles()
{
	CalcShoulderAngle();
	CalcElbowAngle();
	CalcWristAngle();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: CalcWristAngle
 * Return Type 	: double
 * Created On	: Apr 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Wrist Angle
 * Arguments	:
 *******************************************************************/
double PartOfPose::CalcWristAngle( )
{

	ImagePt WristPt  = PartBoxes.at(2).Center;
	ImagePt EndOfArm = PartBoxes.at(3).Center;

	WristAngle = WristPt.SlopeAngle( EndOfArm );

	return WristAngle;
}

/*******************************************************************
 * Function Name: CalculateElbowAngle
 * Return Type 	: double
 * Created On	: Apr 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Elbow Angle
 * Arguments	:
 *******************************************************************/
double PartOfPose::CalcElbowAngle( )
{

	ImagePt ElbowPt = PartBoxes.at(1).Center;
	ImagePt WristPt = PartBoxes.at(2).Center;

	ElbowAngle = ElbowPt.SlopeAngle( WristPt );

	return ElbowAngle;
}

/*******************************************************************
 * Function Name: CalcShoulderAngle
 * Return Type 	: double
 * Created On	: Apr 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Shoulder Angle
 * Arguments	:
 *******************************************************************/
double PartOfPose::CalcShoulderAngle( )
{
	ImagePt ShoulderPt, ElbowPt;

	ShoulderPt 	= PartBoxes.at(0).Center;
	ElbowPt 	= PartBoxes.at(1).Center;

	ShoulderAngle = ShoulderPt.SlopeAngle( ElbowPt );

	return ShoulderAngle;
}


/*******************************************************************
 * Function Name: CalcCarryAngle
 * Return Type 	: int
 * Created On	: Apr 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Carry Angle
 * Arguments	: const ImagePt& Pt
 *******************************************************************/
double PartOfPose::CalcCarryAngle( const ImagePt& Pt) const
{
	const ImagePt EndOfArm	= PartBoxes.at(3).Center;
	const ImagePt WristPt	= PartBoxes.at(2).Center;

	const ImagePt unit_End2Wrist = WristPt.GetUnit(EndOfArm);
	const ImagePt unit_End2CarryPt = EndOfArm.GetUnit( Pt ) ;
	double dDot = unit_End2CarryPt.Dot( unit_End2Wrist );

	double CarryAngle = dDot;

	return CarryAngle;
}


/*******************************************************************
 * Function Name: CalcCarryDist
 * Return Type 	: double
 * Created On	: May 1, 2013
 * Created By 	: hrushi
 * Comments		: Calculate the Carry distance
 * Arguments	: const ImagePt& pt
 *******************************************************************/
double PartOfPose::CalcCarryDist( const Contour& Ct ) const
{
	const ImagePt EndOfArm	= PartBoxes.at(3).Center;
	const ImagePt WristPt	= PartBoxes.at(2).Center;

	const ImagePt Shoulder = PartBoxes.at(0).Center;
	const ImagePt CarryPt = Ct.GetCenter();

	const ImagePt unit_End2Wrist = WristPt.GetUnit(EndOfArm);
	const ImagePt unit_End2CarryPt = EndOfArm.GetUnit( Ct.GetCenter() ) ;

	const ImagePt ClosestPt = Ct.GetClosestPt( EndOfArm);

	double CarryDist = EndOfArm.Distance( ClosestPt );

	return CarryDist;
}

/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: const CImage
 * Created On	: Apr 30, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the part of the pose on the image
 * Arguments	: const CImage& Img
 *******************************************************************/
const ColorImg PartOfPose::Overlay( const CImage& Img) const
{
	ColorImg OrImg;
	cout << "Overlaying Part of Image " << PartType << endl;

	OrImg.SetImage(Img.GetDataRef() );

	for(unsigned int i = 0; i < PartBoxes.size(); i++ )
	{
		Boxes b = PartBoxes.at(i);
		OrImg = b.Overlay( OrImg, RgbPartClr ); // Returns the overlayed image back
	}

	return OrImg;
}


/*******************************************************************
 * Function Name: OverlayStick
 * Return Type 	: const CImage
 * Created On	: May 1, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the Stick Layout of the Arm
 * Arguments	: const CImage& img
 *******************************************************************/
const ColorImg PartOfPose::OverlayStick( const CImage& Img) const
{
	ColorImg OvrlayImg;

	if( ( PartType == "lArm") ||  (PartType == "rArm") )
	{
		OvrlayImg =  OverlayArm(Img);
	}

	else if( PartType == "Torso")
	{
		OvrlayImg = OverlayTorso( Img );
	}
	else if( ( PartType == "rLeg") || (PartType == "lLeg"))
	{
		OvrlayImg = OverlayLegs( Img );
	}
	else if( PartType == "Head")
	{
		OvrlayImg =	OverlayHead( Img );
	}
	else // Return the same image
	{
		OvrlayImg.SetImage( Img.GetDataRef().clone() );
	}


	return OvrlayImg;
}

/*******************************************************************
 * Function Name: OverlayHead
 * Return Type 	: const ColorImg
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: Overlay the Head on the Image
 * Arguments	: const CImage& Img
 *******************************************************************/
const ColorImg PartOfPose::OverlayHead( const CImage& Img) const
{
	ColorImg OvrlayImg;
	cv::Mat DispMat;
	Img.copyTo( DispMat );

	const int RECT_WIDTH = 6;
	const int RECT_HEIGHT = 6;

	cv::Rect RBox( PartBoxes.at(0).Center.GetX(), PartBoxes.at(0).Center.GetY(), RECT_WIDTH , RECT_HEIGHT  );
	cv::rectangle(DispMat, RBox, RgbPartClr, CV_FILLED, CV_AA, 0);

	for(unsigned int i = 0; i < PartBoxes.size() - 1; i++ )
	{
		ImagePt Pt1, Pt2;
		Pt1 = PartBoxes.at(i).Center;
		Pt2 = PartBoxes.at(i+1).Center;

		cv::line( DispMat, Pt1.GetPoint(), Pt2.GetPoint(), RgbPartClr, 1, CV_AA, 0 );
		OvrlayImg.SetImage(DispMat);
	}

	OvrlayImg.SetImage(DispMat);

	return OvrlayImg;
}




/*******************************************************************
 * Function Name: OverlayLegs
 * Return Type 	: ColorImg
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: Overlay Legs
 * Arguments	: const CImage& Img
 *******************************************************************/
const ColorImg PartOfPose::OverlayLegs( const CImage& Img) const
{
	ColorImg OvrlayImg;
	cv::Mat DispMat;
	Img.copyTo( DispMat );

	const int RECT_WIDTH = 6;
	const int RECT_HEIGHT = 6;

	cv::Rect RBox( PartBoxes.at(0).Center.GetX(), PartBoxes.at(0).Center.GetY(), RECT_WIDTH , RECT_HEIGHT  );
	cv::rectangle(DispMat, RBox, RgbPartClr, CV_FILLED, CV_AA, 0);

	ImagePt L1, L2;
	L1 = PartBoxes.at(0).Center;
	L2 = PartBoxes.at(0).Center;

	ImagePt Segm;
	Segm.SetPoint(15, 0);

	L1 = L1 - Segm;
	L2 = L2 + Segm;
	cv::line( DispMat, L1.GetPoint(), L2.GetPoint(), RgbPartClr, 1, CV_AA, 0 );

	for(unsigned int i = 0; i < PartBoxes.size() - 1; i++ )
	{
		ImagePt Pt1, Pt2;
		Pt1 = PartBoxes.at(i).Center;
		Pt2 = PartBoxes.at(i+1).Center;

		cv::line( DispMat, Pt1.GetPoint(), Pt2.GetPoint(), RgbPartClr, 1, CV_AA, 0 );
		OvrlayImg.SetImage(DispMat);
	}

	OvrlayImg.SetImage(DispMat);

	string PartLabel = (PartType == "lLeg")? "L" : "R";
	ImagePt PutPoint( PartBoxes.at(0).Center.GetX(), PartBoxes.at(0).Center.GetY() + RECT_HEIGHT );
	OvrlayImg.PutText(PartLabel, COLOR_BLACK, COLOR_WHITE, PutPoint.GetPoint() );

	return OvrlayImg;
}


/*******************************************************************
 * Function Name: OverlayTorso
 * Return Type 	: const ColorImg
 * Created On	: Dec 27, 2013
 * Created By 	: hrushi
 * Comments		: Overlay Torso on the image
 * Arguments	: const CImage& Img
 *******************************************************************/
const ColorImg PartOfPose::OverlayTorso( const CImage& Img) const
{
	ColorImg OvrlayImg;
	cv::Mat DispMat;
	Img.copyTo( DispMat );

	for(unsigned int i = 0; i < PartBoxes.size(); i++ )
	{
		ImagePt Pt1, Pt2;

		Pt1 = PartBoxes.at(i).Center;

		UINT NextIdx = 0;
		if( (i + 1) == PartBoxes.size())
		{
			NextIdx = 0;
		}
		else
		{
			NextIdx = i + 1;
		}

		Pt2 = PartBoxes.at(NextIdx).Center;

		cv::line( DispMat, Pt1.GetPoint(), Pt2.GetPoint(), RgbPartClr, 1, CV_AA, 0 );
		OvrlayImg.SetImage(DispMat);
	}

	OvrlayImg.SetImage(DispMat);

	return OvrlayImg;
}


/*******************************************************************
 * Function Name: OverlayArm
 * Return Type 	: ColorImg
 * Created On	: Dec 27, 2013
 * Created By 	: hrushi
 * Comments		: Overlay Arm on the image
 * Arguments	: const CImage& Img
 *******************************************************************/
const ColorImg PartOfPose::OverlayArm( const CImage& Img) const
{
	ColorImg OvrlayImg;
	cv::Mat DispMat;
	Img.copyTo( DispMat );

	const int RECT_WIDTH = 6;
	const int RECT_HEIGHT = 6;

	cv::Rect RBox( PartBoxes.at(0).Center.GetX(), PartBoxes.at(0).Center.GetY(), RECT_WIDTH , RECT_HEIGHT  );
	cv::rectangle(DispMat, RBox, RgbPartClr, CV_FILLED, CV_AA, 0);

	ImagePt L1, L2;
	L1 = PartBoxes.at(0).Center;
	L2 = PartBoxes.at(0).Center;

	ImagePt Segm;
	Segm.SetPoint(15, 0);

	L1 = L1 - Segm;
	L2 = L2 + Segm;
	cv::line( DispMat, L1.GetPoint(), L2.GetPoint(), RgbPartClr, 1, CV_AA, 0 );

	for(unsigned int i = 0; i < PartBoxes.size() - 1; i++ )
	{
		ImagePt Pt1, Pt2;
		Pt1 = PartBoxes.at(i).Center;
		Pt2 = PartBoxes.at(i+1).Center;

		cv::line( DispMat, Pt1.GetPoint(), Pt2.GetPoint(), RgbPartClr, 1, CV_AA, 0 );
		OvrlayImg.SetImage(DispMat);
	}

	OvrlayImg.SetImage(DispMat);

	string PartLabel = (PartType == "lArm")? "L" : "R";
	ImagePt PutPoint( PartBoxes.at(0).Center.GetX(), PartBoxes.at(0).Center.GetY() + RECT_HEIGHT );
	OvrlayImg.PutText(PartLabel, COLOR_BLACK, COLOR_WHITE, PutPoint.GetPoint() );

	return OvrlayImg;
}



/*******************************************************************
 * Function Name: SetColor
 * Return Type 	: int
 * Created On	: Apr 30, 2013
 * Created By 	: hrushi
 * Comments		: Sets the Color
 * Arguments	: const char ClrKey
 *******************************************************************/
int PartOfPose::SetColor( const char ClrKey)
{

	PartClr = ClrKey;

	switch( PartClr )
	{
	case 'g': // Green
		RgbPartClr = cv::Scalar(0, 255, 0);
		PartType = "Head";
		break;

	case 'm': // Magenta
		RgbPartClr = cv::Scalar(255, 0, 255);
		PartType = "lArm";
		break;

	case 'y': // Yellow
		RgbPartClr = cv::Scalar(0, 255, 255);
		PartType = "Torso";
		break;

	case 'c':
		RgbPartClr = cv::Scalar(255, 255, 0);
		PartType = "rArm";
		break;

	case 'r':
		RgbPartClr = cv::Scalar(0, 0, 255);
		PartType = "lLeg";
		break;

	case 'b':
		RgbPartClr = cv::Scalar(255, 0, 0);
		PartType = "rLeg";
		break;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetEndOfArm
 * Return Type 	: const ImagePt
 * Created On	: Jul 27, 2013
 * Created By 	: hrushi
 * Comments		: Get the End of Arm Location
 * Arguments	:
 *******************************************************************/
const ImagePt PartOfPose::GetEndOfArm( ) const
{
	ImagePt EndOfArm;

	if( ( PartType == "rArm" ) || ( PartType == "lArm") )
	{
		EndOfArm = PartBoxes.at(3).Center;
	}
	else
	{
		throw ERR_CANNOT_READ_VALUE;
	}

	return EndOfArm;
}

/*******************************************************************
 * Function Name: GetWristPt
 * Return Type 	: const ImagePt
 * Created On	: Sep 22, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Wrist Point
 * Arguments	:
 *******************************************************************/
const ImagePt PartOfPose::GetWristPt( ) const
{
	ImagePt WristPt;


	if( ( PartType == "rArm" ) || ( PartType == "lArm") )
	{
		WristPt = PartBoxes.at(2).Center;
	}
	else
	{
		throw ERR_CANNOT_READ_VALUE;
	}


	return WristPt;
}



/*******************************************************************
 * Function Name: GetMask
 * Return Type 	: const GrayImg
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: Mask for the pose
 * Arguments	: const CImage& Img, const Args& args
 *******************************************************************/
const BinaryImg PartOfPose::GetMask( const cv::Size ImgSize, const Args& args) const
{
	BinaryImg MaskImg(ImgSize);
	cv::Mat DispImg;
	MaskImg.copyTo(DispImg);

	for(unsigned int i = 0; i < PartBoxes.size(); i++ )
	{
		Boxes B = PartBoxes.at(i);
		cv::rectangle(DispImg, B.RectDetect, COLOR_WHITE, CV_FILLED, CV_AA, 0 );
		cv::threshold(DispImg, DispImg, GRAY_VALUE, MAX_GRAY_VALUE, cv::THRESH_BINARY );

		MaskImg.SetImage(DispImg);
	}

	return MaskImg;
}
