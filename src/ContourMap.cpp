/*
 * ContourMap.cpp
 *
 *  Created on: Jan 2, 2013
 *      Author: hrushi
 */

#include "ContourMap.h"

/**********************************************************************
 * Function Name: ContourMap
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Default Constructor; Sets the Number of Rows and Colums as zeros
 * Args			:
 * ToDo			:
 **********************************************************************/
ContourMap::ContourMap()
{

	ImageNumRows = 0;
	ImageNumCols = 0;
	NumLabels = 0;
}

/**********************************************************************
 * Function Name: ContourMap
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Overloaded Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ContourMap::ContourMap( const unsigned int NumRows, const unsigned int NumCols )
{

	ImageNumRows = NumRows;
	ImageNumCols = NumCols;
	NumLabels = 0;


}


/**********************************************************************
 * Function Name: ContourMap
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Default destructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ContourMap::~ContourMap()
{


	LabelImage.clear();
	BkLabels.clear();

}


/**********************************************************************
 * Function Name: ContourMap
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ContourMap::ContourMap( const ContourMap& rhsContourMap )
{
	Allocate_ContourMap( rhsContourMap );
	Copy_ContourMap( rhsContourMap );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
ContourMap& ContourMap :: operator=( const ContourMap & rhsContourMap )
{
	Allocate_ContourMap( rhsContourMap );
	Copy_ContourMap( rhsContourMap );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_ContourMap
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int ContourMap:: Copy_ContourMap(  const ContourMap & rhsContourMap  )
{

	AllContourMap = rhsContourMap.AllContourMap; // Copy the Map

	ImageNumRows = rhsContourMap.ImageNumRows;
	ImageNumCols = rhsContourMap.ImageNumCols;
	LabelImage   = rhsContourMap.LabelImage;
	NumLabels	 = rhsContourMap.NumLabels;
	ScoreMap	 = rhsContourMap.ScoreMap;

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function Name: Allocate_ContourMap
 * Date 		: Jan 2, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 **********************************************************************/
