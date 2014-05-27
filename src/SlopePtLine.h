/*
 * SlopePtLine.h
 *
 *  Created on: Oct 20, 2012
 *      Author: hrushi
 */

#ifndef SLOPEPTLINE_H_
#define SLOPEPTLINE_H_

#include "ProjectIncludes.h"
#include "ImagePt.h"
#include "ColorImg.h"

class SlopePtLine {

private:


public:
	SlopePtLine();
	virtual ~SlopePtLine();

	vector<ImagePt> Interpolate(const ImagePt Pt0, const ImagePt Pt1 ) const;
	double GetSlope(const ImagePt Pt0, const ImagePt Pt1 ) const;
};

#endif /* SLOPEPTLINE_H_ */
