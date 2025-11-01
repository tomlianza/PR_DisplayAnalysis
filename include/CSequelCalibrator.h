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
// SequelCalibrator.h: interface for the CSequelCalibrator class.
//
//////////////////////////////////////////////////////////////////////
//#define SGIFP //Set this for sgi builds

#ifdef SGIFP
	#include "sensor.h"
	#define   SENSOR_WR		0x30
	#define   SENSOR_RD		0x31
#endif

#ifdef _ecVERSION_
	#include "ManchesterB.h"
#endif

#include "Sipcal.h"
#include "Chrfuncs.h"

#if !defined(AFX_SEQUELCALIBRATOR_H__230CBCA1_DD04_11D1_865F_444553540000__INCLUDED_)
#define AFX_SEQUELCALIBRATOR_H__230CBCA1_DD04_11D1_865F_444553540000__INCLUDED_

//this class will now be a child of CGenericCalibrator (a pure virtual class)
#include "CGenericCalibrator.h"


#ifdef WIN32
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#endif



/**************************************************************************\
	MyCalibrator.sciData.whichCalibrator = CalTypeChromaTech;		//must be initialized before calling initialize
	MyCalibrator.sciData.whichGammaCalibrator = GammaTypeNone;		//  ""  
	MyCalibrator.sciData.whichChromaCalibrator = ChromaTypeSerial;	// ""
	MyCalibrator.sciData.usPort = 1;
	MyCalibrator.sciData.pw = {0x47, 0x72, 0x4d, 0x62};
	MyCalibrator.lumUnit = luCandelas;

\***************************************************************************/

typedef enum 
{
	GammaTypeNotImplemented = -2,
	GammaTypeNone = -1,
	GammaTypeSerial = 0,
	GammaTypeUSB,
	GammaTypeSGI_I2C,
	GammaTypeEnableCable
}GammaType;

typedef enum
{
	ChromaTypeNotImplemented = -2,
	ChromaTypeNone = -1,
	ChromaTypeSerial ,
	ChromaTypeUSB,
	ChromaTypeUSBAdapter,
	ChromaTypeADB, 
	ChromaTypeSGI_I2C,
	ChromaTypeUSBSigma,  // added Oct 2001 treat Sigma as a special case of Chroma4USB
	ChromaTypeAutoFind

}ChromaType;

typedef enum 
{
	CalTypeNone = -1,
	CalTypeGamma,
	CalTypeChroma,
	CalTypeChromaTech,
	CalTypeEZ,
	CalTypeManchester
}CalType;

typedef enum 
{

	CalStatusClassNotInitialized  = -100,
	CalStatusCalTypeEnum          = - 99,
	CalStatusChromaTypeEnum       = - 98,
	CalStatusGammaTypeEnum        = - 97,
	CalStatusCalibratorNotFound   = -1,
	CalStatusCalibratorFound      =  0
}CalStatus;

typedef struct SequelCalibratorInfo
{
	CalType			whichCalibrator;     //must be initialized before calling initialize
	GammaType		whichGammaCalibrator;//  ""  
	ChromaType		whichChromaCalibrator;// ""
	long			lSerialNumber;
	char			cDeviceVersionString[256];
	char			cToolKitVersionString[256];
	unsigned short	usPort;
	unsigned char   pw[4];
	bool            bUsePassword; 
}SequelCalibratorInfo;

