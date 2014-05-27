/*
 * ColorImg.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: hrushi
 */

#include "ColorImg.h"

/*******************************************************************
 * Function Name: ColorImg
 * Return Type 	: None
 * Created On	: Oct 10, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
ColorImg::ColorImg()
{

	Initializer();
}



/*******************************************************************
 * Function Name: ~ColorImg
 * Return Type 	: None
 * Created On	: Oct 10, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: None
 *******************************************************************/
ColorImg::~ColorImg()
{

}

/*******************************************************************
 * Function Name: ColorImg
 * Return Type 	: None
 * Created On	: Oct 10, 2013
 * Created By 	: hrushi
 * Comments		: Comment
 * Arguments	: enclosing_method_arguments
 *******************************************************************/
ColorImg::ColorImg(UINT nrows, UINT ncols)
{
	BuildImage(nrows, ncols, COLOR_BLACK);
}


/*******************************************************************
 * Function Name: ColorImg
 * Return Type 	:
 * Created On	: Nov 2, 2013
 * Created By 	: hrushi
 * Comments		: Constructs a image of the given size with the given starting color
 * Arguments	: UINT nrows, UINT ncols, cv::Scalar InitColor
 *******************************************************************/
 ColorImg::ColorImg( UINT nrows, UINT ncols, cv::Scalar InitColor)
{
	 BuildImage(nrows, ncols, InitColor);
}


/*******************************************************************
 * Function Name: BuildImage
 * Return Type 	: int
 * Created On	: Nov 24, 2013
 * Created By 	: hrushi
 * Comments		: Build the image with the given parameters
 * Arguments	: UINT nrows, UINT ncols, cv::Scalar InitColor
 *******************************************************************/
