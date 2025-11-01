// This is a wrapper class for Tom's PR650.h class
// to interface with the CGenericCalibrator class

#ifndef __CPR650CALIBRATOR_H__
#define __CPR650CALIBRATOR_H__

#include "CGenericCalibrator.h"

class CPR650;

class CPR650Calibrator  : public CGenericCalibrator
{
public:
	CPR650Calibrator();
	virtual ~CPR650Calibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	virtual bool MeasureYxyAndSpectralData(double *spectralDataArray, dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){ return (bool)(whichDisplayTech & (int)(CAL_DISPLAY_TECHNOLOGY_CRT|CAL_DISPLAY_TECHNOLOGY_LCD|CAL_DISPLAY_TECHNOLOGY_DLP));}
	
	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);

	//null op for this device
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){return true;}
	virtual int		GetCalibratorType(){ return -1;};
	
	virtual char	*GetVersionString() {return "PR650Cal v0.1";}
	virtual char	*GetToolkitVersionString() { return "v0.1"; }
	
	//to support later?
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData);
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3){return false;};

	//spectral data
	virtual bool   CanSupportSpectralData(){ return true ;}
	virtual bool   GetSpectralDataInfo( double *nmRangeLow, double *nmRangeHigh, double *nmIncrement);
	virtual void   GetSpectralData(double * spectralDataArray, bool usePreviousData = false);



	void SetCOMPort(short prt) { m_port = prt; }

protected:	
	
	CPR650 *m_650;
	short m_port;
};

#endif