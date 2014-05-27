/*
 * App.h
 *
 *  Created on: Feb 2, 2013
 *      Author: hrushi
 */

#ifndef APP_H_
#define APP_H_

#include "ProjectIncludes.h"
#include "ColorImg.h"
#include "GrayImg.h"
#include "Detect.h"
#include "Args.h"
#include "StringOp.h"
#include "Labels.h"
#include "Features.h"
#include "FileSystem.h"
#include "PoseFile.h"
#include "AlgoTest.h"
#include "AlgoTrain.h"
#include "GroundTruth.h"
#include "ShapeFeatures.h"
#include "HuMoments.h"

#include "WritePoseFeature.h"
#include "WriteShapeFeatures.h"

#include "ReadFeatureList.h"
#include "ShapeEM.h"
#include "PoseFile.h"

#include "TrackXML.h"
#include "ViperXML.h"
#include "Loop.h"
#include "ViperGroundTruth.h"

#include "DetectionScoreFile.h"

class App {

private:
	virtual int RunOnImage(const Args& args);    				// Executes the program on single images
	virtual int RunOnManyImages( const Args& args); 			// Executes the program on multiple images
	virtual int RunCopyImage(const Args& args ); 				// Not supported.
	virtual int RunLabelling( const Args& args );   			// RunLabling
	virtual int RunLabels( const Args& args, const std::map<string, string>& TrkMskMap );
	virtual int RunUpdateFeatures(const Args& args); 		// Recalculates and updates all the features from the Label File
	virtual int RunUpdatePoseFeatures( const Args& args); 	// Recalculates the pose features
	virtual int RunUpdatePoseEM( const Args& args ); // Recalculates the EM values for the pose
	virtual int RunUpdateContourFeatures( const Args& args ); // Reclaculates the Contour Features and Updates
	virtual int RunUpdateLocProbImg(const Args& args, const string LabelFileName, const string AllLabelFileName ) ; 		// Recalculates the probability of images
	virtual int RunUpdateLabelType( const Args& args ); 		// Assigns the Label Type
	virtual int RunUpdateLabelType( const Args& args, const string LablMapPath, const string SegImgPath, const int CntrNum, Labels& bgpk_lbl, Labels& suiteCase_lbl );
	virtual int RunUpdatePersonLocProb( const Args& args, const string sFileName, const string sLableFileName, const string bLabelFileName);
	virtual int RunUpdateShape(const Args& args);
	virtual int RunUpdateShapeEM( const Args& args )const;
	virtual int RunUpdateAppearance( const Args& args ) const;
	virtual int RunDemo( const Args& args) const;

	virtual int UpdatePriorProbValues(const Args& args );


	virtual std::map<string, string> MakeTracknMaskImageList( const Args& args ) const;
	virtual std::map<string, string> PopulateMap( const vector<fs::path>& Key, const vector<fs::path>& Val) const; // TrackChip -> Background Chip

	// Helper Function
	virtual int Copy_App( const App& rhsApp );
	virtual int Allocate_App( const App& rhsApp );

	// Open WritePoseFeature Files
	virtual Map_WrtPoseFeature OpenWritePoseFeatureFile( const fs::path FolderPath, const vector<char> PartKey, const fs::path FileAuxName ) const;
	virtual const AllDetectedCtrs GetCarryRegions( const fs::path TrackImg, const fs::path MaskImg, const Args& args) const;
	virtual const AllDetectedCtrs SingleImgDetect( const fs::path TrackPath, const fs::path MaskPath, const fs::path PosePath, const Args& args ) const;

public:

	/***************************************************************************************
	 *  				Class Initialization
	 ***************************************************************************************/
	App();
	virtual ~App();

	// Copy Constructor
	App( const App& rhsApp );

	// Assignment Operator
	App& operator=( const App& rhsApp );



	/***************************************************************************************
	* 			     Aux. Member Functions
	****************************************************************************************/
	virtual int Run(const Args& args);				//Main Function for co-ordination

	/***************************************************************************************
	 * 						Accessors
	 ***************************************************************************************/

};

#endif /* APP_H_ */
