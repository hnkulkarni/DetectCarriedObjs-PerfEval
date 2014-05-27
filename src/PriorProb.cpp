/*
 * PriorProb.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: hrushi
 */

#include "PriorProb.h"

PriorProb::PriorProb()
{
	Init_Members();
}

PriorProb::~PriorProb()
{

}

/*****************************************************
 * Function	: PriorProb Copy Constructor
 * Date		: Jul 14, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
PriorProb::PriorProb(const PriorProb& rhsPriorProb )
{
	Allocate( rhsPriorProb );
	Copy( rhsPriorProb );
}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 14, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
PriorProb& PriorProb:: operator=( const PriorProb& rhsPriorProb )
{
	Allocate( rhsPriorProb );
	Copy( rhsPriorProb );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 14, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int PriorProb::Allocate( const PriorProb& rhsPriorProb )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 14, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int PriorProb::Copy( const PriorProb& rhsPriorProb )
{
	m_NumCntrs 				= rhsPriorProb.m_NumCntrs;
	m_PriorProb_WornObj 	= rhsPriorProb.m_PriorProb_WornObj;
	m_PriorProb_DraggedObj 	= rhsPriorProb.m_PriorProb_DraggedObj;
	m_PriorProb_PersonRgn 	= rhsPriorProb.m_PriorProb_PersonRgn;
	m_LocationPriorProb		= rhsPriorProb.m_LocationPriorProb;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 14, 2013
 * Created By 	: hrushi
 * Comments		: Initializes all the Member Variables
 * Arguments	:
 *******************************************************************/
int PriorProb::Init_Members( )
{

	m_PriorProb_WornObj 	= 0;
	m_PriorProb_DraggedObj 	= 0;
	m_PriorProb_PersonRgn 	= 0;
	m_NumCntrs				= 0;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: CalculatePriorProbs
 * Return Type 	: int
 * Created On	: Jul 14, 2013
 * Created By 	: hrushi
 * Comments		: Calculate Prior Probabilities
 * Arguments	: const string TrainFolderPath, const vector<ProbImg>& vProbsImgs
 *******************************************************************/
int PriorProb::CalculatePriorProbs( const fs::path TrainFolderPath, const vector<ProbImg>& vProbsImgs, const Args& args)
{
	CalculateLocationPriorProbs(vProbsImgs, args );
	CalculateRgnPriorProbs( TrainFolderPath, args );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: CalculateLocationPriorProbs
 * Return Type 	: ProbImg
 * Created On	: Jul 15, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the prior probability of an
 * Arguments	: const vector<ProbImg>& vPrbImgs, const Args& args
 *******************************************************************/
int PriorProb::CalculateLocationPriorProbs( const vector<ProbImg>& vPrbImgs, const Args& args )
{
	ProbImg CombinedProbImg = vPrbImgs.at(0) + vPrbImgs.at(1);
	CombinedProbImg = CombinedProbImg + vPrbImgs.at(2);

	m_LocationPriorProb = CombinedProbImg;
	m_LocationPriorProb.Display(DISP_DELAY);

	string FolderPath = args.GetTrainFolderPath();
	if( FolderPath.length() == 0 )
	{
		FolderPath = args.GetSearchFolderPath();
	}
	const string ImgPath = FolderPath + LOC_PRIOR_PROB_IMGNAME;
	m_LocationPriorProb.SetImagePath(ImgPath);
	m_LocationPriorProb.Write( ImgPath );

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: CalculateRgnPriorProbs
 * Return Type 	: int
 * Created On	: Jul 14, 2013
 * Created By 	: hrushi
 * Comments		: Calculate the Region Prior Probs
 * Arguments	: const string TrainFolderPath
 *******************************************************************/
int PriorProb::CalculateRgnPriorProbs( const fs::path TrainFolderPath, const Args& args)
{

	Labels AllLabels( TrainFolderPath, ALL_LABEL_FILENAME);
	Labels Dragged_Lbl(TrainFolderPath, DRAG_CARRY_LABEL_FILE);
	Labels Worn_Lbl(TrainFolderPath, WORN_CARRY_LABEL_FILE);

	unsigned int NumPersonCntrs(0);
	unsigned int NumWornCntrs(0);
	unsigned int NumDraggedCntrs(0);

	for(tdef_LabelMap::const_iterator itr = AllLabels.GetLabelMapItrBegin(); itr != AllLabels.GetLabelMapItrEnd(); itr++ )
	{
		fs::path RelativeImgPath = itr->first;
		fs::path TrackImgPath 	= AllLabels.GetComplateImgFilePath( RelativeImgPath.string() );

		fs::path MaskImgPath = FileSystem::GetMaskImgPath(args.GetMaskFolderName(), TrackImgPath, args.GetTrackFolderName() );
		ContourMap CntrMap = Detect::GetSegments(TrackImgPath, MaskImgPath, false, args);

		if( CntrMap.GetNumContours() > 1 ) //
		{
			unsigned int NumCtrs = CntrMap.GetNumContours() - 1; // Get Number of contours that are not background
			m_NumCntrs += NumCtrs;

			if( itr->second == NO_CARRIED_OBJECT )
			{
				NumPersonCntrs += NumCtrs;
			}
			else
			{
				// NumPerson Cntrs will be the number of contours -1; -1 for the any of the two labels below
				NumPersonCntrs  += NumCtrs - 1;
				if( Dragged_Lbl.AlreadyPresent(RelativeImgPath) != UN_INITIALIZED_LABEL )
				{
					NumDraggedCntrs++;
				}
				else if( Worn_Lbl.AlreadyPresent(RelativeImgPath) != UN_INITIALIZED_LABEL )
				{
					NumWornCntrs++;
				}

			}
		}
	}

	m_PriorProb_DraggedObj	= (double)NumDraggedCntrs / m_NumCntrs;
	m_PriorProb_WornObj 	= (double)NumWornCntrs 	  / m_NumCntrs;
	m_PriorProb_PersonRgn	= (double)NumPersonCntrs  / m_NumCntrs;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: isValid
 * Return Type 	: bool
 * Created On	: Jul 18, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the Probability calculation is valid or not; If correct then all should sum to 1
 * Arguments	:
 *******************************************************************/
bool PriorProb::isValid( ) const
{
	bool Decision(false);

	double Sum = m_PriorProb_DraggedObj + m_PriorProb_PersonRgn + m_PriorProb_WornObj;
	double Diff = abs( Sum - 1);

	if( Diff < std::numeric_limits<double>::epsilon() )
	{
		Decision = true;
	}
	else
	{
		Decision = false;
	}

	return Decision;
}


/*******************************************************************
 * Function Name: operator<<
 * Return Type 	: ostream&
 * Created On	: Jul 18, 2013
 * Created By 	: hrushi
 * Comments		: Writes the Prior Probabilites
 * Arguments	: const PriorProb& rhsPriorProb
 *******************************************************************/
std::ostream& operator<<( std::ostream& out, const PriorProb& rhsPPrb)
{
	out << "Dragged_Obj " << rhsPPrb.Get_DraggedObjPrior() << endl;
	out << "WornObj " << rhsPPrb.Get_WornObjPrior() << endl;
	out << "Person " << rhsPPrb.Get_PersonPrior() << endl;
	out << "Location_Prior_ImgName " << rhsPPrb.Get_LocationPrior().GetImagePath().filename().string() << endl;

	return out;
}
