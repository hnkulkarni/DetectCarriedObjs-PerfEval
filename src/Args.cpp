/*
 * Args.cpp
 *
 *  Created on: Jan 30, 2013
 *      Author: hrushi
 */

#include "Args.h"

/**********************************************************************
 * Function Name: Args
 * Date 		: Jan 30, 2013
 * Author		: hrushi
 * Comments		: Constructor
 *
 *   Please note that in the arguments section, there should be no spage between the
	   argument longopts and shortopts.
	   Example, "input_path, I" will NOT work
	            "input_path,I" will work


	 For the argument "input_folder_name" the argument "track" is expected
	 For the argument "mask_folder_name" the argument "mask" is expected

	 Use the following tree diagram for reference.

  --Dataset_Folder
  	|-- Neg
	|   |-- Folder1
	|   |   |-- mask  (contains the foreground mask)
	|   |   `-- track (contains the image chip)
	|   |-- Folder2
	|   |   |-- mask
	|   |   `-- track
	|   `-- Folder3
	|       |-- mask
	|       `-- track
	`-- Pos
	    |-- Folder1
	    |   |-- mask
	    |   `-- track
	    |-- Folder2
	    |   |-- mask
	    |   `-- track
	    `-- Folder3
	        |-- mask
	        `-- track


 * Args			:
 **********************************************************************/
Args::Args( )
{

	Init();
	AddArgs();

}

/*******************************************************************
 * Function Name: Init
 * Return Type 	: int
 * Created On	: Nov 21, 2013
 * Created By 	: hrushi
 * Comments		: Initialize all variables
 * Arguments	:
 *******************************************************************/
