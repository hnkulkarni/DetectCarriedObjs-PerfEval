/*
 * DetectionByPose.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: hrushi
 */

#include "DetectByPose.h"

DetectByPose::DetectByPose(const ColorImg ProbeImg, const GrayImg BkImg, const vector<ProbImg> ProbImgs, const ContourMap& Segments,  const Args& args):Detect(ProbeImg, BkImg, Segments, args)
{

	Init_Members(ProbeImg.GetImagePath(), args.GetTrainFolderPath(), ProbImgs );
	LoadAllPoseFeatures(args.GetTrainFolderPath() );

}

DetectByPose::~DetectByPose()
{


}


/*****************************************************
 * Function	: DetectByPose Copy Constructor
 * Date		: Jul 21, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
DetectByPose::DetectByPose(const DetectByPose& rhsDetectByPose ):Detect(rhsDetectByPose)
{
	Allocate( rhsDetectByPose );
	Copy( rhsDetectByPose );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 21, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
DetectByPose& DetectByPose:: operator=( const DetectByPose& rhsDetectByPose )
{
	Allocate( rhsDetectByPose );
	Copy( rhsDetectByPose );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 21, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByPose::Allocate( const DetectByPose& rhsDetectByPose )
{
	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 21, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByPose::Copy( const DetectByPose& rhsDetectByPose )
{
	m_vProbImgs			= rhsDetectByPose.m_vProbImgs;

	//---------- Copying the Map of Pose Feature ---------- //
	for( const auto& mp : rhsDetectByPose.m_Map_Posefeature )
	{
		m_Map_Posefeature[ mp.first ] = mp.second;
	}

	//---------- Copying the Map of Pose EMs ---------- //
	for(const auto& mp : rhsDetectByPose.m_Map_strPoseEM)
	{
		m_Map_strPoseEM[mp.first] = mp.second;
	}

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 21, 2013
 * Created By 	: hrushi
 * Comments		: Initializes all the Member Variables
 * Arguments	:
 *******************************************************************/
