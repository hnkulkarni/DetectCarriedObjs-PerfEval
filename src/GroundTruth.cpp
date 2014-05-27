/*
 * GroundTruth.cpp
 *
 *  Created on: Jul 4, 2013
 *      Author: hrushi
 */

#include "GroundTruth.h"

GroundTruth::GroundTruth()
{
	Init_Members();
}

GroundTruth::~GroundTruth()
{

}


/*******************************************************************
 * Function Name: GroundTruth
 * Return Type 	:
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Constructor taking filename as an argument
 * Arguments	: const fs::path FileName, const Args& args
 *******************************************************************/
GroundTruth::GroundTruth(  const Args& args)
{
	Init_Members();
	Load(args);
}

/*****************************************************
 * Function	: GroundTruth Copy Constructor
 * Date		: Jul 4, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
GroundTruth::GroundTruth(const GroundTruth& rhsGroundTruth )
{
	Allocate( rhsGroundTruth );
	Copy( rhsGroundTruth );

}



/*****************************************************
 * Function	: operator =
 * Date		: Jul 4, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
GroundTruth& GroundTruth:: operator=( const GroundTruth& rhsGroundTruth )
{
	Allocate( rhsGroundTruth );
	Copy( rhsGroundTruth );

	return *this;
}

/*******************************************************************
 * Function Name: Init
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Initializes all the Member variables
 * Arguments	:
 *******************************************************************/
