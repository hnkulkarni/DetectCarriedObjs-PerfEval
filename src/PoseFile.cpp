/*
 * PoseFile.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: hrushi
 */

#include "PoseFile.h"

PoseFile::PoseFile(const fs::path sPath): ReadFile(sPath)
{

	ReadIn();
}

PoseFile::~PoseFile()
{

}

/**********************************************************************
 * Function Name: PoseFile
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
PoseFile::PoseFile( const PoseFile& rhsPoseFile ): ReadFile( rhsPoseFile )
{
	Allocate_PoseFile( rhsPoseFile );
	Copy_PoseFile( rhsPoseFile );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
PoseFile& PoseFile :: operator=( const PoseFile & rhsPoseFile )
{
	Allocate_PoseFile( rhsPoseFile );
	Copy_PoseFile( rhsPoseFile );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_PoseFile
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int PoseFile:: Copy_PoseFile(  const PoseFile & rhsPoseFile  )
{
	m_Pose = rhsPoseFile.m_Pose;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_PoseFile
 * Date 		: Apr 3, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int PoseFile:: Allocate_PoseFile(  const PoseFile & rhsPoseFile  )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadIn
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Reads in the elements from the PoseFile or the Box file into Boxes
 * Arguments	:
 *******************************************************************/
int PoseFile::ReadIn( )
{

	cout << "Reading Pose File " << m_FilePath << endl;

	string line;

	unsigned int uiLineCount  = 0;

	while( isGood() )
	{
		line = GetLine();

		try
		{
			ReadLine(line, uiLineCount);

			uiLineCount++;
		}
		catch( unsigned int err )
		{
			throw( err );
		}
	}


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadLine
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Reads a line from the Pose File
 * Arguments	: const string line
 *******************************************************************/
int PoseFile::ReadLine( const string line,  const unsigned int uiLineCnt  )
{

	StringOp<string> oStr;
	string NonWhiteSpace;
	NonWhiteSpace = oStr.GetNonWhiteSpace(0, line);

	Boxes TempBox;

	if(NonWhiteSpace.size() > 0 )
		{
			char FirstChar = NonWhiteSpace.at(0);

			if( FirstChar == '#' )
			{
				cout << line << endl;
				return EXIT_SUCCESS;
			}
			else
			{
				std::istringstream iss;
				iss.str(line);

				try
				{
					iss >> TempBox;

					char BxClr = PartColor[ uiLineCnt ];
					m_Pose.Add(  BxClr, TempBox );


				}
				catch(unsigned int err )
				{
					cerr << "Error Reading Line Pose File " << m_FilePath << endl;
					throw err;
				}
			}
		}


	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetBoxFilePath
 * Return Type 	: const fs::path
 * Created On	: Jul 21, 2013
 * Created By 	: hrushi
 * Comments		: Returns the box file location for the given image path
 * Arguments	: const fs::path ProbeImgPath
 *******************************************************************/
const fs::path PoseFile::GetBoxFilePath( const fs::path ImgPath )
{
	const fs::path BoxFilePath = 	ImgPath.parent_path().string() + "/Boxes/" + ImgPath.stem().string() + ".txt";

	return BoxFilePath;
}


/*******************************************************************
 * Function Name: AddPoseFeatures
 * Return Type 	: int
 * Created On	: Oct 1, 2013
 * Created By 	: hrushi
 * Comments		: Add Pose features to the WriteFile Class
 * Arguments	: const ColorImg& WorkImg, const ContourMap& Segments, Map_WrtPoseFeature& Carry, Map_WrtPoseFeature& No_Carry
 *******************************************************************/
int PoseFile::AddPoseFeatures( const ColorImg& WorkImg, const ContourMap& Segments, int Label, const vector<char> vPartKey, Map_WrtPoseFeature& Carry, Map_WrtPoseFeature& No_Carry, const Args& args ) const
{
	const fs::path ImagePath = WorkImg.GetImagePath();
	fs::path SaveImgDir = ImagePath.parent_path().string() + "/PoseFeature/";

	for( unsigned int iCntrNum = 1; iCntrNum < Segments.AllContourMap.size(); iCntrNum++ )
	{
		bool isCarry = ( iCntrNum == (unsigned int)Label );

		Contour Ctr = Segments.AllContourMap.at( iCntrNum);
		ColorImg TempImg = WorkImg;

		std::stringstream ssLgdImgPath;
		ssLgdImgPath.clear();
		ssLgdImgPath.str("");
		ssLgdImgPath << SaveImgDir.string() << ImagePath.stem().string() << "_" << iCntrNum << "_";

		for(auto PartKey: vPartKey)
		{
			vector<double> PoseFeature = m_Pose.GetPoseFeature(TempImg, isCarry, PartKey, Ctr, args);

			string ArmName = (PartKey == 'c')? "R" : "L";
			const string LegStr = m_Pose.GetLegendString(ArmName, PoseFeature );
			ssLgdImgPath << "_" << ArmName << "_a_" << (int)PoseFeature.at(0) << "_d_" << (int)PoseFeature.at(1);

			cv::Mat OverlayLgd = TempImg.Legends( LegStr, COLOR_WHITE, COLOR_RED, BOTTOM_LEFT).clone();
			TempImg.SetImage(OverlayLgd);

			if(Label != (int) BACKGROUND_LABEL)
			{
				if( iCntrNum == (unsigned int)Label )
				{
					Carry.at(PartKey)->AddToWriteQue(PoseFeature);
				}
				else if ((Label >= NO_CARRIED_OBJECT) )
				{
					No_Carry.at(PartKey)->AddToWriteQue(PoseFeature);
				}
			}

		}

		ssLgdImgPath << ".png";
		TempImg.Write(ssLgdImgPath.str());

	}


	return EXIT_SUCCESS;
}
