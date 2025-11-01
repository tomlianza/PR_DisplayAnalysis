// This is a wrapper class for Tom's CS1000 class
// to interface with the CGenericCalibrator class

#ifndef __CCS1000CALIBRATOR_H__
#define __CCS1000CALIBRATOR_H__

#include "CGenericCalibrator.h"
#include "ColorDataAdjuster.h"

class C_cs1000a;

class CCS1000Calibrator  : public CGenericCalibrator
{
public:
	CCS1000Calibrator();
	virtual ~CCS1000Calibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	virtual bool MeasureYxyAndSpectralData(double *spectralDataArray, dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){ return (bool)(whichDisplayTech & ((bool)(int)(CAL_DISPLAY_TECHNOLOGY_CRT|CAL_DISPLAY_TECHNOLOGY_LCD|CAL_DISPLAY_TECHNOLOGY_DLP)));}
	
	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);

	//null op for this device
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){return true;}
	virtual int		GetCalibratorType(){ return -1;};
	
	virtual char	*GetVersionString() {return "CS1000Cal v0.1";}
	virtual char	*GetToolkitVersionString() { return "v0.2"; }
	
	//to support later?
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData);
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3){return false;}

	//spectral data
	virtual bool   CanSupportSpectralData(){ return true ;}
	virtual bool   GetSpectralDataInfo( double *nmRangeLow, double *nmRangeHigh, double *nmIncrement);
	virtual void   GetSpectralData(double * spectralDataArray, bool usePreviousData = false);

	void SetCOMPort(short prt) { m_port = prt; }

	// Signon message for CS-1000 plugin tells whether it is using correction data or not.
	virtual bool	SupportsSignonMessage() {return true;}
	virtual unsigned char *GetSignonMessage() { return (unsigned char*)m_signonMessage;}

	// ColorDataAdjuster class allows for us to adjust colorimetry and spectral data 
	// by factors within a CS1000CorrectionData.dat file if provided.
	CColorDataAdjuster m_cda;
	bool m_useCorrectionData;

protected:	
	
	C_cs1000a *m_cs1000;
	short m_port;
	unsigned char m_signonMessage[128];
};

#endif