/*
 * FileSystem.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: hrushi
 */

#include "FileSystem.h"

FileSystem::FileSystem()
{
	// TODO Auto-generated constructor stub

}

FileSystem::~FileSystem()
{
	// TODO Auto-generated destructor stub
}


/*******************************************************************
 * Function Name: ListAllImagesToWork
 * Return Type 	: vector<fs::path>
 * Created On	: Jun 15, 2013
 * Created By 	: hrushi
 * Comments		: List all the images in the folder under the TrackFolder Name.
 * Arguments	: 	1. FolderPath to Search,
 * 					2. Name of the Track folder, typically track.
 *******************************************************************/
vector<fs::path> FileSystem::ListAllTrackImages( const fs::path FolderPath, const string TrackFldrName )
{
	vector<fs::path> ImgList;
	string CurrentDir;

	cout << "Listing files in the folder" << endl;
	cout << "This may take some time, depending on the number of images in the folder" << endl;

	const fs::path ArcPath = FolderPath.string() + ARCHIVE_PATH;

	if(fs::exists(ArcPath))
	{
		ReadLists<fs::path> RL(ArcPath);
		ImgList = RL.GetList();

		cout << "Reading List with " << ImgList.size() << " entries" << endl;
	}
	else
	{

		for (fs::recursive_directory_iterator end, dir(FolderPath); dir != end; ++dir)
		{
			fs::path p = *dir;

			CurrentDir = p.parent_path().filename().string();
			size_t foundLoc  = CurrentDir.find(TrackFldrName);
			string ext = p.extension().string();

			// Given file is an image and is in the track folder.
			if( isImageExt(ext) &&  (foundLoc < CurrentDir.length()) )
			{
				ImgList.push_back(p);
			}

		}

		VectorOp<fs::path>::Archive(ImgList, ArcPath);
	}

	return ImgList;
}

/*******************************************************************
 * Function Name: isImageExt
 * Return Type 	: bool
 * Created On	: Jun 15, 2013
 * Created By 	: hrushi
 * Comments		: Is Image Extension
 * Arguments	: const string sExt
 *******************************************************************/
bool FileSystem::isImageExt( const string TestExt)
{
	vector<string> ValidExts = { ".png", ".jpeg", ".jpg" };

	for(auto Ext : ValidExts)
	{
		if( TestExt.compare( Ext ) == 0)
		{
			return true;
		}
	}

	return false;
}

/*******************************************************************
 * Function Name: GetMaskImgPath
 * Return Type 	: const vector<fs::path>
 * Created On	: Jun 16, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the MaskImage File Name for every track file name in the vector
 * Arguments	: const string MaskFolderName, 	const fs::path& TrackPath, const string TrackFolderName
 *******************************************************************/
const vector<fs::path> FileSystem::GetMaskImgPathVector( const string MaskFolderName, 	const vector<fs::path>& vTrackPath, const string TrackFolderName)
{
	vector<fs::path> vMaskPath;
	fs::path MaskPath;

	for(auto Path : vTrackPath )
	{
		MaskPath = GetMaskImgPath( MaskFolderName, Path, TrackFolderName );
		vMaskPath.push_back( MaskPath );
	}

	return vMaskPath;
}



/*******************************************************************
 * Function Name: GetMaskImgPath
 * Return Type 	: fs::path
 * Created On	: Jun 16, 2013
 * Created By 	: hrushi
 * Comments		: For the given path in the Track folder, it returns the corresponding mask path
 * Arguments	: const string MaskFolderName, 	const fs::path& CurrentPath, const string TrackFolderName
 *******************************************************************/
const fs::path FileSystem::GetMaskImgPath( const string MaskFolderName, const fs::path TrackPath, const string TrackFolderName)
{
	fs::path MaskPath;

	string Path = TrackPath.parent_path().string();

	const size_t FoundLoc = Find(TrackPath, TrackFolderName);

	string sMaskImgPath;

	sMaskImgPath.assign(Path, 0, FoundLoc);
	sMaskImgPath = sMaskImgPath + MaskFolderName + "/mask_" + TrackPath.filename().string();

	MaskPath = sMaskImgPath;

	if( fs::exists( MaskPath ))
	{
		return MaskPath;
	}
	else
	{
		cerr << "Corresponding Mask Image not present at the given location " << endl;
		cerr << "Track Image Path: " << TrackPath << endl;
		cerr << "Mask  Image Path: " << MaskPath <<  endl;
		throw ERR_INVALID_PATH;
	}

	return MaskPath;
}


