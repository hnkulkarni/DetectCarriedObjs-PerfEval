/*
 * Labels.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: hrushi
 */

#include "Labels.h"


/*******************************************************************
 * Function Name: Labels
 * Return Type 	:
 * Created On	: Jul 1, 2013
 * Created By 	: hrushi
 * Comments		: Default Constructor; This is an empty constructor, used for using the Lables as a member variable.
 * Arguments	:
 *******************************************************************/
Labels::Labels( )
{

	bWBanner = false;
}



/*******************************************************************
 * Function Name: Label
 * Return Type 	:
 * Created On	: May 15, 2013
 * Created By 	: hrushi
 * Comments		: Constructor for a new Label file in Write mode
 * Arguments	: const Args& args, const string sPath
 *******************************************************************/
Labels::Labels( const Args& args, const fs::path sPath)
{
	Init(args, sPath);
}


/*******************************************************************
 * Function Name: Labels
 * Return Type 	:
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Overloaded constructor
 * Arguments	: const fs::path SearchFolderPath, const fs::path sPath
 *******************************************************************/
Labels::Labels( const fs::path SearchFolderPath, const fs::path sPath)
{
	Init(SearchFolderPath, sPath );
	Read(Args());
}
/*******************************************************************
 * Function Name: Init
 * Return Type 	: int
 * Created On	: Jul 1, 2013
 * Created By 	: hrushi
 * Comments		: Performs all the default initlaization
 * Arguments	: const Args& args, const fs::path sPath
 *******************************************************************/
int Labels::Init( const Args& args, const fs::path sPath )
{
	return Init(args.GetSearchFolderPath(), sPath );
}


/*******************************************************************
 * Function Name: Init
 * Return Type 	: int
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		:  Performs all the default initlaization with the given search path
 * Arguments	: const fs::path SearchFolderPath, const fs::path sPath
 *******************************************************************/
