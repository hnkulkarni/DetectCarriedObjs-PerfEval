/*
 * AlgoTest.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#include "AlgoTest.h"
#include <iosfwd>

/*****************************************************
 * Function	: Constructor
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	: Sets the loading functions for all the detection class
 * 				1. Saves the Training data path
 * 				2. Loads the Probability Images
 * Args		: Training data path
 * Return	: Self Pointer
 *****************************************************/
AlgoTest::AlgoTest( const Args& args  )
{

	fs::path TrainFolderPath = args.GetTrainFolderPath();

	LoadTrainingPath( TrainFolderPath );
	LoadProbImgs( TrainFolderPath );
	LoadPriorProbs( TrainFolderPath, m_vProbImgs, args );

}


/*****************************************************
 * Function	: Destructor
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: AlgoTest Class Destructor
 * Return	:
 *****************************************************/
AlgoTest::~AlgoTest()
{

}

/*****************************************************
 * Function	: AlgoTest Copy Constructor
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
AlgoTest::AlgoTest(const AlgoTest& rhsAlgoTest )
{
	Allocate( rhsAlgoTest );
	Copy( rhsAlgoTest );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
AlgoTest& AlgoTest:: operator=( const AlgoTest& rhsAlgoTest )
{
	Allocate( rhsAlgoTest );
	Copy( rhsAlgoTest );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int AlgoTest::Allocate( const AlgoTest& rhsAlgoTest )
{

	m_vProbImgs.resize( rhsAlgoTest.m_vProbImgs.size() );


	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int AlgoTest::Copy( const AlgoTest& rhsAlgoTest )
{
	m_TrainFolderPath 	= rhsAlgoTest.m_TrainFolderPath;
	m_vProbImgs 		= rhsAlgoTest.m_vProbImgs;
	m_PriorProbs 		= rhsAlgoTest.m_PriorProbs;


	return EXIT_SUCCESS;
}




/*******************************************************************
 * Function Name: LoadPriorProbs
 * Return Type 	: int
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Loads the Prior Probabilities
 * Arguments	: const fs::path TrainingFolderPath
 *******************************************************************/
const PriorProb AlgoTest::LoadPriorProbs( const fs::path TrainingFolderPath, const vector<ProbImg>& vProbImgs, const Args& args )
{

	const string sPriorProbFilePath = args.GetTrainFolderPath() + PRIOR_PROB_FILENAME;

	if( vProbImgs.size() < 3 )
	{
		cerr << "All Probability images are not calculated " << endl;
		cerr << "These Probability images are required for calculation " << endl;
		cerr << "Returning an error " << endl;
		exit(ERR_INVALID_ARGS);
	}

	try
	{
		ReadPriorProb rdPriorProb( sPriorProbFilePath );
		m_PriorProbs = rdPriorProb.Get_PriorProb();
	}
	catch(int Err)
	{

		switch(Err)
		{
		case ERR_CANNOT_OPEN_FILE:
			cout << "Cannot open PriorProb file. Calculating Prior Probs again " << endl;
			cv::waitKey(ONE_SECOND); // Wait for the user to read the above message!!

			WritePriorProbs wPP( sPriorProbFilePath );
			m_PriorProbs.CalculatePriorProbs(TrainingFolderPath, vProbImgs, args );
			wPP.Set_PriorProb( m_PriorProbs );
			wPP.WriteOut();
			break;
		}
	}

	cout << "Loaded Prior Probs are " << endl;
	cout << m_PriorProbs << endl;

	return m_PriorProbs;
}
/*******************************************************************
 * Function Name: LoadTrainingPath
 * Return Type 	: int
 * Created On	: Jun 18, 2013
 * Created By 	: hrushi
 * Comments		: Loads the Training folder path
 * Arguments	: const fs::path TrainingFolderPath
 *******************************************************************/
