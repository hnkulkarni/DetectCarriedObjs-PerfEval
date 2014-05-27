/*
 * ViperGroundTruth.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: hrushi
 */

#include "ViperGroundTruth.h"

/*******************************************************************
 * Function Name: ViperGroundTruth
 * Return Type 	: None
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
ViperGroundTruth::ViperGroundTruth()
{
	Init();
}



/*******************************************************************
 * Function Name: Init
 * Return Type 	: int
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Initializes the Member variables
 * Arguments	:
 *******************************************************************/
int ViperGroundTruth::Init( )
{

	m_TP = 0;
	m_TN = 0;
	m_FP = 0;
	m_FN = 0;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ~ViperGroundTruth
 * Return Type 	: None
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
ViperGroundTruth::~ViperGroundTruth()
{


}


/*****************************************************
 * Function	: ViperGroundTruth Copy Constructor
 * Date		: Mar 17, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ViperGroundTruth::ViperGroundTruth(const ViperGroundTruth& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Mar 17, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ViperGroundTruth& ViperGroundTruth:: operator=( const ViperGroundTruth& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Mar 17, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ViperGroundTruth::Allocate( const ViperGroundTruth& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Mar 17, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ViperGroundTruth::Copy( const ViperGroundTruth& rhs )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: isCorrect
 * Return Type 	: int
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Checks if the detection is correct
 * Arguments	: const TrackXML& oTrackXML, const ViperXML& oViperXML, const AllDetectedCtrs& allDCs, const fs::path TrkPath, const Args& args
 *******************************************************************/
const vector<bool>  ViperGroundTruth::isCorrect( const AllDetectedCtrs& allDCs, const fs::path TrackFilePath, const Args& args)
{

	const fs::path TrackXMLFilePath = TrackXML::GetTrackFilePath(TrackFilePath);
	static TrackXML *oTrack = new TrackXML(TrackXMLFilePath);

	// Reload if the track file path has changed
	if(oTrack->GetFilePath() != TrackXMLFilePath )
	{
		delete oTrack;
		oTrack = NULL;

		cout << TrackXMLFilePath << endl;
		oTrack = new TrackXML(TrackXMLFilePath);
	}

	const fs::path ViperFilePath = ViperXML::GetViperXMLPath(TrackXMLFilePath);
	static ViperXML *oViperXML = new ViperXML(ViperFilePath);

	//Reload if it is already present
	if(oViperXML->GetFilePath() != ViperFilePath )
	{
		delete oViperXML;
		oViperXML = NULL;

		cout << ViperFilePath << endl;
		oViperXML = new ViperXML(ViperFilePath);
	}

	UINT FrameNum, TrackNum;
	string VideoStemName;

	TrackXML::GetTrkChipNameParts(TrackFilePath.stem().string(), TrackNum, FrameNum, VideoStemName);
	fs::path FullImgPath = oTrack->GetFullImagePath(FrameNum);
	const vector<cv::Rect> GndTruthBdnBx = oViperXML->GetGndTruthBdnBox(FrameNum);
	const cv::Rect TrackBdnBx = oTrack->GetBoundingBox(TrackNum, FrameNum);
	cout << "Viper GndTruth: " 	<< oViperXML->GetGndTruthBdnBox(FrameNum) 		<< endl;

	ImagePt OffSetPt = TrackBdnBx.tl();
	OffSetPt.SwapXY();

	AllDetectedCtrs OffsetDCs = allDCs.Offset(OffSetPt.GetPoint());

	ColorImg FullImg(FullImgPath);
	FullImg.Overlay(TrackBdnBx, COLOR_BLUE);
	FullImg.Overlay(GndTruthBdnBx, COLOR_GREEN);

	DetectionImg DtcImg;
	DtcImg.SetImage(FullImg.GetDataRef());
	DtcImg.Overlay(OffsetDCs, false, args);
	DtcImg.Display(DISP_ONE_SECOND);

	const vector<cv::Rect> OverlapRects = RectOp::GetOverlappingRect(TrackBdnBx, GndTruthBdnBx, 0.7);
	vector<bool> isGndTruth_True = Add2ConfMat(allDCs, TrackBdnBx, GndTruthBdnBx);

	return isGndTruth_True;
}


/*******************************************************************
 * Function Name: Add2ConfMat
 * Return Type 	: int
 * Created On	: Mar 18, 2014
 * Created By 	: hrushi
 * Comments		: const AllDetectedCtrs& allDCs, const vector<cv::Rect>& GndTruth
 * Arguments	: const AllDetectedCtrs& allDCs, const vector<cv::Rect>& GndTruth
 *******************************************************************/
const vector<bool> ViperGroundTruth::Add2ConfMat( const AllDetectedCtrs& allDCs, const cv::Rect TrackBx, const vector<cv::Rect>& GndTruth)
{
	vector<CarryContour> DetectCCs = allDCs.Get_vCtrs();
	vector<cv::Rect> GndTruthInTrack = GetGndTruthinTrack(TrackBx, GndTruth);

	vector<bool> isGndTruthPos;

	if(GndTruthInTrack.size() == 0)
	{
		cout << "No Ground Truth in Track" << endl;
		isGndTruthPos = AnalyzeGnd_NoDetection(allDCs);
	}
	else
	{
		cout << "Ground Truth is in Track" << endl;
		isGndTruthPos = AnalyzeGnd_PosDetection(allDCs, TrackBx, GndTruth);
	}

	return isGndTruthPos;
}


/*******************************************************************
 * Function Name: AnalyzeGnd_PosDetection
 * Return Type 	: int
 * Created On	: Apr 11, 2014
 * Created By 	: hrushi
 * Comments		: Checks if the ground truth has any positive detection.
 * 				  We have following options TruePositive and FalseNagative
 * Arguments	: AllDetectedCtrs
 *******************************************************************/
const vector<bool> ViperGroundTruth::AnalyzeGnd_PosDetection( const AllDetectedCtrs& allDCs, const cv::Rect TrackBx, const vector<cv::Rect>& GndTruth  )
{
	vector<CarryContour> DetectCCs = allDCs.Get_vCtrs();
	//bool GndTruthInTrack = RectOp::Contains(TrackBx, GndTruth.)

	vector<cv::Rect> RelativeRects = RectOp::MakeRelativeToBigRect(TrackBx, GndTruth);

	vector<bool> vGndTruthPos;

	if( allDCs.Get_NumvCntrs() == 0) //There is some ground truth, but there was no detection
	{
		m_FN++;
	}
	else
	{
		bool bDetection(false);

		BinaryImg BlackMask = allDCs.Get_vCtrs().at(0).GetCtrBlackImg().Cvt2Gray();
		BlackMask.FillSolidBox(RelativeRects);

		for(auto CC : DetectCCs)
		{
			CC.GetCtrMaskImg().Display(DISP_ONE_SECOND);
			int CarryType = CC.GetCarryType();

			double Coverage = CC.PercentageCoverage(BlackMask);

			if(Coverage > GND_TRUTH_THRESHOLD)
			{
				vGndTruthPos.push_back(true);

				if(( CarryType == WORN_CARRY_LABEL) ||  (CarryType == DRAG_CARRY_LABEL))
				{
					bDetection = true;
				}
				else
				{
					continue;
				}

			}
			else
			{
				vGndTruthPos.push_back(false);
			}

		}

		if(bDetection)
		{
			m_TP++;
		}
		else
		{
			m_FN++;
		}


	}



	return vGndTruthPos;
}

/*******************************************************************
 * Function Name: AnalyzeWithGndFalse
 * Return Type 	: int
 * Created On	: Apr 9, 2014
 * Created By 	: hrushi
 * Comments		: Since ground truth is false (No detection),
 * 				  then we have following options TrueNegative and FalsePositive
 * Arguments	: const AllDetectedCtrs& allDCs, const cv::Rect TrackBx
 *******************************************************************/
const vector<bool>  ViperGroundTruth::AnalyzeGnd_NoDetection( const AllDetectedCtrs& allDCs)
{
	vector<CarryContour> PosCntr = allDCs.Get_PositiveCtrs();

	vector<bool> vGndTruthPos;
	vGndTruthPos.resize(allDCs.Get_NumvCntrs());

	VectorOp<bool>::SetAll(vGndTruthPos, false);


	// No positive detection by the system
	if(PosCntr.size() == 0)
	{
		m_TN++;
	}
	else
	{
		m_FP++;
	}

	return vGndTruthPos;
}

/*******************************************************************
 * Function Name: Print_ConfusionMat
 * Return Type 	: int
 * Created On	: Mar 18, 2014
 * Created By 	: hrushi
 * Comments		: Print the confusion matrix
 * Arguments	: const Args& args
 *******************************************************************/
int ViperGroundTruth::Print_ConfusionMat( const Args& args) const
{

	cout << "True  Positive: " << m_TP << endl;
	cout << "True  Negative: " << m_TN << endl;
	cout << "False Positive: " << m_FP << endl;
	cout << "False Negative: " << m_FN << endl;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetGntTruthinTrack
 * Return Type 	: vector<cv::Rect>
 * Created On	: Apr 9, 2014
 * Created By 	: hrushi
 * Comments		: Get the ground truth in the track
 * Arguments	: const cv::Rect TrackBx, const vector<cv::Rect>& GndTruth
 *******************************************************************/
const vector<cv::Rect> ViperGroundTruth::GetGndTruthinTrack( const cv::Rect TrackBx, const vector<cv::Rect>& GndTruth ) const
{
	vector<cv::Rect> GndTruthTrk = RectOp::GetOverlappingRect(TrackBx, GndTruth, 0.7);
	//
	//	for(auto GndBx : GndTruth)
	//	{
	//		bool bContains = RectOp::GetOverlappingRect(TrackBx, GndBx, 0.7);
	//
	//		if(bContains == true )
	//		{
	//			GndTruthTrk.push_back(GndBx);
	//		}
	//		else
	//		{
	//			continue;
	//		}
	//	}

	return GndTruthTrk;
}






