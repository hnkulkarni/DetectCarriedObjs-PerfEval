/*
 * App.cpp
 *
 *  Created on: Feb 2, 2013
 *      Author: hrushi
 */

#include "App.h"

/**********************************************************************
 * Function Name: App
 * Date 		: Feb 2, 2013
 * Author		: hrushi
 * Comments		: Constructor
 * Args			:
 **********************************************************************/
App::App() {

}

/**********************************************************************
 * Function Name: ~App
 * Date 		: Feb 2, 2013
 * Author		: hrushi
 * Comments		: Default Destructor
 * Args			:
 **********************************************************************/
App::~App()
{

	cv::destroyAllWindows(); // Close all windows!!

}

/**********************************************************************
 * Function Name: App
 * Date 		: Feb 2, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
App::App(const App& rhsApp)
{
	Allocate_App(rhsApp);
	Copy_App(rhsApp);
}

/**********************************************************************
 * Function Name: operator
 * Date 		: Feb 2, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
App& App::operator=(const App & rhsApp)
{
	Allocate_App(rhsApp);
	Copy_App(rhsApp);

	return *this;
}

/**********************************************************************
 * Function Name: Copy_App
 * Date 		: Feb 2, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int App::Copy_App(const App & rhsApp)
{

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Allocate_App
 * Date 		: Feb 2, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int App::Allocate_App(const App & rhsApp)
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Run
 * Return Type 	: int
 * Created On	: Feb 2, 2013
 * Created By 	: hrushi
 * Comments		: Runs the files using the parsed commands
 * Arguments	: const Args& args
 *******************************************************************/
int App::Run(const Args& args)
{

	std::cout << "Using Boost " << BOOST_VERSION / 100000 << "." // major version
			<< BOOST_VERSION / 100 % 1000 << "."  // minior version
			<< BOOST_VERSION % 100                // patch level
			<< std::endl;

	switch (args.GetRunMode())
	{

	case OP_MULTIPLE_IMAGES:
		RunOnManyImages(args);
		break;

	case OP_COPY_MASK_IMAGES:
		RunCopyImage(args);
		break;

	case OP_SINGLE_IMAGE:
		RunOnImage(args);
		break;

	case OP_LABEL_IMAGES:

		if(args.isLabelGroundTruth())
		{
			RunLabelling(args);
			RunUpdateLabelType(args);
		}
		else
		{
			RunLabelling(args);
			RunUpdateFeatures(args); // Updates Pose Features as well
		}
		break;

	case OP_UPDATE_FEATURES:
		RunUpdateFeatures(args);
		break;


	case OP_DEMO:
		RunDemo(args);
		break;
	}

	return EXIT_SUCCESS;
}




/*******************************************************************
 * Function Name: RunUpdateFeatures
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Recalculates and updates the entire feature file
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdateFeatures(const Args& args)
{
	cout << "Now updating the features" << endl;
	const string FolderPath = args.GetSearchFolderPath() + DATA_FLDR;
	FileSystem::CreateFolder(FolderPath);

	bool isUpdateAll = (args.GetUpdateMode() == UPDATE_MODE_ALL);

	if(isUpdateAll || (args.GetUpdateMode() == UPDATE_MODE_CARRY_TYPE))
	{
		RunUpdateLabelType(args);
	}

	if(isUpdateAll || (args.GetUpdateMode() == UPDATE_LOC_CARRY_PROB))
	{
		//**************************************************************
		// *           Possible Optimization over here !!
		//**************************************************************
		RunUpdateLocProbImg(args, ALL_LABEL_FILENAME, ALL_LABEL_FILENAME);
		RunUpdateLocProbImg(args, DRAG_CARRY_LABEL_FILE, ALL_LABEL_FILENAME);
		RunUpdateLocProbImg(args, WORN_CARRY_LABEL_FILE, ALL_LABEL_FILENAME);
	}

	if( isUpdateAll || ( args.GetUpdateMode() == UPDATE_LOC_PERSON_PROB ))
	{
		RunUpdatePersonLocProb(args, PERSON_LOC_PROB_PROB_IMG, DRAG_CARRY_LABEL_FILE, WORN_CARRY_LABEL_FILE);
	}
	if(isUpdateAll || (args.GetUpdateMode() == UPDATE_PRIOR_PROBS))
	{
		UpdatePriorProbValues(args);
	}

	if(isUpdateAll || (args.GetUpdateMode() == UPDATE_MODE_POSE))
	{
		RunUpdatePoseFeatures(args);
		RunUpdatePoseEM(args);
	}

	if(isUpdateAll || (args.GetUpdateMode() == UPDATE_MODE_SHAPE ))
	{
		RunUpdateShape(args);
		RunUpdateShapeEM(args);
	}

	if(isUpdateAll || (args.GetUpdateMode() == UPDATE_APPEARANCE ))
	{
		RunUpdateAppearance(args);
	}


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: RunUpdateAppearance
 * Return Type 	: int
 * Created On	: Oct 31, 2013
 * Created By 	: hrushi
 * Comments		: Updating Appearance Features
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdateAppearance( const Args& args) const
{
	cout << "Updating Appearance Features" << endl;

	std::map<string, string> TrkMaskMap = MakeTracknMaskImageList(args);

	cout << TrkMaskMap.size() << endl;

	AlgoTrain ATrain;
	ATrain.TrainApperance(args, TrkMaskMap);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: RunUpdateShapeEM
 * Return Type 	: int
 * Created On	: Oct 6, 2013
 * Created By 	: hrushi
 * Comments		: Update Shape EM
 * Arguments	: List of arguments
 *******************************************************************/
