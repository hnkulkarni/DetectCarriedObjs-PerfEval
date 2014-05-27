/*
 * AllDetectedCtrs.cpp
 *
 *  Created on: Jul 6, 2013
 *      Author: hrushi
 */

#include "AllDetectedCtrs.h"

AllDetectedCtrs::AllDetectedCtrs()
{
	Init_Members();
}

AllDetectedCtrs::~AllDetectedCtrs()
{
	// TODO Auto-generated destructor stub
}


/*******************************************************************
 * Function Name: Init_Members
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Intit Member Variables
 * Arguments	:
 *******************************************************************/
int AllDetectedCtrs::Init_Members( )
{
	m_NumPersonContour = 0;
	m_NumWornCarryObj  = 0;
	m_NumDraggedCarryObj = 0;

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: AllDetectedCtrs Copy Constructor
 * Date		: Jul 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
AllDetectedCtrs::AllDetectedCtrs(const AllDetectedCtrs& rhsAllDetectedCtrs )
{
	Allocate( rhsAllDetectedCtrs );
	Copy( rhsAllDetectedCtrs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Jul 6, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
AllDetectedCtrs& AllDetectedCtrs:: operator=( const AllDetectedCtrs& rhsAllDetectedCtrs )
{
	Allocate( rhsAllDetectedCtrs );
	Copy( rhsAllDetectedCtrs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Jul 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int AllDetectedCtrs::Allocate( const AllDetectedCtrs& rhsAllDetectedCtrs )
{
	m_vCtrs.resize(  rhsAllDetectedCtrs.m_vCtrs.size() );
	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Jul 6, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int AllDetectedCtrs::Copy( const AllDetectedCtrs& rhsAllDetectedCtrs )
{
	m_vCtrs = rhsAllDetectedCtrs.m_vCtrs;
	m_NumDraggedCarryObj = rhsAllDetectedCtrs.m_NumDraggedCarryObj;
	m_NumPersonContour	= rhsAllDetectedCtrs.m_NumPersonContour;
	m_NumWornCarryObj	= rhsAllDetectedCtrs.m_NumWornCarryObj;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Set_Ctrs
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Sets the vector of CarriedContours
 * Arguments	: const vector<CarryContour>& vCtrs
 *******************************************************************/
int AllDetectedCtrs::Set_vCtrs( const vector<CarryContour>& vCtrs)
{

	m_vCtrs.resize( vCtrs.size() );
	m_vCtrs = vCtrs;

	Calc_NumDetectionTypes();
	Print_NumDetectionTypes();

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Calc_NumDetectionTypes
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Calculates the number of detection Types
 * Arguments	:
 *******************************************************************/
int AllDetectedCtrs::Calc_NumDetectionTypes( )
{
	for(auto Ctrs: m_vCtrs )
	{
		switch( Ctrs.GetCarryType() )
		{
		case PERSON_LABEL:
			m_NumPersonContour++;
			break;

		case WORN_CARRY_LABEL:
			m_NumWornCarryObj++;
			break;

		case DRAG_CARRY_LABEL:
			m_NumDraggedCarryObj++;
			break;
		}
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Print_NumDetectionTypes
 * Return Type 	: int
 * Created On	: Jul 7, 2013
 * Created By 	: hrushi
 * Comments		: Prints the number of detection types
 * Arguments	:
 *******************************************************************/
int AllDetectedCtrs::Print_NumDetectionTypes( ) const
{

	cout << "Detection Type Counts are " << endl;
	cout << "NumPersonCtr : " << m_NumPersonContour << endl;
	cout << "NumWornCarryObj : " << m_NumWornCarryObj << endl;
	cout << "NumDraggedCarryObj : " << m_NumDraggedCarryObj << endl;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Offset
 * Return Type 	: const AllDetectCtrs
 * Created On	: Mar 17, 2014
 * Created By 	: hrushi
 * Comments		: Offset all the contour points relative to the given point
 * Arguments	: const cv::Point Pt
 *******************************************************************/
const AllDetectedCtrs AllDetectedCtrs::Offset( const cv::Point Pt) const
{

	AllDetectedCtrs Temp = *this;
	vector<CarryContour> NewCtr;

	for(auto CC : m_vCtrs)
	{
		Contour C = CC;
		ImagePt P(Pt);

		Contour C2 = C.Offset(P.GetPoint());
		vector<ImagePt> V = C2.GetCtrPoints();

		CC.SetCtrPoints(V);

		ImagePt TempCnter = CC.GetCenter();
		TempCnter.SwapXY();

		CC.SetCenter( TempCnter );

		NewCtr.push_back(CC);
	}


	Temp.Set_vCtrs(NewCtr);
	return Temp;
}

/*******************************************************************
 * Function Name: Get_PositiveCtrs
 * Return Type 	: const vector<CarryContour>
 * Created On	: Apr 9, 2014
 * Created By 	: hrushi
 * Comments		: Get a vector of positive contours
 * Arguments	:
 *******************************************************************/
const vector<CarryContour> AllDetectedCtrs::Get_PositiveCtrs( ) const
{
	vector<CarryContour> PosCtrs;

	for(auto CC : m_vCtrs)
	{
		int CCType = CC.GetCarryType();

		if(CCType != PERSON_LABEL )
		{
			PosCtrs.push_back(CC);
		}
		else
		{
			continue;
		}
	}

	return PosCtrs;
}


/*******************************************************************
 * Function Name: Get_NegativeCtrs
 * Return Type 	: const vector<CarryContour>
 * Created On	: Apr 9, 2014
 * Created By 	: hrushi
 * Comments		: Get a vector of negative contours
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
const vector<CarryContour> AllDetectedCtrs::Get_NegativeCtrs() const
{
	vector<CarryContour> NegCtrs;

	for(auto CC : m_vCtrs )
	{
		int CCType = CC.GetCarryType();

		if(CCType == PERSON_LABEL )
		{
			NegCtrs.push_back(CC);
		}
		else
		{
			continue;
		}
	}


	return NegCtrs;
}
