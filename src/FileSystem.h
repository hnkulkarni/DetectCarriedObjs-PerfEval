/*
 * FileSystem.h
 *
 *  Created on: Feb 13, 2013
 *      Author: hrushi
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_


#include "ProjectIncludes.h"
#include "WriteList.h"
#include "ReadLists.h"

class FileSystem
{
private:

public:
	FileSystem();
	virtual ~FileSystem();

	vector<fs::path> ListAllImagesInFolder(const string FolderPath );
	static vector<fs::path> ListAllTrackImages( const fs::path FolderPath, const string TrackFldrName );

	static size_t Find( const fs::path& ImPath, const string FolderName ) ;
	vector<fs::path> NameFilter_folderPresent( const vector<fs::path>& FileList, const string FolderName, const bool has ) const;
	vector<fs::path> NameFilter_parentName( const vector<fs::path>& FileList, const string FolderName, const bool has ) const;

	static fs::path MakeRelative(const fs::path& From, const fs::path& To);
	static fs::path MakeRelative(const string FromPath, const string ToPath );
	static const vector<fs::path> MakeRelative(const fs::path& From, const vector<fs::path>& vTo);
	static const vector<string> MakeRelative(const string& From, const vector<string>& vTo);

	static const fs::path GetCompletePath(const fs::path& From, const fs::path& RelativeTo);
	static const vector<fs::path> GetCompletePath(const fs::path& From, const vector<fs::path>& vRelativeTo);
	static const vector<string> GetCompletePath( const string& From, const vector<string>& vRelativeTo );

	static const fs::path GetMaskImgPath(const string MaskFolderName, 	const fs::path TrackPath, const string TrackFolderName);
	static const vector<fs::path> GetMaskImgPathVector( const string MaskFolderName, 	const vector<fs::path>& TrackPath, const string TrackFolderName );
	static bool isImageExt(const string sEXT );
	static const fs::path GetOutputFolderPath( const fs::path TrackImgPath );
	static const fs::path BuildOutputImgPath( const fs::path TrackImgPath );
	static int CreateFolder( const fs::path FolderPath );

	static const vector<string> vFs2vStr(const vector<fs::path>& vFs);
	static const vector<fs::path> vStr2vFs(const vector<string>& vStr);
	static const string Fs2Str(const fs::path& Fs) {return Fs.string();}
	static const fs::path Str2Fs(const string& Str ) { return Str; }
};


#endif /* FILESYSTEM_H_ */
