/*
 * Segmentation.h
 *
 *  Created on: Jan 1, 2013
 *      Author: hrushi
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_


#include "SLIC.h"
#include "ColorImg.h"
#include "GrayImg.h"
#include "ContourMap.h"
#include "Args.h"
#include "VectorOp.h"

class Segmentation
{
protected:


public:
	Segmentation();
	virtual ~Segmentation();


	// Copy Constructor
	Segmentation( const Segmentation& rhsSegmentation );

	// Assignment Operator
	Segmentation& operator=( const Segmentation& rhsSegmentation );

	// Helper Function
	int Copy_Segmentation( const Segmentation& rhsSegmentation );
	int Allocate_Segmentation( const Segmentation& rhsSegmentation );


	void cv_to_argb(Mat& data, unsigned int *buff) const;
	void argb_to_cv(unsigned int *buff, Mat& data) const;

	vector<int> DoSlic( string input_filename, bool bSaveImg);
	vector<int> DoSlic(string input_filename, string output_filename, bool bSaveImg, int k, double m);
	vector<int> DoSlic( const ColorImg ProbeImg, const string output_fileName, bool bSaveImg, int k, double m) const;

	ContourMap MergeLabels(const ColorImg& ProbeImg, const vector<int>& Labelsmint, const GrayImg& BkImg, const Args& args ) const;
	Vec3d AvgLabelColor( const ColorImg& ProbeImg, vector<int> Labels, const unsigned int Label ) const;

	vector<int> MergeBackground( const ColorImg& ProbeImg, const vector<int>& Labelsmint, const GrayImg& BkImage, const Args& args ) const;
	ContourMap MergeForeground( const ColorImg& ProbeImg, const vector<int>& Labelsmint, const GrayImg& BkImage, const Args& args ) const;


	ContourMap GetSegments( const ColorImg& ProbeImg, const GrayImg& BkImg, const string output_filepath, bool bSaveImg, int k, double m,  const Args& args ) const;

	int WriteLabelFile( string FilePath, const vector<int>& LImage, const ColorImg& ProbeImg ) const;

};

#endif /* SEGMENTATION_H_ */
