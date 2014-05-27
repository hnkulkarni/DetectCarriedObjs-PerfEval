/*
 * DetectByShape.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: hrushi
 */

#include "DetectByShape.h"

//---------- Adding static member initialization over here,
// to avoid multiple declaration error---------- //
ShapeFeaturesContainer DetectByShape::m_SFC = ShapeFeaturesContainer();

/*******************************************************************
 * Function Name: DetectByShape
 * Return Type 	: None
 * Created On	: Oct 11, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: const ColorImg, const GrayImg, const ContourMap&, const Args&
 *******************************************************************/
DetectByShape::DetectByShape( const ColorImg ProbeImg, const GrayImg BkImg,  const ContourMap& Segments, const Args& args ):Detect( ProbeImg, BkImg, Segments, args )
{
	Init_Members(args.GetTrainFolderPath());
	LoadShapeFeatures(args.GetTrainFolderPath() );
}


/*******************************************************************
 * Function Name: ~DetectByShape
 * Return Type 	: None
 * Created On	: Oct 11, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
DetectByShape::~DetectByShape()
{


}

/*******************************************************************
 * Function Name: GetCarried
 * Return Type 	: vector<CarryContour>
 * Created On	: Oct 3, 2013
 * Created By 	: hrushi
 * Comments		: Carry contour detected by using shape
 * Arguments	:
 *******************************************************************/
vector<CarryContour> DetectByShape::GetCarried( const ContourMoments& Mtm )
{
	vector<CarryContour> vCarriedCntrs;

	ShapeEM WornCarryEM(3, m_SFC.m_WornShapeFeature);
	ShapeEM DragCarryEM(3, m_SFC.m_DragShapeFeature);
	ShapeEM NoCarryEM(3, m_SFC.m_NoCarryFeature);

	for(TYPE_MAP_ALL_CONTOUR::const_iterator itr = m_Segments.AllContourMap.begin(); itr != m_Segments.AllContourMap.end(); itr++ )
	{
		cout << "Checking for Contour with Label " << itr->second.GetLabel() << endl;

		Contour Ctr = itr->second;

		if( Ctr.GetLabel() == BACKGROUND_LABEL )
		{
			// Continue with the loop if the contour is a background contour
			continue;
		}

		//m_ProbeImg.Overlay(Ctr, DISP_DELAY, COLOR_BLUE, Args()).Display(DISP_DELAY);

		vector<double> vAllScores;
		pr_score Score = isCarry(DragCarryEM, WornCarryEM,  NoCarryEM, Ctr, Mtm, vAllScores);

		CarryContour TempContour = Ctr; // Copy the current contour
		TempContour.SetCarryTypeNScore(Score.first, Score.second);
		TempContour.SetAllScores(vAllScores);

		vCarriedCntrs.push_back(TempContour);

	}
	return vCarriedCntrs;
}

/*******************************************************************
 * Function Name: isCarry
 * Return Type 	: int
 * Created On	: Oct 11, 2013
 * Created By 	: hrushi
 * Comments		: Uses em to decide if the region is carry by "shape" or not
 * Arguments	: const ShapeEM& EMCarry, const ShapeEM& EMNoCarry, const Contour& Ctr
 *******************************************************************/
pr_score DetectByShape::isCarry( const ShapeEM& EMDragCarry, const ShapeEM& EMWornCarry, const ShapeEM& EMNoCarry, const Contour& Ctr,  const ContourMoments& Mtm, vector<double>& vAllScores ) const
{
	VDOUBLE MtmFeature = Mtm.CalculateMoments(Ctr);

	cv::Vec2d RespWornCarry = EMWornCarry.Predict(MtmFeature);
	cv::Vec2d RespDragCarry = EMDragCarry.Predict(MtmFeature);
	cv::Vec2d RespNoCarry	= EMNoCarry.Predict(MtmFeature);

	double DragCarryLogLikelihood	= RespDragCarry.val[0];
	double DragCarryLikelihood		= pow(2, DragCarryLogLikelihood);
	cout << "DragCarryLikelihood "	<< DragCarryLikelihood << endl;

	double WornCarryLogLikelihood 	= RespWornCarry.val[0];
	double WornCarryLikelihood 		= pow(2, WornCarryLogLikelihood);
	cout << "WornCarryLikelihood " << WornCarryLikelihood << endl;

	double NoCarryLogLikelihood 	= RespNoCarry.val[0];
	double NoCarryLikelihood 		= pow(2, NoCarryLogLikelihood);
	cout << "NoCarryLikelihood " << NoCarryLikelihood << endl;

	pr_score RetScore = GetFinalScore(WornCarryLogLikelihood, DragCarryLogLikelihood, NoCarryLogLikelihood, vAllScores);

	return RetScore;
}

