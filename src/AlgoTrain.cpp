/*
 * AlgoTrain.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#include "AlgoTrain.h"

AlgoTrain::AlgoTrain() {
	// TODO Auto-generated constructor stub

}

AlgoTrain::~AlgoTrain() {
	// TODO Auto-generated destructor stub
}

/*****************************************************
 * Function	: AlgoTrain Copy Constructor
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
AlgoTrain::AlgoTrain(const AlgoTrain& rhsAlgoTrain )
{
	Allocate( rhsAlgoTrain );
	Copy( rhsAlgoTrain );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jun 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
AlgoTrain& AlgoTrain:: operator=( const AlgoTrain& rhsAlgoTrain )
{
	Allocate( rhsAlgoTrain );
	Copy( rhsAlgoTrain );

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
int AlgoTrain::Allocate( const AlgoTrain& rhsAlgoTrain )
{

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
int AlgoTrain::Copy( const AlgoTrain& rhsAlgoTrain )
{

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: TrainApperance
 * Return Type 	: int
 * Created On	: Nov 3, 2013
 * Created By 	: hrushi
 * Comments		: Train the Apperance features
 * Arguments	: 	1. Arg Class
 * 					2. Map of all the proble images and the mask images
 * 					3. Flag to decide if all the chips need to be calculated again
 *******************************************************************/
