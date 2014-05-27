/*
 * Labels.h
 *
 *  Created on: Feb 10, 2013
 *      Author: hrushi
 */

#ifndef LABELFILE_H_
#define LABELFILE_H_

#include "ProjectIncludes.h"
#include "Time.h"
#include "Detect.h"
#include "ColorImg.h"
#include "ContourMap.h"
#include "FileSystem.h"
#include "TrackXML.h"
#include "ViperXML.h"
#include "RectOp.h"
#include "MapOp.h"

const int IMAGE_LOC				=  0; // Column number of the image file.
const int LABEL_LOC				=  2; // Column number of the Label

const int LABEL_LATER			= -5; // If the label is -5, this means that it has to be later later on !!

typedef std::map<string, int> tdef_LabelMap;

class Labels {

private:
	fs::path LPath;
	std::ofstream fPtr;
	tdef_LabelMap LabelMap;
	bool bWBanner;

	/***************************************************************************************
	 *  							Private Functions
	 ***************************************************************************************/
	// Helper Function
	virtual int Copy_Labels( const Labels& rhsLabels );
	virtual int Allocate_Labels( const Labels& rhsLabels );

	virtual int WriteBanner();
	virtual int WriteLabels();
	virtual size_t isNeg( const fs::path& ImPath  ) const;

	virtual const fs::path GetMergeImagePath(const fs::path RelativeLabelFilePath, const fs::path ImagePath ) const;

public:
	/***************************************************************************************
	 *  							House Keeping
	 ***************************************************************************************/
	Labels();
	Labels( const Args& args, const fs::path FilePath );   // To Open a new Label file with the given path
	Labels( const fs::path SearchFolderPath, const fs::path sPath );
	virtual ~Labels();

	// Copy Constructor
	Labels( const Labels& rhsLabels );

	// Assignment Operator
	virtual Labels& operator=( const Labels& rhsLabels );

	/***************************************************************************************
	 * 						Mutators
	 ***************************************************************************************/
	virtual int Init( const Args& args, const fs::path sPath ); // Performs all the initilaization
	virtual int Init( const fs::path SearchFolderPath, const fs::path sPath ); // Overloaded function for the Intitialization

	virtual int Add(const fs::path& ImPath, const ColorImg& Overlay, const Args& args, const ContourMap& AllSegments );
	virtual int Add(const fs::path& ImPath, const TrackXML& oTrackXML, const ViperXML& oViperXML, const ColorImg& Overlay, const Args& args, const ContourMap& AllSegments );

	virtual int Read(const Args& args);
	virtual int OpenFile(const Args& args);
	virtual int CloseFile();
	virtual int AddToMap(const string ImageFileName, const int Label);
	virtual int AddToMap(const fs::path& ImPath, const int Label );

	/***************************************************************************************
	 * 			     Aux. Member Functions
	 ****************************************************************************************/
	virtual int Write(const Args& args);
	virtual int MarkBackLogLabels(const Args& args );

	/***************************************************************************************
	 * 						Accessors
	 ***************************************************************************************/
	virtual int GetNumLabels() const {return LabelMap.size(); }
	virtual int AlreadyPresent( const fs::path FilePath ) const;
	virtual int AlreadyPresent(const fs::path Path, const bool isPathRelativeToLabel ) const;
	virtual int GetImageLabel( const fs::path Path, const bool isPathRelative ) const;

	virtual const fs::path GetLabelFilePath() const { return LPath; }
	virtual const string GetComplateImgFilePath( const string sPath ) const;
	virtual const string GetSegImgPath( const string sPath ) const;
	virtual tdef_LabelMap::const_iterator GetLabelMapItrBegin() const{ return LabelMap.begin(); }
	virtual tdef_LabelMap::const_iterator GetLabelMapItrEnd() const{ return LabelMap.end(); }
	virtual const tdef_LabelMap GetLabelMap() const {return LabelMap;}

	virtual int GetOptimalRgn(const ContourMap& AllSegments, const BinaryImg& GndMsk) const;


};

#endif /* LABELFILE_H_ */
