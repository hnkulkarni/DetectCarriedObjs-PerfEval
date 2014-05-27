/*
 * PoseData.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#include "PoseData.h"

PoseData::PoseData() {
	// TODO Auto-generated constructor stub

}

PoseData::~PoseData() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: PoseData
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
PoseData::PoseData( const PoseData& rhsPoseData )
{
	Allocate_PoseData( rhsPoseData );
	Copy_PoseData( rhsPoseData );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
PoseData& PoseData :: operator=( const PoseData & rhsPoseData )
{
	Allocate_PoseData( rhsPoseData );
	Copy_PoseData( rhsPoseData );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_PoseData
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int PoseData:: Copy_PoseData(  const PoseData & rhsPoseData  )
{

	for( MapPartOfPose::const_iterator itr = rhsPoseData.m_PosePartMap.begin(); itr != rhsPoseData.m_PosePartMap.end(); itr++ )
	{
		m_PosePartMap[itr->first] = itr->second;
	}

	return EXIT_SUCCESS;
}





/**********************************************************************
 * Function Name: Allocate_PoseData
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int PoseData:: Allocate_PoseData(  const PoseData & rhsPoseData  )
{


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Add
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Adds a box to the part of the pose
 * Arguments	: char
 *******************************************************************/
int PoseData::Add( char cPartClr, const Boxes& Bx )
{
	m_PosePartMap[cPartClr].Add(Bx);
	m_PosePartMap[cPartClr].SetColor( cPartClr );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: CalculatePartAngles
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Calculates angles between the boxes
 * Arguments	: const Contour& CarriedContour
 *******************************************************************/
int PoseData::CalculatePartAngles()
{
	m_PosePartMap.at('c').CalcAngles();
	m_PosePartMap.at('m').CalcAngles();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: CalcCarryAngles
 * Return Type 	: double
 * Created On	: Apr 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Carry Angle
 * Arguments	: const ImagePt& Pt
 *******************************************************************/
double PoseData::CalcCarryAngles( char PartKey, const ImagePt& Pt) const
{
	return m_PosePartMap.at(PartKey).CalcCarryAngle(Pt);
}


/*******************************************************************
 * Function Name: CalcCarryDist
 * Return Type 	: double
 * Created On	: May 1, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Carry Distance
 * Arguments	: const ImagePt& Pt
 *******************************************************************/
double PoseData::CalcCarryDist(  char PartKey, const Contour& Ct ) const
{
	return m_PosePartMap.at(PartKey).CalcCarryDist(  Ct );
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: const CImage
 * Created On	: Apr 30, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the Pose on the image
 * Arguments	: const CImage& Img
 *******************************************************************/
ColorImg PoseData::Overlay( const CImage& Img, string sOpt) const
{
	ColorImg OrImg;

	OrImg.SetImage( Img.GetDataRef() );
	for(MapPartOfPose::const_iterator itr = m_PosePartMap.begin(); itr != m_PosePartMap.end(); itr++ )
	{
		string PartType = itr->second.GetPartType();
		if( ShouldOverlayPose( PartType, sOpt ))
		{
			OrImg.SetImage( itr->second.OverlayStick( OrImg ).GetDataRef() );
		}
	}

	return OrImg;
}


/*******************************************************************
 * Function Name: ShouldOverlayPose
 * Return Type 	: bool
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: Check if we should overlay pose depending on the selection
 * Arguments	: const string PartType, const string sOpt
 *******************************************************************/
bool PoseData::ShouldOverlayPose( string PartType, string sOpt) const
{
	bool decision 	 = false;
	bool OverlayOpt	 = false;
	bool OverlayArm	 = false;
	bool OverlayLeg  = false;
	bool OverlayTorsoHead = false;

	//---------- Changing to Lower case, to avoid any sanitization issues ---------- //
	boost::algorithm::to_lower(sOpt);

	if( sOpt == "all")
	{
		OverlayOpt = true;
	}

	boost::algorithm::to_lower(PartType);

	//Overlaying if the part selected is Torso and Head
	if((PartType == "torso") || (PartType == "head"))
	{
		if( sOpt == "torso-head")
		{
			OverlayTorsoHead = true;
		}
	}

	// Overlay if the option describes the part type to be overlayed.
	if( (PartType == sOpt ) )
	{
		OverlayArm = true;
	}

	// Check if an Arm Pose
	if( ( PartType == "larm") || ( PartType == "rarm") ){

		if( sOpt == "arms" )
		{
			OverlayArm = true;
		}
		else
		{
			OverlayArm = false;
		}
	}
	else
	{
		OverlayArm = false;
	}

	// Check if a Leg Pose
	if( ( PartType == "lleg") || ( PartType == "rleg") ){

		if( sOpt == "legs" )
		{
			OverlayLeg = true;
		}
		else
		{
			OverlayLeg = false;
		}
	}
	else
	{
		OverlayLeg = false;
	}

	// Display the Pose
	if( OverlayOpt || OverlayArm || OverlayLeg || OverlayTorsoHead || ( sOpt == PartType ))
	{
		decision = true;
	}

	return decision;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: ColorImg
 * Created On	: Aug 2, 2013
 * Created By 	: hrushi
 * Comments		: Displays the given contour and a line joining the end of arm to the center of the contour
 * Arguments	: const CImage & Img, const string PartType, const ImagePt& Pt
 *******************************************************************/
ColorImg PoseData::Overlay( const ColorImg & Img, const string PartType,  const Contour& Ctr ) const
{
	//Passing a dummy contructor to this function argument.
	ColorImg DispImg = Img.Overlay(Ctr, DISP_DELAY, COLOR_GREEN, Args() );

	DispImg = Overlay(DispImg, PartType );

	char MapKey = (PartType == "lArm" )? 'm' : 'c';

	DispImg = Overlay(DispImg, MapKey, Ctr);

	return DispImg;
}



/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: ColorImg
 * Created On	: Aug 3, 2013
 * Created By 	: hrushi
 * Comments		: Overlay pose and contour on the image with a line joining the end of arm to the center of the region
 * Arguments	: const ColorImg& Img, char MapKey, const Contour& Ctr
 *******************************************************************/
ColorImg PoseData::Overlay( const ColorImg& Img, char MapKey, const Contour& Ctr) const
{
	string PartType = (MapKey == 'm')? "lArm" : "rArm";
	ColorImg DispImg = Img.Overlay(Ctr, DISP_DELAY, COLOR_GREEN, Args() );

	DispImg = Overlay(DispImg, PartType );

	const ImagePt EndOfArm = m_PosePartMap.at(MapKey).GetEndOfArm();
	cv::Mat TempMat = DispImg.GetDataRef().clone();

	cv::line( TempMat, EndOfArm.GetPoint(), Ctr.GetClosestPt(EndOfArm).GetPoint(), COLOR_WHITE, 1, 8, 0 );
	DispImg.SetImage(TempMat);

	return DispImg;
}


/*******************************************************************
 * Function Name: OverlayExtn
 * Return Type 	: ColorImg
 * Created On	: Sep 22, 2013
 * Created By 	: hrushi
 * Comments		: Overlay Pose with an arm extension, along which the carry angle is calculated
 * Arguments	: const ColorImg& Img, char MapKey, const Contour& Ctr
 *******************************************************************/
ColorImg PoseData::OverlayExtn( const ColorImg& Img, char MapKey, const Contour& Ctr) const
{
	ColorImg DispImg = Overlay(Img, MapKey, Ctr);
	const ImagePt ExtnEnd = GetExtensionPt(MapKey);
	const ImagePt EndOfArm = m_PosePartMap.at(MapKey).GetEndOfArm();

	cv::Mat TempMat = DispImg.GetDataRef().clone();
	cv::line( TempMat, EndOfArm.GetPoint(), ExtnEnd.GetPoint(), COLOR_RED, 1, 8, 0 );

	DispImg.SetImage(TempMat);

	return DispImg;
}

/*******************************************************************
 * Function Name: GetExtensionPt
 * Return Type 	: const imagePt
 * Created On	: Sep 22, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Extension Line along the arm. This is used for display purposes
 * Arguments	: char MapKey
 *******************************************************************/
const ImagePt PoseData::GetExtensionPt( char MapKey) const
{
	ImagePt EndOfArm 	 = m_PosePartMap.at(MapKey).GetEndOfArm();
	ImagePt WristOfArm = m_PosePartMap.at(MapKey).GetWristPt();

	const ImagePt UnitVector = WristOfArm.GetUnit(EndOfArm);
	const ImagePt ExtnVector = UnitVector * ARM_EXTN_DIST;
	const ImagePt ExtnEnd = EndOfArm + ExtnVector;

	return ExtnEnd;
}

/*******************************************************************
 * Function Name: CalcPoseFeature
 * Return Type 	: const vector<double>
 * Created On	: Sep 24, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the pose feature
 *     Feature 1: Carry Angle
 *     Feature 2: Carry Dist
 * Arguments	: const PartKey, const Contour& Ctr
 *******************************************************************/
const vector<double> PoseData::CalcPoseFeature( char PartKey, const Contour& Ctr ) const
{
	double CarryAngle = CalcCarryAngles( PartKey, Ctr.GetCenter() );
	double CarryDist  = CalcCarryDist(  PartKey, Ctr );

	const vector<double> Feature{CarryAngle, CarryDist};

	return Feature;
}



/*******************************************************************
 * Function Name: GetPoseFeature
 * Return Type 	: const vector<double>
 * Created On	: Sep 24, 2013
 * Created By 	: hrushi
 * Comments		: Calculates pose feature will saving all the display images and showing them to the user
 * Arguments	: const ColorImg DispImg, char PartKey, const Contour& Ctr, const Args& args
 *******************************************************************/
const vector<double> PoseData::GetPoseFeature( ColorImg& DispImg, bool isCarryRgn,  char PartKey, const Contour& Ctr, const Args& args) const
{

	DispImg = OverlayExtn(DispImg, PartKey, Ctr);

	if( isCarryRgn)
	{
		DispImg = DispImg.Overlay(Ctr, DISP_DELAY, COLOR_RED, args );
	}

	const vector<double> PoseFeature = CalcPoseFeature(PartKey, Ctr);

	return PoseFeature;
}



/*******************************************************************
 * Function Name: GetLegendString
 * Return Type 	: string
 * Created On	: Sep 27, 2013
 * Created By 	: hrushi
 * Comments		: Generates a String to be appended in the legend
 * Arguments	: char PartKey
 *******************************************************************/
const string PoseData::GetLegendString( const string ArmName, const vector<double>& Feature) const
{
	std::stringstream ss;

	ss << ArmName << " a:" << Feature.at(0) << " d:" << Feature.at(1) << endl;

	return ss.str();
}


/*******************************************************************
 * Function Name: PoseMask
 * Return Type 	: GrayImg
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: uses the given probe image just for size, and then returns mask for the pose
 * Arguments	: const ColorImg& ProbeImg, const string sOpt
 *******************************************************************/
const BinaryImg PoseData::PoseMask( const cv::Size ImgSize, const string sOpt, const Args& args) const
{
	BinaryImg MaskImg( ImgSize );

	for(MapPartOfPose::const_iterator itr = m_PosePartMap.begin(); itr != m_PosePartMap.end(); itr++ )
	{
		string PartType = itr->second.GetPartType();

		if( ShouldOverlayPose( PartType, sOpt ))
		{
			BinaryImg RetImg = itr->second.GetMask(ImgSize, args);

			MaskImg = MaskImg || RetImg;
		}
	}

	return MaskImg;
}


/*******************************************************************
 * Function Name: GetOverlapPercentage
 * Return Type 	: double
 * Created On	: Jan 2, 2014
 * Created By 	: hrushi
 * Comments		: Calculates the percentage overlap over the given binary image with the pose mask
 * Arguments	: const BinaryImg& Img	: This is the image over which you want to find the overlap. Generally it is the binary foreground mask.
 * 				: const string sPart	: Select the part of the pose that you want to find the overlap of. Eg. Head, Torso, Legs, Arms, lLeg, etc...
 * 				: bool bDisp			: Boolean flag, controls the display
 * 				: const Args& args		: Args class
 *******************************************************************/
double PoseData::GetOverlapPercentage( const BinaryImg& Img, const string sPart, bool bDisp, const Args& args) const
{
	BinaryImg PoseMaskImg = PoseMask(Img.GetImgSize(), sPart, Args());

	if(bDisp)
	{
		PoseMaskImg.Display(DISP_WAIT_FOR_KEY);
		Img.Display(DISP_WAIT_FOR_KEY);
	}

	BinaryImg TempBinImg(Img);
	BinaryImg PoseBkAnd = PoseMaskImg && TempBinImg;

	if(bDisp)
	{
		PoseBkAnd.Display(DISP_WAIT_FOR_KEY);
	}

	double uiPoseImgOverlap = TempBinImg.Percentage_Overlap(PoseBkAnd);

	return uiPoseImgOverlap;
}



/*******************************************************************
 * Function Name: RejectCtrByPoseOverlap
 * Return Type 	: bool: If False, then no significant overlap is present, and not to use this
 * Created On	: Jan 5, 2014
 * Created By 	: hrushi
 * Comments		: Depending on the threshold set, it will return if the given pose need to be rejected by the overlaping pose
 * Arguments	: const Contour& Ctr, const string sPosePart, const Args& args
 *******************************************************************/
bool PoseData::PoseOverlapDetectScore(const BinaryImg& MskImg,  const Contour& Cntr, const string sPosePart, vector<double>& Score, const Args& args) const
{
	bool bDecision = false;
	double OverlapAllScore = 0; // Loading default overlap value

	OverlapAllScore = GetOverlapPercentage(MskImg, "all", false, Args());

	//Set the Size of the score to match the number of labels
	vector<double> DefaultPersonScore;
	DefaultPersonScore.resize(NUM_LABELS);
	DefaultPersonScore.at(WORN_CARRY_LABEL) = 0;
	DefaultPersonScore.at(DRAG_CARRY_LABEL) = 0;
	DefaultPersonScore.at(PERSON_LABEL)		= 1;

	Score.resize(NUM_LABELS);

	bool bUsePoseOverlap = args.isUsePoseOverlap();

	if( ( OverlapAllScore > POSE_BELIEVE_THRLD) && bUsePoseOverlap )
	{
		cout << "Overlap All Score: " << OverlapAllScore << " > " << POSE_BELIEVE_THRLD << endl;
		BinaryImg CtrMsk(Cntr.GetCtrMaskImg());

		//CtrMsk.Display(DISP_KEY_PRESS);

		double PartOverlap = GetOverlapPercentage(CtrMsk, sPosePart, false, Args());
		cout << "Part Overlap " << PartOverlap << endl;

		if(PartOverlap > POSE_PART_BELIEVE_THRLD )
		{
			Score = DefaultPersonScore;
			bDecision = true;

		}
		else
		{
			bDecision = false;
		}

	}

	return bDecision;
}
