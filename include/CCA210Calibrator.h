// This is a wrapper class for Tom's CA210.h class
// to interface with the CGenericCalibrator class

#ifndef __CCA210CALIBRATOR_H__
#define __CCA210CALIBRATOR_H__

#include "CGenericCalibrator.h"

// CA-SDK
#import "..\..\..\ThirdPartySDKS\Win32\Minolta CA200\SDK\CA200Srvr.dll" no_namespace no_implementation 

class CCA210Calibrator  : public CGenericCalibrator
{
public:
	CCA210Calibrator();
	virtual ~CCA210Calibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){ return (bool)(whichDisplayTech & (bool) (int)(CAL_DISPLAY_TECHNOLOGY_CRT|CAL_DISPLAY_TECHNOLOGY_LCD));}
	virtual bool    SupportsDarkCurrentMeasurement(){return true;}


	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);

	//null op for this device
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){return true;}
	virtual int		GetCalibratorType(){ return -1;};
	
	virtual char	*GetVersionString() {return "CA210Cal v0.1";}
	virtual char	*GetToolkitVersionString() { return "v0.1"; }
	
	//to support later?
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData);
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3){return false;};

	virtual bool    SetDarkCurrent(int numSamples=10);

	bool m_initedAlready;

	IConnectionPointPtr m_pIConnectionPointObj;
	DWORD m_dwCk;
	IDispatch* m_pIDispatch;
	IOutputProbesPtr m_pOutputProbesObj;
	IProbesPtr m_pProbesObj;
	ICasPtr m_pCasObj;
	IMemoryPtr m_pMemoryObj;
	IProbePtr m_pProbeObj;
	ICaPtr m_pCaObj;
	ICa200Ptr m_pCa200Obj;

	bool m_darkCurrentMeasured;

protected:	
};

#endif