/*******************************************************************
 * Function Name: CalAllCntrScore
 * Return Type 	: TYPE_MAP_CNTRSCORE
 * Created On	: Dec 11, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Map of all Score
 * Arguments	: const TYPE_MAP_ALL_CONTOUR CtrMap, const ContourMoments& Mtm
 *******************************************************************/
const TYPE_MAP_CNTRSCORE DetectByShape::CalAllCntrScore( const TYPE_MAP_ALL_CONTOUR CtrMap, const ContourMoments& Mtm, PriorProb oPriorProb ) const
{
	TYPE_MAP_CNTRSCORE mpScore;

	ShapeEM WornCarryEM(3, m_SFC.m_WornShapeFeature);
	ShapeEM DragCarryEM(3, m_SFC.m_DragShapeFeature);
	ShapeEM NoCarryEM(3, m_SFC.m_NoCarryFeature);

	for(auto Cntr : CtrMap)
	{
		if( Cntr.first > BACKGROUND_LABEL ) //Region 0 is a Background Region. Hence skipping this.
		{
			mpScore[Cntr.first] = CalScoreAtGivenCtr(DragCarryEM, WornCarryEM, NoCarryEM, Cntr.second, Mtm, oPriorProb );
		}
	}

	return mpScore;
}



/*******************************************************************
 * Function Name: CalScoreAtGivenCtr
 * Return Type 	: const vector<double>
 * Created On	: Dec 11, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: const ShapeEM& EMDragCarry, const ShapeEM& EMWornCarry, const ShapeEM& EMNoCarry, const Contour& Ctr,  const ContourMoments& Mtm
 *******************************************************************/
const vector<double> DetectByShape::CalScoreAtGivenCtr( const ShapeEM& EMDragCarry, const ShapeEM& EMWornCarry, const ShapeEM& EMNoCarry, const Contour& Ctr,  const ContourMoments& Mtm, PriorProb oPriorProb  ) const
{
	vector<double> vScore;
	vScore.resize(3);

	VDOUBLE MtmFeature = Mtm.CalculateMoments(Ctr);

	cv::Vec2d RespWornCarry = EMWornCarry.Predict(MtmFeature);
	cv::Vec2d RespDragCarry = EMDragCarry.Predict(MtmFeature);
	cv::Vec2d RespNoCarry	= EMNoCarry.Predict(MtmFeature);

	double DragCarryLogLikelihood	= RespDragCarry.val[0];
	double DragCarryLikelihood		= pow(2, DragCarryLogLikelihood);

	double WornCarryLogLikelihood 	= RespWornCarry.val[0];
	double WornCarryLikelihood 		= pow(2, WornCarryLogLikelihood);

	double NoCarryLogLikelihood 	= RespNoCarry.val[0];
	double NoCarryLikelihood 		= pow(2, NoCarryLogLikelihood);


	double Denom = DragCarryLikelihood * oPriorProb.Get_DraggedObjPrior() +
			WornCarryLikelihood * oPriorProb.Get_WornObjPrior() +
			NoCarryLikelihood * oPriorProb.Get_PersonPrior();

	vScore.at(WORN_CARRY_LABEL) = (WornCarryLikelihood * oPriorProb.Get_WornObjPrior())/Denom;
	vScore.at(DRAG_CARRY_LABEL) = (DragCarryLikelihood * oPriorProb.Get_DraggedObjPrior()) / Denom;
	vScore.at(PERSON_LABEL)		= (NoCarryLikelihood * oPriorProb.Get_PersonPrior())/Denom;

	return vScore;
}


