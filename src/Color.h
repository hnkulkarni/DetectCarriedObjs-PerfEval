/*
 * Color.h
 *
 *  Created on: Jan 9, 2013
 *      Author: hrushi
 *
 *      Contains all the Color Information
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "CPPIncludes.h"
#include "OpenCV_Includes.h"
#include "MyIncludes.h"
#include "VectorOp.h"

class Color {


protected:

	Vec3d RGB;

public:
	Color();
	virtual ~Color();

	// Copy Constructor
	Color( const Color& rhsColor );

	// Helper Function
	int Copy_Color( const Color& rhsColor );
	int Allocate_Color( const Color& rhsColor );

	/**************************************************************
	 *           Overloaded Operators
	 **************************************************************/
	// Assignment Operator
	Color& operator=( const Color& rhsColor );
	Color& operator=( const cv::Vec3b vec );
	Color operator%(  int d) const;
	Color operator-( const Color& rhsColor ) const;
	Color operator-( const double d ) const;
	Color operator+( const Color& rhsColor ) const;
	Color operator+( const double d ) const;

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	int Set(double R, double G, double B);
	int Set(const cv::Vec3d& vec );


	/**************************************************************
	 *           Accessors
	 **************************************************************/
	const Vec3d& getRgb() const { return RGB; }
};

std::istream& operator>>( std::istream& in, Color& C);
std::ostream& operator<<( std::ostream& out, const Color& C );

#endif /* COLOR_H_ */