/*******************************************************************
 * Function Name: ListAllImagesInFolder
 * Return Type 	: int
 * Created On	: Feb 13, 2013
 * Created By 	: hrushi
 * Comments		: Lists all images and folders inside the given folder.
 * Arguments	: const string FolderPath
 *******************************************************************/
vector<fs::path> FileSystem::ListAllImagesInFolder( const string FolderPath)
{
	vector<fs::path> LS;

	if( FolderPath.length() == 0 )
	{
		cerr << "Given folder is empty" << endl;
		throw ERR_INVALID_ARGS;
	}

	const fs::path ArcPath = FolderPath + ARCHIVE_PATH;

	if(fs::exists(ArcPath))
	{
		ReadLists<fs::path> RL(ArcPath);
		vector<fs::path> LSRelative = RL.GetList();

		LS = FileSystem::GetCompletePath(ArcPath, LSRelative);
		std::sort(LS.begin(), LS.end());
	}
	else
	{

		std::copy(fs::recursive_directory_iterator(FolderPath), fs::recursive_directory_iterator(), std::back_inserter(LS));
		std::sort(LS.begin(), LS.end());

		vector<fs::path> RelativeLS = MakeRelative(ArcPath, LS);
		VectorOp<fs::path>::Archive(RelativeLS, ArcPath);
	}

	return LS;
}

/*******************************************************************
 * Function Name: GetCompletePath
 * Return Type 	: const fs::path
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: Get the complete path from the relative path
 * Arguments	: const fs::path& From, const fs::path& RelativeTo
 *******************************************************************/
const fs::path FileSystem::GetCompletePath( const fs::path& From, const fs::path& RelativeTo)
{
	fs::path iFrom;

	if( fs::is_directory(From))
	{
		iFrom = From;
	}
	else
	{
		iFrom = From.parent_path();
	}

	const fs::path retPath = iFrom.string() + RelativeTo.string();
	return retPath;
}


/*******************************************************************
 * Function Name: GetCompletePath
 * Return Type 	: const vector<string>
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: Get the complete path for each element in the vector
 * Arguments	: const string& From, const vector<string>& vRelativeTo
 *******************************************************************/
const vector<string> FileSystem::GetCompletePath( const string& From, const vector<string>& vRelativeTo)
{
	vector<fs::path> vfsRelative = vStr2vFs(vRelativeTo);
	vector<fs::path> fsComplete	= GetCompletePath(From, vfsRelative);

	vector<string> CplPath = vFs2vStr(fsComplete);

	return CplPath;
}


/*******************************************************************
 * Function Name: GetCompletePath
 * Return Type 	: const vector<fs::path>
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: Get a complete list of paths
 * Arguments	: const fs::path& From, const vector<fs::path>& vRelativeTo
 *******************************************************************/
const vector<fs::path> FileSystem::GetCompletePath( const fs::path& From, const vector<fs::path>& vRelativeTo )
{
	vector<fs::path> CompletePath;

	fs::path FromLoc;

	if(fs::is_directory(From) )
	{
		FromLoc = From;
	}
	else
	{
		FromLoc = From.parent_path();
	}

	for(auto f: vRelativeTo)
	{
		fs::path Cf = GetCompletePath(FromLoc, f);
		CompletePath.push_back(Cf);
	}

	return CompletePath;
}



/*******************************************************************
 * Function Name: NameFilter_hasFolder
 * Return Type 	: size_t
 * Created On	: Feb 16, 2013
 * Created By 	: hrushi
 * Comments		: If the file has any given folder has parent in its path
 * Arguments	: fs::path& ImPath, const string FolderName
 *******************************************************************/