int ContourMap:: Allocate_ContourMap(  const ContourMap & rhsContourMap  )
{


	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: LabelsToContours
 * Return Type 	: int
 * Created On	: Jan 3, 2013
 * Created By 	: hrushi
 * Comments		: Convert the Labels to Contours
 *******************************************************************/
int ContourMap::LabelsToContours(  const vector<int>& Labels, const Args& args  )
{

	LabelImage.resize( Labels.size() );
	std::copy( Labels.begin(), Labels.end(), LabelImage.begin() );

	UpdateContours( args );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: UpdateContours
 * Return Type 	: int
 * Created On	: Jan 21, 2013
 * Created By 	: hrushi
 * Comments		: Update the contours
 * Arguments	:
 *******************************************************************/
int ContourMap::UpdateContours( const Args& args )
{

	unsigned int minLabel = *std::min_element(LabelImage.begin(), LabelImage.end() );

	if( args.isVerbose() )
	{
		cout << "MinLabel: " << minLabel << endl;
	}

	unsigned int maxLabel = *std::max_element(LabelImage.begin(), LabelImage.end() );

	if( args.isVerbose() )
	{
		cout << "MaxLabel: " << maxLabel << endl;
	}

	NumLabels = maxLabel - minLabel;

	AllContourMap.clear();

	for( unsigned int i = 0; i <= NumLabels; i++ )
	{
		AllContourMap[i] = Eight_Connectivity(LabelImage, ImageNumRows, ImageNumCols, i);
	}

	GetListofLabels();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Eight_Connectivity
 * Return Type 	: Contour
 * Created On	: Jan 3, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * TODo			: TODO
 *******************************************************************/
Contour ContourMap::Eight_Connectivity(const vector<int>& LabeledImage, const unsigned int ImageNumRows, const unsigned int ImageNumCols, const unsigned int Label)
{
	Contour LabelContour;
	Mat BinaryImg(ImageNumRows, ImageNumCols, CV_8UC1, cv::Scalar(0,0,0));

	ImagePt PointOnImage;
	ImagePt TopLeft = LabelContour.GetTopLeft();
	ImagePt BottomRight = LabelContour.GetBottomRight();

	CreateBinaryMask(BinaryImg, LabeledImage, Label, TopLeft,  BottomRight);

	//Record the Label
	LabelContour.SetLabel( Label );

	// Create a deep copy of the Binary mask.
	LabelContour.SetCtrMask(BinaryImg.clone() ) ;

	vector< unsigned int > EightNeigbours;

	bool isPixelOnBorder 			= false;
	bool isPixelOnCountourBorder	= false;
	bool isPixelOnMask 				= false;

	for( int i = TopLeft.GetPoint().y; i <= BottomRight.GetPoint().y; i++ )
	{
		for(  int j = TopLeft.GetPoint().x; j <= BottomRight.GetPoint().x; j++ )
		{
			EightNeigbours = GetEightNeighbours(BinaryImg, i, j);
			isPixelOnBorder = isBorderPixel(i, j, ImageNumRows, ImageNumCols );
			isPixelOnCountourBorder = isContourBorder( EightNeigbours );
			isPixelOnMask = isOnMask(BinaryImg, i, j);

			if( isPixelOnMask )
			{
				if( isPixelOnBorder | isPixelOnCountourBorder )
				{
					PointOnImage.Set_X(i);
					PointOnImage.Set_Y(j);

					LabelContour.ContourPoints.push_back( PointOnImage );

					// Reset Cumulative Flags
					isPixelOnBorder = false;
					isPixelOnCountourBorder = false;

				}
			}
		}
	}

	VectorOp<ImagePt> oVPt;
	ImagePt CPt = oVPt.GetMean(LabelContour.ContourPoints);
	CPt.SwapXY(); // Swaping co-ordinates, because the image cordinates are swapped
	LabelContour.SetCenter( CPt );

	return LabelContour;
}


/*******************************************************************
 * Function Name: isOnMask
 * Return Type 	: bool
 * Created On	: Jan 3, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the pixel is on the Mask
 * Arguments	: const Mat& BinaryImage, const unsigned int iRow, const unsigned int iCol
 *******************************************************************/
bool ContourMap::isOnMask(  const Mat& BinaryImage, const unsigned int iRow, const unsigned int iCol) const
{
	bool Decision = false;

	if( BinaryImage.data[ iRow * BinaryImage.cols + iCol ] == 255 )
	{
		Decision = true;
	}
	return Decision;
}

/*******************************************************************
 * Function Name: isContourBorder
 * Return Type 	: bool
 * Created On	: Jan 3, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given pixel is on the contour border
 * Arguments	: const Vector< unsigned int >& EightNeighbours
 *******************************************************************/
bool ContourMap::isContourBorder( const vector< unsigned int >& EightNeighbours ) const
{

	bool Decision = false;

	unsigned int Min = *std::min_element(EightNeighbours.begin(), EightNeighbours.end() );
	unsigned int Max = *std::max_element(EightNeighbours.begin(), EightNeighbours.end() );

	if( Min != Max )
	{
		Decision = true;
	}

	return Decision;
}

/*******************************************************************
 * Function Name: isBorderPixel
 * Return Type 	: bool
 * Created On	: Jan 3, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given pixel is on the border
 * Arguments	: const unsigned int iRow, const unsigned int iCol, const unsigned int MaxRows, const unsigned int MaxCols
 *******************************************************************/
bool ContourMap::isBorderPixel( const unsigned int iRow, const unsigned int iCol, const unsigned int MaxRows, const unsigned int MaxCols ) const
{
	bool Decision = false;

	if( (iRow == 0 ) | (iRow == MaxRows ))
	{
		Decision = true;
	}

	if( (iCol == 0) | (iCol == MaxCols ))
	{
		Decision = true;
	}

	return Decision;
}

/*******************************************************************
 * Function Name: GetEightNeighbours
 * Return Type 	: vector<unsigned int>
 * Created On	: Jan 3, 2013
 * Created By 	: hrushi
 * Comments		: Returns the eight neighbours of pixel
 * TODo			:
 *******************************************************************/
vector<unsigned int> ContourMap::GetEightNeighbours( Mat BinaryImage, int iRow, int iCol )
{
	vector<unsigned int> Neighbours;

	unsigned int DataInx;
	unsigned int PixelVal;

	int iRowPlusI, iColPlusJ;

	for(int i = -1; i < 2; i++)
	{
		for( int j = -1; j < 2; j++)
		{

			iRowPlusI = iRow + i;
			iColPlusJ = iCol + j;

			if( ( iRowPlusI >= 0) & ( iColPlusJ >= 0 ))
			{
				if( ( iRowPlusI <= BinaryImage.rows) & (iColPlusJ <= BinaryImage.cols ))
				{
					DataInx = iRowPlusI *  BinaryImage.cols + iColPlusJ;
					PixelVal = BinaryImage.data[DataInx];

					Neighbours.push_back(PixelVal);
				}

			}

		}
	}

	return Neighbours;
}
/*******************************************************************
 * Function Name: CreateBinaryMask
 * Return Type 	: int
 * Created On	: Jan 3, 2013
 * Created By 	: hrushi
 * Comments		: Create a binary mask for the contour
 * TODo			:
 *******************************************************************/
int ContourMap::CreateBinaryMask( Mat& BinaryImg, const vector<int>& LabeledImage, const int Label, ImagePt& TopLeft, ImagePt& BottomRight )
{
	int PixelLabel;

	unsigned int DataIndx;
	unsigned int iNumRows(BinaryImg.rows), iNumCols( BinaryImg.cols);

	unsigned int MinRow(iNumRows), MinCol(iNumCols), MaxRow(0), MaxCol(0);

	for( unsigned int i = 0; i < iNumRows; i++ )
	{
		for( unsigned int j = 0; j < iNumCols; j++ )
		{
			DataIndx = i * iNumCols + j;
			PixelLabel = LabeledImage.at(DataIndx);

			if( PixelLabel == Label )
			{
				BinaryImg.data[ DataIndx ] = 255;

				if( i < MinRow )
					MinRow = i;

				if( j < MinCol )
					MinCol = j;

				if( i > MaxRow)
					MaxRow = i;

				if( j > MaxCol)
					MaxCol = j;
			}
			else
			{
				BinaryImg.data[ DataIndx ] = 0;
			}
		}
	}


	TopLeft.Set_X( MinCol );
	TopLeft.Set_Y( MinRow );

	BottomRight.Set_X( MaxCol );
	BottomRight.Set_Y( MaxRow );

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetCtrImg
 * Return Type 	: int
 * Created On	: Jan 4, 2013
 * Created By 	: hrushi
 * Comments		: Returns a gray image with the contours overlayed
 * Arguments	: const unsigned int ImageNumRows, const unsigned int ImageNumCols
 *******************************************************************/
GrayImg ContourMap::GetCtrImg( bool bPutText ) const
{
	GrayImg RetImg(ImageNumRows, ImageNumCols);

	Mat DisplayImage( ImageNumRows, ImageNumCols, CV_8UC1, cv::Scalar(0,0,0));

	unsigned int DataPtr;

	Contour BoundaryCtr;

	ImagePt CtrPt;
	ImagePt Center;
	cv::Point Pt;

	for( std::map<unsigned int, Contour >::const_iterator IterAllContour = AllContourMap.begin();	IterAllContour != AllContourMap.end(); IterAllContour++ )
	{

		BoundaryCtr = (*IterAllContour).second;
		for( unsigned int i = 0; i < BoundaryCtr.ContourPoints.size() -1; i++ )
		{
			CtrPt = BoundaryCtr.ContourPoints.at(i);

			DataPtr = CtrPt.GetX() * ImageNumCols + CtrPt.GetY();
			DisplayImage.data[DataPtr] = MAX_GRAY_VALUE;

		}

		if( bPutText )
		{
			BoundaryCtr.SetLabel( (*IterAllContour).first );
			std::stringstream ss;
			ss << BoundaryCtr.GetLabel();
			string strLabel = ss.str();

			Center = BoundaryCtr.GetCenter();
			Pt = Center.GetPoint();
			cv::putText(DisplayImage, strLabel, Pt, cv::FONT_HERSHEY_SIMPLEX, DISP_FONT_SCALE, cv::Scalar(255, 255, 255), 1, CV_AA, false );

			ss.clear();
			ss.flush();
			ss.str("");
		}

	}

	RetImg.SetImage(DisplayImage);

	return RetImg;
}



/*******************************************************************
 * Function Name: isNeighbouring
 * Return Type 	: bool
 * Created On	: Jan 7, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given two contours are neighbours of each other
 * Arguments	: const Contour& Cntur1, const Contour& Cntur2
 *******************************************************************/
bool ContourMap::isNeighbouring( const Contour& Cntur1, const Contour& Cntur2) const
{
	double dist(0);
	bool decision = false;

	ImagePt TempPt;

	for( vector<ImagePt>::const_iterator iter_Cntur1 = Cntur1.ContourPoints.begin(); iter_Cntur1 != Cntur1.ContourPoints.end(); iter_Cntur1++)
	{
		for (vector<ImagePt>::const_iterator  iter_Cntur2 = Cntur2.ContourPoints.begin(); iter_Cntur2 != Cntur2.ContourPoints.end(); iter_Cntur2++)
		{

			TempPt = *iter_Cntur1;

			dist = TempPt.Distance( *iter_Cntur2);

			if( dist == 1)
			{
				decision = true;
				break;
			}
		}

		// No need of going further
		if( decision )
		{
			break;
		}

	}
	return decision;
}

/*******************************************************************
 * Function Name: CalculateEveryContourHistgrm
 * Return Type 	: int
 * Created On	: Jan 10, 2013
 * Created By 	: hrushi
 * Comments		: Calculates histogram for every contour
 * Arguments	: const CImage& ProbeImage
 *******************************************************************/
int ContourMap::CalculateEveryContourHistgrm( const ColorImg& ProbeImage)
{

	MapElevenSpc HistMap;

	string LookUpPath = "./Data/Lookup.txt";
	try{

		static ReadHistLookup Lookup(LookUpPath);
		HistMap = Lookup.GetMap();

		for( std::map<unsigned int, Contour>::iterator itr = AllContourMap.begin();	itr != AllContourMap.end(); itr++)
		{
			(*itr).second.CalculateElevenSpaceHist( ProbeImage, Lookup );
		}
	}
	catch( unsigned int err )
	{
		cerr << " Error in LookUp Read in " << endl;
		throw err;
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetListOfBkCntrs
 * Return Type 	: vector<int>
 * Created On	: Jan 22, 2013
 * Created By 	: hrushi
 * Comments		: Returns the list of contours which lie on the foreground
 * Arguments	: vector<int> Labels, const GrayImg& BkImg
 *******************************************************************/
int ContourMap::ListBkContours( const GrayImg& BkImg, double OverlapThreshold , const Args& args )
{
	bool isBkground = true;
	BkLabels.clear();

	for(std::map<unsigned int, Contour>::iterator itr = AllContourMap.begin(); itr != AllContourMap.end()  ; itr++ )
	{
		if( args.isVerbose() )
		{
			BkImg.Overlay(itr->second, DISP_DELAY, cv::Scalar(255, 0, 0), args).Display(DISP_DELAY);
		}

		isBkground = (*itr).second.isBackground(BkImg, OverlapThreshold);

		if( isBkground  ) // Necessary condition for something to be on the background.
		{
			BkLabels.push_back((*itr).first);
		}
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: PrintBkLabels
 * Return Type 	: int
 * Created On	: Jan 23, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Bk Labels
 * Arguments	:
 *******************************************************************/
int ContourMap::PrintBkLabels( ) const
{

	Print oPrint;

	cout << "The list of background labels are " << endl;
	std::for_each( BkLabels.begin(), BkLabels.end(), oPrint );

	cout << endl;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: EditLabel
 * Return Type 	: int
 * Created On	: Jan 24, 2013
 * Created By 	: hrushi
 * Comments		: For every label in the vector, it sets to the Background Label
 * Arguments	: vector<int> ListofLabels, int NewLabel
 *******************************************************************/
int ContourMap::EditLabel( int BkgLabel  )
{
	for(vector<int>::iterator itr = BkLabels.begin(); itr != BkLabels.end(); itr++ )
	{
		ChangeLabel((*itr), BkgLabel );
	}

	ReOrderLabels();

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReOrderLabels
 * Return Type 	: int
 * Created On	: Jan 28, 2013
 * Created By 	: hrushi
 * Comments		: Reorders the labels from 0 to <n> after label change
 * Arguments	:
 *******************************************************************/
int ContourMap::ReOrderLabels()
{
	GetListofLabels();

	unsigned int NewLabel = 0;
	for( vector<int>::iterator itr = LabelList.begin(); itr != LabelList.end(); itr++ )
	{
		ChangeLabel( (*itr), NewLabel );
		NewLabel++;
	}

	GetListofLabels();

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetListofLabels
 * Return Type 	: int
 * Created On	: Jan 25, 2013
 * Created By 	: hrushi
 * Comments		: Goes through the Labels and lists all the distinct labels
 * Arguments	:
 *******************************************************************/
int ContourMap::GetListofLabels( )
{
	VectorOp <int>oVOp;
	oVOp.GetUniqueElem(LabelList, LabelImage);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: EditLabel
 * Return Type 	: int
 * Created On	: Jan 23, 2013
 * Created By 	: hrushi
 * Comments		: Edits the current label, with a new label
 * Arguments	: int CurrentLabel, int NewLabel
 *******************************************************************/
int ContourMap::ChangeLabel( int LabelToEdit, int NewLabel)
{
	vector<int> TempLabelImage;
	TempLabelImage.resize( LabelImage.size() );

	EditFunctor oEF( LabelToEdit, NewLabel);
	std::transform(LabelImage.begin(), LabelImage.end(), TempLabelImage.begin(), oEF );

	LabelImage.swap( TempLabelImage );

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: CopyLabelImage
 * Return Type 	: int
 * Created On	: Jan 24, 2013
 * Created By 	: hrushi
 * Comments		: Copies the Label Image to the passed vector<int> reference
 * Arguments	: vector<int>& CopyofLabelImg
 *******************************************************************/
int ContourMap::CopyLabelImage( vector<int>& CopyofLabelImg) const
{

	CopyofLabelImg.resize(  LabelImage.size() );
	//std::copy( LabelImage.begin(), LabelImage.end(), CopyofLabelImg.begin() );

	CopyofLabelImg = LabelImage;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: PopulateScoreMap
 * Return Type 	: int
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: Populates the comparision score map of all the contours
 * Arguments	:
 *******************************************************************/
int ContourMap::PopulateScoreMap( const Args& args  )
{

	double ColorDotProduct(0);


	ScoreMap.Initialize( GetNumContours() );

	ElevenSpaceHist Hist1, Hist2;

	// --PopulatedContoures.end() because PopulatedContoures.end() - 1 does not exist
	for(std::map<unsigned int, Contour>::const_iterator itr = AllContourMap.begin(); itr != AllContourMap.end()  ; itr++ )
	{
		for( std::map<unsigned int, Contour >::const_iterator itr_cmpr = AllContourMap.begin(); itr_cmpr != AllContourMap.end(); itr_cmpr++ )
		{
			if( (*itr).first !=  (*itr_cmpr).first )
			{
				if( isNeighbouring( (*itr).second, (*itr_cmpr).second ) )
				{

					Hist1 = (*itr).second.GetElSpcHist();
					Hist2 = (*itr_cmpr).second.GetElSpcHist();

					ColorDotProduct = Hist1.GetMatchScore( Hist2 );

					ScoreMap.Set((*itr).first, (*itr_cmpr).first,  ColorDotProduct );

				}
			}
		}
	}

	if( args.isVerbose() )
	{
		cout << "Score Map" << endl;
		cout << ScoreMap;
	}


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetMatchingCandidate
 * Return Type 	: int
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: Get the matching Candidate for the given contour
 * Arguments	:  unsigned int Cntr
 *******************************************************************/
int ContourMap::GetMatchingCandidate(  unsigned int Cntr, double MatchThreshold ) const
{
	int MatchCandidate = -1;

	MatchCandidate = ScoreMap.GetBestMatch(Cntr, MatchThreshold);

	return MatchCandidate;
}


/*******************************************************************
 * Function Name: GetOpenCVCtrs
 * Return Type 	: const vector< vector< cv::Point> >
 * Created On	: Oct 5, 2013
 * Created By 	: hrushi
 * Comments		: Returs the contours in OpenCV compatible format
 * Arguments	:
 *******************************************************************/
const vector< vector< cv::Point> > ContourMap::GetOpenCVCtrs( ) const
{
	vector< vector< cv::Point> > Ctrs;

	for(unsigned int i = 0; i < AllContourMap.size(); i++ )
	{
		vector<cv::Point> TempPts = AllContourMap.at(i).GetOpenCVPts();
		Ctrs.push_back(TempPts);
	}


	return Ctrs;
}

