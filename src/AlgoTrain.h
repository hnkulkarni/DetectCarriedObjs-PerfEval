/*
 * AlgoTrain.h
 *
 *  Created on: Jun 17, 2013
 *      Author: hrushi
 */

#ifndef ALGOTRAIN_H_
#define ALGOTRAIN_H_

#include "Algo.h"
#include "ProjectIncludes.h"
#include "Detect.h"
#include "DetectByAppearance.h"
#include "ContourMap.h"
#include "ColorImg.h"
#include "GrayImg.h"
#include "Labels.h"
#include "Features.h"
#include "FileSystem.h"
#include "StringOp.h"
#include "BOF.h"

class AlgoTrain: public Algo {

private:
	// Helper Function
	virtual int Copy( const AlgoTrain& rhsAlgoTrain );
	virtual int Allocate( const AlgoTrain& rhsAlgoTrain );
	virtual mp_UINT_Str CreateFolders( const string TrainFldrPath) const;
	virtual mp_Str_vStr GetImageChips( const Args& args, const std::map<string, string>& TrkMskMap ) const;
	virtual int SaveChipMap(const mp_Str_vStr& mp, const Args& args ) const;
	virtual mp_Str_vStr LoadChipMap(const Args& args) const;

public:
	AlgoTrain();
	virtual ~AlgoTrain();

	// Copy Constructor
	AlgoTrain( const AlgoTrain& rhsAlgoTrain );

	// Assignment Operator
	AlgoTrain& operator=( const AlgoTrain& rhsAlgoTrain );

	virtual int TrainApperance( const Args& args, const std::map<string, string>& TrkMskMap ) const;



};

#endif /* ALGOTRAIN_H_ */
