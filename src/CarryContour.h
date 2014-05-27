/*
 * CarryContour.h
 *
 *  Created on: Jun 20, 2013
 *      Author: hrushi
 *
 *      Builds from the Contour Base Class; This will contain extra information specific to the Carry Contour;
 *      Which is, What type of carry is this object, a backpack or a suitecase. Etc.
 */

#ifndef CARRYCONTOUR_H_
#define CARRYCONTOUR_H_

#include "ProjectIncludes.h"
#include "Contour.h"

typedef std::pair<int, double> TYPE_PAIR_CARRY_TYPE_SCORE;
class CarryContour: public Contour
{

private:
	// Helper Function
	virtual int Copy( const CarryContour& rhsCarryContour );
	virtual int Allocate( const CarryContour& rhsCarryContour );
	virtual int Init();

protected:
	int m_CarryType;
	double m_CarryScore;

	vector<double> m_AllScores; //Used for plotting purposes

public:
	CarryContour();
	virtual ~CarryContour();

	// Copy Constructor
	CarryContour( const CarryContour& rhsCarryContour );

	// Assignment Operator
	CarryContour& operator=( const CarryContour& rhsCarryContour );

	// CarryContour Constructor when passed passed with normal contour
	CarryContour( const Contour& rhsContour );


	/**************************************************************
	 *           Accessors
	 **************************************************************/
	const int GetCarryType()const { return m_CarryType; }
	const double GetCarryScore() const { return m_CarryScore; }
	const vector<double> GetAllScores() const { return m_AllScores; }

	/**************************************************************
	 *           Mutators
	 **************************************************************/
	int SetCarryTypeNScore(int CarryType, double CarryScore);
	int SetAllScores(const vector<double>& AllScores);

	/**************************************************************
	 *           Aux Functions
	 **************************************************************/

};



#endif /* CARRYCONTOUR_H_ */