int AlgoTrain::TrainApperance( const Args& args, const std::map<string, string>& TrkMskMap) const
{
	mp_Str_vStr mpLbl_ChipImgs;

	try
	{
		mpLbl_ChipImgs = LoadChipMap(args);
	}
	catch(int err)
	{
		if(err == ERR_INVALID_PATH )
		{
			mpLbl_ChipImgs = GetImageChips(args, TrkMskMap);
			SaveChipMap(mpLbl_ChipImgs, args);
		}
	}

	BOF oBoF(LEARN_MODE); // Bag of features
	oBoF.SaveDescriptors(mpLbl_ChipImgs, args);
	oBoF.Learn_Vocabulary(mpLbl_ChipImgs,  args);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: LoadChipMap
 * Return Type 	: mp_Str_vStr
 * Created On	: Nov 4, 2013
 * Created By 	: hrushi
 * Comments		: Save the chips
 * Arguments	: const Args& args
 *******************************************************************/
mp_Str_vStr AlgoTrain::LoadChipMap( const Args& args) const
{
	mp_Str_vStr Retmp;

	cv::FileStorage fsLblChips2;
	vector<string> Categories, ImPaths;

	string TrainFldrPath = args.GetTrainFolderPath();

	if( TrainFldrPath.length() == 0)
	{
		TrainFldrPath = args.GetSearchFolderPath();
	}

	const string LblPath = TrainFldrPath + CHIP_FILE_LIST;
	cout << "Reading " << LblPath << endl;

	if(!fs::exists(LblPath))
	{
		cerr << "File Path " << LblPath << " Not found" << endl;
		throw ERR_INVALID_PATH;
	}


	fsLblChips2.open(LblPath, cv::FileStorage::READ);

	fsLblChips2["Categories"] >> Categories;


	for(UINT i = 0;  i < Categories.size(); i++ )
	{
		vector<string> vImgNames;
		fsLblChips2[Categories.at(i)] >> vImgNames;
		Retmp[Categories.at(i)] = vImgNames;
	}

	fsLblChips2.release();

	return Retmp;
}


/*******************************************************************
 * Function Name: SaveChipMap
 * Return Type 	: int
 * Created On	: Nov 3, 2013
 * Created By 	: hrushi
 * Comments		: Save a map of chips
 * Arguments	: const mp_Str_vStr& mp
 *******************************************************************/
int AlgoTrain::SaveChipMap( const mp_Str_vStr& mp, const Args& args) const
{
	cv::FileStorage fsLblChips;

	string TrainFldrPath = args.GetTrainFolderPath();

	if( TrainFldrPath.length() == 0)
	{
		TrainFldrPath = args.GetSearchFolderPath();
	}

	const string LblPath = TrainFldrPath + CHIP_FILE_LIST;
	fsLblChips.open(LblPath, cv::FileStorage::WRITE);

	vector<string> vCat;
	for(mp_Str_vStr::const_iterator itr = mp.begin(); itr != mp.end(); itr++ )
	{
		vCat.push_back(itr->first);
		fsLblChips << itr->first << itr->second;
	}

	fsLblChips << "Categories" << vCat;
	fsLblChips.release();

	return EXIT_SUCCESS;
}





/*******************************************************************
 * Function Name: GetImageChips
 * Return Type 	: int
 * Created On	: Nov 1, 2013
 * Created By 	: hrushi
 * Comments		: Get image chips
 * Arguments	: const Args& args
 *******************************************************************/
mp_Str_vStr AlgoTrain::GetImageChips( const Args& args, const std::map<string, string>& TrkMskMap ) const
{
	static Labels Lbl(args, ALL_LABEL_FILENAME);
	Lbl.Read(args);
	tdef_LabelMap lMap = Lbl.GetLabelMap();

	string TrainFolderPath = args.GetTrainFolderPath();

	if(TrainFolderPath.length() == 0 )
	{
		TrainFolderPath = args.GetSearchFolderPath();
	}

	const string ChipPath = TrainFolderPath + CHIP_FILE_LIST;

	std::map<UINT, string> mpChips = CreateFolders(TrainFolderPath);

	UINT uiPersonChipCnt(0), uiDragCnt(0), uiWornCnt(0);
	vector<string> vPersonImgs, vDragImgs, vWornImgs;

	for (tdef_LabelMap::const_iterator itr = lMap.begin(); itr != lMap.end(); itr++)
	{
		fs::path ImagePath 	= itr->first;
		int MarkLabel		= Lbl.AlreadyPresent(itr->first);
		string CmplImgPath 	  =  Lbl.GetComplateImgFilePath(itr->first);

		//---------- Skip the loop if the image is not present ---------- //
		if(!fs::exists(CmplImgPath))
		{
			continue;
		}

		string sMaskImagePath = "";

		try
		{
			sMaskImagePath = TrkMskMap.at(CmplImgPath);
		}
		catch(const std::out_of_range& oor)
		{
			cerr << "Skip the loop as " << sMaskImagePath << " Not present" << endl;
		}

		ColorImg ProbeImg = ColorImg(CmplImgPath);
		GrayImg MskImg    = GrayImg( sMaskImagePath );

		ContourMap Segments = Detect::GetSegments(ProbeImg, MskImg , false, args);

		//---------- Get type of label. Possible optimization over here. Label files are read again and again ---------- //
		UINT LabelType = Detect::GetType(itr->first, args);

		string FldrPath = mpChips.at(LabelType);

		//Starting from iCntr = 1; Because, iCntr = 0 is Background Contour
		for( int iCntr = 1; iCntr < (int)Segments.AllContourMap.size(); iCntr++ )
		{
			Contour Ctr = Segments.AllContourMap.at(iCntr);
			ColorImg ChipImg = Ctr.GetImgChip(ProbeImg);

			cv::SIFT sift;
			vector<cv::KeyPoint> vkeypoints;
			Mat descriptors;
			Mat WorkImg = ChipImg.GetDataRef().clone();
			sift(WorkImg, Mat(), vkeypoints, descriptors);


			if(0) // Draw keypoints, not used, as it takes a lot of time.
			{
				Mat DispMat;
				cv::drawKeypoints(WorkImg, vkeypoints, DispMat);

				ColorImg DispImg;
				DispImg.SetImage(DispMat);
				DispImg.Display(DISP_DELAY);

				cout << "#Keypoints: " << vkeypoints.size() << endl;

				//---------- Skip the chip if the number of keypoints are less than the number of clusters. ---------- //
				if( vkeypoints.size() < BOW_CLUSERS )
				{
					continue;
				}

			}


			std::stringstream ss;
			if( ( LabelType == DRAG_CARRY_LABEL) && ( Ctr.GetLabel() == (UINT)MarkLabel ))
			{
				FldrPath = mpChips.at(DRAG_CARRY_LABEL);
				ss << FldrPath << "/";
				ss << DRAG << std::setfill('0') << std::setw(4) << uiDragCnt << IMG_EXT_PNG;
				uiDragCnt++;

				fs::path RelativePath = FileSystem::MakeRelative(ChipPath, ss.str());

				vDragImgs.push_back(RelativePath.string());


			}
			else if( ( LabelType == WORN_CARRY_LABEL) && ( Ctr.GetLabel() == (UINT)MarkLabel ) )
			{
				FldrPath = mpChips.at(WORN_CARRY_LABEL);
				ss << FldrPath << "/";
				ss << WORN << std::setfill('0') << std::setw(4) << uiWornCnt << IMG_EXT_PNG;
				uiWornCnt++;

				fs::path RelativePath = FileSystem::MakeRelative(ChipPath, ss.str());

				vWornImgs.push_back(RelativePath.string());

			}
			else
			{
				FldrPath = mpChips.at(PERSON_LABEL);
				ss << FldrPath << "/";
				ss << PERSON << std::setfill('0') << std::setw(4) << uiPersonChipCnt << IMG_EXT_PNG;
				uiPersonChipCnt++;

				fs::path RelativePath = FileSystem::MakeRelative(ChipPath, ss.str());

				vPersonImgs.push_back(RelativePath.string());
			}

			cout << ss.str() << endl;
			ChipImg.Write(ss.str());
		}

	}

	mp_Str_vStr mpLbl_ChipImgs;
	mpLbl_ChipImgs[PERSON] 	= vPersonImgs;
	mpLbl_ChipImgs[WORN]	= vWornImgs;
	mpLbl_ChipImgs[DRAG]	= vDragImgs;

	return mpLbl_ChipImgs;
}


/*******************************************************************
 * Function Name: CreateFolders
 * Return Type 	: int
 * Created On	: Nov 2, 2013
 * Created By 	: hrushi
 * Comments		: Creates 4 folders, one is the ChipFolder, then creates the Drag, Worn and Person folder in it
 * Arguments	: const string TrainFolderPath
 *******************************************************************/
std::map<UINT, string> AlgoTrain::CreateFolders( const string TrainFolderPath) const
{
	std::map<UINT, string> mpChipPath;

	string ChipFldr = TrainFolderPath + CHIP_FLDR;
	FileSystem::CreateFolder(ChipFldr);

	string ChipDragFldr = TrainFolderPath + CHIP_DRAG_FLDR;
	FileSystem::CreateFolder(ChipDragFldr);
	mpChipPath[DRAG_CARRY_LABEL] = ChipDragFldr;

	string ChipWornFldr = TrainFolderPath + CHIP_WORN_FLDR;
	FileSystem::CreateFolder(ChipWornFldr);
	mpChipPath[WORN_CARRY_LABEL] = ChipWornFldr;

	string ChipPersonFldr = TrainFolderPath + CHIP_PERSON_FLDR;
	FileSystem::CreateFolder(ChipPersonFldr);
	mpChipPath[PERSON_LABEL] = ChipPersonFldr;

	return mpChipPath;
}

