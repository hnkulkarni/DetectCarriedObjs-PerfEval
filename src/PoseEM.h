/*
 * PoseEM.h
 *
 *  Created on: Jul 22, 2013
 *      Author: hrushi
 */

#ifndef POSEEM_H_
#define POSEEM_H_

#include "EMLearning.h"

#include "PoseFeature.h"



class PoseEM: public EMLearning
{

private:
	// Helper Function
	virtual int Copy( const PoseEM& rhsPoseEM );
	virtual int Allocate( const PoseEM& rhsPoseEM );
	virtual int Init_Members(const vector<PoseFeature>& vPF);

	vector<PoseFeature> m_vPF;

public:
	PoseEM();
	PoseEM( unsigned int NumClasses, const vector<PoseFeature>& vPF );
	virtual ~PoseEM();


	// Copy Constructor
	PoseEM( const PoseEM& rhsPoseEM );

	// Assignment Operator
	PoseEM& operator=( const PoseEM& rhsPoseEM );

	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/
	virtual int LoadData(); 	// Load the Data into the the specific required format
	virtual  cv::Vec2d Predict(const vector<double>& Feature ) const;
	virtual int Populate_ColHeaders();
};

#endif /* POSEEM_H_ */