typedef struct _GammaDeviceData
{

// Calibration Info for Gamma Device 
	
	bool    bCalDataInitilized;  // set to true after setting primary measurement data
	bool    bScaleDataComputed;  // set to true after computing RGB scalling
	bool    bPeriodMode; // false = count is frequency mode, true = count is period mode
	bool    bNoDivideError;
	dXYZ	RedXYZofWhite;		// used for Gamma device
	dXYZ	GreenXYZofWhite;	// used for Gamma device
	dXYZ	BlueXYZofWhite;		// used for Gamma device

	dYxy    RedYxy;
	dYxy    GreenYxy;
	dYxy    BlueYxy;
	
	double  dRedScale;
	double  dGreenScale;
	double  dBlueScale;
	double  dRedValue;			// Used by routine GetGammaYxy to calculate the data.  This must be set beforing calling!
	double  dGreenValue;		// Used by routine GetGammaYxy to calculate the data.  This must be set beforing calling!
	double  dBlueValue;			// Used by routine GetGammaYxy to calculate the data.  This must be set beforing calling!
	double  dRedCalValue;
	double  dGreenCalValue;
	double  dBlueCalValue;
	long    lCountData;	 // Measurement obtained based upon boolean lPeriodMode;
	long    lBlackCountData;        // Dark Count;
	long    lWriteReadDelay; // nominally in millisecs;
	double	dRawScaled;
}GammaDeviceData;

typedef enum LuminaceUnits
{

	luFootLamberts = FOOT_LAMBERTS ,
	luCandelas =  CANDELAS 


}CalLuminanceUnit;

typedef enum MeasSpeed
{

	msRealFast	= 8,
	msFast		= 12,
	msNormal	= 16,
	msLong		= 32

}MeasSpeed;

typedef enum
{
	CALIBRATOR_TECHNOLOGY_CRT,
	CALIBRATOR_TECHNOLOGY_LCD
}CALIBRATOR_TECHNOLOGY;


class CSequelCalibrator  : public CGenericCalibrator
{
public:
	void TurnLEDsOff();
	void TurnLEDsOn();
	void SetLEDs(unsigned char mask);
	bool MeasureAmbient(dYxy *dYxyAmbient);
	CalibratorHeader m_calhdr;
	CSequelCalibrator();
	virtual ~CSequelCalibrator();
	virtual bool	InitializeCalibrator(void *caldata = NULL);
	virtual bool	CloseCalibrator();
	virtual bool    AutoAttach();
	virtual bool	AddExisting(void *caldata=NULL);
	virtual bool	IsLuminanceOnlyDevice();
	
	
	virtual unsigned long GetSerialNumber();
	virtual char *GetVersionString() {return sciData.cDeviceVersionString;}
	virtual char *GetToolkitVersionString() {sipGetToolkitRev(sciData.cToolKitVersionString); return sciData.cToolKitVersionString;}
	virtual int SetDarkCurrentValues(int numsamples);
	virtual bool GetDarkCurrentValues (double *red, double *green, double * blue);
	virtual int GetCalibratorType();
	virtual bool CalibratorDoesDarkCurrent();
	virtual bool CalibratorRequiresFrequencyBeforeDarkCurrent();
	virtual void SetTechnology (CALIBRATOR_TECHNOLOGY tech);
	virtual CALIBRATOR_TECHNOLOGY GetTechnology ();
	virtual bool SupportsTechnology(CALIBRATOR_TECHNOLOGY tech);

	virtual void SetMeasureMode (MEASURE_TYPE mode);
	virtual MEASURE_TYPE CSequelCalibrator::GetMeasureMode ();
	virtual bool CSequelCalibrator::SupportsMeasureMode(MEASURE_TYPE mode);

	virtual void MeasureYxyEx();
	virtual bool MeasureYxyCRTMode();
	virtual bool MeasureYxyCRTMode(dYxy *outYxyData);
	virtual bool SupportsAmbientMeasurements();

// General Measurement Functions	
	virtual void	MeasureFrequency();
	virtual bool	MeasureYxy(int numAvg=1); //we now specify how many times to measure, and average 11/13/02
 	//inline void 	MeasureYxy(){ MeasureYxy(1); }
	virtual bool	MeasureYxyProgramMode();
	virtual bool	MeasureYxyProgramMode(dYxy *outYxyData);

	
		
	virtual void    SetMeasurementSpeed();
	
// General Utility functions
	virtual bool	GetIntegrationTimeSeconds(); // data returned in variable IntegrationTimeSecs
    virtual bool	SetIntegrationTimeSeconds(); // set data in IntegrationTimeSecs!
	virtual bool	GetRGBfromYxy(); // Used for nulling applications: Not valid for Gamma Device

