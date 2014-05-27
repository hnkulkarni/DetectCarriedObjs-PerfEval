/*
 * ImagePt.h
 *
 *  Created on: Jan 4, 2013
 *      Author: hrushi
 *
 *      This contains all the functions related to a point on the image
 *      	Example
 *      		1. Distance
 *
 */

#ifndef IMAGEPT_H_
#define IMAGEPT_H_


#include "CPPIncludes.h"
#include "MyIncludes.h"
#include "OpenCV_Includes.h"
#include "VectorOp.h"

class ImagePt {


private:

	// Helper Function
	virtual int Copy_ImagePt( const ImagePt& rhsImagePt );
	virtual int Allocate_ImagePt( const ImagePt& rhsImagePt );
	virtual int Init();


protected:

	cv::Point2d Pt;

public:
	ImagePt();
	ImagePt(double x, double y);
	virtual ~ImagePt();

	// Copy Constructor
	ImagePt( const ImagePt& rhsImagePt );
	ImagePt( const cv::Point& rhsPt);

	// Assignment Operator
	virtual ImagePt& operator=( const ImagePt& rhsImagePt );
	virtual ImagePt& operator=( const int RHS);
	virtual ImagePt& operator=( const cv::Point& rhsPt );


	// Operator Overloads
	virtual ImagePt operator+( const ImagePt& rhsImagePt ) const;
	virtual ImagePt operator+( const double d ) const;
	virtual ImagePt operator+ ( const cv::Point& rhsPt) const;
	virtual ImagePt operator-( const ImagePt& rhsImagePt ) const;
	virtual ImagePt operator-( const double d ) const;
	virtual ImagePt operator/( const double d) const;
	virtual ImagePt operator*( const double d) const;
	virtual bool operator == ( const ImagePt& rhsImagePt ) const;

	/*
	 * Public Functions
	 */
	virtual double Distance( const ImagePt& Pt2) const;
	virtual double Dot( const ImagePt& Pt2 ) const;
	virtual double Slope( const ImagePt& Pt2 ) const;
	virtual double SlopeAngle( const ImagePt& Pt2 ) const;
	virtual const ImagePt Offset(const cv::Point& rhsPt) const;

	/*
	 * Accessors
	 */
	virtual cv::Point GetPoint() const {cv::Point Temp = Pt; return Temp;}
	virtual int GetX() const { return Pt.x; }
	virtual int GetY() const { return Pt.y; }
	virtual const ImagePt GetUnit( const ImagePt& Pt ) const;

	/*
	 * Mutators
	 */
	virtual int Set_X(int x){ Pt.x = x; return EXIT_SUCCESS; }
	virtual int Set_Y(int y){ Pt.y = y; return EXIT_SUCCESS; }
	virtual int SetPoint( int x, int y) { Pt.x = x; Pt.y = y; return EXIT_SUCCESS;}
	virtual int SetPoint(const cv::Point& rhsPt) { SetPoint(rhsPt.x, rhsPt.y); return EXIT_SUCCESS; }
	virtual int SwapXY();
	virtual int YCompliment( int NumRows );
	virtual int XCompliment( int NumCols );

	/*
	 *  Static Members
	 */





};

std::istream& operator>>( std::istream& in, ImagePt& RHS);
std::ostream& operator<<(std::ostream& out, const ImagePt& RHS );

#endif /* IMAGEPT_H_ */
