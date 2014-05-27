/*
 * Args.h
 *
 *  Created on: Jan 30, 2013
 *      Author: hrushi
 */

#ifndef ARGS_H_
#define ARGS_H_

#include "MyIncludes.h"
#include "CPPIncludes.h"
#include "OpenCV_Includes.h"
#include "Boost.h"


/*******************************************************
 *  Class Related Globals
 *******************************************************/
const int OP_SINGLE_IMAGE 		= 0;
const int OP_MULTIPLE_IMAGES 	= 1;
const int OP_LABEL_IMAGES		= 2;
const int OP_COPY_MASK_IMAGES	= 3;
const int OP_UPDATE_FEATURES	= 4;
const int OP_DEMO				= 5;

/**************************************************************
 *           Const for UPDATE MODES
 **************************************************************/
const int UPDATE_MODE_POSE			= 1;
const int UPDATE_MODE_CONTOUR 		= 2;
const int UPDATE_MODE_ALL			= 3;
const int UPDATE_LOC_CARRY_PROB	= 4;
const int UPDATE_LOC_PERSON_PROB	= 5;
const int UPDATE_MODE_CARRY_TYPE	= 6;
const int UPDATE_PRIOR_PROBS		= 7;
const int UPDATE_MODE_SHAPE		= 8;
const int UPDATE_APPEARANCE		= 9;

class Args
{

private:

	/*******************************************************
	 *  				Private Variables
	 *******************************************************/
	po::options_description m_desc;
	po::variables_map m_vm;

	string m_ProgramPath;
	string m_InputPath;
	string m_MaskPath;
	string m_TrackFolderName;
	string m_MaskFolderName;
	string m_RunFolderPath;
	string m_LabelFileName;
	string m_TrainingDataFolderPath;
	string m_DetectionMode;

	int m_RunMode;
	int m_UpdateMode;

	UINT m_uiSkipWidth;
	UINT m_uiSkipHeight;

	bool m_CopyMaskImages;
	bool m_Versbose;
	bool m_SkipExisting;
	bool m_LabelGroundTruth;
	bool m_bLabelNow;
	bool m_bQuiet;
	bool m_SkipIfNoPose;
	bool m_UsePoseOverlap;
	bool m_UseGndTruthLabels;

	/*******************************************************
	 *  				Private Functions
	 *******************************************************/
	virtual int ArgCheckNParse( int argc, char* argv[]  );
	virtual int ArgUsage();
	virtual int OptionalArgs();
	virtual int ModeArgs();
	virtual int ReadProgramPath(  int argc, char* argv[]);
	virtual int Init();

public:

	/*******************************************************
	 *  				Class Initialization
	 *******************************************************/
	Args( );
	virtual ~Args();

	// Copy Constructor
	Args( const Args& rhsArgs );

	// Assignment Operator
	Args& operator=( const Args& rhsArgs );

	// Helper Function
	virtual int Copy_Args( const Args& rhsArgs );
	virtual int Allocate_Args( const Args& rhsArgs );

	/****************************************************************
	 * 						Mutators
	 ****************************************************************/
	virtual int AddArgs();

	/***************************************************************
	* 			     Aux. Member Functions
	***************************************************************/
	virtual int parse( int argc, char* argv[] );
	virtual int OptionMultipleImages();
	virtual int OptionSingleImage();
	virtual int OptionCopyMaskImages();
	virtual int OptionLabelImages();
	virtual int OptionUpdateFeatures();
	virtual int OptionDemo();
	virtual int ReadCommonArgsForMultipleImages();
	virtual int ReadTrainingFolderPath();
	virtual int ReadDetectMode();
	virtual int help() const;

	/****************************************************************
	 * 						Accessors
	 ****************************************************************/
	virtual string GetInputFilePath() 		const { return m_InputPath;	  		}
	virtual string GetMaskFilePath() 		const { return m_MaskPath;			}
	virtual string GetTrackFolderName() 	const { return m_TrackFolderName;	}
	virtual string GetMaskFolderName()  	const { return m_MaskFolderName;	}
	virtual string GetSearchFolderPath()	const { return m_RunFolderPath;		}
	virtual int	GetRunMode() 				const { return m_RunMode; 			}
	virtual string	GetLabelFileName()		const { return m_LabelFileName;		}
	virtual bool  	isVerbose()				const { return m_Versbose;			}
	virtual string GetProgramPath()	 		const { return m_ProgramPath; 		}
	virtual bool 	isSkipExisting()	 	const { return m_SkipExisting; 		}
	virtual bool 	LabelNow()			 	const { return m_bLabelNow;			}
	virtual	bool 	UseGndTruthforLabels()	const { return m_UseGndTruthLabels;	}
	virtual int 	GetUpdateMode()			const { return m_UpdateMode;		}
	virtual string GetTrainFolderPath() 	const { return m_TrainingDataFolderPath; }
	virtual bool 	isQuiet() 			 	const { return m_bQuiet; 			}
	virtual const 	string GetDetectMode() 	const { return m_DetectionMode; 	}
	virtual bool 	isLabelGroundTruth()  	const { return m_LabelGroundTruth;	}
	virtual UINT	GetSkipWidth() 			const { return m_uiSkipWidth; 		}
	virtual UINT 	GetSkipHeight()			const { return m_uiSkipHeight;		}
	virtual bool 	isSkipIfNoPose() 	 	const { return m_SkipIfNoPose; 		}
	virtual bool	isUsePoseOverlap()		const { return m_UsePoseOverlap;	}

};

#endif /* ARGS_H_ */
