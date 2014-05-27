/*
 * Constants.h
 *
 *  Created on: Dec 31, 2012
 *      Author: hrushi
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "CPPIncludes.h"
#include "FileNames.h"


/**************************************************************
 *           Aux Constants
 **************************************************************/
const char STARS[256] 				= "**********************************************";
const char FEW_STARS[256] 			= "*********";
const unsigned int SEC 			= 1000;
const int GRAY_VALUE				= 128;
const int MAX_GRAY_VALUE 			= 255;
const int MAX_GRAY_VALUE_ROUND_OVER = -1;
const int SOME_LARGE_VALUE 		= 1e8;
const int SOME_SMALL_VALUE 		= 1e-10;
const double HALF_SECOND			= 0.5;
const int ONE_SECOND				= 1;
const int THOUSAND_MILLI_SEC		= 1e3;
const double DISP_DELAY			= 0.1 *  ONE_SECOND;
const double DISP_FONT_SCALE		= 0.3;  				// Scales the font by the given size
const double DISP_WAIT_FOR_KEY		= 0;					// Wait for the key press after displaying the image.
const double DISP_ONE_SECOND		= ONE_SECOND;
const int MAX_HUE_VAL				= 360;
const bool DEBUG					= 0;

/**************************************************************
 *           Image Related Constants
 **************************************************************/
const char IMG_EXT_JPEG[8]			= ".jpg";
const char IMG_EXT_PNG[8]			= ".png";
const unsigned int RESIZE_ROWS	= 140;
const unsigned int RESIZE_COLS	= 70;



/**************************************************************
 *           Constants specific to Carrying Regions
 **************************************************************/
const unsigned int WORN_CARRY_LABEL	= 0;
const unsigned int DRAG_CARRY_LABEL	= 1;
const unsigned int PERSON_LABEL		= 2;
const unsigned int NUM_LABELS			= 3;

const unsigned int BACKGROUND_LABEL	= 0;
const int NO_CARRIED_OBJECT 		= -1;
const int UN_INITIALIZED_LABEL 	= -2; // If the Label has this value, then it means that it is un-initialized.

/**************************************************************
 *           Segmentation Constants
 **************************************************************/
const unsigned int SLIC_K 			= 20;
const double SLIC_M 				= 3;

/**************************************************************
 *           MATH Constants
 **************************************************************/
const double PI = 22/7;
const double LOG_2 = log(2);

/**************************************************************
 *           String Names of Labels
 **************************************************************/
const string WORN 	= "WORN";
const string DRAG 	= "DRAG";
const string PERSON = "PERSON";


/**************************************************************
 *           Learn Type
 **************************************************************/
const string SVML = "svm";
const string EML  = "em";

/**************************************************************
 *           Types of Regions
 **************************************************************/
const vector<string> RGN_TYPES = {WORN, DRAG, PERSON};


/**************************************************************
 *           Ground Truth Threshold
 **************************************************************/
const double GND_TRUTH_THRESHOLD = 0.7;

#endif /* CONSTANTS_H_ */
