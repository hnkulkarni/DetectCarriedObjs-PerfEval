/*
 * BOF.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: hrushi
 */

#include "BOF.h"


/*******************************************************************
 * Function Name: BOF
 * Return Type 	: None
 * Created On	: Oct 31, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	:
 *******************************************************************/
BOF::BOF( const string strLearnType )
{

	m_LearnType = strLearnType;

}


/*******************************************************************
 * Function Name: ~BOF
 * Return Type 	: None
 * Created On	: Oct 31, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
BOF::~BOF() {

}

/*****************************************************
 * Function	: BOF Copy Constructor
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: Copy Constructors do not return anything
 *****************************************************/
BOF::BOF(const BOF& rhs )
{
	Allocate( rhs );
	Copy( rhs );

}

/*****************************************************
 * Function	: operator =
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	: Assignment Operator
 * Args		: Const Reference of the second class
 * Return	: Self Pointer
 *****************************************************/
BOF& BOF:: operator=( const BOF& rhs )
{
	Allocate( rhs );
	Copy( rhs );

	return *this;
}

/*****************************************************
 * Function	: Allocate
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int BOF::Allocate( const BOF& rhs )
{

	return EXIT_SUCCESS;
}

/*****************************************************
 * Function	: Copy
 * Date		: Oct 31, 2013
 * Author	: hrushi
 * Comments	:
 * Args		: Const Reference of the second class
 * Return	: SUCCESS / FAILURE
 *****************************************************/
