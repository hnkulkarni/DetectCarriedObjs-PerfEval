/*
 * Detect.cpp
 *
 *  Created on: Dec 31, 2012
 *      Author: hrushi
 */

#include "Detect.h"

/**********************************************************************
 * Function Name: Detect
 * Date 		: Dec 31, 2012
 * Author		: hrushi
 * Comments		: Constructor
 **********************************************************************/
Detect::Detect(  const ColorImg ProbeImg, const GrayImg BkImg, const ContourMap& Segments, const Args& args  )
{
	m_ProbeImg 	= ProbeImg;
	m_BkImg		= BkImg;
	m_Segments 	= Segments;

	LoadPoseData( args );

	SetDefaults();
}

/*******************************************************************
 * Function Name: SetDefaults
 * Return Type 	: int
 * Created On	: Jan 4, 2014
 * Created By 	: hrushi
 * Comments		: Set the defaults
 * Arguments	:
 *******************************************************************/
int Detect::SetDefaults( )
{
	//Set the Size of the score to match the number of labels
	m_Default_Person_Score.resize(NUM_LABELS);

	m_Default_Person_Score.at(WORN_CARRY_LABEL) = 0;
	m_Default_Person_Score.at(DRAG_CARRY_LABEL) = 0;
	m_Default_Person_Score.at(PERSON_LABEL)		= 1;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Detect
 * Date 		: Dec 31, 2012
 * Author		: hrushi
 * Comments		: Destructor
 **********************************************************************/
Detect::~Detect()
{

}


/**********************************************************************
 * Function Name: Detect
 * Date 		: Dec 31, 2012
 * Author		: hrushi
 * Comments		: Copy Constructor
 **********************************************************************/
Detect::Detect( const Detect& rhsDetect )
{
	Allocate_Detect( rhsDetect );
	Copy_Detect( rhsDetect );
}




/**********************************************************************
 * Function Name: operator
 * Date 		: Dec 31, 2012
 * Author		: hrushi
 * Comments		: Assignment Operator
 **********************************************************************/
Detect& Detect :: operator=( const Detect & rhsDetect )
{
	Allocate_Detect( rhsDetect );
	Copy_Detect( rhsDetect );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Detect
 * Date 		: Dec 31, 2012
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 **********************************************************************/
int Detect:: Copy_Detect(  const Detect & rhsDetect  )
{
	m_BkImg				 	= rhsDetect.m_BkImg;
	m_ProbeImg				= rhsDetect.m_ProbeImg;
	m_Segments				= rhsDetect.m_Segments;
	m_TrainingFolderPath 	= rhsDetect.m_TrainingFolderPath;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_Detect
 * Date 		: Dec 31, 2012
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int Detect:: Allocate_Detect(  const Detect & rhsDetect  )
{

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: GetSegments
 * Return Type 	: int
 * Created On	: Jan 1, 2013
 * Created By 	: hrushi
 * Comments		: Gets the Segments of objects
 *******************************************************************/
ContourMap Detect::GetSegments( const ColorImg ProbeImg, const GrayImg BkImg, bool bSaveOutput, const Args& args  )
{

	fs::path iPath = ProbeImg.GetImagePath();

	fs::path OutputPath;

	OutputPath = GiveSegImgPath(iPath, "_seg");

	ContourMap Cnturs;

	for( int K = SLIC_K; K >= 1; K-- )
	{
		try
		{
			Segmentation Segm;
			Cnturs = Segm.GetSegments(ProbeImg, BkImg, OutputPath.string(), bSaveOutput, K, SLIC_M, args );
		}
		catch(int iERR)
		{
			if( iERR == ERR_SLIC )
			{
				cerr << "Calling Slick with K: " << (K - 1) << endl;
				continue;
			}
		}

		break;
	}

	if(bSaveOutput)
	{
		ColorImg Overlay = ProbeImg.Overlay(Cnturs, 1, cv::Scalar(0, 0, 255), args);
		string OverlayWrite  = GiveSegImgPath(iPath, "_Merge").string();
		Overlay.Write( OverlayWrite );
	}

	return Cnturs;
}


/*******************************************************************
 * Function Name: GiveSegImgPath
 * Return Type 	: const fs::path
 * Created On	: Aug 21, 2013
 * Created By 	: hrushi
 * Comments		: For the given image path. It creates a segmentation folder and returns the path where the image could be stored
 * Arguments	: const fs::path& ImgPath
 *******************************************************************/
const fs::path Detect::GiveSegImgPath( const fs::path& iPath, const string Suffix)
{
	fs::path SegImgPath;


	fs::path SegFldr = iPath.parent_path().string() + "/Seg";
	fs::create_directory(SegFldr);

	string OutputPath;
	OutputPath = SegFldr.parent_path().string() + "/Seg/";
	OutputPath +=  iPath.stem().string() + Suffix;
	OutputPath +=  iPath.extension().string();

	SegImgPath = OutputPath;

	return SegImgPath;
}



/*******************************************************************
 * Function Name: GetFinalScore
 * Return Type 	: const pr_score
 * Created On	: Oct 27, 2013
 * Created By 	: hrushi
 * Comments		: Given the seprate scores for dWorn, dDrag and dNoCarry; It will return a final score
 * Arguments	: double dWorn, double dDrag, double dNoCarry
 *******************************************************************/
const pr_score Detect::GetFinalScore( double dWornLog, double dDragLog, double dNoCarryLog, vector<double>& vAllScores)
{
	pr_score RetPair;

	//---------- The order of these push_back is important
	//           Do not change ---------- //

	double dWorn 	= pow(2, dWornLog);
	vAllScores.push_back(dWorn);

	double dDrag 	= pow(2, dDragLog);
	vAllScores.push_back(dDrag);

	double dPerson 	= pow(2, dNoCarryLog );
	vAllScores.push_back(dPerson);

	//---------- Do not change ends ---------- //
	double dWornRatio = dWorn / dPerson;
	double dDragRatio = dDrag / dPerson;

	if((dWornRatio > 1 ) || (dDragRatio > 1)) //Carry probability is more than no-carry probability
	{
		if( dWornRatio > dDragRatio )
		{
			RetPair.first 	= WORN_CARRY_LABEL;
			RetPair.second	= dWorn;
		}
		else
		{
			RetPair.first 	= DRAG_CARRY_LABEL;
			RetPair.second 	= dDrag;
		}
	}
	else
	{
		RetPair.first	= PERSON_LABEL;
		RetPair.second	= dPerson;
	}

	return RetPair;
}


/*******************************************************************
 * Function Name: GetType
 * Return Type 	: int
 * Created On	: Nov 2, 2013
 * Created By 	: hrushi
 * Comments		: Get the Type of image label, if Worn_Carry, or Drag_Carry or No_Carry
 * Arguments	: const string sImgPath
 *******************************************************************/
int Detect::GetType( const string sImgPath, const Args& args)
{
	Labels Drag_Carry_Lbl(args, DRAG_CARRY_LABEL_FILE);
	Drag_Carry_Lbl.Read(args);

	Labels Worn_Carry_Lbl(args, WORN_CARRY_LABEL_FILE);
	Worn_Carry_Lbl.Read(args);

	Labels AllLbl(args, ALL_LABEL_FILENAME);
	AllLbl.Read(args);

	if( Drag_Carry_Lbl.AlreadyPresent(sImgPath, true ) != UN_INITIALIZED_LABEL )
	{
		return DRAG_CARRY_LABEL;
	}
	else if( Worn_Carry_Lbl.AlreadyPresent(sImgPath, true ) != UN_INITIALIZED_LABEL )
	{
		return WORN_CARRY_LABEL;
	}
	else
	{
		return PERSON_LABEL;
	}

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: PrintScoreMap
 * Return Type 	: int
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Score Map
 * Arguments	:
 *******************************************************************/
int Detect::PrintScoreMap( TYPE_MAP_CNTRSCORE ScoreMap  ) const
{

	cout << "\t Backpack \t Suitcase \t Person " << endl;

	for(auto Score : ScoreMap )
	{
		cout << "[" << std::setw(5)  << Score.first << "] " << Score.second << endl;
	}

	return EXIT_SUCCESS;
}




/*******************************************************************
 * Function Name: AnalyzeScores
 * Return Type 	: const vector<TYPE_PAIR_RGN_TYPE>
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Reads the scores, and returns the carry type against the region number
 * Arguments	: const TYPE_MAP_CNTRSCORE& CtrMap
 *******************************************************************/
const vector<TYPE_TUPLE_RGN_TYPE> Detect::FormatCarryScores( const TYPE_MAP_CNTRSCORE& CtrScoreMap) const
{
	vector<TYPE_TUPLE_RGN_TYPE> vRgnNType;

	for( auto ScoreMap : CtrScoreMap )
	{
		double MaxVal = VectorOp<double>::GetMaxVal( ScoreMap.second );
		int MaxIdx = VectorOp<double>::GetIndex( ScoreMap.second, MaxVal);

		auto TempTuple = std::forward_as_tuple( ScoreMap.first, MaxIdx, MaxVal );
		vRgnNType.push_back( TempTuple );

	}

	return vRgnNType;
}



/*******************************************************************
 * Function Name: GetCarryContours
 * Return Type 	: const vector<CarryContour>
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Returns a vector of Carry Contours based on the the Location Scores
 * Arguments	:  const vector<TYPE_TUPLE_RGN_TYPE>& vRgnType
 *******************************************************************/
const vector<CarryContour> Detect::MakeDetectionContours(  const vector<TYPE_TUPLE_RGN_TYPE>& vRgnType, const TYPE_MAP_CNTRSCORE ScoreMap  ) const
{
	vector<CarryContour> vCarryCtrs;

	cout << "Size of Rgns " << vRgnType.size() << endl;
	PrintScoreTuple(vRgnType);

	for(auto ScrTpl : vRgnType )
	{
		unsigned int RgnNum = std::get<0>(ScrTpl);
		int CarryType = std::get<1>(ScrTpl);
		double CarryScore = std::get<2>( ScrTpl );

		CarryContour TempContour =	m_Segments.AllContourMap.at(RgnNum);
		TempContour.SetCarryTypeNScore(CarryType, CarryScore);
		TempContour.SetAllScores(ScoreMap.at(RgnNum));

		vCarryCtrs.push_back( TempContour );

	}

	return vCarryCtrs;
}


/*******************************************************************
 * Function Name: PrintScoreTuple
 * Return Type 	: const int
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Score Tuples
 * Arguments	: const vector<TYPE_TUPLE_RGN_TYPE>& ScoreTuple
 *******************************************************************/
int Detect::PrintScoreTuple( const vector<TYPE_TUPLE_RGN_TYPE>& vScoreTuple) const
{

	cout << "Rgn # \t Carry Type \t Score " << endl;
	for( auto ScrTpl : vScoreTuple )
	{
		cout << std::get<0>(ScrTpl) << " " << std::get<1>(ScrTpl)  << " " << std::get<2>(ScrTpl) << endl;
	}
	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: LoadPoseData
 * Return Type 	: int
 * Created On	: Dec 28, 2013
 * Created By 	: hrushi
 * Comments		: Load the pose data
 * Arguments	: const Args& args
 *******************************************************************/
int Detect::LoadPoseData( const Args& args)
{
	try
	{
		const fs::path ImgPath = m_ProbeImg.GetImagePath();
		cout << "Probe Img Path is: " << ImgPath << endl;

		const fs::path PosePath = PoseFile::GetBoxFilePath( ImgPath );
		cout << "Pose Path: " << PosePath << endl;

		PoseFile oPose(PosePath);

		//---------- Commenting this display line  ---------- //
		//oPose.m_Pose.Overlay(m_ProbeImg, "all").Display(DISP_KEY_PRESS);

		m_PoseData = oPose.m_Pose;
		m_PoseInfoAvailable = true;

	}
	catch(int Err)
	{
		m_PoseInfoAvailable = false;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: LogToProb
 * Return Type 	: const vector<double>
 * Created On	: Apr 22, 2014
 * Created By 	: hrushi
 * Comments		: Converts the LogLikelihoods to probabilities
 * Arguments	: const vector<double>& vLogScore
 *******************************************************************/
const vector<double> Detect::LogToProb( const vector<double>& vLogScore) const
{
	vector<double> ProbScore;

	for(auto LogElement : vLogScore )
	{
		double Carry_Prob	= pow(2, LogElement);
		ProbScore.push_back(Carry_Prob);
	}

	return ProbScore;
}
