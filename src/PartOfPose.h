/*
 * PartOfPose.h
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#ifndef PARTOFPOSE_H_
#define PARTOFPOSE_H_

#include "ProjectIncludes.h"
#include "Boxes.h"
#include "ColorImg.h"
#include "Contour.h"
#include "SlopePtLine.h"
#include "BinaryImg.h"

class PartOfPose {

private:
	virtual double CalcShoulderAngle();
	virtual double CalcElbowAngle();
	virtual double CalcWristAngle();


	// Helper Function
	virtual int Copy_PartOfPose( const PartOfPose& rhsPartOfPose );
	virtual int Allocate_PartOfPose( const PartOfPose& rhsPartOfPose );

	virtual const ColorImg OverlayArm( const CImage& Img ) const;
	virtual const ColorImg OverlayTorso( const CImage& Img ) const;
	virtual const ColorImg OverlayLegs( const CImage& Img )  const;
	virtual const ColorImg OverlayHead( const CImage& Img ) const;

protected:

	vector<Boxes> PartBoxes;


	/************ Angles for Part ***********************************
	 *           _______
	 *           \ (0)Shoulder Angle
	 *            \
	 *             \________
	 *              |(1)Elbow Angle
	 *              |
	 *              |_______
	 *             /(2)Wrist Angle
	 *            /
	 *           /(3)End of Arm
	 *
	 **************************************************************/
	double ShoulderAngle;
	double ElbowAngle;
	double WristAngle;
	char PartClr; 			// Color of the Part
	cv::Scalar RgbPartClr;  // RGB of the Part Color
	string PartType;

public:

	/**************************************************************
	 *           House keeping functions
	 **************************************************************/
	PartOfPose();
	virtual ~PartOfPose();

	// Copy Constructor
	PartOfPose( const PartOfPose& rhsPartOfPose );

	// Assignment Operator
	PartOfPose& operator=( const PartOfPose& rhsPartOfPose );

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int Add(const Boxes& Bx);
	virtual int CalcAngles( );
	virtual double CalcCarryAngle(const ImagePt& Pt) const;
	virtual double CalcCarryDist(const Contour& Ct ) const;
	virtual int SetColor(const char ClrKey );  // Sets the color key

	/**************************************************************
	 *           Accessors
	 **************************************************************/
	virtual double GetNumBoxes() 		const { return PartBoxes.size(); }
	virtual double GetElbowAngle()		const { return ElbowAngle; 	 }
	virtual double GetShoulderAngle() 	const { return ShoulderAngle; 	 }
	virtual double GetWristAngle() 		const { return WristAngle; 	 }
	virtual const ColorImg OverlayStick( const CImage& Img ) const;
	virtual const ColorImg Overlay( const CImage& Img ) const;
	virtual const string GetPartType() const { return PartType; }
	virtual const ImagePt GetEndOfArm() const;
	virtual const ImagePt GetWristPt() const;

	virtual const BinaryImg GetMask(const cv::Size ImgSize, const Args& args ) const;
};



#endif /* PARTOFPOSE_H_ */
