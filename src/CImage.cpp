/*
 * CImage.cpp
 *
 *  Created on: Dec 23, 2012
 *      Author: hrushi
 */

#include "CImage.h"

/*******************************************************************
 * Function Name: Default Constructor
 * Return Type 	: None
 * Created On	: Dec 23, 2012
 * Created By 	: hrushi
 * Comments		: This is the default constructor of the CImage Class
 * TODo			:
 *******************************************************************/
CImage::CImage()
{
	// TODO Auto-generated constructor stub

	m_nrows 	= 0;
	m_ncols  	= 0;
	m_ImageType = 0;

}

/*******************************************************************
 * Function Name: CImage
 * Return Type 	:
 * Created On	: Jan 11, 2013
 * Created By 	: hrushi
 * Comments		: Creates a Cimage Datatype from the given cv::Mat
 * Arguments	: const Mat& rhsMat
 *******************************************************************/
CImage::CImage( const cv::Mat& rhsMat)
{

	m_data 	= rhsMat.clone();
	m_nrows = rhsMat.rows;
	m_ncols = rhsMat.cols;

	if( rhsMat.depth() == 3)
	{
		m_ImageType = IMAGE_TYPE_COLOR;
	}
	else if( rhsMat.depth() == 1)
	{
		m_ImageType = IMAGE_TYPE_GRAY;
	}


}


/*******************************************************************
 * Function Name: Default Destructor
 * Return Type 	: None
 * Created On	: Dec 23, 2012
 * Created By 	: hrushi
 * Comments		: This is the default constructor of the CImage Class
 * TODo			:
 *******************************************************************/
CImage::~CImage() {
	// TODO Auto-generated destructor stub

	m_data.release();

}


/**********************************************************************
 * Function Name: CImage
 * Date 		: Dec 23, 2012
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
CImage::CImage( const CImage& rhsCImage )
{
	Allocate_CImage( rhsCImage );
	Copy_CImage( rhsCImage );
}



/**********************************************************************
 * Function Name: operator
 * Date 		: Dec 23, 2012
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
const CImage& CImage :: operator=( const CImage & rhsCImage )
{
	Allocate_CImage( rhsCImage );
	Copy_CImage( rhsCImage );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_CImage
 * Date 		: Dec 23, 2012
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int CImage:: Copy_CImage(  const CImage & rhsCImage  )
{

	m_nrows = rhsCImage.m_nrows;
	m_ncols =	rhsCImage.m_ncols;
	m_data  = rhsCImage.m_data.clone();
	m_ImagePath = rhsCImage.m_ImagePath;
	m_ImageType = rhsCImage.m_ImageType;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_CImage
 * Date 		: Dec 23, 2012
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int CImage:: Allocate_CImage(  const CImage & rhsCImage  )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Display
 * Return Type 	: int
 * Created On	: Dec 23, 2012
 * Created By 	: hrushi
 * Comments		: Show
 * TODo			:
 *******************************************************************/
string CImage::Display( const double Delay ) const
{
	return Display(m_data, Delay);
}


/*******************************************************************
 * Function Name: Display
 * Return Type 	: string
 * Created On	: May 28, 2013
 * Created By 	: hrushi
 * Comments		: Displays the image in a new window
 * Arguments	: const string WindowName, const double Delay
 *******************************************************************/
string CImage::Display( const string WindowName, const double Delay) const
{
	return Display(WindowName, m_data, Delay);
}



/*******************************************************************
 * Function Name: Display
 * Return Type 	: int
 * Created On	: Dec 23, 2012
 * Created By 	: hrushi
 * Comments		: Show
 * TODo			:
 *******************************************************************/
string CImage::Display( const Mat& Img, const double Delay ) const
{
	return Display( m_ImagePath.filename().string(), Img, Delay);
}


/*******************************************************************
 * Function Name: Display
 * Return Type 	: string
 * Created On	: May 28, 2013
 * Created By 	: hrushi
 * Comments		: Displays the image
 * Arguments	: const string WindowName, const Mat& Img, const double Delay
 *******************************************************************/
string CImage::Display( const string WindowName, const Mat& Img, const double Delay) const
{

	// Check for the display flag. If it is set to 0, no image will be displayed
	if( DISPLAY_FLAG == 1)
	{
		if(WindowName.length() == 0 )
		{
			cv::namedWindow("Disp", cv::WINDOW_AUTOSIZE);
		}
		else
		{
			cv::namedWindow(WindowName.c_str(), cv::WINDOW_AUTOSIZE);
		}
		cv::imshow(WindowName.c_str(), Img);
		char Key = cv::waitKey( Delay * THOUSAND_MILLI_SEC );

		string sKey(1, Key);

		cv::destroyWindow(WindowName.c_str());


		return sKey;

	}
	else
	{
		//Return empty key
		return "";
	}
}