int Args::Init( )
{

	//---------- Init Primitive Datatypes ---------- //
	m_RunMode 			= -1;
	m_CopyMaskImages	= false;
	m_Versbose			= false;
	m_SkipExisting		= false;
	m_bLabelNow			= false;
	m_UpdateMode		= UPDATE_MODE_ALL; // Un-initialized
	m_bQuiet			= false;
	m_LabelGroundTruth	= false;
	m_SkipIfNoPose		= false;
	m_UsePoseOverlap	= false;
	m_UseGndTruthLabels	= false;

	//---------- Init for Strings ---------- //
	m_LabelFileName   	= LABEL_FILENAME_STR;
	m_ProgramPath 		= "";
	m_InputPath 		= "";
	m_MaskPath 			= "";
	m_TrackFolderName 	= "";
	m_MaskFolderName 	= "";
	m_RunFolderPath 	= "";
	m_TrainingDataFolderPath 	= "";
	m_DetectionMode 		= "";


	//---------- Unsigned integers ---------- //
	m_uiSkipWidth		= 0;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function Name: Args
 * Date 		: Jan 30, 2013
 * Author		: hrushi
 * Comments		: Destructor
 * Args			:
 **********************************************************************/
Args::~Args()
{
	// TODO Auto-generated destructor stub
}

/**********************************************************************
 * Function Name: Args
 * Date 		: Jan 30, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 **********************************************************************/
Args::Args( const Args& rhsArgs )
{
	Allocate_Args( rhsArgs );
	Copy_Args( rhsArgs );
}


/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 30, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
Args& Args :: operator=( const Args & rhsArgs )
{
	Allocate_Args( rhsArgs );
	Copy_Args( rhsArgs );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_Args
 * Date 		: Jan 30, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int Args:: Copy_Args(  const Args & rhsArgs  )
{
	m_InputPath 		= rhsArgs.m_InputPath;
	m_MaskPath 			= rhsArgs.m_MaskPath;
	m_TrackFolderName 	= rhsArgs.m_TrackFolderName;
	m_MaskFolderName 	= rhsArgs.m_MaskFolderName;
	m_RunFolderPath 	= rhsArgs.m_RunFolderPath;
	m_RunMode	 		= rhsArgs.m_RunMode;
	m_CopyMaskImages  	= rhsArgs.m_CopyMaskImages;
	m_Versbose			= rhsArgs.m_Versbose;
	m_ProgramPath 		= rhsArgs.m_ProgramPath;
	m_SkipExisting		= rhsArgs.m_SkipExisting;
	m_bQuiet			= rhsArgs.m_bQuiet;
	m_LabelGroundTruth 	= rhsArgs.m_LabelGroundTruth;
	m_LabelFileName 	= rhsArgs.m_LabelFileName;
	m_TrainingDataFolderPath	= rhsArgs.m_TrainingDataFolderPath;
	m_DetectionMode		= rhsArgs.m_DetectionMode;
	m_UpdateMode		= rhsArgs.m_UpdateMode;
	m_bLabelNow		 	= rhsArgs.m_bLabelNow;
	m_uiSkipWidth		= rhsArgs.m_uiSkipWidth;
	m_uiSkipHeight		= rhsArgs.m_uiSkipHeight;
	m_SkipIfNoPose		= rhsArgs.m_SkipIfNoPose;
	m_UsePoseOverlap	= rhsArgs.m_UsePoseOverlap;
	m_UseGndTruthLabels	= rhsArgs.m_UseGndTruthLabels;

	return EXIT_SUCCESS;
}





/**********************************************************************
 * Function Name: Allocate_Args
 * Date 		: Jan 30, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int Args:: Allocate_Args(  const Args & rhsArgs  )
{

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: AddArgs
 * Return Type 	: int
 * Created On	: Feb 3, 2013
 * Created By 	: hrushi
 * Comments		: Adds arguments to the list
 * Arguments	:
 *******************************************************************/
int Args::AddArgs( )
{
	m_desc.add_options()
					("help,h", 				"produce help message")
					("verbose,v", 			"verbose output while running")
					("single_image,s", 		"Run on a single pair of foreground track and mask image")
					("multiple_images,x", 	"Flag to check if we need to run on multiple image")
					("demo",				"Does not require Ground Truth Data")
					("mode", po::value<string>(), "Input the mode of detection: pose, location" )

					("input_run_folder,r",  po::value<string>(), "Give the parent database folder, which has all the images")
					("track_folder_name,t", po::value<string>(), "This is the common folder name which has all the track chips inside the main dataset folder")
					("mask_folder_name,f",  po::value<string>(), "This is the common folder name, which has all the mask chips inside the main dataset folder")

					("input_path,i",        po::value< string >(), "Input image path or folder path. If a folder path is give, then all the images in this folder will be parsed.")
					("mask_path,m",         po::value< string >(), "Path to the Mask Image or Folder. If a folder path is give, then all the images in this folder will be parsed.")

					("copy_mask,u", 		"Flag to tell if you want to copy the mask chips from the main Vision Folder.")

					("label_images,l", 		"Recusrively label all the images in the folder" )
					("label_file_name,n", 	"Name of the Label File. This will be created in Run_Folder")
					("skip_existing,k", 	"Skips Files that are already Labelled")
					("later", 				"Writes all the merged images for you to label later on")
					("now", 				"Asks the user to label images right now")
					("ground_truth", 		"Label Ground Truth for the images in the given path")
					("useGroundTruth",		"Use Ground Truth for Labeling")

					("update_features,f", 	"Updates the features, for the given label")
					("carry_type", 			"Updates the Carry type")
					("person_loc",			"Update the Location of Person")
					("pose,p", 				"Updates Pose Features")
					("contour", 			"Updates Contour Features")
					("all",					"Updates All Features")
					("prior_prob", 			"Update Prior Probabilities")
					("loc_probability", 	"Builds and stores the location probability image")
					("shape", 				"Update Shape Features")
					("appearance", 		    "Update Appearance Feature" )
					("skip_width",			po::value<UINT>(), "Only Images above this width will be used")
					("skip_height", 		po::value<UINT>(), "Only Images above this height will be used")
					("skip_IfNoPose", 		"Skip the image if corresponding pose file is not present")
					("usePoseOverlap", 		"Select if you want to skip regions based on the amount of overlap with the predicted pose")

					("training_data_path" , po::value<string>(), "Input the folder path which contains all the training data")
					("quiet", 				"Quiet Output")


					//(" ADD NEW OPTIONS OVER HERE Before the Semi Colon ")
					;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: parse
 * Return Type 	: int
 * Created On	: Dec 31, 2012
 * Created By 	: hrushi
 * Comments		: Prints the help comments, if the program is called
 * 					without arguments.
 * TODo			:
 *******************************************************************/
int Args::parse( int argc, char* argv[] )
{
	ReadProgramPath(argc, argv);
	ArgCheckNParse(argc, argv);
	ArgUsage();

	return 0;
}

/*******************************************************************
 * Function Name: ReadProgramPath
 * Return Type 	: int
 * Created On	: Feb 23, 2013
 * Created By 	: hrushi
 * Comments		: Reads the program path. This is the zero-th argument
 * Arguments	: int argc, char* argv[]
 *******************************************************************/
int Args::ReadProgramPath(  int argc, char* argv[])
{
	string ProgramPath( argv[0]);
	m_ProgramPath = ProgramPath;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ArgUsage
 * Return Type 	: int
 * Created On	: Feb 9, 2013
 * Created By 	: hrushi
 * Comments		: Runs the usage of the arguments
 * Arguments	:
 *******************************************************************/
int Args::ArgUsage( )
{
	try
	{
		OptionalArgs();

		ModeArgs();

	} //TRY-END
	catch(const boost::bad_any_cast& ex )
	{
		cerr << "Error with reading arguments. " << endl;
		help();

		cerr << ex.what() << endl;
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ModeArgs
 * Return Type 	: int
 * Created On	: Feb 9, 2013
 * Created By 	: hrushi
 * Comments		: Parse mode specific arguments
 * Arguments	:
 *******************************************************************/
int Args::ModeArgs( )
{
	// -------- Usage Modes --------//
	if( m_vm.count("multiple_images") )
	{
		OptionMultipleImages();
	}
	else if ( m_vm.count("single_image") )
	{
		OptionSingleImage();
	}
	else if( m_vm.count("copy_mask") )
	{
		m_CopyMaskImages = true;

		OptionCopyMaskImages();
	}
	else if( m_vm.count("label_images") )
	{
		OptionLabelImages();
	}
	else if( m_vm.count("update_features"))
	{
		OptionUpdateFeatures();
	}

	if( m_vm.count("demo"))
	{
		OptionDemo();
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: OptionUpdateFeatures
 * Return Type 	: int
 * Created On	: Apr 3, 2013
 * Created By 	: hrushi
 * Comments		: Reads the options required for updating the feature list
 * Arguments	:
 *******************************************************************/
int Args::OptionUpdateFeatures( )
{

	if(m_vm.count("pose") )
	{
		m_UpdateMode = UPDATE_MODE_POSE;
	}

	if( m_vm.count("carry_type") )
	{
		m_UpdateMode = UPDATE_MODE_CARRY_TYPE;
	}

	else if( m_vm.count("contour") )
	{
		m_UpdateMode = UPDATE_MODE_CONTOUR;
	}
	else if( m_vm.count("loc_probability"))
	{
		m_UpdateMode = UPDATE_LOC_CARRY_PROB;
	}
	else if( m_vm.count("person_loc"))
	{
		m_UpdateMode = UPDATE_LOC_PERSON_PROB;
	}
	else if( m_vm.count("prior_prob") )
	{
		m_UpdateMode = UPDATE_PRIOR_PROBS;
	}
	else if( m_vm.count("shape") )
	{
		m_UpdateMode = UPDATE_MODE_SHAPE;
	}
	else if( m_vm.count("appearance"))
	{
		m_UpdateMode = UPDATE_APPEARANCE;
	}
	else if( m_vm.count( "all" ) )
	{
		m_UpdateMode = UPDATE_MODE_ALL;
	}

	m_RunMode = OP_UPDATE_FEATURES;
	ReadCommonArgsForMultipleImages();
	ReadTrainingFolderPath( );

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: OptionalArgs
 * Return Type 	: int
 * Created On	: Feb 9, 2013
 * Created By 	: hrushi
 * Comments		: These are the optional Arguments
 * Arguments	:
 *******************************************************************/
int Args::OptionalArgs( )
{
	// ---- Help Usage ---- //
	if(m_vm.count("help"))
	{
		help();
		return ERR_INVALID_ARGS;
	}

	// ---- Optional Arguments  ----//
	if( m_vm.count("verbose") )
	{
		m_Versbose = true;
	}

	// ---- Quiet Output ----//
	if( m_vm.count("quiet") )
	{
		m_bQuiet = true;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ArgCheck
 * Return Type 	: int
 * Created On	: Feb 9, 2013
 * Created By 	: hrushi
 * Comments		: A quick check if the arguments are correct or not
 * Arguments	:
 *******************************************************************/
int Args::ArgCheckNParse( int argc, char* argv[]  )
{

	try
	{
		po::store(po::parse_command_line(argc, argv, m_desc), m_vm);
		po::notify(m_vm);
	}
	catch(const boost::bad_any_cast& e )
	{
		cerr << "Improper Arguments, please check. The allowed arguments are below" << endl;
		help();
		cerr << e.what() << endl;
		throw( ERR_INVALID_ARGS );
	}
	catch (...)
	{
		cerr << "Improper Arguments, please check. The allowed arguments are below" << endl;
		help();
		exit(ERR_INVALID_ARGS);

	}

	if( argc < 2)
	{
		help();
		exit(ERR_INVALID_ARGS);

	}


	return EXIT_SUCCESS;
}
/*******************************************************************
 * Function Name: OptionLabelImages
 * Return Type 	: int
 * Created On	: Feb 9, 2013
 * Created By 	: hrushi
 * Comments		: Recusively Labels Images from the folder
 * Arguments	: Non
 *******************************************************************/
int Args::OptionLabelImages( )
{
	std::stringstream ss;

	//---------- Set the Label File Name ---------- //
	if( m_vm.count("label_file_name"))
	{
		ss.clear();
		ss.str("");
		ss << m_vm["label_file_name"].as<string >();
		m_LabelFileName = ss.str();
	}

	//---------- Set the Skip existing Flag ---------- //
	if( m_vm.count("skip_existing") )
	{
		m_SkipExisting = true;
	}
	else
	{
		m_SkipExisting = false;
	}

	//---------- Set the Label Now Flag ---------- //
	if( m_vm.count("now") )
	{
		m_bLabelNow = true;
	}
	else
	{
		m_bLabelNow = false;
	}

	//---------- Set the Ground Truth Label Flag ---------- //
	if( m_vm.count("ground_truth"))
	{
		m_LabelGroundTruth = true;
	}
	else
	{
		m_LabelGroundTruth = false;
	}


	//---------- Use Ground Truth Data ---------- //
	if( m_vm.count("useGroundTruth"))
	{
		m_UseGndTruthLabels = true;
	}
	else
	{
		m_UseGndTruthLabels	= false;
	}

	m_RunMode = OP_LABEL_IMAGES;
	ReadCommonArgsForMultipleImages();

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadArgsForMultipleImages
 * Return Type 	: int
 * Created On	: Feb 9, 2013
 * Created By 	: hrushi
 * Comments		: Reads 1. Path to the folder containing all the images, 2. Track Image Path 3. Mask Image Path
 * Arguments	:
 *******************************************************************/
int Args::ReadCommonArgsForMultipleImages( )
{

	std::stringstream ss;

	if(m_vm.count("input_run_folder"))
	{

		ss.clear();
		ss.str("");
		ss << m_vm["input_run_folder"].as<string >();
		m_RunFolderPath = ss.str();

		if( m_vm.count("track_folder_name") )
		{
			ss.clear();
			ss.str("");

			ss << m_vm["track_folder_name"].as<string >();
			m_TrackFolderName = ss.str();
		}
		else
		{
			cout << "Please enter the Track Folder Name" << endl;

			help();
			return ERR_INVALID_ARGS;
		}

		if( m_vm.count("mask_folder_name"))
		{
			ss.clear();
			ss.str("");

			ss << m_vm["mask_folder_name"].as<string >();
			m_MaskFolderName = ss.str();

		}
		else
		{
			cout << "Please enter the Mask Folder Name" << endl;
			help();
			return ERR_INVALID_ARGS;
		}

		if(m_vm.count("skip_width"))
		{
			m_uiSkipWidth = m_vm["skip_width"].as<UINT>();
		}

		if(m_vm.count("skip_height"))
		{
			m_uiSkipHeight = m_vm["skip_height"].as<UINT>();
		}

		if(m_vm.count("skip_IfNoPose"))
		{
			m_SkipIfNoPose	= true;
		}

		if(m_vm.count("usePoseOverlap"))
		{
			m_UsePoseOverlap = true;
		}


	}
	else
	{
		cerr << "Cannot read argument --input_run_folder " << endl;
		cerr << "Make sure you have given the arguments correctly " << endl;

		throw ERR_INVALID_ARGS;

	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: ReadTrainingFolderPath
 * Return Type 	: int
 * Created On	: Jul 1, 2013
 * Created By 	: hrushi
 * Comments		: Reads the Training folder Path from the arguments.
 * Arguments	:
 *******************************************************************/
int Args::ReadTrainingFolderPath( )
{

	std::stringstream ss;

	if( m_vm.count("training_data_path") )
	{
		ss.clear();
		ss.str("");

		ss << m_vm["training_data_path"].as<string>();
		m_TrainingDataFolderPath = ss.str();

	}
	else
	{
		cerr << "Cannot read argument --training_data_path" << endl;
		cerr << "Training data path is required to pull all the training data " << endl;

		throw ERR_INVALID_ARGS;
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: OptionCopyMaskImages
 * Return Type 	: int
 * Created On	: Feb 3, 2013
 * Created By 	: hrushi
 * Comments		: Sets the variables for copying mask images from the source to the destination folder
 * Arguments	:
 *******************************************************************/
int Args::OptionCopyMaskImages( )
{

	std::stringstream ss;

	m_RunMode = OP_COPY_MASK_IMAGES;

	if( m_vm.count("mask_path") )
	{
		ss.clear();
		ss.str("");
		ss << m_vm["mask_path"].as<string>();
		m_MaskPath = ss.str();

		if(m_vm.count("input_path") )
		{
			ss.clear();
			ss.str("");
			ss << m_vm["input_path"].as<string>();
			m_InputPath = ss.str();
		}

	}
	else
	{
		cerr << "Please enter the Mask Src Folder path " << endl;
		exit ( ERR_INVALID_ARGS );
	}


	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: OptionSingleImage
 * Return Type 	: int
 * Created On	: Feb 3, 2013
 * Created By 	: hrushi
 * Comments		: Sets proper variables for working on single pair of images
 * Arguments	:
 *******************************************************************/
int Args::OptionSingleImage( )
{
	std::stringstream ss;

	m_RunMode = OP_SINGLE_IMAGE;

	if( m_vm.count("input_path") )
	{
		ss.clear();
		ss.str("");

		ss << m_vm["input_path"].as<string >();
		m_InputPath = ss.str();

	}
	else
	{
		cout << "Input Path not Set. Please enter the input image path " << endl;
		help();
		return ERR_INVALID_ARGS;
	}


	if( m_vm.count("mask_path"))
	{
		ss.clear();
		ss.str("");

		ss << m_vm["mask_path"].as<string>();
		m_MaskPath = ss.str();

	}
	else
	{
		cout << "Mask Path not set. Please enter a Mask image path" << endl;
		help();
		return ERR_INVALID_ARGS;
	}

	if(m_vm.count( "input_run_folder" ))
	{
		ss.clear();
		ss.str("");

		ss << m_vm["input_run_folder"].as<string>();
		m_RunFolderPath = ss.str();

	}


	ReadTrainingFolderPath();
	ReadCommonArgsForMultipleImages();
	ReadDetectMode();

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: OptionMultipleImages
 * Return Type 	: int
 * Created On	: Feb 3, 2013
 * Created By 	: hrushi
 * Comments		: This option sets the proper member varibables for MultileImage Argument
 * Arguments	:
 *******************************************************************/
int Args::OptionMultipleImages( )
{

	m_RunMode = OP_MULTIPLE_IMAGES;

	ReadCommonArgsForMultipleImages();
	ReadTrainingFolderPath();
	ReadDetectMode();

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: OptionDemo
 * Return Type 	: int
 * Created On	: Dec 5, 2013
 * Created By 	: hrushi
 * Comments		: Sets proper variables for Demo Arguments
 * Arguments	:
 *******************************************************************/
int Args::OptionDemo( )
{

	m_RunMode = OP_DEMO;

	ReadCommonArgsForMultipleImages();
	ReadTrainingFolderPath();
	ReadDetectMode();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: ReadDetectMode
 * Return Type 	: int
 * Created On	: Sep 30, 2013
 * Created By 	: hrushi
 * Comments		: Reads the detection mode
 * Arguments	:
 *******************************************************************/
int Args::ReadDetectMode( )
{

	std::stringstream ss;

	if( m_vm.count("mode") )
	{
		ss.clear();
		ss.str("");

		ss << m_vm["mode"].as<string>();
		m_DetectionMode = ss.str();

	}
	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: help
 * Return Type 	: int
 * Created On	: Feb 2, 2013
 * Created By 	: hrushi
 * Comments		: Prints the Help Text
 * Arguments	:
 *******************************************************************/
int Args::help( ) const
{

	cout << "Additional Arguments " << endl;
	cout << m_desc << endl;

	return EXIT_SUCCESS;
}


