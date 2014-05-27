/*
 * SlopePtLine.cpp
 *
 *  Created on: Oct 20, 2012
 *      Author: hrushi
 */

#include "SlopePtLine.h"


/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
SlopePtLine::SlopePtLine() {
	// DONE Auto-generated constructor stub

}


/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
SlopePtLine::~SlopePtLine() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: Interpolate
 * Return 		:
 * Comments 	: Interpolates from the starting point to the ending point
 * 					using the Slope Intercept form.
 **********************************************************************/
vector<ImagePt> SlopePtLine:: Interpolate(const ImagePt Pt0, const ImagePt Pt1 ) const
//(const double ax, const double ay, const double bx, const double by  )
{
	double tempx, tempy;
	double x0 = Pt0.GetX();
	double y0 = Pt0.GetY();
	double x1 = Pt1.GetX();
	double y1 = Pt1.GetY();

	if(x1 < x0)
	{
		tempx = x0;
		x0 = x1;
		x1 = tempx;

		tempy = y0;
		y0 = y1;
		y1 = tempy;
	}

	double slope = GetSlope(Pt0, Pt1);
	double slope_inv = (double)1/slope;

	int x = 0;
	int y = 0;

	vector<ImagePt> vPt;
	ImagePt TempPt;

	TempPt.SetPoint(x0, y0);
	vPt.push_back(TempPt);

	if( slope >= 1  )
	{
		// Y Major
		for( y = y0; y <= y1; y++)
		{
			x = x0 + slope_inv * (y - y0);
			//Frame.SetPixel(x,y, 255, 255, 255);
			TempPt.SetPoint(x, y);
			vPt.push_back(TempPt);

		}
	}

	// X Major
	else if( slope >= 0 && slope < 1)
	{
		for(x = x0; x <= x1; x++)
		{
			y = y0 + slope * (x - x0);
			//Frame.SetPixel(x,y, 255, 255, 255);
			TempPt.SetPoint(x, y);
			vPt.push_back(TempPt);
		}
	}
	else if( slope < 0 && slope > -1)
	{
		for( x = x0; x <= x1; x++)
		{
			y = y0 + slope * (x - x0);
			//Frame.SetPixel(x,y, 255, 255, 255);
			TempPt.SetPoint(x, y);
			vPt.push_back(TempPt);
		}
	}
	else if( slope < -1 )
	{
		// Y Major
		for( y = y0; y >= y1; y--)
		{
			x = x0 + slope_inv * (y - y0);
			//Frame.SetPixel(x,y, 255, 255, 255);
			TempPt.SetPoint(x, y);
			vPt.push_back(TempPt);
		}
	}



	return vPt;
}


/**********************************************************************
 * Function_Name: Slope
 * Return 		:
 * Comments 	:
 **********************************************************************/
double SlopePtLine::GetSlope(const ImagePt Pt0, const ImagePt Pt1 ) const
//( const double x0, const double y0, const double x1, const double y1 )
{
	double s = (double)(Pt1.GetY() - Pt0.GetY())/(Pt1.GetX() - Pt0.GetX());
	return s;
}
