/*
 * WritePoseFeature.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: hrushi
 */

#include "WritePoseFeature.h"


/*****************************************************
 * Function	: WritePoseFeature
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Default Constructor
 * Return	:
 *****************************************************/
WritePoseFeature::WritePoseFeature( const string sPath):WriteFile(sPath)
{
	if( fs::exists(sPath) )
	{
		WriteBanner();
	}

}

/*****************************************************
 * Function	: WritePoseFeature
 * Date		: Sep 24, 2013
 * Author	: hrushi
 * Comments	: Used for building map(s) of this class.
 * Args		: No Nothing Constructor
 * Return	:
 *****************************************************/
WritePoseFeature::WritePoseFeature():WriteFile("")
{

}



/*****************************************************
 * Function	: WritePoseFeature
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Default destructor
 * Return	:
 *****************************************************/
WritePoseFeature::~WritePoseFeature()
{

}

/*****************************************************
 * Function	: WritePoseFeature Copy Constructor
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
WritePoseFeature::WritePoseFeature(const WritePoseFeature& rhsWritePoseFeature ):WriteFile(rhsWritePoseFeature)
{
	Allocate( rhsWritePoseFeature );
	Copy( rhsWritePoseFeature );

}

/*****************************************************
 * Function	: operator =
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
WritePoseFeature& WritePoseFeature:: operator=( const WritePoseFeature& rhsWritePoseFeature )
{
	// Copying the parent class member variables.
	WriteFile::operator =(rhsWritePoseFeature);

	Allocate( rhsWritePoseFeature );
	Copy( rhsWritePoseFeature );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WritePoseFeature::Allocate( const WritePoseFeature& rhs )
{
	WriteQue.resize( rhs.WriteQue.size() );

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Apr 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int WritePoseFeature::Copy( const WritePoseFeature& rhs )
{

	for(unsigned int i = 0; i < rhs.WriteQue.size(); i++)
	{
		WriteQue.at(i) = rhs.WriteQue.at(i);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Writes the File Banner
 * Arguments	:
 *******************************************************************/
int WritePoseFeature::WriteBanner( )
{

	std::stringstream ss;

	ss << "# " << STARS << STARS ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Pose Feature File " ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Description: Contains the Angles for Arms. The first column is the label, and the following columns \
			 are the Shoulder, Elbow, Wrist and Carry angles";
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	Time T;
	ss << "# Last Updated On : " << T.GetCurrentTime() ;
	WriteLine(ss.str() );

	ss << "# Label " << NO_CARRIED_OBJECT << " " << ": No carried object on this image ";
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column info" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 1: Contour Number Number" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 2: Carry Angle" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# Column 3: Carry Dist" ;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	ss << "# " << STARS << STARS;
	WriteLine(ss.str() );
	ss.clear();
	ss.str("");

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteOut
 * Return Type 	: int
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Writes the Pose Features to the File
 * Arguments	:
 *******************************************************************/
int WritePoseFeature::WriteOut( )
{
	for(unsigned int i = 0; i < WriteQue.size(); i++ )
	{
		WriteLine( WriteQue.at(i));
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: AddToWriteQue
 * Return Type 	: int
 * Created On	: Apr 10, 2013
 * Created By 	: hrushi
 * Comments		: Adds the pose featues to the Write Que
 * Arguments	: int Label, const PoseData& P
 *******************************************************************/
int WritePoseFeature::AddToWriteQue( const vector<double>& Feature )
{

	std::stringstream ss;
	ss << Feature;
	string TempLine = ss.str();

	WriteQue.push_back(TempLine);

	return EXIT_SUCCESS;
}

