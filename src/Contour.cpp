/*
 * Contour.cpp
 *
 *  Created on: Jan 2, 2013
 *      Author: hrushi
 */

#include "Contour.h"

Contour::Contour()
{
	// TODO Auto-generated constructor stub
	Label = -1;
	isBackgroundFlag = false;

}

Contour::~Contour() {
	// TODO Auto-generated destructor stub
}


/**********************************************************************
 * Function Name: Contour
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
Contour::Contour( const Contour& rhsContour )
{
	Allocate_Contour( rhsContour );
	Copy_Contour( rhsContour );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
Contour& Contour :: operator=( const Contour & rhsContour )
{
	Allocate_Contour( rhsContour );
	Copy_Contour( rhsContour );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Contour
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int Contour:: Copy_Contour(  const Contour & rhsContour  )
{
	//Copy all the ContourPoints

	if( ContourPoints.size() == rhsContour.ContourPoints.size())
	{
		for( unsigned int i = 0; i < rhsContour.ContourPoints.size(); i++ )
		{
			ContourPoints.at(i) = rhsContour.ContourPoints.at(i);
		}
	}
	else
	{
		cout << "LHS and RHS number of points are not same, please check " << endl;
		exit( ERR_COPY_CONST_ALLOC );
	}

	TopLeft 	= rhsContour.TopLeft;
	BottomRight = rhsContour.BottomRight;
	Center 		= rhsContour.Center;
	Label 		= rhsContour.Label;
	MedianPt	= rhsContour.MedianPt;

	ContourMask = rhsContour.ContourMask.clone();
	ContourHist = rhsContour.ContourHist;
	EHist		= rhsContour.EHist;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Allocate_Contour
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int Contour:: Allocate_Contour(  const Contour & rhsContour  )
{
	ContourPoints.resize( rhsContour.ContourPoints.size() );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: CalculateElevenSpaceHist
 * Return Type 	: int
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Calculate Eleven Space Histogram
 * Arguments	: const ColorImg& Img
 *******************************************************************/