int GroundTruth::Init_Members( )
{

	Set_ConfusionMat(0);
	Set_RowHeaders();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Set_RowHeaders
 * Return Type 	: int
 * Created On	: Oct 3, 2013
 * Created By 	: hrushi
 * Comments		: Sets the Row Headers
 * Arguments	:
 *******************************************************************/
int GroundTruth::Set_RowHeaders( )
{

	m_RowHeader.push_back(WORN);
	m_RowHeader.push_back(DRAG);
	m_RowHeader.push_back(PERSON);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Set_ConfusionMat
 * Return Type 	: int
 * Created On	: Jul 15, 2013
 * Created By 	: hrushi
 * Comments		: Initialize Confusion Mat
 * Arguments	: unsigned int Val
 *******************************************************************/
int GroundTruth::Set_ConfusionMat( unsigned int Val)
{

	for(unsigned int i = 0; i < GND_CATEGORIES; i++ )
	{
		for(unsigned int j = 0; j < GND_CATEGORIES; j++ )
		{
			m_ConfusionMat[i][j] = Val;
		}
	}

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 4, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int GroundTruth::Allocate( const GroundTruth& rhs )
{
	m_RowHeader.resize(rhs.m_RowHeader.size());
	m_vScores.resize(rhs.m_vScores.size());

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 4, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int GroundTruth::Copy( const GroundTruth& rhs )
{

	m_AllLabels 		= rhs.m_AllLabels;
	m_BagpackLabels 	= rhs.m_BagpackLabels;
	m_SuitecaseLabels 	= rhs.m_SuitecaseLabels;
	m_RowHeader 		= rhs.m_RowHeader;
	m_vScores			= rhs.m_vScores;

	for(UINT i = 0; i < GND_CATEGORIES; i++ )
	{
		for(UINT j = 0; j < GND_CATEGORIES; j++ )
		{
			m_ConfusionMat[i][j] = rhs.m_ConfusionMat[i][j];
		}
	}


	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: isCorrect
 * Return Type 	: bool
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the detection is correct
 * Arguments	: const fs::path ProbeImgPath, const AllDetectedCtrs& AllCtrs
 *******************************************************************/
bool GroundTruth::isCorrect( const fs::path ProbeImgPath, const AllDetectedCtrs& AllCtrs )
{
	bool bDecision(false);
	vector<CarryContour> vDT = AllCtrs.Get_vCtrs();
	vector<CarryContour> vGT = ReplaceWith_Gt(ProbeImgPath, vDT);
	AddToScoreList(AllCtrs);

	for(unsigned int i = 0; i < vGT.size(); i++ )
	{
		unsigned int GTLable = vGT.at(i).GetCarryType();
		unsigned int DetLabel = vDT.at(i).GetCarryType();

		m_ConfusionMat[GTLable][DetLabel]++;
	}

	return bDecision;
}

/*******************************************************************
 * Function Name: AddToScoreList
 * Return Type 	: int
 * Created On	: Oct 27, 2013
 * Created By 	: hrushi
 * Comments		: Adds the scores of all the contours to the score list
 * Arguments	: const AllDetectedCtrs& AllCtrs
 *******************************************************************/
int GroundTruth::AddToScoreList( const AllDetectedCtrs& AllCtrs )
{

	for(auto pr : AllCtrs.Get_vCtrs() )
	{
		pr_score sr;
		sr.first = pr.GetCarryType();
		sr.second = pr.GetCarryScore();

		m_vScores.push_back(sr);
	}

	cout << "Num Entries: " << m_vScores.size() << endl;


	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ReplaceWith_Gt
 * Return Type 	: vector<CarryContur>
 * Created On	: Jul 20, 2013
 * Created By 	: hrushi
 * Comments		: Replace the carry labels with the ground truth labels
 * Arguments	: const vector<CarryContour>& vCC
 *******************************************************************/
vector<CarryContour> GroundTruth::ReplaceWith_Gt( const fs::path ProbeImgPath, const vector<CarryContour>& vCC ) const
{
	vector<CarryContour> vGT;
	vGT.resize( vCC.size() );
	vGT = vCC;

	int GndTrth_Label  = m_AllLabels.GetImageLabel(ProbeImgPath, false );
	int BackPackLabel  = m_BagpackLabels.GetImageLabel(ProbeImgPath, false );
	int SuitecaseLabel = m_SuitecaseLabels.GetImageLabel(ProbeImgPath, false );

	for(unsigned int i = 0; i < vGT.size(); i++ )
	{
		int ContourNum = vGT.at(i).GetLabel(); // I should change this function from GetLabel to GetCntrNum

		if( GndTrth_Label == NO_CARRIED_OBJECT )
		{
			vGT.at(i).SetCarryTypeNScore( PERSON_LABEL, UN_INITIALIZED_LABEL );
		}
		else if( ContourNum == BackPackLabel )
		{
			vGT.at(i).SetCarryTypeNScore( WORN_CARRY_LABEL, UN_INITIALIZED_LABEL );
		}
		else if( ContourNum == SuitecaseLabel )
		{
			vGT.at(i).SetCarryTypeNScore( DRAG_CARRY_LABEL, UN_INITIALIZED_LABEL );
		}
		else
		{
			vGT.at(i).SetCarryTypeNScore( PERSON_LABEL, UN_INITIALIZED_LABEL );
		}
	}

	return vGT;
}


/*******************************************************************
 * Function Name: Load
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Loads the Lables from the Test folder as the Ground Truth
 * Arguments	: const fs::path FileName, const Args& args
 *******************************************************************/
int GroundTruth::Load( const Args& args)
{

	m_AllLabels.Init( args, GROUND_TRUTH_FILE );
	m_AllLabels.Read(args);
	cout << "The number of Groundtruth labels read are: " << m_AllLabels.GetNumLabels() << endl;

	m_BagpackLabels.Init(args, WORN_CARRY_LABEL_FILE);
	m_BagpackLabels.Read(args);
	cout << "Number of Backpack Lables are " << m_BagpackLabels.GetNumLabels() << endl;

	m_SuitecaseLabels.Init(args, DRAG_CARRY_LABEL_FILE);
	m_SuitecaseLabels.Read(args);
	cout << "Number of Suitecase Labels are " << m_SuitecaseLabels.GetNumLabels() << endl;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Print_ConfusionMat
 * Return Type 	: int
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Print the Confusion Matrix
 * Arguments	:
 *******************************************************************/
int GroundTruth::Print_ConfusionMat( const Args& args ) const
{
	cout << "Confusion Matrix is : "  <<  endl;
	cout << "     *****" << " Predicted " << "*****" << endl;
	for( UINT i = 0; i < GND_CATEGORIES; i++ )
	{
		cout << m_RowHeader.at(i) << "\t";


		UINT Row_Sum(0);

		for( UINT j = 0; j < GND_CATEGORIES; j++ )
		{
			cout << std::setw(4) << m_ConfusionMat[i][j] << " & ";

			Row_Sum += m_ConfusionMat[i][j];

			if( j == (GND_CATEGORIES - 1) )
			{
				cout << std::setw(4) << Row_Sum;
			}
		}

		cout << endl;
	}

	cout << endl;

	UINT TotalSum(0);

	cout << "Total \t";
	for( UINT j = 0; j < GND_CATEGORIES; j++ )
	{
		UINT Col_Sum(0);

		for( UINT i = 0; i < GND_CATEGORIES; i++ )
		{
			Col_Sum += m_ConfusionMat[i][j];
			TotalSum += m_ConfusionMat[i][j];
		}

		cout << std::setw(4) << Col_Sum << " & ";

		if( j == (GND_CATEGORIES - 1) )
		{
			cout << std::setw(4) << TotalSum;
		}
	}

	cout << endl;

	PrintStats( args );

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: PrintStats
 * Return Type 	: int
 * Created On	: Oct 27, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Mean, Median, Standard Dev. the EM Score
 * Arguments	:
 *******************************************************************/
int GroundTruth::PrintStats(  const Args& args  ) const
{
	vector<double> AllScoreVal;

	string ScoreSavePath = GetSavePath( args );
	cout << "Saving to: " << ScoreSavePath << endl;

	cv::FileStorage fScore;
	fScore.open(ScoreSavePath, cv::FileStorage::WRITE);

	AllScoreVal.reserve(m_vScores.size());

	for( auto ClassName : RGN_TYPES )
	{
		vector<double> ClassScoreVal;

		for(const auto& val : m_vScores )
		{
			AllScoreVal.push_back( val.second );
			ClassScoreVal.push_back( val.second );
		}

		PrintAllVals(args, fScore, ClassName, ClassScoreVal);
	}

	fScore.release();


	PrintStats(args, AllScoreVal);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: PrintStats
 * Return Type 	: int
 * Created On	: Oct 28, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Stats for all the elements
 * Arguments	: const vector<double>& AllScores
 *******************************************************************/
int GroundTruth::PrintStats(  const Args& args, const vector<double>& ScoreVal) const
{

	cout << "Stddev: " 	<< VectorOp<double>::GetSTDev(ScoreVal);

	cout << "Mean:  " 	<< VectorOp<double>::GetMean(ScoreVal);

	cout << "Median: " 	<< VectorOp<double>::GetMedian(ScoreVal);

	cout << "Min: " 	<< VectorOp<double>::GetMinVal(ScoreVal);

	cout << "Max: " 	<< VectorOp<double>::GetMaxVal(ScoreVal);

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: PrintAllVals
 * Return Type 	: int
 * Created On	: Nov 6, 2013
 * Created By 	: hrushi
 * Comments		: Prints all the values and the LogNormal Distribution
 * Arguments	: const vector<double>& AllScores
 *******************************************************************/
int GroundTruth::PrintAllVals( const Args& args, cv::FileStorage& fScore,  const string Tag, const vector<double>& AllScores) const
{

	vector<double> ProbScores;
	ProbScores.resize(AllScores.size());

	const string AlgoTypeOpt = boost::to_lower_copy( args.GetDetectMode() );

	if(AlgoTypeOpt.compare("location") == 0 )
	{
		ProbScores = AllScores;
	}
	else
	{
		cout << "Performing Raised to Power 2 operation" << endl;
		std::transform( AllScores.begin(), AllScores.end(), ProbScores.begin(), GroundTruth::PWR);
	}



	fScore << Tag << ProbScores;



	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetSavePath
 * Return Type 	: const string
 * Created On	: Nov 18, 2013
 * Created By 	: hrushi
 * Comments		: Get the save path for the given algo type
 * Arguments	: const Args& args, const string AlgoType
 *******************************************************************/
const string GroundTruth::GetSavePath( const Args& args ) const
{
	string ScoreSavePath = args.GetSearchFolderPath();

	const string AlgoTypeOpt = boost::to_lower_copy( args.GetDetectMode() );

	if( AlgoTypeOpt == "pose" )
	{
		ScoreSavePath += POSE_PROB_SCORE_FILE;
	}
	else if( AlgoTypeOpt == "location"  )
	{
		ScoreSavePath += LOC_PROB_SCORE_FILE;
	}
	else if( AlgoTypeOpt == "shape")
	{
		ScoreSavePath += SHAPE_PROB_SCORE_FILE;
	}
	else if( AlgoTypeOpt == "appearance")
	{
		ScoreSavePath += APPR_PROB_SCORE_FILE;
	}

	return ScoreSavePath;
}
/*******************************************************************
 * Function Name: PWR
 * Return Type 	: double
 * Created On	: Nov 6, 2013
 * Created By 	: hrushi
 * Comments		: Finds the 2 power of the given
 * Arguments	: double d
 *******************************************************************/
double GroundTruth::PWR( double d)
{
	double dpow = pow(2, d);
	return dpow;
}




