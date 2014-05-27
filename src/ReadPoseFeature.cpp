/*
 * ReadPoseFeature.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: hrushi
 */

#include "ReadPoseFeature.h"


ReadPoseFeature::ReadPoseFeature( const fs::path sPath):ReadFile( sPath )
{

}

ReadPoseFeature::~ReadPoseFeature()
{


}

/*****************************************************
 * Function	: ReadPoseFeature Copy Constructor
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
ReadPoseFeature::ReadPoseFeature(const ReadPoseFeature& rhsReadPoseFeature ):ReadFile( rhsReadPoseFeature )
{
	Allocate( rhsReadPoseFeature );
	Copy( rhsReadPoseFeature );

}

/*****************************************************
 * Function	: operator =
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
ReadPoseFeature& ReadPoseFeature:: operator=( const ReadPoseFeature& rhsReadPoseFeature )
{
	Allocate( rhsReadPoseFeature );
	Copy( rhsReadPoseFeature );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ReadPoseFeature::Allocate( const ReadPoseFeature& rhsReadPoseFeature )
{

	m_vPoseFeature.resize( rhsReadPoseFeature.m_vPoseFeature.size() );

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Apr 17, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int ReadPoseFeature::Copy( const ReadPoseFeature& rhsReadPoseFeature )
{

	for(unsigned int i = 0; i < rhsReadPoseFeature.m_vPoseFeature.size(); i++ )
	{
		m_vPoseFeature.at(i) = rhsReadPoseFeature.m_vPoseFeature.at(i);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ReadIn
 * Return Type 	: int
 * Created On	: Apr 17, 2013
 * Created By 	: hrushi
 * Comments		: Reads in the file
 * Arguments	:
 *******************************************************************/
int ReadPoseFeature::ReadIn( )
{
	string line;

	while(isGood() )
	{

		line = GetLine();
		const string NewWhiteSpace = StringOp<string>::GetNonWhiteSpace(0, line);

		if( NewWhiteSpace.length() == 0 )
		{
			continue;
		}

		char FirstChar = NewWhiteSpace.at(0);

		if( FirstChar == '#' )
		{
			cout << line << endl;
			continue;
		}
		else if( isGood() )
		{

			PoseFeature PF;
			PF.ReadFromLine(line);
			m_vPoseFeature.push_back( PF );
		}
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: isCarryPose
 * Return Type 	: bool
 * Created On	: Apr 17, 2013
 * Created By 	: hrushi
 * Comments		: Checks the look up table and tells if the current pose matches, with the earlier carry poses seen
 * Arguments	:
 *******************************************************************/
bool ReadPoseFeature::isCarryPose( ) const
{

	static PoseFile PF( m_FilePath );
	PF.ReadIn();

	return EXIT_SUCCESS;

}


/*******************************************************************
 * Function Name: GetMap_String_PoseFeature
 * Return Type 	: const std::map<string, PoseFeature>
 * Created On	: Oct 20, 2013
 * Created By 	: hrushi
 * Comments		: Given the list of all pose file feature names, it will
 * create a map, and will return a map keyed with the given file names to the class of pose features
 * Arguments	: const vector<string> PoseFeatureFileList
 *******************************************************************/
mp_PoseFeature ReadPoseFeature::GetMap_String_PoseFeature( const string TrainFolderPath, const vector<string> PoseFeatureFileList)
{
	mp_PoseFeature RetMap;

	//Create a pair, which filename as a Key
	// and PoseFeature() as a empty standard constructor;
	vector< PoseFeature > Temp;

	for(auto& str: ALL_POSE_FEATURE_FILES )
	{
		RetMap.insert(std::pair<string, vector<PoseFeature> >( str, Temp ));
	}

	for(auto& Mp : RetMap)
	{
		fs::path Feature_Path = TrainFolderPath + Mp.first;
		cout << "Feature_Path: " << Feature_Path << endl;

		ReadPoseFeature oReadPoseFeature( Feature_Path );
		oReadPoseFeature.ReadIn();

		Mp.second = oReadPoseFeature.GetVectorOfPoseFeatures();

	}

	return RetMap;
}

