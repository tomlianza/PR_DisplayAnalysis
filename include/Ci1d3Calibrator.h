/*
 *  Ci1d3Calibrator.h
 *  
 *  This class is a C++ abstraction of the i1d3SDK
 *  
 */
#include "CGenericCalibrator.h"
#include "i1d3SDK.h"
#include "i1d3Funcs.h"

class Ci1d3Calibrator  : public CGenericCalibrator
{
public:
	Ci1d3Calibrator();
	virtual ~Ci1d3Calibrator();
	
	//required overrides by parent (pure virtual)
	virtual bool InitializeCalibrator(void *calSpecificData=NULL);
	virtual bool CloseCalibrator();
	virtual bool AutoAttach();
	virtual bool AddExisting(void *calSpecificData=NULL);
	virtual bool MeasureYxy(dYxy *outYxyData, short sNumAverage=1);
	
	virtual bool    SupportsTechnology(CAL_DISPLAY_TECHNOLOGY whichDisplayTech){ return (bool)(whichDisplayTech & 
		(CAL_DISPLAY_TECHNOLOGY_CRT
		|CAL_DISPLAY_TECHNOLOGY_LCD
		|CAL_DISPLAY_TECHNOLOGY_DLP
		|CAL_DISPLAY_TECHNOLOGY_AMBIENT)
		);};
	virtual bool	SupportsNamedCalibrations(){ return true; }

	//device capabilities - only override what we DO support
	// all others will default to parents false
	virtual bool	SupportsSetIntegrationTimeSecs(){return true;}
	virtual bool	SupportsAmbientMeasurements(){return true;}
	virtual bool    MeasureAmbient(dYxy *dYxyAmbient);
#ifdef DRGXXX
	virtual bool	SupportsRGBdataConversion(){return true;}
#endif
	virtual bool    SupportsMATRIXreturn(){return true;}
	
	// tech specific functions
	virtual bool    SetIntegrationTimeSecs(double numSecs);
	virtual bool	GetIntegrationTimeSecs(double *secs);
	
	virtual unsigned long GetSerialNumber();
	virtual bool    GetSerialNumber(char * strName);
	virtual bool    SetDisplayTechnologyType(CAL_DISPLAY_TECHNOLOGY whichDisplayTech);
	virtual bool    GetRGBfromYxy(dYxy *YxyData, dRGB *RGBData) {return false;}
	virtual bool    GetRGB2XYZmatrix(double *dMatrix3X3);
	virtual int		GetCalibratorType();
	
	virtual char	*GetVersionString() {return "i1d3Cal v0.1";}
	virtual char	*GetToolkitVersionString() {return i1d3GetToolkitVersion(NULL);}
	
	virtual int		GetNamedCalibrationCount();
	virtual bool	GetNamedCalibrationFromIndex(int *slot, unsigned char* name, unsigned int strlen);

	virtual bool	SelectNamedCalibration(unsigned char*);
	virtual bool	SelectNamedCalibration(unsigned int);
	
protected:	
	i1d3Handle	m_device;

	bool dYxy2i1d3Yxy(dYxy *in, i1d3Yxy_t *out);
	bool i1d3Yxy2dYxy(i1d3Yxy_t *in, dYxy *out);
	bool i1d3RGB2dRGB(i1d3RGB_t *in, dRGB *out);
	bool dRGB2i1d3RGB(dRGB *in, i1d3RGB_t *out);
};