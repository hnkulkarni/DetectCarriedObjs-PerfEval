/*
 * Features.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: hrushi
 */

#include "Features.h"


/**********************************************************************
 * Function Name: Features
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Constructor
 * Args			:
 **********************************************************************/
Features::Features(const Args& args, const unsigned int Mode)
{

	Open(args, Mode);

	if(Mode == WRITE_MODE)
	{
		bWBanner = true;
	}
	else
	{
		bWBanner = false;
	}


}

/*******************************************************************
 * Function Name: Open
 * Return Type 	: int
 * Created On	: Feb 26, 2013
 * Created By 	: hrushi
 * Comments		: Opens the Feature File
 * Arguments	: const Args& args, const unsigned int Mode
 *******************************************************************/
int Features::Open( const Args& args, const unsigned int Mode)
{

	FilePath = args.GetSearchFolderPath() + APPEARANCE_FEATURES;

	if( Mode == WRITE_MODE )
	{
		fPtr.open( FilePath.string().c_str(), fstream::out );
		bWBanner = true;
	}
	else
	{
		if( fs::exists( FilePath ))
		{
			cout << "Feature File Already Exist " << endl;
			bWBanner = false; // Since the file is already present, we should not populate it with the background
		}

		fPtr.open(FilePath.string().c_str() , fstream::in | fstream::out | fstream::app);

	}

	if( !fPtr.is_open() )
	{
		cerr << "Cannot Open Feature File "<< FilePath.string() << endl;
		exit(ERR_CANNOT_OPEN_FILE);
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Features
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Destructor
 * Args			:
 * ToDo			:
 **********************************************************************/
Features::~Features()
{
	Close();
}


/*******************************************************************
 * Function Name: Close
 * Return Type 	: int
 * Created On	: Feb 26, 2013
 * Created By 	: hrushi
 * Comments		: Closes the Feature File
 * Arguments	: const Args& args
 *******************************************************************/
int Features::Close( )
{
	if( fPtr.is_open() )
	{
		cout << "Closing Features File " << endl;
		fPtr.close();
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Features
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
Features::Features( const Features& rhsFeatures )
{
	Allocate_Features( rhsFeatures );
	Copy_Features( rhsFeatures );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
Features& Features :: operator=( const Features & rhsFeatures )
{
	Allocate_Features( rhsFeatures );
	Copy_Features( rhsFeatures );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Features
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int Features:: Copy_Features(  const Features & rhsFeatures  )
{

	FilePath = rhsFeatures.FilePath;
	ImgFeature = rhsFeatures.ImgFeature;
	bWBanner   = rhsFeatures.bWBanner;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_Features
 * Date 		: Feb 11, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int Features:: Allocate_Features(  const Features & rhsFeatures  )
{

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Add
 * Return Type 	: int
 * Created On	: Feb 11, 2013
 * Created By 	: hrushi
 * Comments		: Adds features to the feature map
 * Arguments	: const fs::path& ImPath, const ColorImg& ProbeImg, const GrayImg& BkImg, const Args& args
 *******************************************************************/
int Features::Add( const fs::path& ImPath, const int CurrentLabel, const ContourMap& Segments, const Args& args )
{
	Write(args, CurrentLabel, Segments);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Write
 * Return Type 	: int
 * Created On	: Feb 11, 2013
 * Created By 	: hrushi
 * Comments		: Writes the features for the given image into the file.
 * 					The Image name and the features are taken from the
 * 					class member variable map
 * Arguments	:
 *******************************************************************/
int Features::Write( const Args& args, const int CurrentLabel, const ContourMap& Segments )
{
	if(bWBanner)
	{
		WriteBanner();
		bWBanner = false;
	}

	WriteFeatures(args,CurrentLabel, Segments);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteFeatures
 * Return Type 	: int
 * Created On	: Feb 25, 2013
 * Created By 	: hrushi
 * Comments		: Writes the features to the list
 * Arguments	: const Args& args, const ContourMap& Segments
 *******************************************************************/
int Features::WriteFeatures( const Args& args, const int CurrentLabel, const ContourMap& Segments)
{
	ElevenSpaceHist Hst;
	int CntrNum;

	for( std::map< unsigned int, Contour >::const_iterator itr = Segments.AllContourMap.begin(); itr != Segments.AllContourMap.end(); itr++ )
	{
		Hst = itr->second.GetElSpcHist();

		CntrNum = itr->second.GetLabel();

			if(CntrNum == CurrentLabel )
			{
				fPtr << CurrentLabel << " , ";
				fPtr << Hst << endl;
			}

		/**************************************************************
		 *           Get back to this, still not able to figure out
		 *           how to label only the background objects
		 **************************************************************/
		 /* else if( itr->second.GetisBackgroundFlag() )
			{
				fPtr << NO_CARRIED_OBJECT << " , ";
				fPtr << Hst << endl;
			}
			*/


	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: WriteBanner
 * Return Type 	: int
 * Created On	: Feb 11, 2013
 * Created By 	: hrushi
 * Comments		: Writes the banner for the given file
 * Arguments	:
 *******************************************************************/
int Features::WriteBanner( )
{
	// Set the pointer to the starting of the file
	fPtr.seekp(0, std::ios::beg);

	Time T;
	fPtr << "# " << STARS << STARS << endl;
	fPtr << "# Features File " << endl;
	fPtr << "# Description: Contains all the features for the given image " << endl;
	fPtr << "# Created On : " << T.GetCurrentTime() << endl;
	fPtr << "# " << STARS << STARS << endl;
	return EXIT_SUCCESS;

}

/*******************************************************************
 * Function Name: Read
 * Return Type 	: int
 * Created On	: Feb 26, 2013
 * Created By 	: hrushi
 * Comments		: Reads the feature file into the memory
 * Arguments	: const Args& args
 *******************************************************************/
int Features::Read( const Args& args)
{
	string line;
	unsigned int LineCount = 0;

	if( fPtr.is_open() )
	{
		while(fPtr.good())
		{
			getline(fPtr, line);
			LineCount++;

			try
			{
				ReadLine(args, line);
			}
			catch( int Err )
			{
				cerr << "Check Line Number: " << LineCount << endl;
				throw Err;
			}
		}

		ZMUL(args);
	}
	else
	{
		cerr << "Cannot read Feature File " << endl;
		exit(ERR_CANNOT_OPEN_FILE);
	}

	if( ImgFeature.size() == 0 )
	{
		cerr << "No feature read from " << FilePath.string() << endl;
		throw ERR_CANNOT_READ_VALUE;
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ZMUL
 * Return Type 	: int
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Zero Mean and Unit Length
 * Arguments	: const Args& args
 *******************************************************************/
int Features::ZMUL( const Args& args)
{
	for(vector<CntrFeature>::iterator itr = ImgFeature.begin(); itr != ImgFeature.end(); itr++)
	{
		itr->ZMUL(args);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ReadLine
 * Return Type 	: int
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Reads the feature from the line
 * Arguments	: const Args& args
 *******************************************************************/
int Features::ReadLine( const Args& args, string line)
{

	StringOp<string> oStr;
	CntrFeature oCntrFeature;
	string NonWhiteSpace;
	NonWhiteSpace = oStr.GetNonWhiteSpace(0, line);

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

			try
			{
				std::istringstream iss;
				iss.str(line);
				iss >> oCntrFeature.Label;
				iss >> oCntrFeature.Hst;

				ImgFeature.push_back(oCntrFeature);
			}
			catch(  int Err )
			{
				cerr << "Error Reading Feature File " << FilePath.string() << endl;
				throw Err;
			}
		}
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: NearestNeighbour
 * Return Type 	: int
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Returns the label of the nearest neighbour
 * Arguments	: const Histogram& Hst
 *******************************************************************/
int Features::NearestNeighbour( const ElevenSpaceHist& Hst, unsigned int K) const
{

	vector< pair<double, int> > AllDist = GetAllDistances(Hst);

	int Decision = MakeWeightedDecision( AllDist, K );

	return Decision;
}


/*******************************************************************
 * Function Name: MakeWeightedDecision
 * Return Type 	: int
 * Created On	: May 27, 2013
 * Created By 	: hrushi
 * Comments		: Uses the SORTED pairs, makes a weighed decision
 * Arguments	: const vector< pair<double, int> > & AllDist ) const
 *******************************************************************/
int Features::MakeWeightedDecision( const vector< pair<double, int> > & AllDist, unsigned int K )  const
{
	int Decision;
	vector< pair<double, int> > SortDists;
	SortDists.resize(  AllDist.size() );
	SortDists = SortByDistances(AllDist);

	double MinDist(0), MaxDist(0);
	MinDist = SortDists.at(0).first;
	MaxDist = SortDists.at(K).first; // K - 1 because, the index is from 0

	double Vote = 0;

	for( unsigned int i = 0; i < K; i++ )
	{
		Vote += EditVote( SortDists.at(i).second, SortDists.at(i).first, MinDist, MaxDist );
		cout << "Vote " << std::setw(8) << std::setprecision(5) << Vote << " : ";
		cout  << std::setw(8) << std::setprecision(5) << SortDists.at(i).first << " : " << SortDists.at(i).second << endl;
	}

	(Vote > 0)? Decision = 1 : Decision = 0;

	return Decision;
}

/*******************************************************************
 * Function Name: EditVote
 * Return Type 	: double
 * Created On	: May 27, 2013
 * Created By 	: hrushi
 * Comments		: Returns a value by which the vote should be edited;
 * Arguments	: int Label, double SampleDist, double MinDist, double MaxDist
 *******************************************************************/
double Features::EditVote( int SampleLabel, double SampleDist, double MinDist, double MaxDist ) const
{
	double EditVal(0);
	int Flag = 0;

	(SampleLabel > 0 )? Flag =1 : Flag = -1; // Set the Flag as 1 if the Object is Carry, else as -1;

	EditVal = ( MaxDist - SampleDist ) / ( MaxDist - MinDist );
	EditVal *= Flag;

	return EditVal;
}
/*******************************************************************
 * Function Name: SortByDistances
 * Return Type 	: vector< pair<double, int> >
 * Created On	: May 27, 2013
 * Created By 	: hrushi
 * Comments		: Sorts the list of pairs of distances and labels according to distances
 * Arguments	: const vector< pair< double, int> >& AllDistPairs
 *******************************************************************/
vector< pair<double, int> > Features::SortByDistances( const vector< pair< double, int> >& AllDistPairs ) const
{
	vector< pair<double, int> > SortDists;
	SortDists.resize(  AllDistPairs.size() );
	SortDists = AllDistPairs;

	std::sort(SortDists.begin(), SortDists.end(), CompairPair);

	return SortDists;
}

/*******************************************************************
 * Function Name: Functor for comparing the pairs
 * Return Type 	: bool
 * Created On	: May 27, 2013
 * Created By 	: hrushi
 * Comments		: Comparairs the two pairs of elements, according to the distance.
 * Arguments		: const pair<double,int>&, const pair<double,int>&
 *******************************************************************/
bool CompairPair( const pair<double, int>& lhs, const pair<double, int>& rhs )
{
	return lhs.first < rhs.first;
}

/*******************************************************************
 * Function Name: GetAllDistances
 * Return Type 	: vector< pair<double, int> >
 * Created On	: May 27, 2013
 * Created By 	: hrushi
 * Comments		: Get distances from every point in the cloud
 * Arguments	: const ElevenSpaceHist& ElHist
 *******************************************************************/
vector< pair<double, int> > Features::GetAllDistances( const ElevenSpaceHist& ElHist) const
{
	vector< pair<double, int> > AllDistandLabel;
	pair<double, int> NgnTuple;

	VectorOp<double> vOP;
	double Dist 	= 0;
	int Label 		= 0;

	for(unsigned int i = 0; i < ImgFeature.size(); i++)
	{
		Dist = vOP.Dist(ImgFeature.at(i).Hst.m_Hist, ElHist.m_Hist );
		Label 	= ImgFeature.at(i).Label;

		//This red line is because eclipse CDT cannot support c++ 11 standard
		NgnTuple = std::make_pair(  Dist, Label );
		AllDistandLabel.push_back( NgnTuple );
	}

	return AllDistandLabel;
}