/*******************************************************************
 * Function Name: ImageProps
 * Return Type 	: int
 * Created On	: Dec 31, 2012
 * Created By 	: hrushi
 * Comments		: Displays the Image Properties on the Terminal
 *******************************************************************/
int CImage::ImageProps() const
{

	cout << STARS << endl;
	cout << "nrows: " << m_nrows << endl;
	cout << "ncols : " << m_ncols << endl;
	cout << "dims : " << m_data.dims << endl;
	cout << "channels: " << m_data.channels() << endl;

	cout << STARS << endl;
	return EXIT_SUCCESS;
}




/*******************************************************************
 * Function Name: GetNumRows
 * Return Type 	: int
 * Created On	: Jan 1, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Number of Rows
 *******************************************************************/
unsigned int CImage::GetNumRows() const
{
	return m_nrows;
}

/*******************************************************************
 * Function Name: GetNumCols
 * Return Type 	: int
 * Created On	: Jan 1, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Number of Columns
 *******************************************************************/
unsigned int CImage::GetNumCols() const
{
	return m_ncols;
}



/*******************************************************************
 * Function Name: GetDataRef
 * Return Type 	: const Mat&
 * Created On	: Jan 1, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Const Reference to Data
 * TODo			:
 *******************************************************************/
const Mat CImage::GetDataRef() const
{
	return m_data;
}


/*******************************************************************
 * Function Name: GetImagePath
 * Return Type 	: FilePath
 * Created On	: Jan 1, 2013
 * Created By 	: hrushi
 * Comments		: Returns the Image 'FilePath'
 * TODo			:
 *******************************************************************/
fs::path CImage::GetImagePath() const
{
	return m_ImagePath;
}


/*******************************************************************
 * Function Name: GetType
 * Return Type 	: int
 * Created On	: Jan 10, 2013
 * Created By 	: hrushi
 * Comments		: Get the Image Type
 * Arguments	:
 *******************************************************************/
int CImage::GetType( ) const
{
	return m_data.type();
}





/*******************************************************************
 * Function Name: GetGrayVal
 * Return Type 	: unsigned int
 * Created On	: Jan 12, 2013
 * Created By 	: hrushi
 * Comments		: Returns gray value at the given i, j
 * TODo			:
 *******************************************************************/
unsigned char CImage::GetGrayVal(const unsigned int i, const unsigned int j) const
{
	unsigned char val;
	val = m_data.at< unsigned char >(i,j);

	return val;
}



/*******************************************************************
 * Function Name: SetNumRows
 * Return Type 	: int
 * Created On	: Jan 20, 2013
 * Created By 	: hrushi
 * Comments		: Sets the number of rows in the image
 * Arguments	:
 *******************************************************************/
