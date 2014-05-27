/*
 * AllDetectedCtrs.h
 *
 *  Created on: Jul 6, 2013
 *      Author: hrushi
 */

#ifndef ALLDETECTEDCTRS_H_
#define ALLDETECTEDCTRS_H_
#include "ProjectIncludes.h"
#include "CarryContour.h"

class AllDetectedCtrs
{

private:

	// Helper Function
	virtual int Copy( const AllDetectedCtrs& rhsAllDetectedCtrs );
	virtual int Allocate( const AllDetectedCtrs& rhsAllDetectedCtrs );
	virtual int Init_Members();

protected:

	vector<CarryContour> m_vCtrs;
	unsigned int m_NumPersonContour;
	unsigned int m_NumWornCarryObj;
	unsigned int m_NumDraggedCarryObj;

public:
	AllDetectedCtrs();
	virtual ~AllDetectedCtrs();

	// Copy Constructor
	AllDetectedCtrs( const AllDetectedCtrs& rhsAllDetectedCtrs );

	// Assignment Operator
	AllDetectedCtrs& operator=( const AllDetectedCtrs& rhsAllDetectedCtrs );

	/**************************************************************
	 *           Accessors
	 **************************************************************/
	virtual const vector<CarryContour> Get_vCtrs() const { return m_vCtrs;}
	virtual const unsigned int Get_NumPersonContour() const { return m_NumPersonContour; }
	virtual const unsigned int Get_NumWornCarryObjs() const { return m_NumWornCarryObj; }
	virtual const unsigned int Get_NumDraggedCarryObjs() const { return m_NumDraggedCarryObj; }
	virtual const UINT	Get_NumvCntrs() const { return m_vCtrs.size(); }
	virtual const vector<CarryContour> Get_PositiveCtrs() const;
	virtual const vector<CarryContour> Get_NegativeCtrs() const;

	int Print_NumDetectionTypes() const;

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	virtual int Set_vCtrs( const vector<CarryContour>& vCtrs );
	virtual int Calc_NumDetectionTypes();

	/**************************************************************
	 *           Aux Functions
	 **************************************************************/

	virtual const AllDetectedCtrs Offset(const cv::Point Pt) const;


};

#endif /* ALLDETECTEDCTRS_H_ */
