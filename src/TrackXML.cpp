/*
 * TrackXML.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: hrushi
 */

#include "TrackXML.h"

/*******************************************************************
 * Function Name: TrackXML
 * Return Type 	: None
 * Created On	: Mar 4, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
TrackXML::TrackXML(const fs::path FilePath):XMLReader(FilePath)
{
	cout << "Using Track File: " << FilePath << endl;
	cout << "Video: " << m_XMLFile.child("video").attribute("name").value() << endl;
	cout << "Date: " << m_XMLFile.child("video").attribute("date").value() << endl;

	m_trackList = m_XMLFile.child("video").child("trackList");

}


/*******************************************************************
 * Function Name: ~TrackXML
 * Return Type 	: None
 * Created On	: Mar 4, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
TrackXML::~TrackXML()
{

}

/*****************************************************
 * Function	: TrackXML Copy Constructor
 * Date		: Mar 4, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
TrackXML::TrackXML(const TrackXML& rhs ):XMLReader(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Mar 4, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
TrackXML& TrackXML:: operator=( const TrackXML& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Mar 4, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int TrackXML::Allocate( const TrackXML& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Mar 4, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int TrackXML::Copy( const TrackXML& rhs )
{
	XMLReader::operator =(rhs);
	m_trackList	= rhs.m_trackList;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: PrintAll
 * Return Type 	: int
 * Created On	: Mar 4, 2014
 * Created By 	: hrushi
 * Comments		: Prints all the nodes in the tree
 * Arguments	:
 *******************************************************************/
int TrackXML::PrintAll( ) const
{
	for (pugi::xml_node track = m_trackList.child("track"); track; track = track.next_sibling("track"))
	{
		cout << "track: " << track.attribute("id").value() << endl;

		for(pugi::xml_node frame = track.child("frame"); frame; frame = frame.next_sibling("frame"))
		{
			cout << "frame: " << frame.attribute("time").value() << " x: " << frame.attribute("x").value() << " y: " << frame.attribute("y").value() << endl;
		}
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetBoundingBox
 * Return Type 	: const cv::Rect
 * Created On	: Mar 4, 2014
 * Created By 	: hrushi
 * Comments		: Get the bounding box for the number
 * Arguments	: UINT trackID, UINT FrameNum
 *******************************************************************/
const cv::Rect TrackXML::GetBoundingBox( UINT trackID, UINT FrameNum) const
{
	cv::Rect BndBox;

	string strTrackID = StringOp<UINT>::GetString(trackID);
	pugi::xml_node track = m_trackList.find_child_by_attribute("track", "id", strTrackID.c_str());

	if(!track.empty() )
	{
		string strFrameNum = StringOp<UINT>::GetString(FrameNum);
		pugi::xml_node frame = track.find_child_by_attribute("frame", "time", strFrameNum.c_str());

		//cout << "frame: " << frame.attribute("time").value() << " x: " << frame.attribute("x").value() << " y: " << frame.attribute("y").value() << endl;

		if(!frame.empty() )
		{
			UINT x 		= GetValueInType<UINT>(frame.attribute("x").value() );
			UINT y 		= GetValueInType<UINT>(frame.attribute("y").value() );
			UINT width 	= GetValueInType<UINT>(frame.attribute("width").value() );
			UINT height	= GetValueInType<UINT>(frame.attribute("height").value() );

			BndBox = cv::Rect(x, y, width, height);

		}
	}

	return BndBox;
}

/*******************************************************************
 * Function Name: GetTrackFilePath
 * Return Type 	: const fs::path
 * Created On	: Mar 5, 2014
 * Created By 	: hrushi
 * Comments		: Get the TrackFile path from the given TrackImage path
 * Arguments	: const fs::path TrackChipPath
 *******************************************************************/
const fs::path TrackXML::GetTrackFilePath( const fs::path fsTrackChipPath)
{
	fs::path fsTrackFldrPath = fsTrackChipPath.parent_path().parent_path();
	string stemname = fsTrackChipPath.stem().string();

	UINT TrackNum, FrameNum;
	string VideoBaseName;

	GetTrkChipNameParts(stemname, TrackNum, FrameNum, VideoBaseName);
	fs::path fsTrackFilePath = fsTrackFldrPath.string() + "/" + VideoBaseName + "_track.xml";

	return fsTrackFilePath;
}


/*******************************************************************
 * Function Name: GetTrkChipNameParts
 * Return Type 	: int
 * Created On	: Mar 5, 2014
 * Created By 	: hrushi
 * Comments		: For the given basename, it will find out the parts for it
 * Arguments	: const string& basename, UINT& TrkNum, UINT& FrameNum, string& VideoName
 *******************************************************************/
int TrackXML::GetTrkChipNameParts( const string& stemname, UINT& TrkNum, UINT& FrameNum, string& VideoStemName)
{
	vector<string> strs;
	boost::split(strs, stemname, boost::is_any_of("t_f")  );

	//Str.at(0) is blank. Hence starting with strs.at(1)
	TrkNum 		= GetValueInType<int>( strs.at(1) );
	FrameNum 	= GetValueInType<int>( strs.at(2) );
	VideoStemName 	= strs.at(3);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetFullImagePath
 * Return Type 	: const fs::path
 * Created On	: Mar 8, 2014
 * Created By 	: hrushi
 * Comments		: Returns the corresponding full image path for the given track image
 * Arguments	:
 *******************************************************************/
const fs::path TrackXML::GetFullImagePath( UINT FrameNum ) const
{
	const fs::path Parentfldr = GetFilePath().parent_path();
	const string FldrName = Parentfldr.stem().string();

	string ImgStemName = StringOp<UINT>::GetString(FrameNum, '0', 5);

	fs::path FullImgPath = Parentfldr.string() + "/full/" +  FldrName + "." + ImgStemName + ".jpeg";

	return FullImgPath;
}
