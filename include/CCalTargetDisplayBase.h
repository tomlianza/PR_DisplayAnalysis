/*
 * Copyright 1998, Sequel Imaging, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Sequel Imaging, Inc.,
 * 25 Nashua Rd, Londonderry, NH 03053.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SEQUEL IMAGING, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SEQUEL IMAGING, INC.
 */
// CalTargetDisplay.h: interface for the CCalTargetDisplay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALTARGETDISPLAYBASE_H__230CBCA2_DD04_11D1_865F_444553540000__INCLUDED_)
#define AFX_CALTARGETDISPLAYBASE_H__230CBCA2_DD04_11D1_865F_444553540000__INCLUDED_

#ifdef WIN32
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#endif

// Don't need to include all of the Sipcal stuff. Just the three typedefs below.
//#include "CSequelCalibrator.h"

//#include "cieColor.h"

#include "ColorStructs.h"


typedef struct xy_specDisplay
{

	bool   bRefreshDisplay;  // always erase last point if true
	bool   bShowTargetOnly;  //Don't do calculation yet
	bool   bOne2OneAspectRatio;  // Maintain a 1:1 aspect ratio when plotting
	dYxy  *ReferenceAbsolute;
	dYxy  *MeasuredAbsolute;
	dRGB  *DisplayAdjustment;
	// Set up constants for plot data
 // used for error rings...
	double dxySpec;	

}xy_SpecDisplay;

typedef struct xy_CTDisplay 
{

	double dxRed;
	double dyRed;

	double dxGreen;
	double dyGreen;

	double dxBlue;
	double dyBlue;


	double dxWhite;
	double dyWhite;

}dxy_CTDisplay;

class CCalTargetDisplayBase
{
public:
	CCalTargetDisplayBase() {};
	virtual ~CCalTargetDisplayBase() {};
	virtual void DisplayPatchColor(bool) = 0;
	virtual void DisplayBlackBackground(bool) = 0;		
	virtual void BuildTargetValues(double dGamma) = 0; //builds an RGB array of 100 values corresponding to L*0->100

	dRGB  m_LstarValues[100];   //RGB values computed and indexed by Lstar
	short Red;
	short Green;
	short Blue;
	long  lSettleTime; // in millisecs
	xy_SpecDisplay		SpecData; // data for xy target adjustment apps.
	dxy_CTDisplay       CTdata;   // data for color temperature plot 

private:
};

#endif

