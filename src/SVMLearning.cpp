/*
 * SVMLearning.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: hrushi
 */

#include "SVMLearning.h"

/*******************************************************************
 * Function Name: SVMLearning
 * Return Type 	: None
 * Created On	: Nov 10, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
SVMLearning::SVMLearning()
{

}


/*******************************************************************
 * Function Name: ~SVMLearning
 * Return Type 	: None
 * Created On	: Nov 10, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
SVMLearning::~SVMLearning()
{


}


/*****************************************************
 * Function	: SVMLearning Copy Constructor
 * Date		: Nov 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
SVMLearning::SVMLearning(const SVMLearning& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Nov 10, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
SVMLearning& SVMLearning:: operator=( const SVMLearning& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Nov 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int SVMLearning::Allocate( const SVMLearning& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Nov 10, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int SVMLearning::Copy( const SVMLearning& rhs )
{
	MLearning::operator =(rhs);

	m_SVM = rhs.m_SVM;
	m_SVMParam = rhs.m_SVMParam;

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: GetSVM
 * Return Type 	: CvSVM
 * Created On	: Nov 10, 2013
 * Created By 	: hrushi
 * Comments		: For the given samples and labels it trains and gets an SVM
 * Arguments	: const pr_Mat_Mat& pr
 *******************************************************************/
unsigned int SVMLearning::Train( const pr_Mat_Mat& Pr)
{
	cv::Mat  Samples = Pr.first;
	Samples.convertTo(Samples, CV_32FC1);

	cv::Mat Labels = Pr.second;

	//---------- Build and Train SVM With Cross Validation ---------- //
	m_SVM.train_auto(Samples, Labels, Mat(), Mat(), m_SVMParam, 5);

	cv::Size Sz = cv::Size(Samples.cols,1);
	cv::Mat OneSample( Sz, CV_32FC1);
	OneSample = Samples.row( Samples.rows -1 );
	cout << OneSample <<endl;

	Predict(OneSample);

	Check(Samples.clone(), Labels.clone());

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Check
 * Return Type 	: int
 * Created On	: Nov 10, 2013
 * Created By 	: hrushi
 * Comments		: Checks how many of the train labels can be detected correctly
 * Arguments	: const Mat Samples, const Mat ActLabels
 *******************************************************************/
int SVMLearning::Check( const Mat Samples, const Mat ActLabels) const
{
	Samples.convertTo(Samples, CV_32FC1);

	Mat PredictLabels;
	m_SVM.predict(Samples, PredictLabels);

	cout << "Actual: \t " << ActLabels << endl;
	cout << "Predicted: \t " << PredictLabels << endl;

	return EXIT_SUCCESS;
}
/*******************************************************************
 * Function Name: Save
 * Return Type 	: int
 * Created On	: Nov 10, 2013
 * Created By 	: hrushi
 * Comments		: Save SVM
 * Arguments	: const fs::path fs
 *******************************************************************/
int SVMLearning::Save( const fs::path fs) const
{
	cout << "Writing to: " << fs.string() << endl;

	m_SVM.save(fs.string().c_str());

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Load
 * Return Type 	: int
 * Created On	: Nov 11, 2013
 * Created By 	: hrushi
 * Comments		: Loads the SVM parameters from the File
 * Arguments	: const fs::path fs
 *******************************************************************/
int SVMLearning::Load( const fs::path fsPath)
{

	if(!fs::exists(fsPath))
	{
		cerr << "File: " << fsPath << " Not found." << endl;
	}

	m_SVM.load(fsPath.string().c_str());

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Predict
 * Return Type 	: const cv::Vec2d
 * Created On	: Nov 10, 2013
 * Created By 	: hrushi
 * Comments		: Predict function using the SVM
 * Arguments	: const cv::Mat
 *******************************************************************/
const cv::Vec2d SVMLearning::Predict( const cv::Mat OneSample) const
{
	cv::Vec2d Response;
	cv::Mat Sample;

	OneSample.convertTo(Sample, CV_32FC1);
	float PredictVal = m_SVM.predict(Sample);

	cout << "Result: " << PredictVal << endl;

	Response.val[0] = PredictVal;

	float PredictDist = m_SVM.predict(Sample, 1);
	Response.val[1] = PredictDist;

	return Response;
}
