/*
 * KeyColor.cpp
 *
 *  Created on: Mar 12, 2013
 *      Author: hrushi
 */

#include "KeyColor.h"

KeyColor::KeyColor() {
	// TODO Auto-generated constructor stub

}

KeyColor::~KeyColor() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: KeyColor
 * Date 		: Mar 12, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
KeyColor::KeyColor( const KeyColor& rhsKeyColor ):Color(rhsKeyColor)
{
	Allocate_KeyColor( rhsKeyColor );
	Copy_KeyColor( rhsKeyColor );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Mar 12, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
KeyColor& KeyColor :: operator=( const KeyColor & rhsKeyColor )
{
	Allocate_KeyColor( rhsKeyColor );
	Copy_KeyColor( rhsKeyColor );

	return *this;
}


/*******************************************************************
 * Function Name: operator==
 * Return Type 	: bool
 * Created On	: Mar 13, 2013
 * Created By 	: hrushi
 * Comments		: Checks if the two KeyColors are equal
 * Arguments	: const KeyColor& rhsKeyColor
 *******************************************************************/
bool KeyColor::operator==( const KeyColor& rhsKeyColor) const
{
	bool decision = true;

	for( unsigned int i = 0; i < 3; i++ )
	{
		if( RGB.val[i] != rhsKeyColor.RGB.val[i] )
		{
			decision = false;
			break;
		}
	}

	return decision;
}


/**********************************************************************
 * Function Name: Copy_KeyColor
 * Date 		: Mar 12, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int KeyColor:: Copy_KeyColor(  const KeyColor & rhsKeyColor  )
{

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_KeyColor
 * Date 		: Mar 12, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int KeyColor:: Allocate_KeyColor(  const KeyColor & rhsKeyColor  )
{

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: GetString
 * Return Type 	: string
 * Created On	: Mar 15, 2013
 * Created By 	: hrushi
 * Comments		: Returns the string equivalent of the KeyColor. This has been done because it was very difficult for me to use this Color as a key to the map
 * Arguments	:
 *******************************************************************/
string KeyColor::GetString( ) const
{
	string EqString;

	std::stringstream ss;

	for(unsigned int i = 0; i < 3; i++ )
	{
		ss << RGB.val[i] << " ";
	}

	EqString = ss.str();

	return EqString;
}