int ColorImg::BuildImage( UINT nrows, UINT ncols, cv::Scalar InitColor)
{
	Initializer();
	m_data.create(nrows, ncols, CV_8UC3);
	m_data = InitColor;

	UpdateImageParams();

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: ColorImg
 * Date 		: Jan 20, 2013
 * Author		: hrushi
 * Comments		: Copy Constructor
 * Args			:
 * ToDo			:
 **********************************************************************/
ColorImg::ColorImg( const ColorImg& rhsColorImg )
{
	Initializer();
	Allocate_ColorImg( rhsColorImg );
	Copy_ColorImg( rhsColorImg );
}



/*******************************************************************
 * Function Name: ColorImg
 * Return Type 	:
 * Created On	: Nov 9, 2013
 * Created By 	: hrushi
 * Comments		: Sets the Image with the given cv::Mat
 * Arguments	: const cv::Mat& rhsMat
 *******************************************************************/
 ColorImg::ColorImg( const cv::Mat& rhsMat)
{
	 SetImage(rhsMat);
}

/*******************************************************************
 * Function Name: ColorImg
 * Return Type 	:
 * Created On	: Jun 17, 2013
 * Created By 	: hrushi
 * Comments		: Enables passing path for Image object
 * Arguments	: const fs::path FilePath
 *******************************************************************/
ColorImg::ColorImg( const fs::path FilePath)
{
	Initializer();
	Load(FilePath.string());
}

/**********************************************************************
 * Function Name: operator
 * Date 		: Jan 20, 2013
 * Author		: hrushi
 * Comments		: Assignment Operator
 * ToDo			:
 **********************************************************************/
ColorImg& ColorImg :: operator=( const ColorImg & rhsColorImg )
{
	Allocate_ColorImg( rhsColorImg );
	Copy_ColorImg( rhsColorImg );

	return *this;
}


/**********************************************************************
 * Function Name: Copy_ColorImg
 * Date 		: Jan 20, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Copy all the Data
 * ToDo			:
 **********************************************************************/
int ColorImg:: Copy_ColorImg(  const ColorImg & rhsColorImg  )
{

	CImage::operator =( rhsColorImg );

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function Name: Allocate_ColorImg
 * Date 		: Jan 20, 2013
 * Author		: hrushi
 * Comments		: Helper Function to Allocate all the Data
 * ToDo			:
 **********************************************************************/
int ColorImg:: Allocate_ColorImg(  const ColorImg & rhsColorImg  )
{

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Initalizer
 * Return Type 	: int
 * Created On	: Jun 20, 2013
 * Created By 	: hrushi
 * Comments		: Implements the Initializer for a Class
 * Arguments	:
 *******************************************************************/
int ColorImg::Initializer( )
{

	SetImageType();

	return EXIT_SUCCESS;
}

/*******************************************************************
 * Function Name: Cvt2Gray
 * Return Type 	: CImage
 * Created On	: Jan 11, 2013
 * Created By 	: hrushi
 * Comments		: Converts the given image to gray
 * Arguments	:
 *******************************************************************/
GrayImg ColorImg::Cvt2Gray( ) const
{
	Mat GrayMat;
	GrayImg Gray;

	if( m_data.channels() == 3 ) //Data is an RGB Image
	{
		cv::cvtColor(m_data, GrayMat, CV_RGB2GRAY);
		Gray.SetImage(GrayMat, m_ImagePath);

	}
	else // Copy data as it is.
	{
		cout << "The number of channels in the image is " << m_data.channels() << endl;
		cout << "Cannot convert to Gray" << endl;

		Gray.SetImage(m_data, m_ImagePath);
	}

	return Gray;
}


/*******************************************************************
 * Function Name: at
 * Return Type 	: Vec3b
 * Created On	: Jan 9, 2013
 * Created By 	: hrushi
 * Comments		: Returns the value at the given i, j
 * Arguments	: const unsigned int i, const unsigned int j
 *******************************************************************/
Vec3b ColorImg::at( const unsigned int i, const unsigned int j) const
{
	Vec3b Val;

	if( m_data.channels() == 3 )
	{

		Val = m_data.at< Vec3b >(i,j);
	}
	else
	{
		cout << "Dimension in CImage(at), mismatch: Please check " << endl;
		exit(0);
	}

	return Val;
}


/*******************************************************************
 * Function Name: at
 * Return Type 	: int
 * Created On	: Jun 7, 2013
 * Created By 	: hrushi
 * Comments		: Sets the value at the given pixel
 * Arguments	: unsigned int i, unsigned int j, char B, char G, char R
 *******************************************************************/
int ColorImg::at( unsigned int i, unsigned int j, char B, char G, char R)
{

	cv::Vec3b BGR;
	BGR.val[0] = B;
	BGR.val[1] = G;
	BGR.val[2] = R;

	return at(i,j, BGR);
}

/*******************************************************************
 * Function Name: at
 * Return Type 	: int
 * Created On	: Jun 7, 2013
 * Created By 	: hrushi
 * Comments		: Sets the RGB value at the given location
 * Arguments	: unsigned int i, unsigned int j, const cv::Vec3b& RGB
 *******************************************************************/
int ColorImg::at( unsigned int i, unsigned int j, const cv::Vec3b& RGB)
{
	m_data.at< Vec3b >(i,j) = RGB;

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: int
 * Created On	: Jan 28, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the contourmap onto the image.
 * Arguments	: const ContourMap& Ctr
 *******************************************************************/
ColorImg ColorImg::Overlay( const ContourMap& Ctr, const int Delay, cv::Scalar DrwColor, const Args& args ) const
{
	Contour BoundaryCtr;
	Mat Img = m_data.clone();
	ColorImg RetImage;

	for( std::map<unsigned int, Contour >::const_iterator IterAllContour = Ctr.AllContourMap.begin(); IterAllContour != Ctr.AllContourMap.end(); IterAllContour++ )
	{
		BoundaryCtr = (*IterAllContour).second;
		BoundaryCtr.SetLabel( (*IterAllContour).first );

		RetImage = Overlay(Img, BoundaryCtr, Delay, DrwColor, true, args);
	}


	RetImage.SetImage(Img);

	if( args.isVerbose() )
	{
		RetImage.Display(ONE_SECOND);
	}

	return RetImage;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: ColorImg
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the given color on the contour
 * Arguments	: const Contour& Ctr, const int Delay, cv::Scalar Color, const Args& args
 *******************************************************************/
ColorImg ColorImg::Overlay( const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, const Args& args ) const
{
	Mat Img = m_data.clone();
	ColorImg RetImage = Overlay(Img, BoundaryCtr, Delay, DrwColor, true, args);

	return RetImage;
}

/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: ColorImg
 * Created On	: Oct 10, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the image, but lets the user decide if it wants the contour number to be printed at the center
 * Arguments	: const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, bool bPutText, const Args& args
 *******************************************************************/
ColorImg ColorImg::Overlay( const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, bool bPutText, const Args& args) const
{
	Mat Img = m_data.clone();
	ColorImg RetImage = Overlay(Img, BoundaryCtr, Delay, DrwColor, bPutText, args);

	return RetImage;
}

/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: ColorImg
 * Created On	: Feb 27, 2013
 * Created By 	: hrushi
 * Comments		: Overloaded
 * Arguments	: const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, const Args& args
 *******************************************************************/
ColorImg ColorImg::Overlay(  cv::Mat& Img, const Contour& BoundaryCtr,  const int Delay, cv::Scalar DrwColor, bool bPutText = true, const Args& args = Args() ) const
{
	ColorImg RetImage;

	ImagePt CtrPt;
	ImagePt Center;
	cv::Point Pt;

	for( unsigned int i = 0; i < BoundaryCtr.ContourPoints.size() -1; i++ )
	{
		CtrPt = BoundaryCtr.ContourPoints.at(i);

		Img.at<Vec3b>(CtrPt.GetX(), CtrPt.GetY()).val[0] = DrwColor.val[0];
		Img.at<Vec3b>(CtrPt.GetX(), CtrPt.GetY()).val[1] = DrwColor.val[1];
		Img.at<Vec3b>(CtrPt.GetX(), CtrPt.GetY()).val[2] = DrwColor.val[2];

	}

	std::stringstream ss;

	//Skip Printing background lable, because it is confusing
	if( BoundaryCtr.GetLabel() == BACKGROUND_LABEL )
	{
		RetImage.SetImage(Img);
		return RetImage;
	}

	ss << BoundaryCtr.GetLabel();
	string strLabel = ss.str();

	Center = BoundaryCtr.GetCenter();
	Pt = Center.GetPoint();

	if(bPutText)
	{
		Img = PutText(Img, strLabel, DrwColor, Pt );
	}

	ss.clear();
	ss.flush();
	ss.str("");

	RetImage.SetImage(Img);

	return RetImage;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: ColorImg
 * Created On	: May 5, 2013
 * Created By 	: hrushi
 * Comments		: Overlays the image point on the color image
 * Arguments	: const vector<ImagePt> vPt,  const int Delay, cv::Scalar DrwColor, const Args& args
 *******************************************************************/
ColorImg ColorImg::Overlay( const vector<ImagePt> vPt,  const int Delay, cv::Scalar DrwColor, const Args& args) const
{
	ColorImg OverlayImg;
	cv::Mat Img = m_data.clone();

	for( unsigned int i = 0; i < vPt.size(); i++ )
	{
		ImagePt Pt = vPt.at(i);
		Pt.SwapXY(); // Swap because of the images are stored.
		Img.at<Vec3b>(Pt.GetX(), Pt.GetY())[0] = DrwColor.val[0];
		Img.at<Vec3b>(Pt.GetX(), Pt.GetY())[1] = DrwColor.val[1];
		Img.at<Vec3b>(Pt.GetX(), Pt.GetY())[2] = DrwColor.val[2];
	}

	OverlayImg.SetImage(Img);

	return OverlayImg;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: ColorImg
 * Created On	: May 5, 2013
 * Created By 	: hrushi
 * Comments		: Overlays an ImagePt on the Color Image
 * Arguments	: const vector<ImagePt> vPt,  const int Delay, cv::Scalar DrwColor, const Args& args
 *******************************************************************/
ColorImg ColorImg::Overlay( const ImagePt imPt,  const int Delay, cv::Scalar DrwColor, const Args& args) const
{
	ColorImg OverlayImg;
	cv::Mat Img = m_data.clone();

	ImagePt Pt = imPt;
	//Pt.SwapXY(); // Swap because of the images are stored.
	cv::Rect RBox( Pt.GetX(), Pt.GetY(), 6, 6 );
	cv::rectangle(Img, RBox, DrwColor, CV_FILLED, CV_AA, 0);

	OverlayImg.SetImage(Img);

	return OverlayImg;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: int
 * Created On	: Dec 5, 2013
 * Created By 	: hrushi
 * Comments		: Overlay a rectangle over the image
 * Arguments	: const vector<cv::Rect>& Rt
 *******************************************************************/
int ColorImg::Overlay( const vector<cv::Rect>& Rt, const cv::Scalar RectColor)
{
	for(auto r : Rt)
	{
		Overlay(r, RectColor);
	}

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Overlay
 * Return Type 	: int
 * Created On	: Mar 8, 2014
 * Created By 	: hrushi
 * Comments		: Overlay Color for a single rectangle
 * Arguments	: const cv::Rect& Rt, const cv::Scalar RectColor
 *******************************************************************/
int ColorImg::Overlay( const cv::Rect& Rt, const cv::Scalar RectColor)
{
	UINT lineWidth = 3;
	cv::rectangle(m_data, Rt.tl(), Rt.br(), RectColor, lineWidth);

	return EXIT_SUCCESS;
}


/*******************************************************************
 * Function Name: Mask
 * Return Type 	: int
 * Created On	: Nov 24, 2013
 * Created By 	: hrushi
 * Comments		: Masks the current image with given mask
 * Arguments	: const BinaryImg& Msk
 *******************************************************************/
int ColorImg::Mask( const GrayImg& Msk)
{
	UINT Mask_numRows = Msk.GetNumRows();
	UINT Mask_numCols = Msk.GetNumCols();

	if(Msk.GetNumCols() != GetNumCols() || (Msk.GetNumRows() != GetNumRows() ))
	{
		cerr << "Mask should be of the same dimension of *this image " << endl;
		cerr << "Mask Props: " << endl;
		Msk.ImageProps();

		cerr << "Current Image Props: " << endl;
		ImageProps();

		throw ERR_DIMENSION_MISMATCH;
	}


	ColorImg ChipImg(GetNumRows(), GetNumCols(), COLOR_WHITE);

	for(UINT i = 0; i < Mask_numRows; i++ )
	{
		for(UINT j = 0; j < Mask_numCols; j++ )
		{
			UINT PixVal = Msk.at(i, j);

			if(PixVal == (UINT)MAX_GRAY_VALUE)
			{
				ChipImg.at(i,j, at(i,j));
			}
		}
	}

	//---------- Copy the chip image  ---------- //
	*this = ChipImg;

	return EXIT_SUCCESS;
}
