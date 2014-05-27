/*
 * ContourMap.h
 *
 *  Created on: Jan 2, 2013
 *      Author: hrushi
 */

#ifndef CONTOURMAP_H_
#define CONTOURMAP_H_

#include "Contour.h"
#include "ColorImg.h"
#include "GrayImg.h"
#include "VectorOp.h"
#include "CntrScoreMap.h"
#include "ReadHistLookup.h"
#include "Args.h"

class ColorImg; //Partial Declaration
class GrayImg; // Partial Declaration
class Contour; // Partial Declaration


typedef std::map< unsigned int, Contour > TYPE_MAP_ALL_CONTOUR;
/*******************************************************************
 * Class Name	: ContourMap
 * Created On	: Jan 21, 2013
 * Created By 	: hrushi
 * Comments		: This class contains the map of Contours and all related functions.
 *******************************************************************/
class ContourMap
{

private:

	// Helper Function
	virtual int Copy_ContourMap( const ContourMap& rhsContourMap );
	virtual int Allocate_ContourMap( const ContourMap& rhsContourMap );


protected:
	/**************************************************************
	 *           Protected Member Variables
	 **************************************************************/
	unsigned int ImageNumRows;
	unsigned int ImageNumCols;

	vector<int> LabelImage;
	vector<int> LabelList;

	vector<int> BkLabels; // Contains the list of background Labels.

	unsigned int NumLabels;

	CntrScoreMap ScoreMap;

	/**************************************************************
	 *           Protected Functions
	 **************************************************************/


public:
	ContourMap();
	ContourMap(  const unsigned int NumRows, const unsigned int NumCols );
	virtual ~ContourMap();

	// Copy Constructor
	ContourMap( const ContourMap& rhsContourMap );

	// Assignment Operator
	ContourMap& operator=( const ContourMap& rhsContourMap );

	/*******************************************************************
	 * Generic Member Functions
	 *******************************************************************/
	// Convert the Labels to Contours

	virtual int LabelsToContours( const vector<int>& Labelsmint, const Args& args );
	virtual Contour Eight_Connectivity(const vector<int>& LabeledImage, const unsigned int iNumRows, const unsigned int iNumCols, const unsigned int Label);
	virtual int CreateBinaryMask( Mat& BinaryImg, const vector<int>& LabeledImage, const int Label, ImagePt& TopLeft, ImagePt& BottomRight );
	virtual vector< unsigned int > GetEightNeighbours( Mat BinaryImage, int iRow, int iCol );
	virtual bool isBorderPixel(const unsigned int iRow, const unsigned int iCol, const unsigned int MaxRows, const unsigned int MaxCols) const;
	virtual bool isContourBorder( const vector< unsigned int >& EightNeighbours ) const;
	virtual bool isOnMask( const Mat& BinaryImage, const unsigned int iRow, const unsigned int iCol ) const;
	virtual GrayImg  GetCtrImg( bool bPutText ) const;
	virtual bool isNeighbouring( const Contour& Cntur1, const Contour& Cntur2) const;

	virtual int CalculateEveryContourHistgrm(const ColorImg& ProbeImage) ;
	virtual int UpdateContours( const Args& args);

	virtual int EditLabel(int NewLabel );
	virtual int ChangeLabel(int CurrentLable, int NewLabel );

	virtual int ListBkContours(const GrayImg& BkImg, double OverlapThreshold , const Args& args );
	virtual int PrintBkLabels() const;

	virtual int CopyLabelImage( vector<int>& CopyofLabelImg ) const;
	virtual int ReOrderLabels();
	virtual int GetListofLabels();

	virtual int PopulateScoreMap( const Args& args  );

	/******************************************************************
	 * Public Member Variables
	 ******************************************************************/
	TYPE_MAP_ALL_CONTOUR AllContourMap;

	/*******************************************************************
	 * Accessors
	 *******************************************************************/
	virtual unsigned int GetNumContours() const {return AllContourMap.size(); }
	virtual const vector< vector< cv::Point> > GetOpenCVCtrs() const;
	virtual int GetMatchingCandidate(  unsigned int Cntr, double ScoreThreshold ) const;
};

/*******************************************************************
 * Class Name	: PrintFunctor
 * Created On	: Jan 21, 2013
 * Created By 	: hrushi
 * Comments		: Prints all the elements in the vector
 *******************************************************************/
class Print
{
public:
	Print(){};

	/*******************************************************************
	 * Function Name: operator()
	 * Return Type 	: int
	 * Created On	: Jan 23, 2013
	 * Created By 	: hrushi
	 * Comments		: Prints all the elements in the vector
	 * Arguments	: int i
	 *******************************************************************/
	int	operator()( int i) const
	{
		cout << i << " ";

		return i;
	}


	~Print(){};
};




/*******************************************************************
 * Class Name	: ReplaceFunctor
 * Created On	: Jan 21, 2013
 * Created By 	: hrushi
 * Comments		: This funtor replaces an element in the vector with
 * 					the given value, if it is equal to the given variable
 *******************************************************************/
class EditFunctor
{
public:
	EditFunctor(int i, int j ): EditVal( i) , NewVal( j ) {}

	/*******************************************************************
	 * Function Name: operator()
	 * Return Type 	: void
	 * Created On	: Jan 21, 2013
	 * Created By 	: hrushi
	 * Comments		: If the element in the vector is equal to the
	 * 				  OriginalVal, it is replaced by the NewVal
	 * Arguments	: int i
	 *******************************************************************/
	int operator()(int i)
	{
		if(i == EditVal)
		{
			i = NewVal;
		}

		return i;
	}

private:
		int EditVal;
		int NewVal;
};



/*******************************************************************
 * Functor Name	: DecrementIf_Functor
 * Created On	: Jan 21, 2013
 * Created By 	: hrushi
 * Comments		: This Functor decrements the value of an element
 * 					in the vector if it is greater than the given
 * 					element.
 *******************************************************************/
class DecrementIf_Functor
{
public:
	DecrementIf_Functor(int i):CompareVal(i){}

	/*******************************************************************
	 * Function Name: operator()
	 * Return Type 	: int
	 * Created On	: Jan 22, 2013
	 * Created By 	: hrushi
	 * Comments		: Decrements the label value if the label is greater than given
	 *******************************************************************/
	int operator()(int i)
	{
		if(i > CompareVal)
		{

			i = i - 1;

		}

		return i;

	}

	~DecrementIf_Functor(){}

private:
	int CompareVal;

};

#endif /* CONTOURMAP_H_ */
