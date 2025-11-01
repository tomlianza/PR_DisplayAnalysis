/*
 *  CCirrusCalibrator.h
 *  BlueEye.XCode
 *
 *  Created by Ben Guthro on Mon Mar 21 2005.
 *  Copyright (c) 2005 gmb. All rights reserved.
 *
 *  This class is a C++ abstraction of the CirrusSDK
 *  
 */
#include "CGenericCalibrator.h"
#include "CirrusMonSDK.h"
class CCirrusCalibrator  : public CGenericCalibrator
{
public:
	CCirrusCalibrator();
	CCirrusCalibrator
		(unsigned int vid, unsigned int pid, unsigned char pw[4]);

	virtual ~CCirrusCalibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech)
		{ return (whichDisplayTech & (CAL_DISPLAY_TECHNOLOGY_CRT|CAL_DISPLAY_TECHNOLOGY_LCD|CAL_DISPLAY_TECHNOLOGY_AMBIENT)) !=0;};
	
	//device capabilities - only override what we DO support
	// all others will default to parents false
	virtual bool	SupportsAmbientMeasurements(){return true;}
	virtual bool	SupportsSetIntegrationTimeSecs(){return false;}
	virtual bool	SupportsRGBdataConversion(){return true;}
	virtual bool    SupportsMATRIXreturn(){return true;}
	
	// tech specific functions
	virtual bool    MeasureAmbient(dYxy *dYxyAmbient);
	virtual bool    SetIntegrationTimeSecs(double numSecs);
	virtual bool	GetIntegrationTimeSecs(double *secs);
	
	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech);
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData);
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3);
	virtual int		GetCalibratorType();
	
	virtual char	*GetVersionString() {return "CirrusCal v0.1";}
	virtual char	*GetToolkitVersionString() {return "v0.1";}
	
	// functions for Flashy LEDs
	virtual bool    SupportsLEDs() {return true; }
	virtual void	TurnLEDsOff();
	virtual void	TurnLEDsOn();
	virtual unsigned short GetNumberOfLEDs();
	virtual void	SetLEDs(unsigned char mask);

	virtual void	SetEmbeddedCalibrator(bool isEmbedded) { m_embedded = isEmbedded;}
	virtual bool	IsEmbeddedCalibrator() {return m_embedded;}

	virtual bool	SelectNamedCalibration(unsigned char*);
	
protected:	
	gmbCirHandle	m_device;

	bool dYxy2cirYxy(dYxy *in, gmbCirYxy_t *out);
	bool cirYxy2dYxy(gmbCirYxy_t *in, dYxy *out);
	bool cirRGB2dRGB(gmbCirRGB_t *in, dRGB *out);
	bool dRGB2cirRGB(dRGB *in, gmbCirRGB_t *out);
};