/*******************************************************************
 * Function Name: SetTrainingFolderPath
 * Return Type 	: int
 * Created On	: Oct 3, 2013
 * Created By 	: hrushi
 * Comments		: Set the Training folder path
 * Arguments	: const fs::path fsPath
 *******************************************************************/
int DetectByShape::SetTrainingFolderPath( const fs::path fsPath)
{
	m_TrainingFolderPath = fsPath;

	return EXIT_SUCCESS;
}




/*****************************************************
 * Function	: DetectByShape Copy Constructor
 * Date		: Oct 11, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
DetectByShape::DetectByShape(const DetectByShape& rhs ):Detect(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 11, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
DetectByShape& DetectByShape:: operator=( const DetectByShape& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 11, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByShape::Allocate( const DetectByShape& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 11, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int DetectByShape::Copy( const DetectByShape& rhs )
{
	Detect::operator =(rhs);
	/*VectorOp<double>::DeepCopy(m_WornShapeFeature, rhs.m_WornShapeFeature);
	VectorOp<double>::DeepCopy(m_DragShapeFeature, rhs.m_DragShapeFeature);
	VectorOp<double>::DeepCopy(m_NoCarryFeature, rhs.m_NoCarryFeature);*/

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Oct 11, 2013
 * Created By 	: hrushi
 * Comments		: Initializes the members
 * Arguments	:
 *******************************************************************/
int DetectByShape::Init_Members( const fs::path fsPath )
{

	SetTrainingFolderPath(fsPath);
	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: LoadShapeFeatures
 * Return Type 	: int
 * Created On	: Oct 11, 2013
 * Created By 	: hrushi
 * Comments		: Load the Shape Features from the Train Folder
 * Arguments	: const fs::path TrainFolderPath
 *******************************************************************/
int DetectByShape::LoadShapeFeatures( const fs::path TrainFolderPath)
{
	vector<string> vFileList = {SHAPE_DRAG_CARRY, SHAPE_WORN_CARRY, SHAPE_NO_CARRY};

	for(auto FileName : vFileList )
	{
		string FeatureFilePath = TrainFolderPath.string() + FileName;
		cout << "FeatureFilePath " << FeatureFilePath << endl;

		ReadFeatureList oRead(FeatureFilePath);

		if( FileName == SHAPE_DRAG_CARRY)
		{
			if(m_SFC.m_DragShapeFeature.size() == 0)
			{
				oRead.ReadIn();
				m_SFC.m_DragShapeFeature = oRead.GetFeatureList();
				cout << "m_DragShapeFeature: " << m_SFC.m_DragShapeFeature.size() << endl;
			}
			else
			{
				cout << "Drag Shape file already loaded." << endl;
			}
		}
		else if( FileName == SHAPE_WORN_CARRY )
		{
			if(m_SFC.m_WornShapeFeature.size() == 0)
			{
				oRead.ReadIn();
				m_SFC.m_WornShapeFeature = oRead.GetFeatureList();
				cout << "m_WornShapeFeature: " << m_SFC.m_WornShapeFeature.size() << endl;
			}
			else
			{
				cout << "Worn Shape file already loaded." << endl;
			}
		}
		else if( FileName == SHAPE_NO_CARRY )
		{
			if( m_SFC.m_NoCarryFeature.size() == 0 )
			{
				oRead.ReadIn();
				m_SFC.m_NoCarryFeature = oRead.GetFeatureList();
				cout << "m_NoCarryFeature: " << m_SFC.m_NoCarryFeature.size() << endl;
			}
			else
			{
				cout << "No Carry Shape file already loaded." << endl;
			}
		}
	}

	return EXIT_SUCCESS;
}
