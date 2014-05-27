/*
 * FileNames.h
 *
 *  Created on: Sep 30, 2013
 *      Author: hrushi
 *
 *      Contains all the constant Filenames
 */

#ifndef FILENAMES_H_
#define FILENAMES_H_

#include "CPPIncludes.h"


/**************************************************************
 *           Directory Names
 **************************************************************/
const string DATA_FLDR					= "/Data";

/**************************************************************
 *           FileNames
 **************************************************************/

const string APPEARANCE_FEATURES		= DATA_FLDR + "/AppearanceFeatures.txt";
const string LABEL_FILENAME_STR			= "Labels.txt";
const string LABEL_FILENAME				= "/" + LABEL_FILENAME_STR;
const string ALL_LABEL_FILENAME			= DATA_FLDR + LABEL_FILENAME;

const string PRIOR_PROB_FILENAME 		= DATA_FLDR + "/PriorProbValues.txt";
const string LOC_PRIOR_PROB_IMGNAME 	= DATA_FLDR + "/LocPriorProb.png";

const string DRAG_CARRY_BASENAME		= "/Drag_Carry";
const string DRAG_CARRY_LABEL_FILE 		= DATA_FLDR + DRAG_CARRY_BASENAME + "_Labels.txt";
const string DRAG_CARRY_PROB_IMG	 	= DATA_FLDR + DRAG_CARRY_BASENAME + "_LabelsProb.png";

const string WORN_CARRY_BASENAME		= "/Worn_Carry";
const string WORN_CARRY_LABEL_FILE 		= DATA_FLDR + WORN_CARRY_BASENAME + "_Labels.txt";
const string WORN_CARRY_PROB_IMG	 	= DATA_FLDR + WORN_CARRY_BASENAME + "_LabelsProb.png";

const string PERSON_LOC_PROB_BASENAME	= "/PersonLocProb";
const string PERSON_LOC_PROB_PROB_IMG	= DATA_FLDR + PERSON_LOC_PROB_BASENAME + ".png";

const string SHAPE_DRAG_CARRY	  		= DATA_FLDR + DRAG_CARRY_BASENAME + "_Shape_Carry.txt";
const string SHAPE_WORN_CARRY 			= DATA_FLDR + WORN_CARRY_BASENAME + "_Shape_Carry.txt";
const string SHAPE_NO_CARRY				= DATA_FLDR + "/Shape_NoCarry.txt";
const string SHAPE_DRAG_CARRY_EM		= DATA_FLDR + DRAG_CARRY_BASENAME + "ShapeCarry_EM.dat";
const string SHAPE_WORN_CARRY_EM    	= DATA_FLDR + WORN_CARRY_BASENAME + "ShapeCarry_EM.dat";
const string SHAPE_NO_CARRY_EM		    = DATA_FLDR + "/ShapeNoCarry_EM.dat";
const string ARCHIVE_PATH				= "/FileList.txt";


/**************************************************************
 *           Appearance Files
 **************************************************************/
const string CHIP_FLDR				= DATA_FLDR + "/Chip";
const string CHIP_DRAG_FLDR			= CHIP_FLDR + "/Drag";
const string CHIP_WORN_FLDR			= CHIP_FLDR + "/Worn";
const string CHIP_PERSON_FLDR		= CHIP_FLDR + "/Person";
const string CHIP_FILE_LIST			= DATA_FLDR + "/Chip_List.xml";

const string BAG_SIFT_VOCAB			= DATA_FLDR + "/SIFT_VOCAB.xml";


/**************************************************************
 *           Pose Files
 **************************************************************/

const string WORN_POSE_FEATURE_STEM		= "Worn_PoseFeature";
const string DRAG_POSE_FEATURE_STEM		= "Drag_PoseFeature";
const string NO_CARRY_POSE_FEATURE_STEM	= "No_Carry_PoseFeature";
const string TXT_EXTN					= ".txt";

const string WORN_POSE_FEATURE_FILE		= WORN_POSE_FEATURE_STEM 	 + TXT_EXTN;
const string DRAG_POSE_FEATURE_FILE		= DRAG_POSE_FEATURE_STEM 	 + TXT_EXTN;
const string NO_CARRY_POSE_FEATURE_FILE	= NO_CARRY_POSE_FEATURE_STEM + TXT_EXTN;

//---------- Left Hand Files ---------- //
const string LEFT_MAP_IDX = "m";
const string LEFT_WORN_POSE_FEATURE_FILE	= DATA_FLDR + "/" + LEFT_MAP_IDX + WORN_POSE_FEATURE_STEM 	  + TXT_EXTN;
const string LEFT_DRAG_POSE_FEATURE_FILE   	= DATA_FLDR + "/" + LEFT_MAP_IDX + DRAG_POSE_FEATURE_STEM 	  + TXT_EXTN;
const string LEFT_NOCARRY_POSE_FEATURE_FILE	= DATA_FLDR + "/" + LEFT_MAP_IDX + NO_CARRY_POSE_FEATURE_STEM + TXT_EXTN;

//---------- Right Hand Files ---------- //
const string RIGHT_MAP_IDX = "c";
const string RIGHT_WORN_POSE_FEATURE_FILE	= DATA_FLDR + "/" + RIGHT_MAP_IDX + WORN_POSE_FEATURE_STEM	   + TXT_EXTN;
const string RIGHT_DRAG_POSE_FEATURE_FILE  	= DATA_FLDR + "/" + RIGHT_MAP_IDX + DRAG_POSE_FEATURE_STEM	   + TXT_EXTN;
const string RIGHT_NOCARRY_POSE_FEATURE_FILE= DATA_FLDR + "/" + RIGHT_MAP_IDX + NO_CARRY_POSE_FEATURE_STEM + TXT_EXTN;

const string EM_EXTN   = "_EM.dat";



/**************************************************************
 *           Prob Score Paths
 **************************************************************/
const string POSE_PROB_SCORE_FILE 	= DATA_FLDR + "/Pose_Prob_Score.xml";
const string LOC_PROB_SCORE_FILE 	= DATA_FLDR + "/Loc_Prob_Score.xml";
const string SHAPE_PROB_SCORE_FILE 	= DATA_FLDR + "/Shape_Prob_Score.xml";
const string APPR_PROB_SCORE_FILE 	= DATA_FLDR + "/Appr_Prob_Score.xml";

//---------------- Ground Truth -----------------//
const string GROUND_TRUTH_FILE		= DATA_FLDR + "/GroundTruth.txt";

#endif /* FILENAMES_H_ */