	// Sequel Gamma Device specific calls 
	virtual void	MeasureLumOnlyRedY();		// assumes a red patch is displayed
	virtual void	MeasureLumOnlyGreenY();	// assumes a green patch is displayed
	virtual void	MeasureLumOnlyBlueY();	// assumes a blue  patch is displayed
	virtual void	GetLumOnlyYxy(dYxy *inYxy); // puts data into inYxy
	virtual void    CalcRedScaleFactor();   // assumes appropriate red of white is on screen;
	virtual void    CalcGreenScaleFactor(); // assumes Green of white is on screen
	virtual void    CalcBlueScaleFactor();  // assumes Blue of white is on screen;  
	virtual void    CalcCorrectedScaleFactors(); // additional trim after all three values have been calculated. 
	virtual long    GetLumOnlyData();
	virtual void    MeasureLumOnlyBlack();
	virtual void    SetLumOnlyRedMonitorYxy(dYxy *inYxy); //let the calibrator know about the monitors red chromaticity
	virtual void    SetLumOnlyGreenMonitorYxy(dYxy *inYxy); //let the calibrator know about the monitors green chromaticity
	virtual void    SetLumOnlyBlueMonitorYxy(dYxy *inYxy); //let the calibrator know about the monitors blue chromaticity

//Public Variables
	CalStatus               sciStatus;
	SequelCalibratorInfo	sciData;
    GammaDeviceData         gddData;
	CalLuminanceUnit         lumUnit;

	dYxy	AmbientYxy;
	dYxy	CalYxy;
	dRGB	CalRGB;
	dXYZ	CalXYZ;
	
	double IntegrationTimeSecs;
	double Frequency;
	MeasSpeed  MeasurementSpeed;
	
	bool     m_bCalibratorAttached;
#ifdef _ecVERSION_
	bool				m_bEnableCableOpen;
	MANCHESTER_DATA		m_ManchesterData; 
#endif
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage); // this is for CGenericCalibrator

	//we need to conform to CGenericCalibrator
	// Query functions for capabilities 
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech);
	virtual bool    SupportsDarkCurrentMeasurement();
	virtual bool    SupportsSetFrequency();
	virtual bool    SupportsLEDs();
	virtual bool    SupportsSetIntegrationTimeSecs();
	virtual bool    SupportsRGBdataConversion();
	virtual bool    SupportsMATRIXreturn(); 
	virtual bool	SupportsDarkCurrentValueReturn();
	
	virtual bool SetDarkCurrent(int numSamples=10);
	virtual bool GetIntegrationTimeSecs(double *secs);
	virtual bool SetIntegrationTimeSecs();
	virtual bool GetSerialNumber(char*);
	virtual bool SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY);
	virtual bool GetRGBfromYxy(dYxy*, dRGBColor*);
	virtual bool GetRGB2XYZmatrix(double*);
	//virtual bool GetDarkCurrentValues(double *red, double *green, double *blue);
	
	//multi cal support
	virtual bool AttachWithInventoryInfo(CALINVENTORY *calInv);
private:
// Private stuff
	long TxSensor( int address, unsigned char *buffer, long length );
	long RxSensor( int address, unsigned char *buffer, long length );

	double	dGammaWhiteRatios[3];
	double	dGammaMeasuredRatios[3];

	CALDATA_BLOCK *m_caldata;

	long	InitializeCalibratorSerial(unsigned short usPort);
	void	CloseCalibratorSerial();
	bool	InitializeGamma(GammaType whichGamma);
	bool	InitializeEZ();

	CALIBRATOR_TECHNOLOGY m_calTechnology;
	MEASURE_TYPE	m_MeasMode;
};

#endif // !defined(AFX_SEQUELCALIBRATOR_H__230CBCA1_DD04_11D1_865F_444553540000__INCLUDED_)