size_t FileSystem::Find( const fs::path& CompletePath, const string FolderName)
{
	size_t foundLoc;

	string FileName = CompletePath.filename().string();
	if( FileName.length() ) // Any valid Length
	{
		StringOp<string> oStr;
		string FILENAME = oStr.GetUpper(FileName);
		string CMPR_FOLDER_NAME = oStr.GetUpper( FolderName );

		string FILEPATH = oStr.GetUpper(CompletePath.string());
		foundLoc = FILEPATH.find(CMPR_FOLDER_NAME );


		if ( FILENAME == CMPR_FOLDER_NAME )
		{
			if( foundLoc < FILEPATH.length() )
			{
				return foundLoc;
			}
		}
		else
		{
			foundLoc = Find(CompletePath.parent_path(), FolderName);
		}

	}
	else
	{
		return 0;
	}

	return foundLoc;

}


/*******************************************************************
 * Function Name: NameFilter_hasFolder
 * Return Type 	: vector<string>
 * Created On	: Feb 16, 2013
 * Created By 	: hrushi
 * Comments		: Filters the list of all the files, returning only those which have the given folder as their directory parent
 * Arguments	: const vector<string>& FileList, const string FolderName
 *******************************************************************/
vector<fs::path> FileSystem::NameFilter_folderPresent( const vector<fs::path>& FileList, const string FolderName, const bool has ) const
{
	vector<fs::path> FilterList;

	for(vector<fs::path>::const_iterator it = FileList.begin(); it != FileList.end(); it++ )
	{
		// Has folder, and the search request is also the same.
		if( Find(*it, FolderName ) && ( has == true ) )
		{
			FilterList.push_back(*it);
		}

		// Does not have the folder and the search request also does not want it
		if( !Find(*it, FolderName ) && ( has == false )  )
		{
			FilterList.push_back(*it);
		}
	}

	return FilterList;
}


/*******************************************************************
 * Function Name: NameFilter_parentName
 * Return Type 	: vector<string>
 * Created On	: Feb 16, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the given file path has the passed parent name
 * Arguments	: const vector<string>& FileList, const string FolderName
 *******************************************************************/
vector<fs::path> FileSystem::NameFilter_parentName( const vector<fs::path>& FileList, const string FolderName,  const bool has) const
{
	vector<fs::path> FilterList;

	for( vector<fs::path>::const_iterator it = FileList.begin(); it != FileList.end(); it++)
	{
		fs::path Path = *it;

		if( !fs::is_directory(Path) ) // If the given path is not a directory
		{
			fs::path ParentPath = Path.parent_path();
			string ParentName = ParentPath.filename().string();
			string PARENTNAME = StringOp<string>::GetUpper( ParentName );
			string FOLDERNAME = StringOp<string>::GetUpper( FolderName );

			if( PARENTNAME == FOLDERNAME )
			{
				if( has == true )
				{
					FilterList.push_back( *it );
				}
			}
			else
			{
				if( has == false )
				{
					FilterList.push_back( *it );
				}
			}
		}
	}

	return FilterList;
}

/*******************************************************************
 * Function Name: MakeRelative
 * Return Type 	: vector<fs::path>
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: Make the entire list of paths relative
 * Arguments	: const fs::path& From, const vector<fs::path>& vTo
 *******************************************************************/
const vector<fs::path> FileSystem::MakeRelative( const fs::path& From, const vector<fs::path>& vTo)
{
	vector<fs::path> vRTo;
	for(auto f : vTo)
	{
		fs::path Relative = MakeRelative(From, f);
		vRTo.push_back(Relative);
	}

	return vRTo;
}

/*******************************************************************
 * Function Name: MakeRelative
 * Return Type 	: const vector<string>
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: Make the file paths relative
 * Arguments	: const string& From, const vector<string>& vStrTo
 *******************************************************************/
const vector<string> FileSystem::MakeRelative( const string& From, const vector<string>& vStrTo)
{
	vector<string> vRTo;

	for(auto f: vStrTo)
	{
		fs::path relative = MakeRelative(From, f);
		vRTo.push_back(relative.string());
	}

	return vRTo;
}


/*******************************************************************
 * Function Name: MakeRelative
 * Return Type 	: fs::path
 * Created On	: Feb 23, 2013
 * Created By 	: hrushi
 * Comments		: Returns a relative path 'From' 'To'
 * Arguments	: const fs::path& From, const fs::path &To
 * TODO			: Make this function generalized
 *******************************************************************/