int DetectByPose::Init_Members( const fs::path ProbeImgPath, const fs::path TrainFolderPath, vector<ProbImg> ProbImgs  )
{
	SetTrainingFolderPath( TrainFolderPath );

	if(!fs::exists(ProbeImgPath) ) // Return Error if File Does not exist.
	{
		cerr << "Image Path does not exist " << endl;
		cerr << "Given Image Path: " << ProbeImgPath << endl;

		throw ERR_INVALID_PATH;
	}

	int iRet = ReadPose(ProbeImgPath);

	if( iRet == ERR_INVALID_PATH )
	{
		return ERR_INVALID_PATH;
	}

	// Copy the Prior Probabilities
	m_vProbImgs = ProbImgs;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: SetTrainingFolderPath
 * Return Type 	: int
 * Created On	: Jul 29, 2013
 * Created By 	: hrushi
 * Comments		: Set the Training Folder Path
 * Arguments	: const fs::path fsPath
 *******************************************************************/
int DetectByPose::SetTrainingFolderPath( const fs::path fsPath )
{

	m_TrainingFolderPath = fsPath;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: LoadAllPoseFeatures
 * Return Type 	: int
 * Created On	: Jul 22, 2013
 * Created By 	: hrushi
 * Comments		: Loads all the Pose Features
 * ColorSet		: 	green   - head
					magenta - left arm
					yellow  - torso
					cyan    - right arm
					red     - left leg
					blue    - right leg
 * Arguments	: const fs::path TrainingFolderPath
 *******************************************************************/
int DetectByPose::LoadAllPoseFeatures( const fs::path TrainingFolderPath)
{

	m_Map_Posefeature = ReadPoseFeature::GetMap_String_PoseFeature(TrainingFolderPath.string(), ALL_POSE_FEATURE_FILES);

	for(auto& Mp: m_Map_Posefeature )
	{
		PoseEM Temp = PoseEM(3, Mp.second);
		m_Map_strPoseEM.insert( std::pair<string, PoseEM>( Mp.first, Temp ));
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadPose
 * Return Type 	: int
 * Created On	: Jul 21, 2013
 * Created By 	: hrushi
 * Comments		: Reads the Pose data for the given file
 * Arguments	: Probe Image File Path
 *******************************************************************/
int DetectByPose::ReadPose( const fs::path ProbeImgPath )
{

	cout << "Reading Pose Path for the given image " << endl;
	cout << ProbeImgPath << endl;

	const fs::path PoseBoxFilePath = PoseFile::GetBoxFilePath( ProbeImgPath );
	if( !fs::exists(PoseBoxFilePath ))
	{
		cerr << "No Box File Present " << endl;

		return ERR_INVALID_PATH;
	}

	cout << "Reading the Box File " << PoseBoxFilePath << endl;
	PoseFile PF(PoseBoxFilePath);
	m_Pose = PF.m_Pose;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetCarried
 * Return Type 	: int
 * Created On	: Jul 21, 2013
 * Created By 	: hrushi
 * Comments		: Get Carried regions using Pose Data
 * Arguments	:
 *******************************************************************/
vector<CarryContour> DetectByPose::GetCarried( )
{
	vector<CarryContour> vCarriedCntrs;

	double dLike(0);

	if( m_Pose.GetNumParts() == 0 ) // Pose file Valid
	{
		return vCarriedCntrs; // Return empty vector of CarriedContours
	}

	for(TYPE_MAP_ALL_CONTOUR::const_iterator itr = m_Segments.AllContourMap.begin(); itr != m_Segments.AllContourMap.end(); itr++ )
	{
		cout << "Checking for Contour with Label " << itr->second.GetLabel() << endl;

		if( itr->second.GetLabel() == BACKGROUND_LABEL )
		{
			// Continue with the loop if the contour is a background contour
			continue;
		}

		CarryContour TempContour = Check_if_Cntr_Carry( itr->second, dLike );

		vCarriedCntrs.push_back( TempContour );
	}

	return vCarriedCntrs;
}

/*******************************************************************
 * Function Name: Check_if_Cntr_Carry
 * Return Type 	: int
 * Created On	: Jul 26, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given contour is a carry region
 * Arguments	: const Contour& Ctr
 *******************************************************************/
CarryContour DetectByPose::Check_if_Cntr_Carry( const Contour& Ctr, double& dLike ) const
{

	CarryContour RetCtr = Ctr;

	vector<double> lArmScore, rArmScore;
	pr_score LeftArm_Score 	= isArmCarry("lArm", Ctr, lArmScore);
	pr_score RightArm_Score = isArmCarry("rArm", Ctr, rArmScore);

	vector<double> vAllScores;
	std::copy(lArmScore.begin(), lArmScore.end(), std::back_inserter(vAllScores));
	std::copy(rArmScore.begin(), rArmScore.end(), std::back_inserter(vAllScores));

	pr_score FinalSore = MakeDecision(LeftArm_Score, RightArm_Score);

	RetCtr.SetCarryTypeNScore(FinalSore.first, FinalSore.second);
	RetCtr.SetAllScores(vAllScores);

	return RetCtr;

}



/*******************************************************************
 * Function Name: MakeDecision
 * Return Type 	: const pr_score
 * Created On	: Oct 25, 2013
 * Created By 	: hrushi
 * Comments		: Makes a decision if the given region is a carry region or not based on the scores calculated for the Left_Hand and the Right Hand
 * Arguments	: const pr_score& LeftScore, const pr_score& RightScore
 *******************************************************************/
const pr_score DetectByPose::MakeDecision( const pr_score& LeftScore, const pr_score& RightScore) const
{
	pr_score FinalScore;

	double LeftProb  = pow(2, LeftScore.second);
	double RightProb = pow(2, RightScore.second );

	if( LeftProb > RightProb )
	{
		FinalScore.first = LeftScore.first;
		FinalScore.second = LeftScore.second;
	}
	else
	{
		FinalScore.first = RightScore.first;
		FinalScore.second = RightScore.second;

	}

	return FinalScore;
}

/*******************************************************************
 * Function Name: isArmCarry
 * Return Type 	: std::pair<bool, double>
 * Created On	: Oct 21, 2013
 * Created By 	: hrushi
 * Comments		: Check if the arm is carry or not carry
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
pr_score DetectByPose::isArmCarry( const string PartType, const Contour& Ctr, vector<double>& vAllScore ) const
{
	pr_score RetPair;

	char MapKey = (PartType == "lArm" )? 'm' : 'c';

	PoseEM DragCarryEM, WornCarryEM, NoCarryEM;

	if( PartType == "lArm")
	{
		WornCarryEM = m_Map_strPoseEM.at(LEFT_WORN_POSE_FEATURE_FILE);
		DragCarryEM = m_Map_strPoseEM.at(LEFT_DRAG_POSE_FEATURE_FILE);
		NoCarryEM 	= m_Map_strPoseEM.at(LEFT_NOCARRY_POSE_FEATURE_FILE);

	}
	else
	{
		WornCarryEM = m_Map_strPoseEM.at(RIGHT_WORN_POSE_FEATURE_FILE);
		DragCarryEM = m_Map_strPoseEM.at(RIGHT_DRAG_POSE_FEATURE_FILE);
		NoCarryEM 	= m_Map_strPoseEM.at(RIGHT_NOCARRY_POSE_FEATURE_FILE);

	}

	ColorImg DispImg = m_Pose.OverlayExtn(m_ProbeImg, MapKey, Ctr);

	const vector<double> PoseFeature = m_Pose.CalcPoseFeature(MapKey, Ctr );

	double dWornLog(0), dDragLog(0), dPersonLog(0);
	double dWornRatio = GetRatio(PoseFeature, WornCarryEM, NoCarryEM, dWornLog, dPersonLog); //Note: dPersonLog value will be the same, because we have only one EM
	double dDragRatio = GetRatio(PoseFeature, DragCarryEM, NoCarryEM, dDragLog, dPersonLog);

	//---------- Order or push_back important ---------- //
	vAllScore.push_back(dWornLog);
	vAllScore.push_back(dDragLog);
	vAllScore.push_back(dPersonLog);

	vAllScore = LogToProb(vAllScore);

	if((dWornRatio > 1 ) || (dDragRatio > 1)) //Carry probability is more than no-carry probability
	{
		if( dWornRatio > dDragRatio )
		{
			RetPair.first 	= WORN_CARRY_LABEL;
			RetPair.second	= dWornLog;

			//DispImg.Overlay(Ctr, DISP_DELAY, COLOR_RED, Args() ).Display(DISP_DELAY);
			cout << PartType << " : " << "Worn" << endl;
		}
		else
		{
			RetPair.first 	= DRAG_CARRY_LABEL;
			RetPair.second 	= dDragLog;
			//DispImg.Overlay(Ctr, DISP_DELAY, COLOR_GREEN, Args() ).Display(DISP_DELAY);
			cout << PartType << " : " << "Drag" << endl;
		}
	}
	else
	{
		RetPair.first	= PERSON_LABEL;
		RetPair.second	= dPersonLog;
		//DispImg.Overlay(Ctr, DISP_DELAY, COLOR_BLUE, Args() ).Display(DISP_DELAY);
		cout << PartType << " : " << "Person" << endl;
	}

	return RetPair;
}


/*******************************************************************
 * Function Name: GetRatio
 * Return Type 	: std::pair<bool, double>
 * Created On	: Oct 21, 2013
 * Created By 	: hrushi
 * Comments		: Get the ratio of EM Carry and NoCarry
 * Arguments	: const VDOUBLE& vFeature
 *******************************************************************/
double DetectByPose::GetRatio(const VDOUBLE& PoseFeature, const PoseEM& CarryEM, const PoseEM& NoCarryEM, double& LogCarry_Prob, double& LogNoCarry_Prob ) const
{

	const cv::Vec2d ResCarry 	=   CarryEM.Predict( PoseFeature );
	const cv::Vec2d ResNoCarry 	= NoCarryEM.Predict( PoseFeature );

	LogCarry_Prob 	= ResCarry.val[0];
	const double Carry_Prob	 	= pow(2, LogCarry_Prob);

	LogNoCarry_Prob= ResNoCarry.val[0];
	const double NoCarry_Prob 	= pow(2, LogNoCarry_Prob);
	const double dRatio 		= Carry_Prob/NoCarry_Prob;

	return dRatio;
}



/*******************************************************************
 * Function Name: CalAllCntrScore
 * Return Type 	: const TYPE_MAP_CNTRSCORE
 * Created On	: Jan 8, 2014
 * Created By 	: hrushi
 * Comments		: Calculate the score for all the contours in the required formal
 * Arguments	: const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args
 *******************************************************************/
const TYPE_MAP_CNTRSCORE DetectByPose::CalAllCntrScore( const TYPE_MAP_ALL_CONTOUR CtrMap, const Args& args) const
{
	TYPE_MAP_CNTRSCORE Score;

	cout << "Calc All Cntr Score " << endl;

	vector<double> vScore;
	vScore.reserve( m_vProbImgs.size()); // Create a vector of double, for each element to probability image
	double ProbScore = 0;

	for( unsigned int i = 0; i < m_vProbImgs.size(); i++)
	{

	}


	return Score;
}
