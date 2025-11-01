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
// SequelCalibrator.h: interface for the CGenericCalibrator class.
//
//////////////////////////////////////////////////////////////////////
#ifndef __CGENERICCALIBRATOR_H__
#define __CGENERICCALIBRATOR_H__

#include "cieColor.h"

typedef enum
{
	CAL_DISPLAY_TECHNOLOGY_CRT = 1,
	CAL_DISPLAY_TECHNOLOGY_LCD = 2,
	CAL_DISPLAY_TECHNOLOGY_DLP = 4,
	CAL_DISPLAY_TECHNOLOGY_LITEBOX_F = 8,
	CAL_DISPLAY_TECHNOLOGY_AMBIENT = 16,
}CAL_DISPLAY_TECHNOLOGY;


class CGenericCalibrator  
{
public:
	
	
	//  General Functions 
	CGenericCalibrator(){};
	virtual ~CGenericCalibrator(){};
	virtual bool	InitializeCalibrator(void *calSpecificData=NULL)=0;
	virtual bool	CloseCalibrator()=0;
	virtual bool    AutoAttach()=0;
	virtual bool	AddExisting(void *calSpecificData=NULL)=0;
	virtual bool    MeasureYxy(dYxy  *outYxyData, short sNumAverage=1)=0;
	virtual bool MeasureYxyAndSpectralData(double *spectralDataArray,
		dYxy *outYxyData, short sNumAverage=1) {return false;}

	virtual void	MeasureFrequency() {return;}
	virtual char	*GetVersionString() {return "V0.0";}
	virtual char	*GetToolkitVersionString() {return "v0.0";}
	virtual bool    MeasureAmbient(dYxy *dYxyAmbient) {return false;}

	// Query functions for capabilities 
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech)=0;
	virtual bool    SupportsDarkCurrentMeasurement(){return false;}
	virtual bool    SupportsDarkCurrentValueReturn(){return false;}
	virtual bool	SupportsAmbientMeasurements(){return false;}
	virtual bool    SupportsSetFrequency(){return false;}
	virtual bool    SupportsSetIntegrationTimeSecs(){return false;}
	virtual bool    SupportsRGBdataConversion(){return false;}
	virtual bool    SupportsMATRIXreturn(){return false;}
	virtual bool    CalibratorRequiresFrequencyBeforeDarkCurrent(){return false;}

	//for devices that index by name
	virtual bool	SupportsNamedCalibrations(){ return false; }

// Capability Functions 	
	virtual bool    SetDarkCurrent(int numSamples=10){return false;}
	virtual bool    GetDarkCurrentValues(double *red, double *green, double *blue){return false;}

	virtual bool    SetIntegrationTimeSecs(double numSecs){ return false; }
	virtual bool  GetIntegrationTimeSecs(double *secs){return false;}
	
	virtual unsigned long GetSerialNumber(){ return 0; };
	virtual bool    GetSerialNumber(char * strName){return false;}

	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech)=0;

	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData)=0;
// Extract the conversion matrix 
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3)=0; 
	
	virtual int		GetCalibratorType()=0;
	
	//functions for luminance only devices
	virtual bool	IsLuminanceOnlyDevice(){return false;}
	virtual void	MeasureLumOnlyRedY(){};		// assumes a red patch is displayed
	virtual void	MeasureLumOnlyGreenY(){};	// assumes a green patch is displayed
	virtual void	MeasureLumOnlyBlueY(){};	// assumes a blue  patch is displayed
	virtual void	GetLumOnlyYxy(dYxy *inYxy){}; // puts data into cal Yxy
	virtual void    SetLumOnlyRedMonitorYxy(dYxy *inYxy){}; //let the calibrator know about the monitors red chromaticity
	virtual void    SetLumOnlyGreenMonitorYxy(dYxy *inYxy){}; //let the calibrator know about the monitors green chromaticity
	virtual void    SetLumOnlyBlueMonitorYxy(dYxy *inYxy){}; //let the calibrator know about the monitors blue chromaticity

	// functions for SpectralDevices 
	virtual bool   CanSupportSpectralData() {return false ;}
	virtual bool   GetSpectralDataInfo( double *nmRangeLow, double *nmRangeHigh, double *nmIncrement){ return false; }
	virtual void   GetSpectralData(double * spectralDataArray, bool usePreviousData = false){};
	
	// functions for Flashy LEDs
	virtual bool    SupportsLEDs() {return false; }
	virtual void	TurnLEDsOff(){}
	virtual void	TurnLEDsOn(){}
	virtual unsigned short GetNumberOfLEDs() { return 0; }
	virtual void	SetLEDs(unsigned char mask){}

	//functions for named calibrations
	virtual int		GetNamedCalibrationCount() { return 0; }
	virtual bool	GetNamedCalibrationFromIndex(int *index, unsigned char* name, unsigned int cnt){return false;} 
	virtual bool	SelectNamedCalibration(unsigned char*) {return false;}
	virtual bool	SelectNamedCalibration(unsigned int) {return false;}


	// Initial support for embedded calibrators
	bool m_embedded;
	virtual void	SetEmbeddedCalibrator(bool isEmbedded) { m_embedded = isEmbedded;}
	virtual bool	IsEmbeddedCalibrator() {return false;}

	// allows for optional sign-on message from the calibrator - for GenMeasureTool use
	virtual bool	SupportsSignonMessage() {return false;}
	virtual unsigned char *GetSignonMessage() { return NULL;}
};

#endif