fs::path FileSystem::MakeRelative( const fs::path& From, const fs::path &To)
{
	fs::path RelativePath;
	string sFromParentPath 	= From.parent_path().string();
	string sToPath		 	= To.string();

	while(sFromParentPath.length() > 0 )
	{
		size_t findLoc = sToPath.find(sFromParentPath);

		if( findLoc < sToPath.size() )
		{
			string sRelative;
			sRelative.assign(sToPath,findLoc + sFromParentPath.size(), sToPath.size() );
			RelativePath = sRelative;
			break;
		}
		else
		{

			fs::path TempFromPath = sFromParentPath;
			TempFromPath = TempFromPath.parent_path();
			sFromParentPath = TempFromPath.string();

		}
	}

	if( sFromParentPath.length() == 0 )
	{
		cout << "Relative Path not found " << endl;
	}

	return RelativePath;
}


/*******************************************************************
 * Function Name: MakeRelative
 * Return Type 	: fs::path
 * Created On	: Feb 23, 2013
 * Created By 	: hrushi
 * Comments		: Makes the relative path, given two strings.
 * Arguments	: const string From, const string To
 *******************************************************************/
fs::path FileSystem::MakeRelative( const string FromPath, const string ToPath)
{
	fs::path RelativePath;
	fs::path From 	= FromPath;
	fs::path To		= ToPath;

	RelativePath = MakeRelative(From, To);

	return RelativePath;
}

/*******************************************************************
 * Function Name: GetOutputFolderPath
 * Return Type 	: const fs::path
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Get the Output Folder Path from the Image Path
 * Arguments	: const fs::path TrackImgPath
 *******************************************************************/
const fs::path FileSystem::GetOutputFolderPath( const fs::path TrackImgPath )
{
	const fs::path fsOutputFolderPath = TrackImgPath.parent_path();
	return fsOutputFolderPath;
}


/*******************************************************************
 * Function Name: GetOutputImagePath
 * Return Type 	: const fs::path
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Get Output Image path from the Track Image path;
 * 					Creates the folder if not already present.
 * Arguments	: const fs::path TrackImgPath
 *******************************************************************/
const fs::path FileSystem::BuildOutputImgPath( const fs::path TrackImgPath)
{
	string DetFolderName = "/Detection/";
	string ImgName 		 = TrackImgPath.filename().string();
	string FolderPath = GetOutputFolderPath(TrackImgPath).string() + DetFolderName;

	fs::path fsOutputImgPath;
	try
	{
		CreateFolder(FolderPath);
		fsOutputImgPath = FolderPath + ImgName;
		return fsOutputImgPath;
	}
	catch(int Err )
	{
		throw Err;
	}

	return fsOutputImgPath;
}


/*******************************************************************
 * Function Name: CreateFolderPath
 * Return Type 	: const fs::path
 * Created On	: Jul 8, 2013
 * Created By 	: hrushi
 * Comments		: Creates the folder at the given path
 * Arguments	: fs::path FolderPath
 *******************************************************************/
int FileSystem::CreateFolder( fs::path FolderPath)
{

	if( !fs::exists(FolderPath) )
	{
		cout << "Creating the Folder Path " << FolderPath << endl;

		try
		{
			fs::create_directories(FolderPath);
		}
		catch(...)
		{
			cerr << "Cannot Create Directory at Location : " << endl;
			cerr << FolderPath << endl;
			throw ERR_INVALID_PATH;
		}
	}


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Fs2Str
 * Return Type 	: vector<string>
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: Convert a string into boost filesystem
 * Arguments	: const vector<fs::path>& vFs
 *******************************************************************/
const vector<string> FileSystem::vFs2vStr( const vector<fs::path>& vFs)
{
	vector<string> vStr(vFs.size());

	std::transform(vFs.begin(), vFs.end(), vStr.begin(), Fs2Str);

	return vStr;
}

/*******************************************************************
 * Function Name: vStr2vFs
 * Return Type 	: const vector<fs::path>
 * Created On	: Mar 14, 2014
 * Created By 	: hrushi
 * Comments		: convert a vector of strings into fs::path
 * Arguments	: const vector<string>& vStr
 *******************************************************************/
const vector<fs::path> FileSystem::vStr2vFs( const vector<string>& vStr)
{
	vector<fs::path> vFs(vStr.size());

	std::transform(vStr.begin(), vStr.end(), vFs.begin(), Str2Fs);

	return vFs;
}
