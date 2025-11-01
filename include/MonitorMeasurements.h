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
// MonitorMeasurements.h: interface for the CMonitorMeasurements class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORMEASUREMENTS_H__F3E979C0_E0FC_11D1_96C9_004033E05B37__INCLUDED_)
#define AFX_MONITORMEASUREMENTS_H__F3E979C0_E0FC_11D1_96C9_004033E05B37__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SequelCalibrator.h"
#include "CalTargetDisplay.h"
#define START_TEMP 4000
#define END_TEMP 24950
#define TEMP_INC 50
#define N_MEASURED_PTS   18
#define nearzero 1.0E-20
#define D_MULT 10000
#define realtype double

#define MAX_MEASURED_POINTS N_MEASURED_PTS
#define LINEARFIT		1
//#define SPLINEFIT		1

#define USE_GAMMA_ESTIMATES   0


typedef struct blackbody_point{
double ColorTemp;
double u;
double v;
}BlackBodyPoint;

 

typedef struct _polycurve
{

	short npts; 
	realtype *xpt;
	realtype *ypt;
	
}POLYCURVE; 

typedef POLYCURVE Pcurv;

typedef enum _MapperErrors 
{
 	MAPPER_OK= 0,
 	MAPPER_NEEDS_MORE_POINTS1,
 	MAPPER_NEEDS_MORE_POINTS2,
 	MAPPER_MEMORY_ERROR,
	MAPPER_SPLINE_ERROR
 	
}MAPPER_ERROR; 


typedef struct MonitorMeasurements
{
// Measured Data
	dYxy	Red;
	dYxy	Green;
	dYxy	Blue;
	dYxy	White;
	dYxy	Black;
	dYxy    GrayRamp[N_MEASURED_PTS];//Yxy Data usually 18 points and equally spaced.
	dRGB    GrayRGB[N_MEASURED_PTS]; // Values used to measure the ramp target
	double  dFrequency;

//Calculated single point data
	double  dMonitorGamma;
	double  dMonitorColorTempB;// BlackBody locus
	double  dMonitorColorTempC;// CIE locus
//Data calculated for use by other routines but specific to this measurement set.
	dRGB    GrayRGBfromRamp[N_MEASURED_PTS]; // the nominal RGB data synthesized from the Yxy data
	double  dXYZ2RGB[9];
	double  dRGB2XYZ[9];
}MONITORMEASUREMENTS; 

typedef struct MonitorLuts
{

	short Red[256];
	short Blue[256];
	short Green[256];

}MonitorLuts;

typedef struct MonitorLuts16
{
	short	Red[65536];
	short   Green[65536];
	short   Blue[65536];


}MonitorLuts16;

#ifndef _CTData_
#define _CTData_
	typedef struct CTData {
		DWORD  sindex;
		double dRMK;
		double dTemp;
		double du;
		double dv;
		double dslope;
	}CTPoint;
#endif

typedef struct xyL 
{
	double x;
	double y;
	double z;
	double L;


}xyL;

typedef struct uvL 
{
	double u;
	double v;
	double w;
	double L;


}uvL;


class CMonitorMeasurements  
{
public:
	CMonitorMeasurements();
	virtual ~CMonitorMeasurements();
	// These variables must be set for the class functions to work.
	CGenericCalibrator *Calibrator;// this is the calibrator to use
	CCalTargetDisplay *Display;	// this is the display class to use
	CProgressCtrl *ProgressBar; // Must be set to NULL if progress bar is not used.
	CStatic       *TestText;    // Must be set to NULL if no test text is needed.
	HWND		  CancelHwnd;

	MONITORMEASUREMENTS currentMeasurements; 
	
	MONITORMEASUREMENTS desiredMeasurements;

	bool m_bDesiredMeasurementsValid;
	bool m_bCurrentMeasurementsValid; //Set after Full suite is measured 
	bool m_bLutCalcOK; // The lut is valid 
	MonitorLuts         currentLuts;
// Measurement functions
	bool MeasureFullSuite(); //the desired Measurement field should be filled and the boolean set.
	bool MeasureSetUp();
	bool MeasureRed();
	bool MeasureGreen();
	bool MeasureBlue();
	bool MeasureBlack();
	bool MeasureWhite();
	bool MeasureGrayRamp();
	bool MeasureFrequency();
	bool CheckForCancel();
//Data extraction routines    
	double GetGamma();
	double GetColorTempBlackBody();
	double GetColorTempCIEDaylight();
//m_bCurrentMeasurementsValid must be set to true for these to work;
	bool CalcMonitorMetrics();
	bool CalcMonitorMatrices();
	bool CalcRGBRamp();
	void TrimRGBChromaForWhitePoint();
//m_bDesiredMeasurementsValid and the above functions must have been executed before calculating luts
	bool CalcCorrectionLut();
// General purpose functions
	void GetCIExyFromColorTemp(double *x, double *y, double CT);
	double Pxy2Kelvin(double x, double y	);
	short Kelvin2xy(double ColorTemp,double *x, double *y);
	double xy2Kelvin(double x, double y);
	void LinInterpPos (double *xIn,double *yIn, short countIn,double *xOut,double *yOut, short countOut);
	
	
	void xyL_XYZ( xyL *xyLptr, dXYZ *XYZptr );
	void Yxy2XYZ(dYxy *YxyData,dXYZ *XYZdata);
	void XYZ2Yxy(dXYZ *XYZdata,dYxy *YxyData);
	short MatMult ( double *aptr, short nrow, short pcol, double *bptr, short prow, short ncol, double *outptr);


	
	CTPoint sgColorTempData[31]; 


	void MeasureDisplayedColor(short sRed,short sGreen,short sBlue);
		 

	void Invert ( double *matptr,  short order );
	void Trans ( double *inptr, short nrow, short ncol, double *outptr );
	
	short A_solve(double *c_mat,short c_rows,short c_cols,double *b_mat,short b_rows,short b_cols, double *a_mat);
	short find_yd(double x,double *yd);
	void CalcSpline(realtype *xv, realtype *coef, short n, realtype x, realtype *y);
	short CubicSplines(realtype *x, realtype *y, short n, realtype *s);

	void xyL_uvL( xyL *xyLptr, uvL *uvLptr );

private:	
	/* Routines from mapper stuf*/

 
MAPPER_ERROR Mapper(Pcurv* Measured, Pcurv* Desired, Pcurv* Output); 
void tridiag(realtype *mat, short n, realtype *vec);

realtype PolyCalc(realtype XIn, realtype *CoefVector, int order) ;



};

#endif // !defined(AFX_MONITORMEASUREMENTS_H__F3E979C0_E0FC_11D1_96C9_004033E05B37__INCLUDED_)
