/*
 * RectOp.h
 *
 *  Created on: Mar 9, 2014
 *      Author: hrushi
 */

#ifndef RECTOP_H_
#define RECTOP_H_

#include "MyIncludes.h"
#include "BinaryImg.h"

class RectOp
{
private:
	// Helper Function
	virtual int Copy( const RectOp& rhs );
	virtual int Allocate( const RectOp& rhs );

protected:


public:
	RectOp();
	virtual ~RectOp();

	// Copy Constructor
	RectOp( const RectOp& rhsRectOp );

	// Assignment Operator
	RectOp& operator=( const RectOp& rhsRectOp );

	static bool Contains(const cv::Rect& BigRect, const cv::Rect& SmallRect );
	static const vector<cv::Rect> GetContaining( const cv::Rect& BigRect, const vector<cv::Rect>& SmallRects );
	static const cv::Rect GetIntersection( const cv::Rect& BigRect, const cv::Rect& SmallRect );
	static const vector<cv::Rect> GetOverlappingRect( const cv::Rect& BigRect,  const vector<cv::Rect>& SmallRects, double OverlapThreshold );
	static const vector<cv::Rect> MakeRelativeToBigRect( const cv::Rect& BigRect,  const vector<cv::Rect>& SmallRects);
	static const BinaryImg MakeMasks(const cv::Size MaskSize, const vector<cv::Rect>& Rt);
};

#endif /* RECTOP_H_ */
