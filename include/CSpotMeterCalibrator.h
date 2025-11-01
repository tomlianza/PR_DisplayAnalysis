/*
 *  CSpotMeterCalibrator.h
 *  BlueEye.XCode
 *
 *  Created by Ben Guthro on Mon Mar 21 2005.
 *  Copyright (c) 2005 gmb. All rights reserved.
 *
 *  This class is a C++ abstraction of the CirrusSDK
 *  
 */
#include "CGenericCalibrator.h"
#include "SpotMeterSDK.h"
class CSpotMeterCalibrator  : public CGenericCalibrator
{
public:
	CSpotMeterCalibrator();
	virtual ~CSpotMeterCalibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){ return (bool)(whichDisplayTech & (CAL_DISPLAY_TECHNOLOGY_CRT|CAL_DISPLAY_TECHNOLOGY_LCD|CAL_DISPLAY_TECHNOLOGY_DLP));};
	virtual bool	SupportsNamedCalibrations(){ return true; }

	//device capabilities - only override what we DO support
	// all others will default to parents false
	virtual bool	SupportsSetIntegrationTimeSecs(){return true;}
	virtual bool	SupportsRGBdataConversion(){return true;}
	virtual bool    SupportsMATRIXreturn(){return true;}
	virtual bool    SupportsDarkCurrentMeasurement(){return true;}
	
	// tech specific functions
	virtual bool    SetIntegrationTimeSecs(double numSecs);
	virtual bool	GetIntegrationTimeSecs(double *secs);
	
	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech);
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData);
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3);
	virtual int		GetCalibratorType();
	
	virtual char	*GetVersionString() {return "SpotMeterCal v0.1";}
	virtual char	*GetToolkitVersionString() {return gmbSpotGetToolkitVersion(NULL);}
	
	virtual bool    SetDarkCurrent(int numSamples=10);

	virtual int		GetNamedCalibrationCount();
	virtual bool	GetNamedCalibrationFromIndex(int *slot, unsigned char* name, unsigned int strlen);

	virtual bool	SelectNamedCalibration(unsigned char*);
	virtual bool	SelectNamedCalibration(unsigned int);

	
protected:	
	gmbSpotHandle	m_device;

	bool dYxy2spotYxy(dYxy *in, gmbSpotYxy_t *out);
	bool spotYxy2dYxy(gmbSpotYxy_t *in, dYxy *out);
	bool spotRGB2dRGB(gmbSpotRGB_t *in, dRGB *out);
	bool dRGB2spotRGB(dRGB *in, gmbSpotRGB_t *out);
};