int Labels::Init( const fs::path SearchFolderPath, const fs::path sPath)
{
	LPath = SearchFolderPath.string() + sPath.string();
	bWBanner = false;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: OpenFile
 * Return Type 	: int
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Opens the Label File, and puts the pointer to the start
 * Arguments	: const Args& args
 *******************************************************************/
int Labels::OpenFile( const Args& args)
{
	if( !fPtr.is_open() ) // Check if the file is already opened.
	{
		if( fs::exists(LPath) )
		{
			cerr << "Label File Already Exists. Overwriting " << endl;
			bWBanner = false; // Do not print banner, as it is already present
		}
		else
		{
			bWBanner = true; // Print the banner, because the file is not present.
		}

		fPtr.open(LPath.string().c_str());

		if( !fPtr.is_open() )
		{
			cout << "Cannot Open File " << LPath.string() << endl;
			exit(ERR_CANNOT_OPEN_FILE);
		}
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Labels
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Destructor
 * Args			:
 **********************************************************************/
Labels::~Labels()
{
	CloseFile();
}



/*******************************************************************
 * Function Name: CloseFile
 * Return Type 	: int
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Closes the Label File
 * Arguments	:
 *******************************************************************/
int Labels::CloseFile( )
{

	if( fPtr.is_open() )
	{
		fPtr.close();
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Labels
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 **********************************************************************/
Labels::Labels( const Labels& rhsLabels )
{
	Allocate_Labels( rhsLabels );
	Copy_Labels( rhsLabels );
}

/**********************************************************************
 * Function Name: operator
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 **********************************************************************/
Labels& Labels :: operator=( const Labels & rhsLabels )
{
	Allocate_Labels( rhsLabels );
	Copy_Labels( rhsLabels );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Labels
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 **********************************************************************/
int Labels:: Copy_Labels(  const Labels & rhsLabels  )
{
	LPath 		= rhsLabels.LPath;
	LabelMap 	= rhsLabels.LabelMap;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Allocate_Labels
 * Date 		: Feb 10, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 **********************************************************************/
int Labels:: Allocate_Labels(  const Labels & rhsLabels  )
{

	return EXIT_SUCCESS;
}

/****************************************************************************************************************************
 * Function Name: Add
 * Return Type 	: int
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Collects response and adds label for the given file
 * Arguments	: const fs::path& ImPath 		- Contains the path to the Image relative to the position of the Label File
 * 				  const ColorImg& Overlay 		- Displays the overlayed image for the user to Label
 * 				  const Args& args				- Reference to the list of arguments.
 * 				  const ContourMap& AllSegments - Used for checking if the entered label is present or not
 ****************************************************************************************************************************/
int Labels::Add(const fs::path& ImPath, const ColorImg& Overlay, const Args& args, const ContourMap& AllSegments)
{

	std::map<string, int>::iterator itr = LabelMap.find( ImPath.string() ); // Check if the Label Exist
	fs::path ProgramPath = args.GetProgramPath();

	FileSystem oFS;
	fs::path RelativeImPath = oFS.MakeRelative(LPath, ImPath.string() );

	int CurrentLabel  = NO_CARRIED_OBJECT;

	if( itr == LabelMap.end() ) // If Label not present
	{
		CurrentLabel =  AlreadyPresent(RelativeImPath , true);
		bool b2 = args.isSkipExisting();

		if( ( CurrentLabel != UN_INITIALIZED_LABEL ) && b2 )
		{
			cout << "Skip: " << ImPath.string() << endl;
		}
		else
		{
			if( isNeg(RelativeImPath ) )
			{
				CurrentLabel = NO_CARRIED_OBJECT;
				AddToMap(RelativeImPath, CurrentLabel);

			}
			else
			{
				if( args.LabelNow() ) // Label Later On
				{
					bool validInput = false;

					while( !validInput )
					{
						try
						{
							string KeyPress = Overlay.Display(0);
							cout << "KeyPress: " << KeyPress << endl;
							if( KeyPress.compare(" ") == 0 )
							{
								CurrentLabel = NO_CARRIED_OBJECT;
								AddToMap(RelativeImPath, CurrentLabel);
								validInput = true;
							}
							else
							{
								CurrentLabel = GetValueInType<int>(KeyPress);
							}

						}
						catch(int Err)
						{
							if( Err == ERR_TYPE_MISMATCH )
							{
								validInput = false;
								cerr << "Invalid entry, please try again " << endl;
							}
						}

						if( CurrentLabel < (int)AllSegments.GetNumContours() )
						{
							validInput = true;
						}
						else
						{
							cerr << "Invalid Entry, please try again " << endl;
						}
					}
				}
				else
				{
					CurrentLabel = LABEL_LATER;
				}

				if( CurrentLabel == NO_CARRIED_OBJECT )
				{

					AddToMap(RelativeImPath, NO_CARRIED_OBJECT);
				}
				else
				{
					AddToMap(RelativeImPath, CurrentLabel);
					cout << "Added Label " << CurrentLabel << "To the Map" << endl;
				}

			}
		}

		Write(args);
	}

	return CurrentLabel;
}



/*******************************************************************
 * Function Name: Add
 * Return Type 	: int
 * Created On	: Mar 6, 2014
 * Created By 	: hrushi
 * Comments		: Adds the label by reading the GroundTruth Data
 * Arguments	: const fs::path& ImPath, const TrackXML& oTrackXML, const GroundTruth& oGndTruth, const ColorImg& Overlay, const Args& args, const ContourMap& AllSegments
 *******************************************************************/
int Labels::Add( const fs::path& ImPath, const TrackXML& oTrackXML, const ViperXML& oViperXML, const ColorImg& Overlay, const Args& args, const ContourMap& AllSegments)
{

	cout << "Adding labels for the given image " << ImPath << endl;

	UINT FrameNum, TrackNum;
	string VideoStemName;
	int CurrentLabel  = NO_CARRIED_OBJECT;

	TrackXML::GetTrkChipNameParts(ImPath.stem().string(), TrackNum, FrameNum, VideoStemName);

	const vector<cv::Rect> GndTruthBdnBx = oViperXML.GetGndTruthBdnBox(FrameNum);
	const cv::Rect TrackBdnBx = oTrackXML.GetBoundingBox(TrackNum, FrameNum);

	fs::path RelativeImPath = FileSystem::MakeRelative(LPath, ImPath.string() );

	if(GndTruthBdnBx.size() == 0 )
	{
		cout << ".";
		std::flush(cout);

		AddToMap(RelativeImPath, CurrentLabel);
		Write(args);

	}
	else
	{
		fs::path FullImgPath = oTrackXML.GetFullImagePath(FrameNum);
		cout << "Adding Labels using the Given Ground Truth " << endl;
		cout << "Viper GndTruth: " 	<< oViperXML.GetGndTruthBdnBox(FrameNum) 		<< endl;
		cout << "Track BdnBox: " 	<< oTrackXML.GetBoundingBox(TrackNum, FrameNum) << endl;


		ColorImg FullImg(FullImgPath);
		FullImg.Overlay(TrackBdnBx, COLOR_BLUE);
		FullImg.Overlay(GndTruthBdnBx, COLOR_GREEN);
		FullImg.Display(ONE_SECOND);

		const vector<cv::Rect> OverlapRects = RectOp::GetOverlappingRect(TrackBdnBx, GndTruthBdnBx, 0.7);
		const vector<cv::Rect> RelativeRects = RectOp::MakeRelativeToBigRect(TrackBdnBx, OverlapRects);
		cout << RelativeRects << endl;

		BinaryImg GndMsk = RectOp::MakeMasks(TrackBdnBx.size(), RelativeRects);
		//GndMsk.Display(ONE_SECOND);

		CurrentLabel = GetOptimalRgn(AllSegments, GndMsk);

		if(CurrentLabel != UN_INITIALIZED_LABEL )
		{
			AddToMap(RelativeImPath, CurrentLabel);
			Write(args);
		}

	}

	return CurrentLabel;
}


/*******************************************************************
 * Function Name: GetOptimalRgn
 * Return Type 	: int
 * Created On	: Mar 10, 2014
 * Created By 	: hrushi
 * Comments		: Get an optimal region for which has a maximum overlap over the given mask
 * Arguments	: const GrayImg& GndMask
 *******************************************************************/
int Labels::GetOptimalRgn( const ContourMap& AllSegments, const BinaryImg& GndMsk) const
{
	std::map<double, UINT> OverlapLabel;

	for(auto Rgn : AllSegments.AllContourMap)
	{
		if(Rgn.first != BACKGROUND_LABEL )
		{
			BinaryImg RgnMask(Rgn.second.GetCtrMaskImg());
			double Overlap =  RgnMask.Percentage_Overlap(GndMsk);

			if(!isnan(Overlap))
			{
				OverlapLabel[Overlap] = Rgn.first;
			}
		}
	}


	MapOp<std::map<double, UINT>>::Print(OverlapLabel);

	int RgnNum(NO_CARRIED_OBJECT);

	if(OverlapLabel.size())
	{
		if(OverlapLabel.rbegin()->first > 0 ) //Overlap score is more than 0
		{
			RgnNum = OverlapLabel.rbegin()->second;
		}
	}


	return RgnNum;
}


/*******************************************************************
 * Function Name: Read
 * Return Type 	: int
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Reads the Label file, into the member variable map
 * Arguments	: const Args& args
 *******************************************************************/
int Labels::Read(const Args& args)
{
	string line;
	StringOp<string> oStr;

	std::ifstream TempReadPtr;

	cout << LPath.string().c_str() << endl;
	TempReadPtr.open(LPath.string().c_str() );


	try{

		if( !TempReadPtr.is_open() )
		{
			cout << "Cannot Open File " << LPath.string() << endl;
			throw ERR_CANNOT_OPEN_FILE;
		}
	}
	catch(int err)
	{
		if( err == ERR_CANNOT_OPEN_FILE )
		{
			if(args.isSkipExisting())
			{
				cerr << "For SkipExisting Flag " << LPath << "should be found" << endl;
				throw ERR_CANNOT_OPEN_FILE;
			}
			else
			{
				//---------- Do Nothing ---------- //
			}
		}
	}


	string ImgName;
	int Label;
	if( TempReadPtr.is_open() )
	{
		while( TempReadPtr.good() )
		{
			getline(TempReadPtr, line);

			string NonWhiteSpace;
			NonWhiteSpace = oStr.GetNonWhiteSpace(0, line);

			if(NonWhiteSpace.size() > 0 )
			{
				char FirstChar = NonWhiteSpace.at(0);
				if( FirstChar == '#' )
				{
					//cout << line << endl;
				}
				else
				{
					ImgName = oStr.GetNonWhiteSpace(IMAGE_LOC, line);

					NonWhiteSpace = oStr.GetNonWhiteSpace(LABEL_LOC, line );
					Label = GetValueInType<int>(NonWhiteSpace);

					AddToMap(ImgName, Label);

				}
			}
		}
	}

	TempReadPtr.close();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: LabelAlreadyPresent
 * Return Type 	: bool
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given file is already Present
 * Arguments	: const string FilePath
 *******************************************************************/
int Labels::AlreadyPresent( const fs::path FilePath) const
{
	int L = UN_INITIALIZED_LABEL;

	try
	{
		L = LabelMap.at(FilePath.string() );
	}
	catch(const std::out_of_range& oor)
	{
		L = UN_INITIALIZED_LABEL;
	}

	return L;
}


/*******************************************************************
 * Function Name: AlreadyPresent
 * Return Type 	: int
 * Created On	: Mar 2, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the path is already present in the given map.
 * Arguments	: const fs::path Path, const bool isPathRelativeToLabel
 *******************************************************************/
int Labels::AlreadyPresent( const fs::path ImPath, const bool isPathRelativeToLabel ) const
{
	fs::path RelativeImPath;

	if( !isPathRelativeToLabel )
	{
		RelativeImPath = FileSystem::MakeRelative(LPath, ImPath.string() );
	}
	else
	{
		RelativeImPath = ImPath;
	}

	// Parent path will give the Data Folder path
	// its Parent path will give the data folder path

	fs::path Containing_Fldr_path = LPath.parent_path();
	fs::path CompletePath = Containing_Fldr_path.parent_path().string() + RelativeImPath.string() ;
	if(! fs::exists( CompletePath ) )
	{
		cerr << "File " << RelativeImPath  << "Does not exist at the given location " << endl;
		throw ERR_INVALID_PATH;
	}

	return AlreadyPresent(RelativeImPath.string());

}


/*******************************************************************
 * Function Name: GetImageLabel
 * Return Type 	: int
 * Created On	: Jul 4, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Label of the image; If the image is not found, then it returns an UN_INITIALIZED_LABEL
 * Arguments	: const fs::path Path, const bool isPathRelative
 *******************************************************************/
int Labels::GetImageLabel( const fs::path Path, const bool isPathRelative ) const
{

	/*
	 * Since this functionality is done by an existing function, it has been called over here.
	 * AlreadyPresent is a function that does this same work. Hence calling it over here.
	 */

	return AlreadyPresent(Path, isPathRelative);
}

/*******************************************************************
 * Function Name: AddToMap
 * Return Type 	: int
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Adds the string and the lable number to the Map
 * Arguments	: const string& Name, const int Label
 *******************************************************************/
int Labels::AddToMap( const string Name, const int Label)
{
	LabelMap[Name] = Label;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: AddToMap
 * Return Type 	: int
 * Created On	: Feb 24, 2013
 * Created By 	: hrushi
 * Comments		: Adds the path to the map
 * Arguments	: const fs::path& ImPath, const int Label
 *******************************************************************/
int Labels::AddToMap( const fs::path& ImPath, const int Label)
{
	AddToMap(ImPath.string(), Label);

	return EXIT_SUCCESS;
}
/*******************************************************************
 * Function Name: Write
 * Return Type 	: int
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Writes All the Labels into the folder
 * Arguments	:
 *******************************************************************/
int Labels::Write( const Args& args )
{
	OpenFile(args);

	/*
	 * File Pointer has been set to zero, because, when the file is
	 * read for labels, the entire table is printed again, causing
	 * the same file entry to show up multiple times
	 */
	fPtr.clear();
	fPtr.seekp(0, std::ios::beg);

	WriteBanner();

	WriteLabels();

	CloseFile();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteLabels
 * Return Type 	: int
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Writes all the labels, with comma seperated values
 * Arguments	:
 *******************************************************************/
int Labels::WriteLabels( )
{
	for( std::map<string, int>::const_iterator itr = LabelMap.begin(); itr != LabelMap.end(); itr++ )
	{
		fPtr << itr->first << " , " << itr->second << endl;
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Writes the File Banner
 * Arguments	:
 *******************************************************************/
int Labels::WriteBanner( )
{
	// Set the pointer to the starting of the file
	fPtr.seekp(0, std::ios::beg);

	Time T;
	fPtr << "# " << STARS << STARS << endl;
	fPtr << "# Label File " << endl;
	fPtr << "# Description: Contains list of images and contour number containing carried object" << endl;
	fPtr << "# \t     If contour number = -1, then that image has no carried object " << endl;
	fPtr << "# Contains " << GetNumLabels() << " Labels" << endl;
	fPtr << "# Last Updated On : " << T.GetCurrentTime() << endl;
	fPtr << "# Label " << NO_CARRIED_OBJECT << " " << ": No carried object on this image " << endl;
	fPtr << "# Label " << LABEL_LATER       << " " << ": This image has been marked to label later. The Merged contour image is in /Seg Folder " << endl;
	fPtr << "# " << STARS << STARS << endl;
	return EXIT_SUCCESS;

}

/*******************************************************************
 * Function Name: isNeg
 * Return Type 	: bool
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the image is in the Neg Folder of the DataSet
 * Arguments	: const fs::path& ImPath
 *******************************************************************/
size_t Labels::isNeg( const fs::path& ImPath ) const
{
	FileSystem oFS;
	return oFS.Find(ImPath, "NEG" );
}



/*******************************************************************
 * Function Name: MarkBackLogLabels
 * Return Type 	: int
 * Created On	: Apr 2, 2013
 * Created By 	: hrushi
 * Comments		: Updates the labels marked for labelling at a later date
 * Arguments	: const Args& args
 *******************************************************************/
int Labels::MarkBackLogLabels( const Args& args)
{
	int CurrentLabel  = NO_CARRIED_OBJECT;

	for( tdef_LabelMap::const_iterator itr = LabelMap.begin();  itr != LabelMap.end(); itr++ )
	{
		if( itr->second == LABEL_LATER )
		{

			fs::path ImagePath = itr->first;
			fs::path MergeFilePath = GetMergeImagePath( LPath, ImagePath );

			if( fs::exists(MergeFilePath) )
			{
				cout << "Merge File Path " << MergeFilePath << endl;
				ColorImg LMergeImg;
				LMergeImg.Load(MergeFilePath.string() );

				string KeyPress = LMergeImg.Display(0);
				CurrentLabel = GetValueInType<int>(KeyPress);

				AddToMap(itr->first, CurrentLabel);

				Write(args);

			}
			else
			{
				cerr << "Merged Contour File Does not exist " << endl;
				throw ERR_CANNOT_OPEN_FILE;
			}

		}
		else
		{
			//cout << itr->first << " Already Labelled " << itr->second << endl;
			cout << ".";
			std::flush(cout);
		}
	}

	Write(args);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetMergeImagePath
 * Return Type 	: string
 * Created On	: Apr 2, 2013
 * Created By 	: hrushi
 * Comments		: Uses the label file path, and the image path to get the segmentation path
 * Arguments	: const string RelativeLabelPath, const string ImagePath
 *******************************************************************/
const fs::path Labels::GetMergeImagePath( const fs::path RelativeLabelPath, const fs::path ImagePath) const
{
	string SegFolderPath = RelativeLabelPath.parent_path().string() + ImagePath.parent_path().string() + "/Seg/";
	string MergeImagePath = SegFolderPath + ImagePath.stem().string() + "_Merge" + ImagePath.extension().string();

	fs::path MergePath = MergeImagePath;

	return MergePath;
}



/*******************************************************************
 * Function Name: GetComplateImgFilePath
 * Return Type 	: const string
 * Created On	: May 19, 2013
 * Created By 	: hrushi
 * Comments		: Returns the complete path to the relative path of the image, i.e the first column
 * Arguments	: const string sPath
 *******************************************************************/
const string Labels::GetComplateImgFilePath( const string sPath) const
{
	string RetComplPath;

	fs::path ContainingFldrPath = LPath.parent_path();

	RetComplPath = ContainingFldrPath.parent_path().string() + sPath;

	return RetComplPath;
}


/*******************************************************************
 * Function Name: GetSegImgPath
 * Return Type 	: const string
 * Created On	: May 19, 2013
 * Created By 	: hrushi
 * Comments		: Returns the segmented image path for the given relative label image path
 * Arguments	: const string sPath
 *******************************************************************/
const string Labels::GetSegImgPath( const string sPath) const
{
	string RetSegImgPath;

	fs::path pPath = GetComplateImgFilePath( sPath );

	RetSegImgPath = pPath.parent_path().string() + "/Seg/" + pPath.stem().string() + "_Merge" + pPath.extension().string();

	return RetSegImgPath;
}




