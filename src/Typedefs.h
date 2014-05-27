/*
 * Typedefs.h
 *
 *  Created on: Jan 13, 2013
 *      Author: hrushi
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include "CPPIncludes.h"
#include "OpenCV_Includes.h"

/**************************************************************
 *           Premitive Typedefs
 **************************************************************/
typedef unsigned int UINT;
typedef unsigned long * ULONG_PTR;
typedef unsigned char WCHAR;
typedef const unsigned int CUINT;

/**************************************************************
 *          Vector Typedefs
 **************************************************************/
typedef vector<double> VDOUBLE;
typedef vector< vector<double> > VVDOUBLE;

/**************************************************************
 *           Pair Typedefs
 **************************************************************/
typedef std::pair<int, double> pr_score;
typedef std::pair<cv::Mat, cv::Mat> pr_Mat_Mat;

/**************************************************************
 *           Map Typedefs
 **************************************************************/
typedef std::map<string, vector<string> > mp_Str_vStr;
typedef std::map<UINT, string> mp_UINT_Str;
typedef std::map<string, cv::Mat> mp_Str_Mat;

#endif /* TYPEDEFS_H_ */
