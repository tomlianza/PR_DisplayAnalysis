/*
 *  CI1ProCalibrator.h
 *
 *  Created by Ben Guthro on Mon Mar 21 2005.
 *  Copyright (c) 2005 gmb. All rights reserved.
 *
 *  This class is a C++ abstraction of the EyeOne SDK
 *  
 */
#ifndef __CI1PROCALIBRATOR_H__
#define __CI1PROCALIBRATOR_H__

#include "CGenericCalibrator.h"
#ifdef WIN32
#include "EyeOne.h"
#else
#import <i1C/EyeOne.h>
#endif
class CI1ProCalibrator  : public CGenericCalibrator
{
public:
	CI1ProCalibrator();
	virtual ~CI1ProCalibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	virtual bool MeasureYxyAndSpectralData(double *spectralDataArray, dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){ return (bool)(whichDisplayTech & (int)(CAL_DISPLAY_TECHNOLOGY_CRT|CAL_DISPLAY_TECHNOLOGY_LCD));}
	virtual bool    SupportsDarkCurrentMeasurement(){return true;}

	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);

	//null op for this device
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){return true;}
	
	virtual bool    SetDarkCurrent(int numSamples=10);

	virtual int		GetCalibratorType(){ return -1;};
	
	virtual char	*GetVersionString() {return "I1ProCal v0.2";}
	virtual char	*GetToolkitVersionString() { return (char*)I1_GetOption(I1_VERSION); }
	
	//to support later?
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData){return false;};
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3){return false;};


	// functions for SpectralDevices 
	virtual bool   CanSupportSpectralData() {return true;}
	virtual bool   GetSpectralDataInfo( double *nmRangeLow, double *nmRangeHigh, double *nmIncrement);
	virtual void   GetSpectralData(double * spectralDataArray, bool usePreviousData = false);
	
protected:	

};

#endif