int CImage::UpdateNumRows()
{
	m_nrows =  m_data.rows;
	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: SetNumCols
 * Return Type 	: int
 * Created On	: Jan 20, 2013
 * Created By 	: hrushi
 * Comments		: Sets the number of Colums
 * Arguments	:
 *******************************************************************/
int CImage::UpdateNumCols()
{
	m_ncols = m_data.cols;
	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: SetImage
 * Return Type 	: int
 * Created On	: Jan 20, 2013
 * Created By 	: hrushi
 * Comments		: Sets the data in the image using the referred data
 * Arguments	: const cv::Mat& rhsImage
 *******************************************************************/
int CImage::SetImage( const cv::Mat& rhsImageMat, const fs::path& Path  )
{

	m_data = rhsImageMat.clone();
	SetParams(Path);

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: SetImage
 * Return Type 	: int
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Overloaded Image Fuction
 * Arguments	: const Mat& rhsImage
 *******************************************************************/
int CImage::SetImage( const Mat& rhsImage)
{
	fs::path EmptyFile;
	SetImage(rhsImage, EmptyFile);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: SetImagePath
 * Return Type 	: int
 * Created On	: Jan 20, 2013
 * Created By 	: hrushi
 * Comments		: Sets the Image Path
 * Arguments	: const FilePath& ImageFilePath
 *******************************************************************/
int CImage::SetImagePath( const fs::path& Path)
{
	m_ImagePath = Path;

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: UpdateImageParams
 * Return Type 	: int
 * Created On	: Apr 29, 2013
 * Created By 	: hrushi
 * Comments		: Udates the NumRows and NumCols for the image w.r.t modified image
 * Arguments	:
 *******************************************************************/
int CImage::UpdateImageParams( )
{
	UpdateNumCols();
	UpdateNumRows();

	return EXIT_SUCCESS;
}
/*******************************************************************
 * Function Name: SetParams
 * Return Type 	: int
 * Created On	: Jan 20, 2013
 * Created By 	: hrushi
 * Comments		: Sets all the Parameters of the image
 * Arguments	: const FilePath& Path
 *******************************************************************/
int CImage::SetParams( const fs::path& Path)
{

	UpdateNumCols();
	UpdateNumRows();
	SetImagePath(Path);

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: copyTo
 * Return Type 	: int
 * Created On	: Jan 27, 2013
 * Created By 	: hrushi
 * Comments		: Copies the image to the given mat
 * Arguments	: Mat& cpyMat
 *******************************************************************/
int CImage::copyTo( Mat& cpyMat) const
{
	cpyMat = m_data.clone();

	return EXIT_SUCCESS;
}



/*******************************************************************
 * Function Name: Load
 * Return Type 	: int
 * Created On	: Dec 23, 2012
 * Created By 	: hrushi
 * Comments		: Loads the Image given by the FilePath
 * TODo			:
 *******************************************************************/
int CImage::Load(const fs::path FilePath )
{
	if( fs::exists(FilePath.string()))
	{
		try
		{
			if( m_ImageType == IMAGE_TYPE_COLOR )
			{
				m_data = cv::imread(FilePath.string(), CV_LOAD_IMAGE_COLOR);
			}
			else if( m_ImageType == IMAGE_TYPE_GRAY )
			{
				m_data = cv::imread(FilePath.string(), CV_LOAD_IMAGE_GRAYSCALE);
			}

			if( m_data.data == NULL )
			{
				cerr << "Cannot open file: " << FilePath << endl;
				cerr << "Image Type: " << m_ImageType << endl;
				exit(ERR_CANNOT_OPEN_IMAGE);
			}

			m_ImagePath = FilePath;
			m_nrows = m_data.rows;
			m_ncols = m_data.cols;
		}
		catch(...)
		{

		}
	}
	else
	{
		cerr << "Cannot find path " << FilePath;
		throw ERR_INVALID_PATH;
	}
	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Write
 * Return Type 	: int
 * Created On	: Feb 10, 2013
 * Created By 	: hrushi
 * Comments		: Write the Image at the given file location
 * Arguments	: const string FilePath
 *******************************************************************/
int CImage::Write( const fs::path FilePath) const
{
	if( fs::exists( FilePath ) )
	{
		cout << "Overwriting: " << FilePath << endl;
	}

	fs::path ParentPath = FilePath.parent_path();

	if( !fs::exists(ParentPath) )
	{
		cout << "Parent Path does not exist " << endl;
		cout << "Given Path "  << ParentPath.string() << endl;

		cv::imwrite(FilePath.string(), m_data);
	}
	else
	{
		cv::imwrite(FilePath.string(), m_data);
	}

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Resize
 * Return Type 	: int
 * Created On	: Apr 29, 2013
 * Created By 	: hrushi
 * Comments		: This function resizes the image size
 * Arguments	: unsigned int uiRows, unsigned int uiCols
 *******************************************************************/
int CImage::Resize( unsigned int uiRows, unsigned int uiCols)
{
	Mat Temp;
	Temp = Mat::zeros(uiRows, uiCols, m_data.type() );

	if( (m_data.rows == 0 ) || ( m_data.cols == 0) )
	{
		m_data = Temp.clone();
	}
	else
	{
		cv::resize( m_data, Temp, Temp.size(), 0, 0, cv::INTER_CUBIC);
		m_data = Temp.clone();
	}

	UpdateImageParams();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: PutText
 * Return Type 	: cv::Mat
 * Created On	: May 26, 2013
 * Created By 	: hrushi
 * Comments		: Inserts Text at the default location with a white background
 * Arguments	: const string strText
 *******************************************************************/
const cv::Mat CImage::PutText( const string strText )
{
	cv::Mat TempImg = m_data.clone();
	cv::Size TextSize = cv::getTextSize(strText, cv::FONT_HERSHEY_SIMPLEX, DISP_FONT_SCALE, 1, 0 );

	cv::Point PtTemp;
	PtTemp.x = (double) m_ncols / 2;

	// Offset the text so that it lays in the center
	PtTemp.x -= (double)TextSize.width/2;

	PtTemp.y = TextSize.height + 1;

	m_data = PutText( TempImg, strText, COLOR_WHITE, COLOR_RED, PtTemp, 1 );

	return m_data.clone();
}

/*******************************************************************
 * Function Name: PutText
 * Return Type 	: int
 * Created On	: May 19, 2013
 * Created By 	: hrushi
 * Comments		: Puts the text at the given location on the image
 * Arguments	: const string strText, const cv::Point Pt
 *******************************************************************/
const cv::Mat CImage::PutText( const string strText, cv::Scalar DrwColor, const cv::Point Pt)
{
	cv::Mat TempImg = m_data.clone();
	m_data = PutText(TempImg, strText, COLOR_WHITE,  DrwColor, Pt, 1 );

	return m_data.clone();
}

/*******************************************************************
 * Function Name: PutText
 * Return Type 	: cv::Mat
 * Created On	: May 19, 2013
 * Created By 	: hrushi
 * Comments		: Overlay Text on an image
 * Arguments	:  const string strText, cv::Scalar BkColor, cv::Scalar DrwColor, const cv::Point Pt
 *******************************************************************/
const cv::Mat CImage::PutText(  const string strText, cv::Scalar BkColor, cv::Scalar DrwColor, const cv::Point Pt )
{
	cv::Mat TempImg = m_data.clone();
	m_data = PutText(TempImg, strText, BkColor, DrwColor, Pt, 1 );

	return m_data.clone();
}


/*******************************************************************
 * Function Name: PutText
 * Return Type 	: int
 * Created On	: May 19, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the text on the image refrence passed
 * Arguments	: cv::Mat& Img, const string strText, const cv::Point Pt
 *******************************************************************/
const cv::Mat CImage::PutText( const cv::Mat& Img, const string strText, cv::Scalar DrwColor, const cv::Point Pt) const
{
	cv::Mat TempImg = Img.clone();
	TempImg = PutText(TempImg, strText, cv::Scalar(0,0,0), DrwColor, Pt, 1 );

	return TempImg.clone();
}

/*******************************************************************
 * Function Name: PutText
 * Return Type 	: cv::Mat
 * Created On	: May 19, 2013
 * Created By 	: hrushi
 * Comments		: Overlay Text on an image with the given background
 * Arguments	:  const cv::Mat& Img, const string strText, cv::Scalar BkColor,  cv::Scalar DrwColor, const cv::Point Pt
 *******************************************************************/
const cv::Mat CImage::PutText(  const cv::Mat& Img, const string strText, cv::Scalar BkColor,  cv::Scalar DrwColor, const cv::Point Pt, unsigned int FontSize = 1 ) const
{

	cv::Mat TempImg = Img.clone();

	int baseline = 0;
	cv::Size TextSize = cv::getTextSize(strText, cv::FONT_HERSHEY_SIMPLEX, DISP_FONT_SCALE, FontSize, &baseline );
	cv::Point Pt2;
	Pt2.x = Pt.x + TextSize.width;
	Pt2.y = Pt.y - TextSize.height;

	cv::rectangle(TempImg, Pt, Pt2, BkColor, CV_FILLED );
	cv::putText(TempImg, strText, Pt, cv::FONT_HERSHEY_SIMPLEX, DISP_FONT_SCALE, DrwColor, FontSize, CV_AA, false );

	return TempImg.clone();

}


/*******************************************************************
 * Function Name: Legends
 * Return Type 	: const cv::Mat
 * Created On	: Sep 22, 2013
 * Created By 	: hrushi
 * Comments		: Adds a Legend to an Image. Currently supports only BOTTOM Location
 * Arguments	: const string strText, const cv::Scalar BkColor, const cv::Scalar DrwColor, unsigned int Loc
 *******************************************************************/
const cv::Mat CImage::Legends( const string strText, const cv::Scalar BkColor, const cv::Scalar DrwColor, unsigned int Loc )
{
	int baseline = 0;
	cv::Size TextSize = cv::getTextSize(strText, cv::FONT_HERSHEY_SIMPLEX, DISP_FONT_SCALE, 1, &baseline );
	cv::Size ImgSize  = m_data.size();

	const unsigned int LdgHt = ImgSize.height + 2 * TextSize.height;
	unsigned int LdgWt(0), diff(0);

	if( ImgSize.width > TextSize.width)
	{
		LdgWt = ImgSize.width;
		diff = 0;
	}
	else
	{
		LdgWt = TextSize.width;
		diff = TextSize.width - ImgSize.width;

	}
	LdgWt = LdgWt + 0.1 * LdgWt;


	cv::Mat LgdImg = cv::Mat::zeros( LdgHt, LdgWt, m_data.type() );

	cv::copyMakeBorder(m_data, LgdImg, 0, 2 * TextSize.height, 0, diff, cv::BORDER_CONSTANT, COLOR_BLACK);

	cv::Point Pt;

	if( Loc == BOTTOM_LEFT)
	{
		Pt = cv::Point(1, LdgHt - TextSize.height/2);
	}

	LgdImg = PutText(LgdImg, strText, BkColor, DrwColor, Pt, 1 );

	m_data = LgdImg.clone();

	return m_data.clone();
}