int BOF::Copy( const BOF& rhs )
{
	m_Vocab = rhs.m_Vocab.clone();

	MapOp<mp_Str_SVML>::DeepCopy(m_mpSVM, rhs.m_mpSVM);
	MapOp<mp_Str_ApprEM>::DeepCopy(m_mpEM, rhs.m_mpEM);

	m_LearnType = rhs.m_LearnType;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Learn_Vocabulary
 * Return Type 	: int
 * Created On	: Nov 3, 2013
 * Created By 	: hrushi
 * Comments		: Learn the saved vocabulary
 * Arguments	:
 *******************************************************************/
int BOF::Learn_Vocabulary(const mp_Str_vStr& mp_ClassName_vStr,  const Args& args ) const
{
	Mat Vocab = LoadVocab(args).clone();
	mp_Str_Mat mp_ClassResponse = GetClassResponses(mp_ClassName_vStr, Vocab, args);

	if(m_LearnType.compare(SVML) == 0 ) //Learning Type is SVM
	{
		mp_Str_SVML mp_SVM = TrainSVM(mp_ClassResponse, args);
		cout << "#SVMs " << mp_SVM.size() << endl;
	}
	else if( m_LearnType.compare(EML) == 0 )
	{
		cout << "Learning EMs" << endl;
		TrainEM(mp_ClassResponse, args);

	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: TrainEM
 * Return Type 	: const mp_Str_ApprEM
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Traing 1 EM per class
 * Arguments	: const mp_Str_Mat& mp, const Args& args
 *******************************************************************/
const mp_Str_ApprEM BOF::TrainEM( const mp_Str_Mat& mp, const Args& args) const
{
	cout << "Training EM " << endl;
	mp_Str_ApprEM mpEM;

	for(auto Class : mp )
	{
		cv::Mat HistResp = Class.second;
		string ClassName = Class.first;

		ApprEM EM(DEFAULT_NUM_CLASSES, HistResp);
		fs::path SavePath = args.GetTrainFolderPath() + DATA_FLDR + "/EM_Appr_" +  ClassName + ".xml";

		cout << "Saving EM to: " << SavePath << endl;
		EM.Write(SavePath);

	}

	cout << "EM Training Done" << endl;

	return mpEM;
}

/*******************************************************************
 * Function Name: TrainSVM
 * Return Type 	: const mp_Str_SVM
 * Created On	: Nov 9, 2013
 * Created By 	: hrushi
 * Comments		: Trains 1 SVM per class
 * Arguments	: const mp_Str_Mat& mp
 *******************************************************************/
const mp_Str_SVML BOF::TrainSVM( const mp_Str_Mat& mp, const Args& args ) const
{
	cout << "Training SVM " << endl;
	mp_Str_SVML mp_SVM;

	string FldrPath = args.GetTrainFolderPath();

	if( FldrPath.length() == 0)
	{
		FldrPath = args.GetSearchFolderPath();
	}

	for(mp_Str_Mat::const_iterator itr = mp.begin(); itr != mp.end(); itr++ )
	{
		string ClassName = itr->first;
		pr_Mat_Mat Pr = CreateSamples(mp, ClassName);

		SVMLearning oSVM;
		oSVM.Train(Pr);

		mp_SVM[ClassName].Train(Pr);

		fs::path SavePath = FldrPath + DATA_FLDR + "/SVM_" +  ClassName + ".xml";
		mp_SVM[ClassName].Save(SavePath);
	}

	return mp_SVM;
}



/*******************************************************************
 * Function Name: CreateSamples
 * Return Type 	: pr_Mat_Mat
 * Created On	: Nov 9, 2013
 * Created By 	: hrushi
 * Comments		: Create Samples for the given class name
 * Arguments	: const mp_Str_Mat& mp, const string ClassName
 *******************************************************************/
const pr_Mat_Mat BOF::CreateSamples( const mp_Str_Mat& mp, const string ClassName) const
{
	cout << "Creating samples for " << ClassName << endl;

	pr_Mat_Mat SampleLabelPair;
	cv::Mat Responses, Labels;

	for(mp_Str_Mat::const_iterator itr = mp.begin(); itr != mp.end(); itr++ )
	{
		Responses.push_back( itr->second);

		UINT numResponses = itr->second.rows;
		cout << "ClassNm " << itr->first << " Entries: " << numResponses << endl;

		if(itr->first == ClassName)
		{
			cv::Mat PosLabels = cv::Mat::ones(numResponses, 1, CV_32FC1);
			Labels.push_back(PosLabels);
		}
		else
		{
			cv::Mat NegLabels = cv::Mat::zeros(numResponses, 1, CV_32FC1);
			Labels.push_back(NegLabels);
		}
	}

	SampleLabelPair = std::make_pair(Responses, Labels);

	cout << "Size: " << Responses.rows << " : " << Labels.rows << endl;

	return SampleLabelPair;
}


/*******************************************************************
 * Function Name: GetClassResponses
 * Return Type 	: const mp_Str_Mat
 * Created On	: Nov 9, 2013
 * Created By 	: hrushi
 * Comments		: For the given map of all the classes and images, it will returns a set of vocabulary histogram responses
 * Arguments	: const mp_Str_vStr& mp_Lbl_vStr,  const Args& args
 *******************************************************************/
const mp_Str_Mat BOF::GetClassResponses( const mp_Str_vStr& mp_Lbl_vStr, const cv::Mat& Vocab,  const Args& args) const
{
	mp_Str_Mat mp_ClassResp;


	string TrainFolderPath = args.GetTrainFolderPath();

	if(TrainFolderPath.length() == 0 )
	{
		TrainFolderPath = args.GetSearchFolderPath();
	}

	const string ChipXMLPath = TrainFolderPath + CHIP_FILE_LIST;



	for(mp_Str_vStr::const_iterator itr = mp_Lbl_vStr.begin(); itr != mp_Lbl_vStr.end(); itr++ )
	{
		string ClassType = itr->first;
		cout << "For Type: " << ClassType << " we have: " << itr->second.size() << endl;
		vector<string> vImgPaths = itr->second;

		vImgPaths = FileSystem::GetCompletePath(ChipXMLPath, vImgPaths);

		cout << vImgPaths << endl;

		cv::Mat ClassResponse;

		for( vector<string>::const_iterator itrImg = vImgPaths.begin(); itrImg != vImgPaths.end(); itrImg++)
		{
			cout << ".";
			std::flush(cout);

			try
			{
				cv::Mat Response = GetVocabHist(*itrImg, Vocab).clone();
				ClassResponse.push_back(Response);
			}
			catch(int err)
			{
				if(err == ERR_NO_KEY_PTS)
				{
					continue;
				}
				else
				{
					throw err;
				}
			}

		}

		cout << endl;

		cout << "Adding " << ClassResponse.rows << " Hist Entries to Class Type: " << ClassType << endl;
		mp_ClassResp[ClassType] = ClassResponse;
	}

	return mp_ClassResp;
}


/*******************************************************************
 * Function Name: GetVocabHist
 * Return Type 	: cv::Mat
 * Created On	: Nov 9, 2013
 * Created By 	: hrushi
 * Comments		: For the given image, it runs the extractor and returns a histogram
 * Arguments	: const string ImgPath
 *******************************************************************/
cv::Mat BOF::GetVocabHist( const string ImgPath, const cv::Mat& Vocab) const
{
	cv::Mat Response_hist;
	ColorImg Chip(ImgPath);

	try
	{
		Response_hist = GetVocabHist(Chip, Vocab);
	}
	catch(int err)
	{
		throw err;
	}

	return Response_hist.clone();
}



/*******************************************************************
 * Function Name: GetVocabHist
 * Return Type 	: cv::Mat
 * Created On	: Nov 11, 2013
 * Created By 	: hrushi
 * Comments		: Get the histogram for the vocabulary
 * Arguments	: const ColorImg& Img, const cv::Mat& Vocab
 *******************************************************************/
cv::Mat BOF::GetVocabHist( const ColorImg& Chip, const cv::Mat& Vocab) const
{
	cv::Mat Response_hist;

	cv::Ptr<cv::DescriptorExtractor> DescExt = ( new cv::SiftDescriptorExtractor());
	cv::Ptr<cv::DescriptorMatcher> Mtchr = cv::DescriptorMatcher::create("BruteForce");

	cv::BOWImgDescriptorExtractor oBOW(DescExt, Mtchr);

	oBOW.setVocabulary(Vocab);

	vector<cv::KeyPoint> vKeyPts;
	std::vector<std::vector<int> >pids;
	std::vector<std::vector<std::vector<int> > >pids_array;

	Mat WorkImg = Chip.GetDataRef().clone();

	cv::SIFT detector;
	detector.detect(WorkImg, vKeyPts);

	Mat DispMat;
	cv::drawKeypoints(WorkImg, vKeyPts, DispMat);

	if(vKeyPts.size() == 0 )
	{
		ColorImg DispImg(DispMat);
		DispImg.Display(DISP_DELAY);

		cerr << "No Keypoints detected" << endl;
		throw ERR_NO_KEY_PTS;
	}


	// Calculating the Histogram over here;
	oBOW.compute(WorkImg, vKeyPts, Response_hist, &pids );

	Response_hist = Response_hist * vKeyPts.size();

	return Response_hist;
}

/*******************************************************************
 * Function Name: LoadVocab
 * Return Type 	: int
 * Created On	: Nov 4, 2013
 * Created By 	: hrushi
 * Comments		: Loads the member variable in the Vocabulary
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
Mat BOF::LoadVocab( const Args& args ) const
{
	string TrainFldrPath = args.GetTrainFolderPath();
	if(TrainFldrPath.length() == 0 )
	{
		TrainFldrPath = args.GetSearchFolderPath();
	}

	string BagSiftVocabFile = TrainFldrPath + BAG_SIFT_VOCAB;

	cv::FileStorage fs;
	fs.open(BagSiftVocabFile, cv::FileStorage::READ);

	Mat Vocabulary;

	fs["vocabulary"] >> Vocabulary;

	fs.release();

	return Vocabulary.clone();
}


/*******************************************************************
 * Function Name: Load
 * Return Type 	: int
 * Created On	: Nov 15, 2013
 * Created By 	: hrushi
 * Comments		: Load the Vocabulary and the SVMs
 * Arguments	: const Args& args
 *******************************************************************/
int BOF::Load( const Args& args)
{
	const fs::path TrainingPath = args.GetTrainFolderPath();

	m_Vocab = LoadVocab(args).clone();

	if(m_LearnType.compare(SVML) == 0 )
	{
		LoadSVM(TrainingPath);
	}
	else if( m_LearnType.compare(EML) == 0)
	{
		LoadEM(TrainingPath);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: LoadEM
 * Return Type 	: int
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Load the EM
 * Arguments	: const fs::path fsPath
 *******************************************************************/
int BOF::LoadEM( const fs::path fsPath)
{
	for(auto ClassNames : RGN_TYPES )
	{
		fs::path LoadPath = fsPath.string() + DATA_FLDR + "/EM_Appr_" +  ClassNames + ".xml";

		if(fs::exists(LoadPath))
		{
			cout << "Loading EM from : " << LoadPath << endl;
			m_mpEM[ClassNames].Load(LoadPath);
		}
		else
		{
			cerr << "EM File : " << LoadPath << " not found " << endl;
			throw ERR_INVALID_PATH;
		}
	}

	return EXIT_SUCCESS;

}


/*******************************************************************
 * Function Name: LoadSVM
 * Return Type 	: int
 * Created On	: Nov 15, 2013
 * Created By 	: hrushi
 * Comments		: Load the SVM into the member variables
 * Arguments	: const Args& args
 *******************************************************************/
int BOF::LoadSVM( const fs::path fsPath)
{
	for(auto ClassNames : RGN_TYPES )
	{
		fs::path LoadPath = fsPath.string() + DATA_FLDR + "/SVM_" +  ClassNames + ".xml";

		cout << "Loading SVM from : " << LoadPath << endl;
		m_mpSVM[ClassNames].Load(LoadPath);

	}

	return EXIT_SUCCESS;
}





/*******************************************************************
 * Function Name: SaveDescriptors
 * Return Type 	: int
 * Created On	: Nov 3, 2013
 * Created By 	: hrushi
 * Comments		: Saves the descriptor for the given images
 * Arguments	: const mp_Str_vStr& mp_Lbl_vStr
 *******************************************************************/
int BOF::SaveDescriptors( const mp_Str_vStr& mp_Lbl_vStr, const Args& args) const
{
	cv::SIFT sift;
	vector<cv::KeyPoint> vkeypoints;
	Mat descriptors;
	Mat Training_Descriptors;

	if(0) // Don't exececute
	{
		FileSystem::CreateFolder(fs::path("Temp"));
	}

	string TempPath;
	UINT Chip_counter(0);

	string TrainFolderPath = args.GetTrainFolderPath();

	if(TrainFolderPath.length() == 0 )
	{
		TrainFolderPath = args.GetSearchFolderPath();
	}

	const string ChipXMLPath = TrainFolderPath + CHIP_FILE_LIST;

	for(mp_Str_vStr::const_iterator itr = mp_Lbl_vStr.begin(); itr != mp_Lbl_vStr.end(); itr++ )
	{
		cout << "For Type: " << itr->first << " we have: " << itr->second.size() << endl;
		vector<string> vImgPaths = itr->second;

		for( vector<string>::const_iterator itrImg = vImgPaths.begin(); itrImg != vImgPaths.end(); itrImg++)
		{

			fs::path ChipPath = FileSystem::GetCompletePath(ChipXMLPath, *itrImg);

			ColorImg Chip(ChipPath);

			Mat WorkImg = Chip.GetDataRef().clone();

			sift(WorkImg, Mat(), vkeypoints, descriptors);

			Mat DispMat;
			cv::drawKeypoints(WorkImg, vkeypoints, DispMat);

			ColorImg DispImg;
			DispImg.SetImage(DispMat);
			//DispImg.Display(DISP_DELAY);

			if(0) // No Need to write again and again
			{
				std::stringstream ss;
				ss.clear();
				ss << "./Temp/ChipDesc" << std::setw(5) << std::setfill('0') << Chip_counter << ".png" << endl;
				cout << ss.str() << endl;
				DispImg.Write(fs::path(ss.str()));
				Chip_counter++;
			}

			Training_Descriptors.push_back(descriptors);
		}
	}

	cv::BOWKMeansTrainer bowTrainer(BOW_CLUSERS);
	bowTrainer.add(Training_Descriptors);
	cout << "Clustering BOW features: " << endl;

	cv::Mat Vocabulary = bowTrainer.cluster();

	std::cout<<"vocab size "<<Vocabulary.rows<<" x "<<Vocabulary.cols << endl;
	cv::FileStorage f;

	string TrainFldrPath = args.GetTrainFolderPath();
	if(TrainFldrPath.length() == 0 )
	{
		TrainFldrPath = args.GetSearchFolderPath();
	}

	string BagSiftVocabFile = TrainFldrPath + BAG_SIFT_VOCAB;

	cout << "Saving BOW Vocab to: " << BagSiftVocabFile << endl;

	f.open( BagSiftVocabFile , cv::FileStorage::WRITE);
	f <<"vocabulary"<< Vocabulary;
	f.release();

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: GetChipType
 * Return Type 	: pr_score
 * Created On	: Nov 15, 2013
 * Created By 	: hrushi
 * Comments		: Get the Chip Type for the given vocabulary
 * Arguments	: const ColorImg& Chip, const Args& args
 *******************************************************************/
const pr_score BOF::GetChipType( const ColorImg& Chip, vector<double>& vAllScores, const Args& args ) const
{
	pr_score Score;

	try{


		Mat Resp_Hist = GetVocabHist(Chip, m_Vocab).clone();

		std::map<string, cv::Vec2d> mp_ClassScore;
		vector<string> vNames = {WORN, PERSON, DRAG};

		for(auto ClassName : RGN_TYPES)
		{
			cv::Vec2d dMap;
			if(m_LearnType.compare(SVML) == 0)
			{
				dMap = m_mpSVM.at(ClassName).Predict(Resp_Hist);
			}
			else if( m_LearnType.compare(EML) == 0)
			{
				dMap = m_mpEM.at(ClassName).Predict(Resp_Hist);
			}

			ss::insert(mp_ClassScore)(ClassName, dMap);
		}

		Score = WiningScore(mp_ClassScore, vAllScores);
	}
	catch(int err)
	{
		if(err == ERR_NO_KEY_PTS)
		{
			cerr << "No Key Points detected" << endl;

		}

	}

	return Score;
}


/*******************************************************************
 * Function Name: WiningScore
 * Return Type 	: const pr_score
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Calculate the Winning score by calling the appropriate functions
 * Arguments	: const std::map<string, cv::Vec2d>& mpScores
 *******************************************************************/
const pr_score BOF::WiningScore( const std::map<string, cv::Vec2d>& mpScores, vector<double>& vAllScores) const
{
	pr_score WinScore;

	if(m_LearnType.compare(SVML) == 0)
	{
		WinScore = WinScore_SVM(mpScores);
	}
	else if( m_LearnType.compare(EML) == 0)
	{
		WinScore = WinScore_EM(mpScores, vAllScores);
	}

	return WinScore;
}


/*******************************************************************
 * Function Name: WinScore_EM
 * Return Type 	: const pr_score
 * Created On	: Nov 17, 2013
 * Created By 	: hrushi
 * Comments		: Calculate the winning score via EM
 * Arguments	: const std::map<string, cv::Vec2d>& mpScores
 *******************************************************************/
const pr_score BOF::WinScore_EM( const std::map<string, cv::Vec2d>& mpScores, vector<double>& vAllScores) const
{
	double dWornLog = mpScores.at(WORN).val[0];
	double dDragLog = mpScores.at(DRAG).val[0];
	double dPersonLog = mpScores.at(PERSON).val[0];

	pr_score WinScore = Detect::GetFinalScore(dWornLog, dDragLog, dPersonLog, vAllScores);

	return WinScore;
}


/*******************************************************************
 * Function Name: WinScore_SVM
 * Return Type 	: const std::map<string, cv::Vec2d>& mpScores
 * Created On	: Nov 16, 2013
 * Created By 	: hrushi
 * Comments		: Give a list of scores, it will choose the least
 * Arguments	: const std::map<string, cv::Vec2d>& noScores
 *******************************************************************/
const pr_score BOF::WinScore_SVM( const std::map<string, cv::Vec2d>& mpScores ) const
{
	pr_score WinScore;

	cout << "Finding Wining Score between: " << endl;

	for(auto mp: mpScores)
	{
		cout << mp.first << " : " << mp.second << endl;
	}

	//---------- Copy all positive Scores ---------- //
	std::map<string, cv::Vec2d> mpAllPos;
	for(auto mp: mpScores)
	{
		if(mp.second.val[0] == 1 )
		{
			mpAllPos[mp.first] = mp.second;
		}
	}


	for(auto mp: mpAllPos)
	{
		cout << mp.first << " : " << mp.second << endl;
	}

	//---------- Select the one at is closest to the hyper plane ---------- //
	double MinDist = DBL_MAX;
	for(auto mp: mpAllPos)
	{
		if( mp.second.val[1] < MinDist )
		{
			MinDist = mp.second.val[1];

			WinScore.first = Str2Label(mp.first);
			WinScore.second = MinDist;
		}

	}

	return WinScore;

}


/*******************************************************************
 * Function Name: Str2Label
 * Return Type 	: int
 * Created On	: Nov 18, 2013
 * Created By 	: hrushi
 * Comments		: Converts string to Label
 * Arguments	: const string Str
 *******************************************************************/
int BOF::Str2Label( const string Str) const
{
	int Label = UN_INITIALIZED_LABEL;

	if(Str.compare(PERSON) == 0)
	{
		Label = PERSON_LABEL;
	}
	else if( Str.compare(WORN) == 0)
	{
		Label = WORN_CARRY_LABEL;
	}
	else if( Str.compare(DRAG) == 0)
	{
		Label = DRAG_CARRY_LABEL;
	}

	return Label;
}
