// This is a wrapper class for the Topcon SR-3 device
// to interface with the CGenericCalibrator class

#ifndef __SR3CALIBRATOR_H__
#define __SR3CALIBRATOR_H__

#include "CGenericCalibrator.h"

class C_SR3;

class CSR3Calibrator  : public CGenericCalibrator
{
public:
	CSR3Calibrator();
	virtual ~CSR3Calibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){ return (bool)(whichDisplayTech & (bool)(int)(CAL_DISPLAY_TECHNOLOGY_CRT|CAL_DISPLAY_TECHNOLOGY_LCD|CAL_DISPLAY_TECHNOLOGY_DLP));}
	
	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);

	//null op for this device
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){return true;}
	virtual int		GetCalibratorType(){ return -1;};
	
	virtual char	*GetVersionString() {return "CS1000Cal v0.1";}
	virtual char	*GetToolkitVersionString() { return "v0.1"; }
	
	//to support later?
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData);
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3){return false;}

#ifdef NOTYET
	//spectral data
	virtual bool   CanSupportSpectralData(){ return false ;} // NOT YET IMPLEMENTED
	virtual bool   GetSpectralDataInfo( double *nmRangeLow, double *nmRangeHigh, double *nmIncrement);
	virtual void   GetSpectralData(double * spectralDataArray);
#endif

	void SetCOMPort(short prt) { m_port = prt; }


protected:	
	
	C_SR3 *m_SR3;
	short m_port;
};

#endif