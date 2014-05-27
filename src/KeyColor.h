/*
 * KeyColor.h
 *
 *  Created on: Mar 12, 2013
 *      Author: hrushi
 */

#ifndef KEYCOLOR_H_
#define KEYCOLOR_H_

#include "Color.h"

class KeyColor: public Color {

private:
	// Helper Function
	int Copy_KeyColor( const KeyColor& rhsKeyColor );
	int Allocate_KeyColor( const KeyColor& rhsKeyColor );

public:

	/**************************************************************
	 *           House Keeping
	 **************************************************************/
	KeyColor();
	virtual ~KeyColor();

	// Copy Constructor
	KeyColor( const KeyColor& rhsKeyColor );

	// Assignment Operator
	KeyColor& operator=( const KeyColor& rhsKeyColor );


	/**************************************************************
	 *           Member Functions
	 **************************************************************/
	bool operator==( const KeyColor& rhsKeyColor) const;
	string GetString() const;

};

class KeyColorCompare{
public:
	bool operator()( const KeyColor& C1, const KeyColor& C2 ) const
	{

		const Vec3d C1Vec = C1.getRgb();
		const Vec3d C2Vec = C2.getRgb();

		bool decision = true;

		if( C1Vec.val[0] == C2Vec.val[0] ) // Check if Red Channels Match
		{
			if(  C1Vec.val[1] == C2Vec.val[1] ) // Check if the Green Channels match
			{
				if(  C1Vec.val[2] == C2Vec.val[2] ) // Check if the Blue Channels match
				{
					decision =  C1Vec.val[2] < C2Vec.val[2];
				}
			}
			else
			{
				decision =  C1Vec.val[1] < C2Vec.val[1];
			}
		}
		else
		{
			decision =  C1Vec.val[0] < C2Vec.val[0];
		}


		return decision;

	}
};

#endif /* KEYCOLOR_H_ */
