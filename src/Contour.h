/*
 * Contour.h
 *
 *  Created on: Jan 2, 2013
 *      Author: hrushi
 */

#ifndef CONTOUR_H_
#define CONTOUR_H_


#include "CPPIncludes.h"
#include "MyIncludes.h"
#include "OpenCV_Includes.h"

#include "ImagePt.h"
#include "GrayHistorgram.h"
#include "ReadHistLookup.h"
#include "ElevenSpaceHist.h"
#include "ColorImg.h"
#include "GrayImg.h"
#include "SlopePtLine.h"
#include "VectorOp.h"

class GrayImg; 	// Partial Declaration
class ColorImg; // Partial Declaration

class Contour {

private:

	// Helper Function
	virtual int Copy_Contour( const Contour& rhsContour );
	virtual int Allocate_Contour( const Contour& rhsContour );

protected:
	/**************************************************************
	 *           Protected Variables
	 **************************************************************/
	unsigned int Label;
	GrayHistorgram ContourHist;
	ElevenSpaceHist EHist;

	ImagePt Center;
	ImagePt MedianPt;
	ImagePt TopLeft;
	ImagePt BottomRight;

	bool isBackgroundFlag;

	cv::Mat ContourMask;

public:

	/**************************************************************
	 *           Member Variables
	 **************************************************************/
	vector<ImagePt> ContourPoints;

	/**************************************************************
	 *           House Keeping Tasks
	 **************************************************************/
	Contour();
	virtual ~Contour();

	// Copy Constructor
	Contour( const Contour& rhsContour );

	// Assignment Operator
	Contour& operator=( const Contour& rhsContour );

	/**************************************************************
	 *           Member Functions
	 **************************************************************/
	virtual int CalculateGrayHist(const GrayImg& GrImg);
	virtual int CalculateElevenSpaceHist( const ColorImg& Img, const ReadHistLookup& Lookup );
	virtual double CalcContourLocProb( const GrayImg& LocProbImg) const;
	virtual int DisplayContourMask() const;
	virtual const GrayHistorgram& GetHistogram() const;
	virtual bool isBackground( const CImage& BkMask, double OverlapThreshold ) ;
	virtual double PercentageCoverage(const CImage& BkMask) const;
	virtual bool isOnContour( const ImagePt& Pt ) const;
	const Contour Offset(const cv::Point Pt) const;

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int SetCenter( ImagePt Pt ) 		{ Center = Pt; 				return EXIT_SUCCESS;}
	virtual int SetMedianPt( ImagePt Pt ) 	{ MedianPt = Pt; 			return EXIT_SUCCESS;}
	virtual int SetTopLeft( ImagePt Pt ) 		{ TopLeft = Pt; 			return EXIT_SUCCESS;}
	virtual int SetBottomRight( ImagePt Pt ) { BottomRight = Pt; 		return EXIT_SUCCESS;}
	virtual int SetLabel( unsigned int  L ) 	{ Label = L;  				return EXIT_SUCCESS;}
	virtual int SetCtrMask( const cv::Mat& Msk ){ ContourMask = Msk.clone();return EXIT_SUCCESS;}
	virtual int CalculateCntrParam();
	virtual int SetCtrPoints( const vector<ImagePt>& rhsPts );


	/**************************************************************
	 *           Accessors
	 **************************************************************/
	virtual ImagePt GetCenter()						const { return Center;			}
	virtual ImagePt GetMedianPt() 					const { return MedianPt;		}
	virtual ImagePt GetTopLeft() 					const { return TopLeft; 		}
	virtual ImagePt GetBottomRight()				const { return BottomRight; 	}
	virtual bool	GetisBackgroundFlag()			const { return isBackgroundFlag;}
	virtual unsigned int GetLabel()					const { return Label; 			}
	virtual const GrayHistorgram GetContourHist() 	const { return ContourHist; 	}
	virtual const vector<double> GetElHist() 		const { return EHist.m_Hist;	}
	virtual const ElevenSpaceHist GetElSpcHist() 	const { return EHist; 			}
	virtual const cv::Rect GetBoundingRect() const;
	virtual const ImagePt GetClosestPt( const ImagePt& Pt ) const;
	virtual const vector<cv::Point> GetOpenCVPts() const;
	virtual const cv::Mat GetCtrMask() const 		{ return ContourMask.clone(); }
	virtual const GrayImg GetCtrMaskImg() const;
	virtual const ColorImg GetCtrBlackImg() const;
	virtual const ColorImg GetImgChip(ColorImg ProbeImg ) const;
	virtual const vector<ImagePt>& GetCtrPoints() 	const { return ContourPoints; }

};

#endif /* CONTOUR_H_ */
