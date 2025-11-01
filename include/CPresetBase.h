#ifndef CPRESETBASE_H_INCLUDED
#define CPRESETBASE_H_INCLUDED

#ifdef DONT_INCLUDE_LIST
#else
	#include <list>
#endif

#include <time.h>
using namespace std;

#include "GammaRamp.h"

#ifdef LINUX
 #define USE_TEXT_PRESETS
#endif

typedef struct WorkSpaceDescriptorEx
{
	unsigned long			ulSize;			// the size of this structure, used for version control
	short				sVersionID;		// Used to check software revs.
	
	double				dGamma;			// the Workspace Gamma;
	bool				bGammaCustom;	// Used for monitor matching if true use the gammaRamp
	CSIGammaRamp		grData;			// structure defined in VesaMonitor.h  This is used for matching purposes

	double				dColorTemp;				// describes a color temperature on the daylight locus
	bool				bColorTempCustom;		// if true, use the Yxy value to define a custom color temperature;
	double				dCustomColorTemp_x;     // custom white point not used in Level III applications. 
	double				dCustomColorTemp_y;     // custom white point not used in Level III applications. 

	// Note: if bColorTempCustom is true, a colorTemp value should be calculated and put in dColorTemp.  Use xy2Kelvin in CIEcolor.cpp 

	bool				bUseAbsoluteLuminanceWhite; // used to set an absolute adjustment for monitor luminances
	bool                bUseAbsoluteLuminanceBlack;
	bool				bUseNativeGamma;			// Don't calibrate LUTs.
	bool				bIgnoreDefaultMaxGains;
	double				dLuminanceWhite;
	double				dLuminanceBlack;
	
	char				szWorkspaceName[128];	// string describing workspace

	bool                bAmbientMeasurementValid;
	double				dAmbientLuminance;
	double              dDarkLuminance; 
	
	short               sNativeBiasSetting;
	double              dDarkLuminanceNative;

	double				dMaxMeasuredWhite;

	bool				bReadOnly;
	time_t				timeLastCalibrated;


} sicmWorkSpaceDescriptor;

class CPresetBase
{
public:
	enum {MAX_PRESET_NAME_LENGTH = 60};
	enum {PRESET_VERSION_NUMBER = 3};

	CPresetBase();
	virtual ~CPresetBase();

	char* GetName();
	void SetName(char *name);

	inline short GetVersion() {return wsd.sVersionID;};

	double GetGamma();
	void SetGamma(double gamma);

	bool GetGammaCustom();
	void SetGammaCustom(bool isCustom);

	double GetColorTemp();
	void SetColorTemp(double temp);

	bool GetColorTempCustom();
	void SetColorTempCustom(bool isCustom);

	double GetColorTempCustomX ();
	void SetColorTempCustomX (double customVal);

	double GetColorTempCustomY ();
	void SetColorTempCustomY (double customVal);

	bool GetUseAbsoluteWhite();
	void SetUseAbsoluteWhite(bool useIt);

	double GetMaxMeasuredWhite();
	void SetMaxMeasuredWhite(double max);

	bool GetUseAbsoluteBlack();
	void SetUseAbsoluteBlack(bool useIt);

	double GetLumValueWhite();
	void SetLumValueWhite(double val);

	double GetLumValueBlack();
	void SetLumValueBlack(double val);

	bool GetAmbientMeasurementValid();
	void SetAmbientMeasurementValid(bool valid);

	double GetAmbientLuminance();
	void SetAmbientLuminance(double val);

	double GetDarkLuminance();
	void SetDarkLuminance(double val);

	short GetNativeBiasSetting();
	void SetNativeBiasSetting(short val);

	double GetDarkLuminanceNative();
	void SetDarkLuminanceNative(double val);

	bool GetIgnoreGainFlag();
	void SetIgnoreGainFlag(bool ignoreIt);

	bool GetUseNativeGamma();
	void SetUseNativeGamma(bool useIt);


	time_t GetLastCalibrationTime();
	void SetLastCalibrationTime(time_t lastCalTime);

	bool GetReadOnly();
	void SetReadOnly(bool readOnly);

	virtual bool Add();
	virtual bool Delete();
	virtual bool DeleteWithFullPath(char *fName);
	virtual bool DeleteWithGroup(char *groupName);
	virtual bool Save();
	virtual bool SaveWithFullPath(char *fName);
	virtual bool SaveWithGroup(char *groupName);
	virtual bool Load(char *name);
	virtual bool LoadWithGroup(char *name, char *groupName);
	virtual bool LoadWithFullPath(char *fName);

	inline sicmWorkSpaceDescriptor* GetWSD() {return &wsd;}
	inline unsigned int	GetSize() {return wsd.ulSize;}

	virtual bool IsEqual(CPresetBase *other);	
	virtual bool IsEqual(sicmWorkSpaceDescriptor *wsd);

	virtual bool HasExpertFeatures();
	virtual bool ValidateContents(char *buf, int bytesRead);

  #ifdef USE_TEXT_PRESETS
  bool ParseTextBasedContents(char *fname, sicmWorkSpaceDescriptor *theWsd);
  bool SaveTextBasedContents(char *c);
  #endif

protected:
	sicmWorkSpaceDescriptor wsd;
};

#endif // CPRESETBASE_H_INCLUDED