int AlgoTest::LoadTrainingPath( const fs::path TrainingFolderPath)
{
	if( fs::exists( TrainingFolderPath ))
	{
		m_TrainFolderPath = TrainingFolderPath;
	}
	else
	{
		cerr << "Train Path: " << TrainingFolderPath << " does not exist "<< endl;
		throw ERR_INVALID_PATH;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: LoadProbImg
 * Return Type 	: int
 * Created On	: Jun 18, 2013
 * Created By 	: hrushi
 * Comments		: Loads the Probability Images used for Testing
 * Arguments	: const fs::path TrainingPath
 *******************************************************************/
int AlgoTest::LoadProbImgs( const fs::path TrainingPath)
{
	vector<string> vProbImgList = {WORN_CARRY_PROB_IMG, DRAG_CARRY_PROB_IMG, PERSON_LOC_PROB_PROB_IMG};
	ProbImg ProbTemp;

	for(auto ImgName : vProbImgList)
	{
		ProbTemp.Load( TrainingPath.string() + ImgName );
		m_vProbImgs.push_back(ProbTemp);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: CalLocationPriorProb
 * Return Type 	: const ProbImg
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the combined Location Prior Probability of an image
 * Arguments	: const vector<ProbImg>& vPrbImgs
 *******************************************************************/
const ProbImg AlgoTest::CalLocationPriorProb( const vector<ProbImg>& vPrbImgs) const
{
	ProbImg CombinedProbImg = vPrbImgs.at(0) + vPrbImgs.at(1);
	CombinedProbImg = CombinedProbImg + vPrbImgs.at(2);
	return CombinedProbImg;
}


/*******************************************************************
 * Function Name: DetectionAlgo
 * Return Type 	: vector<Contour>
 * Created On	: Jun 17, 2013
 * Created By 	: hrushi
 * Comments		: Runs my Detection Algo
 * Arguments	:  const ColorImg& ProbeImg, const GrayImg& BkImg, const Args& args
 *******************************************************************/
const AllDetectedCtrs AlgoTest::DetectionAlgo(  const fs::path ProbeImgPath, const fs::path BkImgPath,  const string AlgoType, const Args& args)
{

	const string AlgoTypeOpt = boost::to_lower_copy( AlgoType );
	bool bAllTypes = ( AlgoTypeOpt == "all" )? true : false;

	AllDetectedCtrs CarriedDetections;

	ContourMap Segments = Detect::GetSegments(ProbeImgPath, BkImgPath, true, args);

	vector<CarryContour>  CarryByPose, CarryRgn_ByLocation, CarryRgn_ByShape, CarryRgn_ByAppr;

	/**************************************************************
	 *           Detection By Pose
	 **************************************************************/
	if( bAllTypes || ( AlgoTypeOpt == "pose" ))
	{
		DetectByPose DPos( ProbeImgPath, BkImgPath, m_vProbImgs, Segments, args );
		CarryByPose = DPos.GetCarried();
		CarriedDetections.Set_vCtrs( CarryByPose );

	}

	/**************************************************************
	 *           Detection By Location
	 **************************************************************/
	if( bAllTypes || ( AlgoTypeOpt == "location"  ))
	{
		DetectByLocation DLoc( ProbeImgPath, BkImgPath, m_vProbImgs, m_PriorProbs, Segments, args );
		CarryRgn_ByLocation = DLoc.GetCarried( args );
		CarriedDetections.Set_vCtrs( CarryRgn_ByLocation );
	}

	/**************************************************************
	 *           Detect By Shape
	 **************************************************************/
	if( bAllTypes || ( AlgoTypeOpt == "shape"))
	{
		DetectByShape DShape( ProbeImgPath, BkImgPath,  Segments, args);
		CarryRgn_ByShape = DShape.GetCarried( HuMoments() );
		CarriedDetections.Set_vCtrs( CarryRgn_ByShape);
	}
	/**************************************************************
	 *           Detect By Appearance
	 **************************************************************/
	if( bAllTypes || (AlgoTypeOpt == "appearance"))
	{
		BOF oBof(LEARN_MODE);
		oBof.Load(args);

		DetectByAppearance DAppr( ProbeImgPath, BkImgPath, Segments, args);
		CarryRgn_ByAppr = DAppr.GetCarried(oBof, args);
		CarriedDetections.Set_vCtrs( CarryRgn_ByAppr);

	}

	if(bAllTypes)
	{
	vector<CarryContour> Combined = DetectbyVoting(CarryRgn_ByLocation,CarryRgn_ByShape,CarryByPose, CarryRgn_ByAppr);
	CarriedDetections.Set_vCtrs( Combined );
	}

	/*	if(bAllTypes)
	{
		CarriedDetections = DetectionByAll(ProbeImgPath, BkImgPath, Segments, AlgoType, args);
	}
	 */


	return CarriedDetections;
}

/*******************************************************************
 * Function Name: DetectByVoting
 * Return Type 	: const AllDetectedCtrs
 * Created On	: Jan 10, 2014
 * Created By 	: hrushi
 * Comments		: Detecting if the given region is carried based on different detection votes
 * Arguments	: const vector<CarryContour>& CrLoc, const vector<CarryContour>& CrShape, const vector<CarryContour>& CrPose, const vector<CarryContour>& CrAppr
 *******************************************************************/
const vector<CarryContour> AlgoTest::DetectbyVoting( const vector<CarryContour>& CrLoc, const vector<CarryContour>& CrShape, const vector<CarryContour>& CrPose, const vector<CarryContour>& CrAppr) const
{
	vector<CarryContour> DVote;
	bool bPoseInfo = false;
	UINT VoteWinCount = 1;

	if( CrPose.size() > 0 )
	{
		bPoseInfo = true;
		VoteWinCount = 2;
	}
	else
	{
		VoteWinCount = 1;
	}

	for(UINT i = 0; i < CrLoc.size(); i++ )
	{
		UINT CrryTypLoc 	 = CrLoc.at(i).GetCarryType();
		UINT CrryTypPose = 0;

		if( bPoseInfo )
		{
			CrryTypPose  = CrPose.at(i).GetCarryType(); //( CrryTypPose != PERSON_LABEL )
		}

		UINT CrryTypShape = CrShape.at(i).GetCarryType();
		UINT CrryTypAppr  = CrAppr.at(i).GetCarryType();

		CarryContour TempCtr = CrLoc.at(i);
		UINT VoteCount = 0;

		if( CrryTypLoc != PERSON_LABEL )
		{
			VoteCount++;
		}

		if( bPoseInfo && ( CrryTypPose != PERSON_LABEL ) )
		{
			VoteCount++;
		}


		if( CrryTypShape != PERSON_LABEL )
		{
			VoteCount++;
		}

		if( CrryTypAppr != PERSON_LABEL )
		{
			VoteCount++;
		}

		if( VoteCount > VoteWinCount )
		{
			TempCtr.SetCarryTypeNScore(DRAG_CARRY_LABEL, CrLoc.at(i).GetCarryScore() );
		}
		else
		{
			TempCtr.SetCarryTypeNScore(PERSON_LABEL, CrLoc.at(i).GetCarryScore() );
		}

		DVote.push_back(TempCtr);

	}


	return DVote;
}


/*******************************************************************
 * Function Name: DetectionByAll
 * Return Type 	: AllDetectedCtrs
 * Created On	: Dec 11, 2013
 * Created By 	: hrushi
 * Comments		: All Detected Contours
 * Arguments	: const fs::path ProbeImgPath, const fs::path BkImgPath, const string AlgoType, const Args& args
 *******************************************************************/
const AllDetectedCtrs AlgoTest::DetectionByAll( const fs::path ProbeImgPath, const fs::path BkImgPath, const ContourMap& Segments, const string AlgoType, const Args& args )
{
	AllDetectedCtrs CarriedDetections;

	//---------- Score by Location Detection ---------- //
	TYPE_MAP_CNTRSCORE mapLocScore;
	DetectByLocation DLoc( ProbeImgPath, BkImgPath, m_vProbImgs, m_PriorProbs, Segments, args );
	mapLocScore = DLoc.CalAllCntrScore( Segments.AllContourMap, args);
	DLoc.PrintScoreMap(mapLocScore);

	//---------- Score by Shape Detection  ---------- //
	TYPE_MAP_CNTRSCORE mapShapeScore;
	DetectByShape DShape( ProbeImgPath, BkImgPath,  Segments, args);
	mapShapeScore = DShape.CalAllCntrScore(Segments.AllContourMap,  HuMoments(), m_PriorProbs );
	DShape.PrintScoreMap(mapShapeScore);

	//---------- Score by Pose Detection ---------- //
	TYPE_MAP_CNTRSCORE mapPoseScore;
	DetectByPose DPose( ProbeImgPath, BkImgPath, m_vProbImgs,  Segments, args);
	mapPoseScore = DPose.CalAllCntrScore(Segments.AllContourMap, args);


	//---------- Score by Apperance Detection ---------- //
	TYPE_MAP_CNTRSCORE mapApprScore;
	DetectByAppearance DAppr( ProbeImgPath, BkImgPath, Segments, args);
	DAppr.CalAllCntrScore(Segments.AllContourMap, args);

	//---------- Taking the Products of the scores ---------- //
	TYPE_MAP_CNTRSCORE mapProd;
	mapProd = Product(mapLocScore, mapShapeScore);

	DLoc.PrintScoreMap(mapProd);

	vector<TYPE_TUPLE_RGN_TYPE> vRgnNType = DLoc.FormatCarryScores( mapProd );
	vector<CarryContour> CarriedCntrs = DLoc.MakeDetectionContours( vRgnNType, mapLocScore );

	CarriedDetections.Set_vCtrs(CarriedCntrs);



	return CarriedDetections;
}


/*******************************************************************
 * Function Name: Product
 * Return Type 	: TYPE_MAP_CNTRSCORE
 * Created On	: Dec 11, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: const TYPE_MAP_CNTRSCORE M1, const TYPE_MAP_CNTRSCORE M2
 *******************************************************************/
const TYPE_MAP_CNTRSCORE AlgoTest::Product( const TYPE_MAP_CNTRSCORE& M1, const TYPE_MAP_CNTRSCORE& M2) const
{
	TYPE_MAP_CNTRSCORE mpProduct;

	// Cntr1 is bypassed because it is a background
	for(UINT i = 1; i <= M1.size(); i++ )
	{
		mpProduct[i] = M1.at(i) * M2.at(i);
	}


	return mpProduct;
}
/*******************************************************************
 * Function Name: DisplayDetections
 * Return Type 	: int
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Display the detections on the ProbeImage
 * Arguments	: const fs::path ProbeImgPath, const vector<CarryContour>& vCrryCtr
 *******************************************************************/
ColorImg AlgoTest::DisplayDetections( const fs::path ProbeImgPath, const vector<CarryContour>& vCrryCtr, const Args& args) const
{

	ColorImg DispImg;
	DispImg.Load( ProbeImgPath );

	for(auto CarryCtr : vCrryCtr )
	{
		DispImg = DisplayCarriedCtr(DispImg, CarryCtr, args);
	}

	DispImg.Display(ONE_SECOND);

	return DispImg;
}



/*******************************************************************
 * Function Name: DisplayCarriedCtr
 * Return Type 	: ColorImg
 * Created On	: Jul 6, 2013
 * Created By 	: hrushi
 * Comments		: Displays the carry contour on the passed image, and returns the overlayed image.
 * Arguments	: ColorImg ProbeImg, const CarryContour& CrrCtr, const Args& args
 *******************************************************************/
ColorImg AlgoTest::DisplayCarriedCtr( ColorImg ProbeImg, const CarryContour& CarryCtr, const Args& args) const
{
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

	return ProbeImg;
}
