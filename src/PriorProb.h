/*
 * PriorProb.h
 *
 *  Created on: Jul 14, 2013
 *      Author: hrushi
 */

#ifndef PRIORPROB_H_
#define PRIORPROB_H_

#include "ProjectIncludes.h"
#include "ProbImg.h"
#include "Labels.h"


class PriorProb
{
private:

	// Helper Function
	virtual int Copy( const PriorProb& rhsPriorProb );
	virtual int Allocate( const PriorProb& rhsPriorProb );
	virtual int Init_Members();

	unsigned int m_NumCntrs;


protected:
	double m_PriorProb_WornObj;
	double m_PriorProb_DraggedObj;
	double m_PriorProb_PersonRgn;
	ProbImg m_LocationPriorProb;

	int CalculateRgnPriorProbs( const fs::path TrainFolderPath, const Args& args );
	int CalculateLocationPriorProbs( const vector<ProbImg>& vProbImg, const Args& args );

public:
	PriorProb();
	virtual ~PriorProb();

	// Copy Constructor
	PriorProb( const PriorProb& rhsPriorProb );

	// Assignment Operator
	PriorProb& operator=( const PriorProb& rhsPriorProb );


	int CalculatePriorProbs( const fs::path TrainFolderPath, const vector<ProbImg>& vProbImg, const Args& args );

	/**************************************************************
	 *           Get Functions
	 **************************************************************/
	const ProbImg Get_LocationPrior()const {return m_LocationPriorProb; }
	double Get_WornObjPrior() const { return m_PriorProb_WornObj; }
	double Get_DraggedObjPrior() const { return m_PriorProb_DraggedObj; }
	double Get_PersonPrior() const { return m_PriorProb_PersonRgn; }
	bool isValid() const;


	/**************************************************************
	 *           Set Functions
	 **************************************************************/
	void Set_PriorProb_WornObj(double d){ m_PriorProb_WornObj = d; };
	void Set_PriorProb_DraggedObj(double d){m_PriorProb_DraggedObj = d; };
	void Set_PriorProb_PersonRgn(double d){ m_PriorProb_PersonRgn = d; };
	void Set_LocationPriorProb(const ProbImg P ){ m_LocationPriorProb = P; };

};

std::ostream& operator<<( std::ostream&, const PriorProb& rhsPriorProb );



#endif /* PRIORPROB_H_ */
