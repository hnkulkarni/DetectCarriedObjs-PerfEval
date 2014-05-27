/*
 * ViperXML.cpp
 *
 *  Created on: Mar 6, 2014
 *      Author: hrushi
 */

#include "ViperXML.h"

/*******************************************************************
 * Function Name: ViperXML
 * Return Type 	: None
 * Created On	: Mar 6, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: const fs::path
 *******************************************************************/
ViperXML::ViperXML(const fs::path FilePath):XMLReader(FilePath)
{
	cout << "Loading Viper file: " << FilePath << endl;
	m_bagList = m_XMLFile.child("viper").child("data").child("sourcefile");

}

/*******************************************************************
 * Function Name: ~ViperXML
 * Return Type 	: None
 * Created On	: Mar 6, 2014
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
ViperXML::~ViperXML()
{


}

/*****************************************************
 * Function	: ViperXML Copy Constructor
 * Date		: Mar 6, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ViperXML::ViperXML(const ViperXML& rhs ):XMLReader(rhs)
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Mar 6, 2014
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ViperXML& ViperXML:: operator=( const ViperXML& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Mar 6, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ViperXML::Allocate( const ViperXML& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Mar 6, 2014
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ViperXML::Copy( const ViperXML& rhs )
{

	XMLReader::operator =(rhs);
	m_bagList = rhs.m_bagList;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: GetViperViperXMLPath
 * Return Type 	: const fs::path
 * Created On	: Mar 6, 2014
 * Created By 	: hrushi
 * Comments		: For the given track.xml file, get the corresponding Viper ground truth file, assuming that it is in the same folder
 * Arguments	: const fs::path TrackFilePath
 *******************************************************************/
const fs::path ViperXML::GetViperXMLPath( const fs::path TrackFilePath)
{
	fs::path ViperFilePath = "";
	vector<fs::path> V;
	std::copy(fs::directory_iterator(TrackFilePath.parent_path()), fs::directory_iterator(), std::back_inserter(V));

	std::size_t found;
	for(auto p : V )
	{
		string base = p.stem().string();

		found = base.find(VIPER_STEM_END);
		if (found!=std::string::npos)
		{
			ViperFilePath = p;
			return ViperFilePath;
		}
	}

	if(found == string::npos)
	{
		cerr << "Cannot find a Viper file with name type: " << VIPER_STEM_END << endl;
		exit(ERR_INVALID_PATH);
	}

	return ViperFilePath;
}


/*******************************************************************
 * Function Name: GetGndTruthBdnBox
 * Return Type 	: const cv::Rect
 * Created On	: Mar 7, 2014
 * Created By 	: hrushi
 * Comments		: Get the ground truth bounding box for the given frame
 * Arguments	: const fs::path TrackFilePath
 *******************************************************************/
const vector<cv::Rect> ViperXML::GetGndTruthBdnBox(UINT frameNum ) const
{
	vector<cv::Rect> BdnBx;
	vector<pugi::xml_node> Nodes = GetXMLNodesForFrames(frameNum);

	for(auto BagNode : Nodes)
	{
		cv::Rect Bdn = GetBagBdnBox(BagNode);
		BdnBx.push_back(Bdn);
	}

	return BdnBx;
}

/*******************************************************************
 * Function Name: GetBagBdnbox
 * Return Type 	: const cv::Rects
 * Created On	: Mar 8, 2014
 * Created By 	: hrushi
 * Comments		: Get the bounding box for the bag
 * Arguments	: const pugi::xml_node& BagNode
 *******************************************************************/
const cv::Rect ViperXML::GetBagBdnBox( const pugi::xml_node& BagNode) const
{
	UINT height =  GetValueInType<UINT>(BagNode.attribute("height").value());
	UINT width 	=  GetValueInType<UINT>(BagNode.attribute("width").value());
	UINT x 		=  GetValueInType<UINT>(BagNode.attribute("x").value());
	UINT y 		=  GetValueInType<UINT>(BagNode.attribute("y").value());

	cv::Rect BdnBox(x, y, width, height);

	return BdnBox;
}

/*******************************************************************
 * Function Name: GetXMLNodesForFrames
 * Return Type 	: const vector<pugi::xml_node>
 * Created On	: Mar 8, 2014
 * Created By 	: hrushi
 * Comments		: Returns all nodes from the VIPER xml file which have the given frame. There can be multiple objects in the same frame of data
 * Arguments	: UINT frame
 *******************************************************************/
const vector<pugi::xml_node> ViperXML::GetXMLNodesForFrames( UINT frameNum) const
{
	vector<pugi::xml_node> NodeList;

	for(pugi::xml_node objectNode = m_bagList.child("object"); objectNode; objectNode = objectNode.next_sibling("object"))
	{
		vector<UINT> spanParts = StringOp<UINT>::GetSplitParts( objectNode.attribute("framespan").value(), VIPER_DELIMITERS ) ;

		//max_element and min_element return iterators. Hence use *max_iterators
		UINT minFrameNum = *std::min_element(spanParts.begin(), spanParts.begin() + spanParts.size());
		UINT maxFrameNum = *std::max_element(spanParts.begin(), spanParts.begin() + spanParts.size());

		if((frameNum >= minFrameNum) && (frameNum <= maxFrameNum))
		{
			pugi::xml_node bagBoundingBox = objectNode.find_child_by_attribute("attribute", "name", "bagBoundingBox");

			string strFramNum = StringOp<UINT>::GetString(frameNum);
			string searchAttribute = strFramNum + ":" + strFramNum;

			pugi::xml_node BagNode = bagBoundingBox.find_child_by_attribute("data:bbox", "framespan", searchAttribute.c_str());

			// If a valid node is present
			if(!BagNode.empty())
			{
				NodeList.push_back(BagNode);
			}

		}

	}

	return NodeList;
}
