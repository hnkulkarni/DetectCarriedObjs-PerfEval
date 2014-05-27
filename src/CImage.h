/*
 * CImage.h
 *
 *  Created on: Dec 23, 2012
 *      Author: hrushi
 */

#ifndef CIMAGE_H_
#define CIMAGE_H_

#include "ProjectIncludes.h"

const UINT IMAGE_TYPE_COLOR 	= 1;
const UINT IMAGE_TYPE_GRAY		= 2;
const UINT IMAGE_TYPE_BINARY	= 3;


/**********************************************
 * 			Text Overlay Constants
 **********************************************/
const unsigned int TOP_CENTER		= 0;
const unsigned int TOP_LEFT		= 1;
const unsigned int TOP_RIGHT		= 2;
const unsigned int BOTTOM_CENTER	= 3;
const unsigned int BOTTOM_LEFT	= 4;
const unsigned int BOTTOM_RIGHT	= 5;

class CImage
{

protected:
	/**********************************************
	 * 			Protected Data Members
	 **********************************************/
	unsigned int m_ncols;
	unsigned int m_nrows;
	cv::Mat m_data;
	fs::path m_ImagePath;

	unsigned int m_ImageType;

	/**********************************************
	 * 			Protected: Helper Functions
	 **********************************************/
	int Copy_CImage( const CImage& rhsCImage );
	int Allocate_CImage( const CImage& rhsCImage );
	string Display( const Mat& Img, const double Delay ) const;

public:
	/**********************************************
	 * 			Code House Keeping
	 **********************************************/

	CImage();
	CImage( const cv::Mat& rhsMat );

	virtual ~CImage();

	// Assignment Operator
	const CImage& operator=( const CImage& rhsCImage );

	// Copy Constructor
	CImage( const CImage& rhsCImage );


	/**************************************************************
	 *           Pure Virtual Functions
	 **************************************************************/

	virtual int SetImageType() = 0; // This is used to load the image
	virtual int Initializer() = 0; // Forces its children to call Initializers

	/**********************************************
	 * 			Primary Operations
	 **********************************************/
	// Displays the Image for the given delay on the screen
	virtual string Display( const double Delay ) const;
	virtual string Display( const string WindowName, const double Delay) const;
	virtual string Display( const string WindowName, const Mat& Img, const double Delay ) const;

	// Write Image Function
	virtual int Write( const fs::path FilePath ) const;

	/**********************************************
	 * 			Accessors
	 **********************************************/
	// ImageProps
	virtual int ImageProps() const;

	// Accessors
	virtual unsigned int GetNumRows() const;
	virtual unsigned int GetNumCols() const;
	virtual const cv::Size GetImgSize()const { return m_data.size(); }
	virtual const cv::Mat GetDataRef() const;
	virtual fs::path GetImagePath() const;
	virtual int GetType() const;
	virtual unsigned char GetGrayVal(const unsigned int i, const unsigned int j) const;
	virtual int copyTo( Mat& cpyMat ) const;

	/**********************************************
	 * 			Mutators
	 **********************************************/
	virtual int Load( const fs::path FilePath  );

	virtual int UpdateNumRows();
	virtual int UpdateNumCols();
	virtual int UpdateImageParams();

	virtual int SetImagePath( const fs::path& Path );
	virtual int SetImage( const Mat& rhsImage, const fs::path& Path );
	virtual int SetImage( const Mat& rhsImaage );
	virtual int SetParams( const fs::path& Path );
	virtual int Resize(unsigned int uiNumRows, unsigned int uiNumCols );


	/**********************************************
	 * 			Put Text on an Image.
	 **********************************************/
	virtual const cv::Mat PutText( const string strText );
	virtual const cv::Mat PutText( const string strText, cv::Scalar DrwColor, const cv::Point Pt);
	virtual const cv::Mat PutText( const string strText, cv::Scalar BkColor, cv::Scalar DrwColor, const cv::Point Pt);

	virtual const cv::Mat PutText( const cv::Mat& Img, const string strText, cv::Scalar DrwColor, const cv::Point Pt) const;
	virtual const cv::Mat PutText( const cv::Mat& Img, const string strText, cv::Scalar BkColor,  cv::Scalar DrwColor, const cv::Point Pt, unsigned int FontSize) const;

	/**************************************************************
	 *           Add Legends on Image
	 **************************************************************/
	virtual const cv::Mat Legends( const string strText, const cv::Scalar BkColor, const cv::Scalar DrwColor, unsigned int Loc);
};

#endif /* CIMAGE_H_ */
