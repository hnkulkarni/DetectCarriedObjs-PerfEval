/*
 * ViperXML.h
 *
 *  Created on: Mar 6, 2014
 *      Author: hrushi
 */

#ifndef VIPERXML_H_
#define VIPERXML_H_

#include "XMLReader.h"

#define VIPER_STEM_END "ViperGT"
#define VIPER_DELIMITERS ": " //space is also a delimiters!!

class ViperXML: public XMLReader
{

private:
	// Helper Function
	virtual int Copy( const ViperXML& rhs );
	virtual int Allocate( const ViperXML& rhs );


	pugi::xml_node m_bagList;

protected:
	const vector<pugi::xml_node> GetXMLNodesForFrames(UINT frame) const;
	const cv::Rect GetBagBdnBox( const pugi::xml_node& BagNode ) const;

public:
	ViperXML(const fs::path FilePath);
	virtual ~ViperXML();

	// Copy Constructor
	ViperXML( const ViperXML& rhsViperXML );

	// Assignment Operator
	ViperXML& operator=( const ViperXML& rhsViperXML );
	const vector<cv::Rect> GetGndTruthBdnBox(UINT frameNum ) const;


/**************************************************************
 *           Static Functions
 **************************************************************/
	static const fs::path GetViperXMLPath(const fs::path TrackFilePath );

};

#endif /* VIPERXML_H_ */