int App::RunUpdateShapeEM( const Args& args ) const
{
	vector<string> FileList = {SHAPE_DRAG_CARRY, SHAPE_WORN_CARRY, SHAPE_NO_CARRY};
	string TrainingFolderPath = args.GetSearchFolderPath();

	VVDOUBLE FeatureDragCarry, FeatureWornCarry, FeatureNoCarry;

	for( unsigned int i = 0; i < FileList.size(); i++ )
	{
		string FilePath = TrainingFolderPath + FileList.at(i);
		cout << "Reading features from: " << FilePath << endl;

		ReadFeatureList oRead(FilePath);
		oRead.ReadIn();

		switch(i)
		{
		case 0:
			FeatureDragCarry = oRead.GetFeatureList();
			break;

		case 1:
			FeatureWornCarry = oRead.GetFeatureList();
			break;

		case 2:
			FeatureNoCarry = oRead.GetFeatureList();
			break;
		}
	}

	ShapeEM DragCarryEM(3, FeatureDragCarry);
	fs::path fsEMDragPath = TrainingFolderPath + SHAPE_DRAG_CARRY_EM;
	WriteEM wEMDragCarry(fsEMDragPath, DragCarryEM);

	ShapeEM WornCarryEM(3, FeatureWornCarry);
	fs::path fsEMWornPath = TrainingFolderPath + SHAPE_WORN_CARRY_EM;
	WriteEM wEMWornCarry(fsEMWornPath, DragCarryEM);

	ShapeEM NoCarryEM(3, FeatureNoCarry);
	fs::path fsEMPath_NoCarry = TrainingFolderPath + SHAPE_NO_CARRY_EM;
	WriteEM wEMNoCarry(fsEMPath_NoCarry, NoCarryEM);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: RunUpdatePoseEM
 * Return Type 	: int
 * Created On	: Aug 3, 2013
 * Created By 	: hrushi
 * Comments		: Recalculates the PoseEM
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdatePoseEM( const Args& args)
{

	string TrainingFolderPath = args.GetSearchFolderPath();

	mp_PoseFeature map_FileFeature = ReadPoseFeature::GetMap_String_PoseFeature(TrainingFolderPath, ALL_POSE_FEATURE_FILES);

	for(auto& Mp : map_FileFeature)
	{
		fs::path Feature_Path = TrainingFolderPath + Mp.first;
		fs::path fsEM = Feature_Path.parent_path().string() + "/" + Feature_Path.stem().string() + EM_EXTN;

		PoseEM PEM(3, Mp.second);
		WriteEM wEM1(fsEM, PEM );

		cout << "Writing to: " << fsEM << endl;
	}

	return EXIT_SUCCESS;
}




/*******************************************************************
 * Function Name: UpdatePriorProbValues
 * Return Type 	: int
 * Created On	: Jul 21, 2013
 * Created By 	: hrushi
 * Comments		: Update Prior Prob Values
 * Arguments	: const Args& args
 *******************************************************************/
int App::UpdatePriorProbValues( const Args& args)
{
	const string TrainingFolderPath = args.GetSearchFolderPath();
	const string sPriorProbFilePath = TrainingFolderPath + PRIOR_PROB_FILENAME;

	cout << "TrainFolderPath " << TrainingFolderPath << endl;

	cout << "Calculating the Prior Priobs again!!" << endl;

	// Load the Prior Probabilties of the Region Locations; Like Bagpack,  Suitecase and Person
	vector<string> vProbImgList = {WORN_CARRY_PROB_IMG, DRAG_CARRY_PROB_IMG, PERSON_LOC_PROB_PROB_IMG};
	ProbImg ProbTemp;

	vector<ProbImg> vProbImgs;

	for(auto ImgName : vProbImgList)
	{
		ProbTemp.Load( TrainingFolderPath + ImgName );
		vProbImgs.push_back(ProbTemp);
	}

	// Calculate the Prior Probs and write them down in a file.
	PriorProb PP;
	WritePriorProbs wPP( sPriorProbFilePath );
	PP.CalculatePriorProbs(TrainingFolderPath, vProbImgs, args );
	wPP.Set_PriorProb( PP );
	wPP.WriteOut();

	return EXIT_SUCCESS;
}
/*******************************************************************
 * Function Name: RunUpdatePersonLocProb
 * Return Type 	: int
 * Created On	: Jun 3, 2013
 * Created By 	: hrushi
 * Comments		: Builds the Person Contour Look Up Table and then calls RunUpdateLocProbImg
 * Arguments	: const Args& args, const string sFileName, const string sLableFileName, const string bLabelFileName
 *******************************************************************/
int App::RunUpdatePersonLocProb( const Args& args, const string sFileName, const string sLabelFileName, const string bLabelFileName)
{

	Labels suitecase_Lbl(args, sLabelFileName); suitecase_Lbl.Read(args);
	Labels bagpack_Lbl(args, bLabelFileName);	bagpack_Lbl.Read(args);

	Labels Lbl(args, ALL_LABEL_FILENAME);
	Lbl.Read(args);
	tdef_LabelMap lMap = Lbl.GetLabelMap();

	std::map<string, string> TrkMaskMap = MakeTracknMaskImageList(args);

	unsigned int uiCount(0);
	int ProbImgRows(140), ProbImgCols(70);
	Mat LocProb = Mat::zeros(ProbImgRows, ProbImgCols, CV_64F);

	cout << "Calculating Person Probability from " << sLabelFileName << ", " << bLabelFileName << " : " << endl;

	for (tdef_LabelMap::const_iterator itr = lMap.begin(); itr != lMap.end(); itr++)
	{
		string LblSegImgPath =itr->first;

		int isSuiteCase	= suitecase_Lbl.AlreadyPresent( LblSegImgPath );
		int isBagPack 	= bagpack_Lbl.AlreadyPresent( LblSegImgPath );

		uiCount++;

		string RelativeImgPath = itr->first;
		fs::path ImagePath =  Lbl.GetComplateImgFilePath( RelativeImgPath );

		string sMaskImagePath = TrkMaskMap.at(ImagePath.string());

		ContourMap Segments = Detect::GetSegments(ImagePath, fs::path(sMaskImagePath), false, args);

		GrayImg CntrMask;

		//Starting from iCntr = 1; Because, iCntr = 0 is Background Contour
		for( int iCntr = 1; iCntr < (int)Segments.AllContourMap.size(); iCntr++ )
		{
			if( (isSuiteCase == UN_INITIALIZED_LABEL) && ( isBagPack == UN_INITIALIZED_LABEL ))
			{
				CntrMask.SetImage(Segments.AllContourMap.at(iCntr).GetCtrMask());
				CntrMask.Resize(ProbImgRows, ProbImgCols);

				for (unsigned int i = 0; i < CntrMask.GetNumRows(); i++)
				{
					for (unsigned int j = 0; j < CntrMask.GetNumCols(); j++)
					{
						if (CntrMask.at(i, j) == MAX_GRAY_VALUE) // We are inside the contour
						{
							LocProb.at<double>(i, j) = LocProb.at<double>(i, j) + 1;
						}
					}
				}
			}
		}

		UINT MapSize = lMap.size();
		Loop::PrintStatus(uiCount, MapSize);
	}

	LocProb = (LocProb / uiCount) * MAX_GRAY_VALUE;
	Mat Gray(140, 70, CV_8UC1);

	for (int i = 0; i < ProbImgRows; i++)
	{
		for (int j = 0; j < ProbImgCols; j++)
		{
			Gray.at<char>(i, j) = (char) LocProb.at<double>(i, j);
		}
	}

	GrayImg TempImg;
	TempImg.SetImage(Gray);
	TempImg.Display(DISP_DELAY);

	TempImg.Write(args.GetSearchFolderPath() + sFileName );


	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunUpdateLabelType
 * Return Type 	: int
 * Created On	: May 7, 2013
 * Created By 	: hrushi
 * Comments		: Displayes the images that are already labelled and then updates its Label Type
 * 					Type 'c': Manually Carry, eg. Suitcase, airbag
 * 					Type 'b': Bagpacks, Shabnams,
 * 					Type 'p': Person
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdateLabelType(const Args& args)
{
	cout << "Label Now Flag " << args.LabelNow() << endl;

	Labels Drag_Carry_Lbl(args, DRAG_CARRY_LABEL_FILE);
	Drag_Carry_Lbl.Read(args);

	Labels Worn_Carry_Lbl(args, WORN_CARRY_LABEL_FILE);
	Worn_Carry_Lbl.Read(args);

	string LblFilePath = "";
	if(args.isLabelGroundTruth())
	{
		LblFilePath = GROUND_TRUTH_FILE;
	}
	else
	{
		LblFilePath = ALL_LABEL_FILENAME;
	}


	Labels Lbl(args, LblFilePath);
	Lbl.Read(args);

	tdef_LabelMap lMap = Lbl.GetLabelMap();

	for (tdef_LabelMap::const_iterator itr = lMap.begin(); itr != lMap.end(); itr++)
	{
		string LblSegImgPath = Lbl.GetSegImgPath(itr->first);

		if (itr->second > 0)
		{
			if( args.isSkipExisting() )
			{
				bool isPresent_Dragged 	= Drag_Carry_Lbl.AlreadyPresent(itr->first) != UN_INITIALIZED_LABEL;
				bool isPresent_Worn 	= Worn_Carry_Lbl.AlreadyPresent( itr->first) != UN_INITIALIZED_LABEL;

				if( isPresent_Dragged || isPresent_Worn)
				{
					cout << "Skipping " << itr->first << endl;
					continue;
				}
				else
				{
					RunUpdateLabelType(args, itr->first, LblSegImgPath, itr->second, Worn_Carry_Lbl, Drag_Carry_Lbl);
				}

			}
			else
			{
				RunUpdateLabelType(args, itr->first, LblSegImgPath, itr->second, Worn_Carry_Lbl, Drag_Carry_Lbl);
			}
		}
	}

	Worn_Carry_Lbl.Write(args);
	Drag_Carry_Lbl.Write(args);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunUpdateLabelType
 * Return Type 	: int
 * Created On	: May 19, 2013
 * Created By 	: hrushi
 * Comments		: Updates the two label classes with the relative image path and the countour numbers
 * Arguments	: const Args& args, Labels& bgpk_lbl, Labels& suiteCase_lbl
 *******************************************************************/
int App::RunUpdateLabelType(const Args& args, const string LablMapPath, const string SegImgPath, const int CntrNum, Labels& Worn_CarryObj_lbl, Labels& Dragged_CarryObj_lbl)
{

	ColorImg TempClrImg;
	TempClrImg.Load(SegImgPath);

	StringOp<int> oStr;
	string strCntrNum = "For: " + oStr.GetString(CntrNum);

	cv::Point Pt(10, 10);
	TempClrImg.PutText(strCntrNum, COLOR_WHITE, COLOR_RED, Pt);
	string Type = TempClrImg.Display(DISP_WAIT_FOR_KEY);

	if (Type.compare("d") == 0)
	{
		Dragged_CarryObj_lbl.AddToMap(LablMapPath, CntrNum);
		cout << "Pose Dependent Carry Obj. Size: " << Dragged_CarryObj_lbl.GetNumLabels() << endl;
	}
	else if (Type.compare("w") == 0)
	{
		Worn_CarryObj_lbl.AddToMap(LablMapPath, CntrNum);
		cout << "Pose Independent Obj. Size: " << Worn_CarryObj_lbl.GetNumLabels() << endl;
	}
	else
	{

		cerr << "Invalid entry: " << endl;
		cerr << "(p): For Pose Dependent  type carry objects " << endl;
		cerr << "(i): For Pose InDependent type objects " << endl;
		cerr << "Calling Label function again " << endl;
		RunUpdateLabelType(args, LablMapPath, SegImgPath, CntrNum, Worn_CarryObj_lbl, Dragged_CarryObj_lbl);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunUpdateLocProbImg
 * Return Type 	: int
 * Created On	: Apr 23, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the Probability image; if the the image is not present, it is created.
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdateLocProbImg(const Args& args, const string LabelFileName, const string AllLabelFileName )
{

	Labels AllLbl(args, LabelFileName);
	AllLbl.Read(args);
	const unsigned int TotalCount = AllLbl.GetNumLabels();

	Labels Lbl(args, LabelFileName);
	Lbl.Read(args);

	std::map<string, string> TrkMaskMap = MakeTracknMaskImageList(args);
	const fs::path LabelFilePath 		= Lbl.GetLabelFilePath();
	const fs::path LabelFileFolderPath 	= LabelFilePath.parent_path();
	const fs::path LocProbilityImgPath 	= LabelFileFolderPath.string() + "/" + LabelFilePath.stem().string() + "Prob.png";

	Mat LocProb = Mat::zeros(RESIZE_ROWS, RESIZE_COLS, CV_64F);
	GrayImg TempImg;

	cout << "Calculating from: " << LabelFileName << " : ";
	UINT LoopCntr(0);

	for (tdef_LabelMap::const_iterator itr = Lbl.GetLabelMapItrBegin();	itr != Lbl.GetLabelMapItrEnd(); itr++)
	{
		int Label = itr->second;

		if ((Label > NO_CARRIED_OBJECT) & (Label != (int) BACKGROUND_LABEL)) // Calculate pose features only if there is a carried object.
		{

			string RelativeImgPath = itr->first;
			fs::path ImagePath = Lbl.GetComplateImgFilePath( RelativeImgPath );

			string sMaskImagePath = TrkMaskMap.at(ImagePath.string());

			ContourMap Segments = Detect::GetSegments(ImagePath, fs::path(sMaskImagePath), false, args);

			GrayImg CntrMask;
			CntrMask.SetImage(Segments.AllContourMap.at(Label).GetCtrMask());

			CntrMask.Resize(RESIZE_ROWS, RESIZE_COLS);

			for (unsigned int i = 0; i < CntrMask.GetNumRows(); i++)
			{
				for (unsigned int j = 0; j < CntrMask.GetNumCols(); j++)
				{
					if (CntrMask.at(i, j) == MAX_GRAY_VALUE) // We are inside the contour
					{
						LocProb.at<double>(i, j) = LocProb.at<double>(i, j) + 1;
					}
				}
			}
		}

		LoopCntr++;
		Loop::PrintStatus(LoopCntr, Lbl.GetNumLabels());
	}

	LocProb = (LocProb / TotalCount) * MAX_GRAY_VALUE;
	Mat Gray(140, 70, CV_8UC1);

	for (unsigned int i = 0; i < RESIZE_ROWS; i++)
	{
		for (unsigned int j = 0; j < RESIZE_COLS; j++)
		{
			Gray.at<char>(i, j) = (char) LocProb.at<double>(i, j);
		}
	}

	TempImg.SetImage(Gray);
	TempImg.Display(DISP_DELAY);
	TempImg.Write(LocProbilityImgPath.string());
	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunUpdatePoseFeatures
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Recalculates the Pose Features for the given image
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdatePoseFeatures(const Args& args)
{

	vector<string> FileList = {DRAG_CARRY_LABEL_FILE, WORN_CARRY_LABEL_FILE};

	Labels TempLbl(args, DRAG_CARRY_LABEL_FILE);
	fs::path LabelFileFolderPath = TempLbl.GetLabelFilePath().parent_path();

	vector<char> vPartKey {'c', 'm'};
	Map_WrtPoseFeature WritePF_NoCarry 	= OpenWritePoseFeatureFile(LabelFileFolderPath, vPartKey,  NO_CARRY_POSE_FEATURE_FILE);

	for( auto LblFile : FileList )
	{
		Labels Lbl(args, LblFile);
		Lbl.Read(args);

		string Pose_Feature_File = "";

		if( LblFile == DRAG_CARRY_LABEL_FILE)
		{
			Pose_Feature_File = DRAG_POSE_FEATURE_FILE;
		}
		else if( LblFile == WORN_CARRY_LABEL_FILE )
		{
			Pose_Feature_File = WORN_POSE_FEATURE_FILE;
		}

		std::map<string, string> TrkMaskMap = MakeTracknMaskImageList(args);

		cout << "DEBUG: " <<  Pose_Feature_File << endl;

		Map_WrtPoseFeature WritePF_Carry 	= OpenWritePoseFeatureFile(LabelFileFolderPath, vPartKey,  Pose_Feature_File);

		for (tdef_LabelMap::const_iterator itr = Lbl.GetLabelMapItrBegin();	itr != Lbl.GetLabelMapItrEnd(); itr++)
		{
			int Label = itr->second;

			fs::path ImagePath = Lbl.GetComplateImgFilePath(itr->first);
			fs::path BoxFilePath = ImagePath.parent_path().string() + "/Boxes/" + ImagePath.stem().string() + ".txt";
			fs::path SaveImgDir = ImagePath.parent_path().string() + "/PoseFeature/";

			FileSystem::CreateFolder(SaveImgDir);
			ColorImg WorkImg, TempImg;
			WorkImg.Load(ImagePath.string());

			if (!fs::exists(BoxFilePath))
			{
				cout << "No Pose File found for: " << ImagePath << endl;
				continue;
			}

			PoseFile PF(BoxFilePath.string());
			PF.ReadIn();

			fs::path sMaskImagePath = TrkMaskMap.at(ImagePath.string());

			ContourMap Segments = Detect::GetSegments(ImagePath, sMaskImagePath, false, args);
			cout << "Size of ContourMap " << Segments.AllContourMap.size() << " Label " <<  Label << endl;

			PF.AddPoseFeatures(WorkImg, Segments, Label, vPartKey, WritePF_Carry, WritePF_NoCarry, args );
		}


		for(auto PartKey: vPartKey)
		{
			WritePF_Carry.at(PartKey)->WriteOut();
		}

		WritePF_Carry.clear();

	}

	for(auto PartKey: vPartKey)
	{
		WritePF_NoCarry.at(PartKey)->WriteOut();
	}

	WritePF_NoCarry.clear();


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: RunUpdateShape
 * Return Type 	: int
 * Created On	: Sep 29, 2013
 * Created By 	: hrushi
 * Comments		: Calculate the shape features for regions
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdateShape( const Args& args)
{

	Labels AllLbl(args, ALL_LABEL_FILENAME);
	AllLbl.Read(args);

	Labels WornCarry(args, WORN_CARRY_LABEL_FILE);
	WornCarry.Read(args);

	Labels DragCarry(args, DRAG_CARRY_LABEL_FILE);
	DragCarry.Read(args);

	std::map<string, string> TrkMaskMap = MakeTracknMaskImageList(args);

	// This is the path to the Data Folder.
	fs::path LabelFileFolderPath = AllLbl.GetLabelFilePath().parent_path().parent_path();

	string Carried_CarryFeature_Path = LabelFileFolderPath.string() + SHAPE_DRAG_CARRY;
	WriteShapeFeatures Write_PoseDependent_Carry(Carried_CarryFeature_Path);

	string Worn_CarryFeature_Path = LabelFileFolderPath.string() + SHAPE_WORN_CARRY;
	WriteShapeFeatures Write_PoseInDependent_Carry(Worn_CarryFeature_Path);

	string NoCarryFeature_Path = LabelFileFolderPath.string() + SHAPE_NO_CARRY;
	WriteShapeFeatures Write_NoCarry( NoCarryFeature_Path );

	for (tdef_LabelMap::const_iterator itr = AllLbl.GetLabelMapItrBegin();	itr != AllLbl.GetLabelMapItrEnd(); itr++)
	{
		fs::path ImagePath = AllLbl.GetComplateImgFilePath(itr->first);
		cout << ImagePath << endl;

		int isPoseDependent = DragCarry.AlreadyPresent(itr->first);

		ColorImg WorkImg, TempImg;

		try
		{
			WorkImg.Load(ImagePath.string());
		}
		catch(int e)
		{
			cerr << "Error Opening " << ImagePath.string() << endl;
			cerr << "Continuing with next image" << endl;
			continue;
		}

		fs::path sMaskImagePath = TrkMaskMap.at(ImagePath.string());
		ContourMap Segments = Detect::GetSegments(ImagePath, sMaskImagePath, false, args);

		int Label = itr->second;

		ShapeFeatures SF;
		HuMoments HuM;

		if(isPoseDependent != UN_INITIALIZED_LABEL )
		{
			VDOUBLE SF_Hu = SF.AddShapeFeatures(Segments, HuM, Label, Write_PoseDependent_Carry, Write_NoCarry );
		}
		else
		{
			VDOUBLE SF_Hu = SF.AddShapeFeatures(Segments, HuM, Label, Write_PoseInDependent_Carry, Write_NoCarry );
		}

	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: OpenWritePoseFeatureFile
 * Return Type 	: std::map<char, WritePoseFeature>
 * Created On	: Sep 24, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Map indexed with part key pointing to the WritePoseFeature File
 * Arguments	: const fs::path FolderPath, char PartKey
 *******************************************************************/
Map_WrtPoseFeature App::OpenWritePoseFeatureFile( const fs::path FolderPath, const vector<char> vPartKey, const fs::path FileAuxName ) const
{
	Map_WrtPoseFeature MapWritePF;

	for( auto PartKey : vPartKey )
	{
		fs::path PoseFeatureFilePath = FolderPath.string()	+ "/" + PartKey + FileAuxName.filename().string();

		shptr_WrPF TempWritePF( new WritePoseFeature(PoseFeatureFilePath.string()) );
		MapWritePF[PartKey] = TempWritePF;
	}

	return MapWritePF;
}


/*******************************************************************
 * Function Name: RunUpdateContourFeatures
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Re-calculates all the contour features again, and updates them
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunUpdateContourFeatures(const Args& args)
{

	string searchFolderPath = args.GetSearchFolderPath();
	string TrackFolderName 	= args.GetTrackFolderName();
	string MaskFoldername 	= args.GetMaskFolderName();

	Labels Lbl(args, ALL_LABEL_FILENAME);
	Lbl.Read(args);

	Features ObjFeatures(args, WRITE_MODE);

	std::map<string, string> TrkMaskMap = MakeTracknMaskImageList(args);

	int CurrentLabel = UN_INITIALIZED_LABEL;
	for (tdef_LabelMap::const_iterator itr = Lbl.GetLabelMapItrBegin(); itr != Lbl.GetLabelMapItrEnd(); itr++)
	{
		fs::path p = itr->first;
		cout << "Path " << p << endl;

		CurrentLabel = Lbl.AlreadyPresent(p.string());
		cout << "Current Label" << CurrentLabel << endl;

		string RelativeImgPath = itr->first;
		fs::path LabelFilePath = Lbl.GetLabelFilePath();
		fs::path ImagePath = LabelFilePath.parent_path().string()	+ RelativeImgPath;

		fs::path MaskPath = TrkMaskMap[ImagePath.string()];

		ColorImg Img;
		ContourMap Segments(Img.GetNumRows(), Img.GetNumCols() );// = Dtct.GetSegments(ImagePath.string(),MaskPath.string(), args);
		Segmentation Segm;
		vector<int> kLabels = Segm.DoSlic(ImagePath.string(), false);
		Segments.LabelsToContours(kLabels, args );
		Segments.CalculateEveryContourHistgrm(Img);

		GrayImg BkMask;

		double OverlapThreshold = 0.01;
		Segments.ListBkContours( BkMask, OverlapThreshold, args );

		ObjFeatures.Add(p, CurrentLabel, Segments, args);

	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunLabelling
 * Return Type 	: int
 * Created On	: Feb 9, 2013
 * Created By 	: hrushi
 * Comments		: Writes Lables for all the images in the given folder
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunLabelling(const Args& args)
{

	cout << "Inside Labelling " << endl;
	std::map<string, string> TrkMaskMap = MakeTracknMaskImageList(args);

	const string FolderPath = args.GetSearchFolderPath() + DATA_FLDR;
	FileSystem::CreateFolder(FolderPath);

	RunLabels(args, TrkMaskMap);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunLabels
 * Return Type 	: int
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Run Labels for all the images in the given folder
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunLabels(const Args& args,	const std::map<string, string>& TrkMskMap)
{

	string searchFolderPath = args.GetSearchFolderPath();
	string TrackFolderName = args.GetTrackFolderName();
	string MaskFoldername = args.GetMaskFolderName();

	Features ObjFeatures(args, WRITE_MODE);

	cout << "Label Current Ground Truth Flag: " << args.isLabelGroundTruth() << endl;

	string LblFilePath = "";

	if(args.isLabelGroundTruth())
	{
		LblFilePath = GROUND_TRUTH_FILE;
	}
	else
	{
		LblFilePath = ALL_LABEL_FILENAME;
	}

	Labels Lbl(args, LblFilePath);
	Lbl.Read(args);

	// Update the labels marked for labelling at a later date
	if (args.LabelNow())
	{
		Lbl.MarkBackLogLabels(args);
	}

	for (std::map<string, string>::const_iterator itr = TrkMskMap.begin();	itr != TrkMskMap.end(); itr++)
	{
		const fs::path p = itr->first;
		cout << "Using: " << p << endl;

		int AlLbl = Lbl.AlreadyPresent(p, false);
		int CurrentLabel;

		if (AlLbl == UN_INITIALIZED_LABEL)
		{
			ColorImg Img(itr->first);

			if( (args.GetSkipWidth() > 0 ) && (Img.GetNumCols() < args.GetSkipWidth() ))
			{
				//cout << "Skip as Img Width(" << Img.GetNumCols() << ") < " << args.GetSkipWidth() << endl;
				continue;
			}

			if( (args.GetSkipHeight() > 0 ) && (Img.GetNumRows() < args.GetSkipHeight() ))
			{
				//cout << "Skip as Img Width(" << Img.GetNumRows() << ") < " << args.GetSkipHeight() << endl;
				continue;
			}


			ContourMap Segments = Detect::GetSegments(fs::path( itr->first ) , fs::path(itr->second), true,	args);

			ColorImg Overlay = Img.Overlay(Segments, 1, cv::Scalar(0, 0, 255), 	args);

			if(args.UseGndTruthforLabels() )
			{
				cout << "Using the given ground truth" << endl;
				const fs::path TrackFilePath = TrackXML::GetTrackFilePath(fs::path(itr->first));
				static TrackXML oTrack(TrackFilePath);

				// Reload if the track file path has changed
				if(oTrack.GetFilePath() != TrackFilePath )
				{
					cout << TrackFilePath << endl;
					oTrack = TrackXML(TrackFilePath);
				}


				const fs::path ViperFilePath = ViperXML::GetViperXMLPath(TrackFilePath);
				static ViperXML oViperXML(ViperFilePath);

				//Reload if it is already present
				if(oViperXML.GetFilePath() != ViperFilePath )
				{
					oViperXML = ViperXML(ViperFilePath);
				}

				CurrentLabel = Lbl.Add(p, oTrack, oViperXML, Overlay, args, Segments);

			}
			else
			{
				CurrentLabel = Lbl.Add(p, Overlay, args, Segments);
			}

			if(CurrentLabel > NO_CARRIED_OBJECT )
			{
				Overlay = Overlay.Overlay(Segments.AllContourMap.at(CurrentLabel), DISP_DELAY, COLOR_CYAN, args);
				Overlay.Display(DISP_DELAY);
				string OverwritePath = Detect::GiveSegImgPath( itr->first, "_Merge").string();
				Overlay.Write(OverwritePath);
			}

			ObjFeatures.Add(p, CurrentLabel, Segments, args);

		}
		else
		{
			//cout << "Skipped Already labeled " << p.string() << endl;
			cout << ".";
			std::flush(cout);
		}

	}

	return EXIT_SUCCESS;

}

/*******************************************************************
 * Function Name: MakeImageList
 * Return Type 	: std::map<string, string>
 * Created On	: Feb 13, 2013
 * Created By 	: hrushi
 * Comments		: Creates a map of all the mask Images and Track Images
 * Arguments	: const Args& args
 *******************************************************************/
std::map<string, string> App::MakeTracknMaskImageList(const Args& args) const
{

	const string searchFolderPath = args.GetSearchFolderPath();
	const string TrackFolderName = args.GetTrackFolderName();
	const string MaskFoldername = args.GetMaskFolderName();
	const string CurrentDir, MaskImgPath, CurrentPath;

	cout << "Populating image list " << endl;
	cout << "This may take some time, depending on the number of images " << endl;

	FileSystem oFS;
	cout << "Listing Images" << endl;
	vector<fs::path> LS = oFS.ListAllImagesInFolder(searchFolderPath);

	cout << "Sorting if the parent folder is present " << endl;
	vector<fs::path> LS_Track = oFS.NameFilter_folderPresent(LS, TrackFolderName, true);

	cout << "Sorting if the track folder is present " << endl;
	vector<fs::path> LS_Track_Parent = oFS.NameFilter_parentName(LS_Track, TrackFolderName, true);

	cout << "Making Mask Image List " << endl;
	vector<fs::path> LS_Mask = FileSystem::GetMaskImgPathVector(MaskFoldername, LS_Track_Parent, TrackFolderName);

	cout << "Populating Map" << endl;
	std::map<string, string> TrkMaskMap = PopulateMap(LS_Track_Parent, LS_Mask);

	cout << "Done populating map" << endl;

	return TrkMaskMap;
}

/*******************************************************************
 * Function Name: PopulateMap
 * Return Type 	: std::map<string, string>
 * Created On	: Feb 16, 2013
 * Created By 	: hrushi
 * Comments		: Creates a map using the strings in the vector, to the strings in the value vector
 * Arguments	: const vector<string>& key, const vector<string>& val
 *******************************************************************/
std::map<string, string> App::PopulateMap(const vector<fs::path>& Key, const vector<fs::path>& Val) const
{
	std::map<string, string> MyMap;

	if (Key.size() != Val.size())
	{
		cout << "Num Keys and Num Values do not match while creating the map " 	<< endl;
		exit(ERR_DIMENSION_MISMATCH);
	}
	else
	{
		vector<fs::path>::const_iterator itrVal = Val.begin();
		for (vector<fs::path>::const_iterator itrKey = Key.begin(); itrKey != Key.end(); itrKey++, itrVal++)
		{
			MyMap[itrKey->string() ] = itrVal->string();
		}
	}

	return MyMap;
}

/*******************************************************************
 * Function Name: RunOnManyImages
 * Return Type 	: int
 * Created On	: Feb 4, 2013
 * Created By 	: hrushi
 * Comments		: Run the code on many images
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunOnManyImages(const Args& args)
{
	const std::map<string, string> mapTrkMsk = MakeTracknMaskImageList(args);
	ViperGroundTruth VGT;

	string ScoreFileName = args.GetSearchFolderPath() + "/ScoreFile_" + args.GetDetectMode() + ".txt";
	cout << ScoreFileName << endl;

	DetectionScoreFile DSF(ScoreFileName);

	for( auto TrkMsk : mapTrkMsk )
	{

		const fs::path TrkPath = TrkMsk.first;
		const fs::path MskPath = TrkMsk.second;

		ColorImg Img(TrkPath);

		if( (args.GetSkipWidth() > 0 ) && (Img.GetNumCols() < args.GetSkipWidth() ))
		{
			cout << "Skip " << TrkPath.string() << " Width(" << Img.GetNumCols() << ") < " << args.GetSkipWidth() << endl;
			continue;
		}

		if( (args.GetSkipHeight() > 0 ) && (Img.GetNumRows() < args.GetSkipHeight() ))
		{
			cout << "Skip " << TrkPath.string() << " Width(" << Img.GetNumRows() << ") < " << args.GetSkipHeight() << endl;
			continue;
		}

		cout << "Using the given ground truth" << endl;
		const fs::path TrackFilePath = TrackXML::GetTrackFilePath(TrkPath);

		cout << "Trk: " << TrkMsk.first << endl;
		AllDetectedCtrs CarryDetections = GetCarryRegions(TrkPath, MskPath, args);

		if( CarryDetections.Get_NumvCntrs() >= 0 )
		{

			vector<bool> isGndTruth_True = VGT.isCorrect(CarryDetections, TrkPath, args);
			VGT.Print_ConfusionMat(args);
			cv::waitKey(2 * DISP_ONE_SECOND); // Wait for the user to read the confusion matrix.

			DSF.AddToScoreLine(TrkPath, isGndTruth_True, CarryDetections);
		}

		cout << endl;
	}

	VGT.Print_ConfusionMat(args);
	cv::waitKey(2 * DISP_ONE_SECOND); // Wait for the user to read the confusion matrix.

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: SingleImgDetect
 * Return Type 	: const AllDetectedCtrs
 * Created On	: Dec 27, 2013
 * Created By 	: hrushi
 * Comments		: Performs the detection for a single image
 * Arguments	: const fs::path TrackPath, const fs::path MaskPath, const fs::path PosePath, const Args& args
 *******************************************************************/
const AllDetectedCtrs App::SingleImgDetect( const fs::path TrackPath, const fs::path MaskPath, const fs::path PosePath, const Args& args) const
{
	AllDetectedCtrs CarryDetections;

	if( args.isSkipIfNoPose() )
	{
		cout << "Pose File Path: " << PosePath << endl;
		if( !fs::exists(PosePath ))
		{
			cout << "No Box File Present " << endl;
			return CarryDetections;

		}

	}

	ColorImg TempTrack(TrackPath);
	UINT imgWidth = TempTrack.GetNumCols();
	UINT imgHeight = TempTrack.GetNumRows();

	if( (imgWidth > args.GetSkipWidth()) && (imgHeight > args.GetSkipHeight() )  )
	{
		cout << "Detection Mode " << args.GetDetectMode() << endl;

		AlgoTest MyDetectAlgo( args );
		CarryDetections = MyDetectAlgo.DetectionAlgo( TrackPath, MaskPath, args.GetDetectMode() , args );

		DetectionImg DtcImg;
		DtcImg.Load(TrackPath);
		DtcImg.Overlay(CarryDetections, true, args);
		DtcImg.Display(DISP_DELAY);

		fs::path OutputFilePath = FileSystem::BuildOutputImgPath( TrackPath );
		DtcImg.Write( OutputFilePath );

		cout << "Writing detection output to: " << OutputFilePath << endl;
	}

	return CarryDetections;
}

/*******************************************************************
 * Function Name: GetCarryRegions
 * Return Type 	: const AllDetectCtrs
 * Created On	: Dec 22, 2013
 * Created By 	: hrushi
 * Comments		: Gets the carry regions from the given image
 * Arguments	: const Args& args
 *******************************************************************/
const AllDetectedCtrs App::GetCarryRegions( const fs::path TrackImg, const fs::path MaskImg, const Args& args) const
{
	AlgoTest MyDetectAlgo( args );

	cout << "MaskImgPath: " << MaskImg << endl;
	cout << "Detection Mode " << args.GetDetectMode() << endl;

	AllDetectedCtrs CarryDetections = SingleImgDetect(TrackImg, MaskImg, PoseFile::GetBoxFilePath( TrackImg ), args );

	return CarryDetections;

}

/*******************************************************************
 * Function Name: RunDemo
 * Return Type 	: int
 * Created On	: Dec 5, 2013
 * Created By 	: hrushi
 * Comments		: Runs the application in demo more
 * Arguments	:
 *******************************************************************/
int App::RunDemo( const Args& args ) const
{

	const std::map<string, string> mapMskTrk = MakeTracknMaskImageList(args);

	cout << "Running Demo Now" << endl;

	for( auto MskTrk : mapMskTrk )
	{
		AllDetectedCtrs CarryDetections = GetCarryRegions(fs::path(MskTrk.first), fs::path(MskTrk.second), args);

	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunOnImage
 * Return Type 	: int
 * Created On	: Feb 2, 2013
 * Created By 	: hrushi
 * Comments		: Runs the code on  the images
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunOnImage(const Args& args)
{

	const fs::path InputPath = args.GetInputFilePath();
	const fs::path MaskPath = args.GetMaskFilePath();
	const fs::path PosePath = PoseFile::GetBoxFilePath( InputPath );

	cout << "Input Image Path " << InputPath << endl;
	cout << "Mask Image Path " << MaskPath << endl;

	if (!fs::is_regular_file(InputPath))
	{
		cout << "The given input are not a file " << endl;
		return 0;
	}

	if (!fs::is_regular_file(MaskPath))
	{
		cout << "The given Mask file is not a valid file." << endl;
		cout << "Given Path: " << MaskPath << endl;
		return 0;
	}

	AllDetectedCtrs CarryDetections = SingleImgDetect(InputPath, MaskPath, PosePath, args);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: RunCopyImage
 * Return Type 	: int
 * Created On	: Feb 3, 2013
 * Created By 	: hrushi
 * Comments		: Copies images with the mask name from the source
 * 					folder to the destination folder.
 * Arguments	: const Args& args
 *******************************************************************/
int App::RunCopyImage(const Args& args)
{
	string InputPath = args.GetInputFilePath();
	string MaskPath = args.GetMaskFilePath();

	fs::path InputFile(InputPath);
	fs::path MaskFile(MaskPath);

	return EXIT_SUCCESS;
}

