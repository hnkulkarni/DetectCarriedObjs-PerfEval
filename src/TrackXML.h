/*
 * TrackXML.h
 *
 *  Created on: Mar 4, 2014
 *      Author: hrushi
 */

#ifndef TRACKXML_H_
#define TRACKXML_H_

#include "XMLReader.h"

class TrackXML: public XMLReader
{
private:
	// Helper Function
	virtual int Copy( const TrackXML& rhs );
	virtual int Allocate( const TrackXML& rhs );

protected:

	pugi::xml_node m_trackList;

public:
	TrackXML(const fs::path FilePath);
	virtual ~TrackXML();

	// Copy Constructor
	TrackXML( const TrackXML& rhsTrackXML );

	// Assignment Operator
	TrackXML& operator=( const TrackXML& rhsTrackXML );

	virtual int PrintAll() const;
	virtual const cv::Rect GetBoundingBox(UINT trackID, UINT FrameNum ) const;
	virtual const fs::path GetFullImagePath(UINT FrameNum) const;


	/**************************************************************
	 *           Static Functions
	 **************************************************************/
	static int GetTrkChipNameParts(const string& basename, UINT& TrkNum, UINT& FrameNum, string& VideoName );
	static const fs::path GetTrackFilePath(const fs::path fsTrackChipPath );


};

#endif /* TRACKXML_H_ */
