/*
 * BOF.h
 *
 *  Created on: Oct 31, 2013
 *      Author: hrushi
 */

#ifndef BOF_H_
#define BOF_H_

#include "ProjectIncludes.h"
#include "ColorImg.h"
#include "FileSystem.h" 	// Required for creating a temp folder
#include "SVMLearning.h" 	// Required for Learning SVM.
#include "ApprEM.h"  // Required for Learning an EM
#include "Detect.h"

const UINT BOW_CLUSERS = 12;
const string LEARN_MODE = EML;

class BOF {

private:
	// Helper Function
	virtual int Copy( const BOF& rhs );
	virtual int Allocate( const BOF& rhs );

	virtual const mp_Str_Mat GetClassResponses(const mp_Str_vStr& mp_Lbl_vStr, const cv::Mat& Vocab,  const Args& args) const;

	virtual const mp_Str_SVML TrainSVM(const mp_Str_Mat& mp, const Args& args ) const;
	virtual const mp_Str_ApprEM TrainEM(const mp_Str_Mat& mp, const Args& args ) const;
	virtual const pr_Mat_Mat CreateSamples(const mp_Str_Mat& mp, const string ClassName) const;
	virtual const pr_score WinScore_EM(const std::map<string, cv::Vec2d>& mpScores, vector<double>& vAllScores ) const;
	virtual const pr_score WinScore_SVM(const std::map<string, cv::Vec2d>& mpScores ) const;
	virtual int Str2Label(const string Str ) const;
	/**************************************************************
	 *           Member Variables, populated only while testing
	 **************************************************************/
	Mat m_Vocab;
	mp_Str_SVML m_mpSVM;
	mp_Str_ApprEM 	m_mpEM;
	string m_LearnType;

protected:

	/**************************************************************
	 *           Functions
	 **************************************************************/
	virtual int LoadSVM( const fs::path fsPath);
	virtual int LoadEM(const fs::path fsPath );

public:
	BOF( const string strLearnType );
	virtual ~BOF();


	// Copy Constructor
	BOF( const BOF& rhsBOF );

	// Assignment Operator
	BOF& operator=( const BOF& rhsBOF );

	//---------- Load Operators ---------- //
	virtual int Load(const Args& args);
	virtual int SaveDescriptors(const mp_Str_vStr& mp_Lbl_vStr, const Args& args) const;
	virtual int Learn_Vocabulary(const mp_Str_vStr& mp_Lbl_vStr, const Args& args ) const;
	virtual Mat LoadVocab(const Args& args ) const;

	//---------- Get Operators  ---------- //
	virtual cv::Mat GetVocabHist(const string ImgPath, const cv::Mat& Vocab) const;
	virtual cv::Mat GetVocabHist(const ColorImg& Img, const cv::Mat& Vocab) const;
	virtual const pr_score GetChipType(const ColorImg& Chip, vector<double>& vAllScores, const Args& args ) const;
	virtual const pr_score WiningScore(const std::map<string, cv::Vec2d>& mpScores, vector<double>& vAllScores ) const;

};

#endif /* BOF_H_ */