int Contour::CalculateElevenSpaceHist( const ColorImg& Img, const ReadHistLookup& Lookup  )
{
	Color TempClr;

	GrayImg GrImg;
	GrImg.SetImage(ContourMask);  // Set Contour Mask

	unsigned int iCount = 0;

	for(unsigned int i = 0; i < Img.GetNumRows(); i++ )
	{
		for(unsigned int j = 0; j < Img.GetNumCols(); j++ )
		{

			unsigned char cT = GrImg.at(i,j);

			if( cT == MAX_GRAY_VALUE ) // If the pixel is on the contour that we are considering
			{

				TempClr = Img.at(i,j);
				EHist.AddCount(TempClr, Lookup);

				iCount++;

			}

		}
	}

	EHist.m_Hist = EHist.m_Hist/iCount;

	CalculateCntrParam();

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: CalcContourLocProb
 * Return Type 	: double
 * Created On	: May 29, 2013
 * Created By 	: hrushi
 * Comments		: Calculate the Loction probability given an location image
 * Arguments	: const GrayImg& LocProbImg
 *******************************************************************/
double Contour::CalcContourLocProb( const GrayImg& LocProbImg) const
{
	double Prob(0);

	GrayImg CtrMsk;
	CtrMsk.SetImage( ContourMask );
	CtrMsk.Resize(LocProbImg.GetNumRows(), LocProbImg.GetNumCols() );
	CtrMsk.Display(DISP_DELAY);

	unsigned int uiCntrArea(0);
	for(unsigned int i = 0; i < CtrMsk.GetNumRows(); i++ )
	{
		for(unsigned int j = 0; j < CtrMsk.GetNumCols(); j++ )
		{
			unsigned char cT = CtrMsk.at(i,j);

			if( cT == MAX_GRAY_VALUE ) // If the pixel is on the contour that we are considering
			{
				uiCntrArea++;
				// Dividing by Max Gray value because the image probabilities
				// have been mapped to gray for display purposes
				Prob += (double)LocProbImg.at(i, j)/MAX_GRAY_VALUE;
			}
		}
	}

	return Prob;
}
/*******************************************************************
 * Function Name: CalculateGrayHist
 * Return Type 	: int
 * Created On	: Mar 9, 2013
 * Created By 	: hrushi
 * Comments		: Calculate Gray Histogram
 * Arguments	: const CImage& GryImage
 *******************************************************************/
int Contour::CalculateGrayHist( const GrayImg& GryImage)
{

	unsigned int DataIndx = 0;
	unsigned int Val = 0;

	for( unsigned int i = 0; i < GryImage.GetNumRows(); i++ )
	{
		for( unsigned int j = 0; j < GryImage.GetNumCols(); j++ )
		{

			DataIndx = i *  GryImage.GetNumCols() + j;

			if(ContourMask.data[ DataIndx ] == MAX_GRAY_VALUE)
			{
				Val = GryImage.GetGrayVal(i,j);
				ContourHist.AddCount(Val);
			}
		}
	}

	ContourHist.Normalize();

	if( DEBUG )
	{
		cout << "Histogram for " << std::setw(2) << Label << " is "  <<  ContourHist << endl;
	}

	CalculateCntrParam();

	return EXIT_SUCCESS;

}

/*******************************************************************
 * Function Name: DisplayContourMask
 * Return Type 	: int
 * Created On	: Jan 11, 2013
 * Created By 	: hrushi
 * Comments		: Displays the contour mask image
 * Arguments	:
 *******************************************************************/
int Contour::DisplayContourMask( ) const
{
	GrayImg CtrMskImg;
	CtrMskImg.SetImage( ContourMask );

	CtrMskImg.Display(0);


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetHistogram
 * Return Type 	: vector<unsigned int>
 * Created On	: Jan 13, 2013
 * Created By 	: hrushi
 * Comments		: Returns a copy of the histogram
 * TODo			:
 *******************************************************************/
const GrayHistorgram&  Contour::GetHistogram() const
{
	return ContourHist;
}


/*******************************************************************
 * Function Name: isBackground
 * Return Type 	: int
 * Created On	: Jan 15, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given controur is on the background
 * Arguments	: const CImage& BkMask,
 * 					overlapthreshold: This is the precentage( 0 to 1 ) of the coverage
 *******************************************************************/
bool Contour::isBackground( const CImage& BkMask, double OverlapThreshold  )
{
	double Percentage = PercentageCoverage(BkMask);

	if( Percentage <= OverlapThreshold ) // Less than 50 percentage is covered
	{
		isBackgroundFlag = true;
		return true;
	}
	else
	{
		isBackgroundFlag = false;
		return false;
	}

	return false;

}


/*******************************************************************
 * Function Name: PercentageForegroundinCountour
 * Return Type 	: double
 * Created On	: Apr 23, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Percentage of foreground pixels that are encompassed inside the foreground contour
 * Arguments	: const CImage& BkImg
 *******************************************************************/
double Contour::PercentageCoverage( const CImage& BkMask) const
{
	double Percentage(0);

	unsigned int DataIndx = 0;
	unsigned int Val = 0;

	unsigned int ForegroundPixels(0), ContourPixels(0);

	for( unsigned int i = 0; i < BkMask.GetNumRows(); i++ )
	{
		for( unsigned int j = 0; j < BkMask.GetNumCols(); j++ )
		{
			DataIndx = i *  BkMask.GetNumCols() + j;

			if(ContourMask.data[ DataIndx ] == MAX_GRAY_VALUE)
			{
				ContourPixels++;
				Val = BkMask.GetGrayVal(i,j);

				if( (int)Val == MAX_GRAY_VALUE )
				{
					ForegroundPixels++;
				}

			}
		}
	}

	Percentage = (double)ForegroundPixels/ContourPixels;

	return Percentage;
}

/*******************************************************************
 * Function Name: GetBoundingRect
 * Return Type 	: cv::Rect
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Returns the bounding rectangle for the contour
 * Arguments	:
 *******************************************************************/
const cv::Rect Contour::GetBoundingRect( ) const
{
	cv::Rect BdnRect( TopLeft.GetPoint(), BottomRight.GetPoint() );

	return BdnRect;
}


/*******************************************************************
 * Function Name: CalculateCntrParam
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Top Left and Bottom Right of Images
 * Arguments	:
 *******************************************************************/
int Contour::CalculateCntrParam( )
{
	int MinX(SOME_LARGE_VALUE), MinY(SOME_LARGE_VALUE), MaxX(SOME_SMALL_VALUE), MaxY(SOME_SMALL_VALUE);
	cv::Point TempPt;

	for(unsigned int i = 0; i < ContourPoints.size(); i++ )
	{
		TempPt = ContourPoints.at(i).GetPoint();

		if(  TempPt.x < MinX )
		{
			MinX = TempPt.x;

		}

		if( TempPt.x > MaxX )
		{
			MaxX = TempPt.x;

		}


		if( TempPt.y < MinY )
		{
			MinY = TempPt.y;

		}

		if( TempPt.y > MaxY )
		{
			MaxY = TempPt.y;

		}
	}

	TopLeft.Set_X( MinX );
	TopLeft.Set_Y( MinY );

	BottomRight.Set_X( MaxX );
	BottomRight.Set_Y(MaxY);

	Center = (BottomRight + TopLeft)/2;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: isOnContour
 * Return Type 	: bool
 * Created On	: May 5, 2013
 * Created By 	: hrushi
 * Comments		: Checkes if the given point lies on the contour
 * Arguments	: const ImagePt& Pt
 *******************************************************************/
bool Contour::isOnContour( const ImagePt& Pt) const
{
	bool decision(false);

	for( unsigned int i = 0; i < ContourPoints.size(); i++ )
	{

		if( ContourPoints.at(i) == Pt )
		{
			decision = true;
			return decision;
		}
	}


	return decision;
}


/*******************************************************************
 * Function Name: GetClosestPt
 * Return Type 	: const ImagePt
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: Returns the closest point on the countour to the given point
 * Arguments	: const ImagePt& Pt
 *******************************************************************/
const ImagePt Contour::GetClosestPt( const ImagePt& Pt) const
{
	ImagePt ClosestPt;

	double MinDist = DBL_MAX;

	ImagePt TempPt = Pt;
	TempPt.SwapXY();
	for( unsigned int i = 0; i < ContourPoints.size(); i++ )
	{
		double dist = ContourPoints.at(i).Distance(TempPt);

		if( dist < MinDist )
		{
			MinDist = dist;
			ClosestPt = ContourPoints.at(i);
		}
	}

	ClosestPt.SwapXY(); // DON'T REMOVE: NEEDS TO SWAP!!!!!!!!!!!!!!!!!
	return ClosestPt;
}



/*******************************************************************
 * Function Name: GetAllPts
 * Return Type 	: const vector<cv::Point>
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Returns a vector of all points in the contour
 * Arguments	:
 *******************************************************************/
const vector<cv::Point> Contour::GetOpenCVPts( ) const
{
	vector<cv::Point> CtrPts;

	for(unsigned int i = 0; i < ContourPoints.size(); i++ )
	{
		cv::Point Pt = ContourPoints.at(i).GetPoint();
		CtrPts.push_back(Pt);
	}

	return CtrPts;
}


/*******************************************************************
 * Function Name: GetCtr_BlackImg
 * Return Type 	: GrayImg
 * Created On	: Oct 10, 2013
 * Created By 	: hrushi
 * Comments		: Returns a Countour mask on a BlackImage background
 * Arguments	:
 *******************************************************************/
const ColorImg Contour::GetCtrBlackImg( ) const
{
	ColorImg CrlRet(ContourMask.rows, ContourMask.cols);
	CrlRet = CrlRet.Overlay(*this, DISP_DELAY, COLOR_WHITE, false, Args());

	return CrlRet;
}


/*******************************************************************
 * Function Name: GetimgChip
 * Return Type 	: const ColorImg
 * Created On	: Nov 2, 2013
 * Created By 	: hrushi
 * Comments		: Get the image chip over the contour mask
 * Arguments	: ColorImg Probeimg
 *******************************************************************/
const ColorImg Contour::GetImgChip( ColorImg ProbeImg) const
{
	ColorImg ChipImg(ProbeImg.GetNumRows(), ProbeImg.GetNumCols(), COLOR_WHITE);

	unsigned int DataIndx = 0;

	for( unsigned int i = 0; i < ProbeImg.GetNumRows(); i++ )
	{
		for( unsigned int j = 0; j < ProbeImg.GetNumCols(); j++ )
		{
			DataIndx = i *  ProbeImg.GetNumCols() + j;

			if(ContourMask.data[ DataIndx ] == MAX_GRAY_VALUE)
			{
				ChipImg.at(i,j, ProbeImg.at(i,j));
			}
		}
	}

	return ChipImg;
}


/*******************************************************************
 * Function Name: GetCtrMaskImg
 * Return Type 	: const BinaryImg
 * Created On	: Jan 4, 2014
 * Created By 	: hrushi
 * Comments		: Return a BinaryImg instead of the ContourMask
 * Arguments	:
 *******************************************************************/
const GrayImg Contour::GetCtrMaskImg() const
{
	GrayImg Img;
	Img.SetImage(ContourMask);

	return Img;
}


/*******************************************************************
 * Function Name: SetCtrPoints
 * Return Type 	: int
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Set the contour points
 * Arguments	: const vector<ImagePt>& rhsPts
 *******************************************************************/
int Contour::SetCtrPoints( const vector<ImagePt>& rhsPts)
{
	VectorOp<ImagePt>::DeepCopy(ContourPoints, rhsPts);
	CalculateCntrParam();

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Offset
 * Return Type 	: const CarryContour
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: offsets the contour with respect to the given point
 * Arguments	: const cv::Point Pt
 *******************************************************************/
const Contour Contour::Offset( const cv::Point Pt) const
{
	Contour Ctr = *this;

	vector<ImagePt> OffSetPts = ContourPoints;

	for(UINT i = 0; i < OffSetPts.size(); i++)
	{
		OffSetPts.at(i) = OffSetPts.at(i) +  Pt;
	}

	Ctr.SetCtrPoints(OffSetPts);
	Ctr.CalculateCntrParam();

	return Ctr;
}
