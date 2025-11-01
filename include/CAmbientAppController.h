/*
 *  CAmbientAppController.h
 *  CirrusAmbientMonitor
 *
 *  Created by Ben Guthro on Wed Feb 23 2005.
 *  Copyright (c) 2005 gmb. All rights reserved.
 *
 */
#ifndef __CAMBIENTAPPCONTROLLER_H__
#define __CAMBIENTAPPCONTROLLER_H__
class CMonitorWorld;
class CGenericCalibrator;
class CPreset;
class CVesaMonitor;
class CSIGammaRamp;

#include "ColorStructs.h"

class CAmbientAppController
{
public:
	CAmbientAppController(bool ownsMonWorld=true);
	virtual ~CAmbientAppController();
	bool Init();
	bool ReInit();
	

	bool MeasureAndCorrectDisplays(bool flashLEDs=true);
	bool AdjustDisplaysToNewPreset(CPreset* p, bool commitProfile = true);
	bool SaveDisplayProfile(char *name, char *desc, CVesaMonitor *mon);
	bool WriteLinearDisplayProfiles();
	bool AnyDisplayIsCalibrated();
	void LinearizeGammaRamp(CSIGammaRamp *gr);
	void BuildAndExpandGammaRampEx(CSIGammaRamp *gr);
	bool WriteProfile(CVesaMonitor *mon, bool useLinearLuts);

	//necessary to use cocoa methods with this class
	void SetProfileNamePrefix(const char*c);
	void SetProfileDescription(const char *c);

	bool LinearizeLUTs();
	
	//! extended for use in main calibration app this will
	//! measure on an open calibrator and adjust the display
	//! accordingly  
	bool MeasureAndCorrectDisplay(CGenericCalibrator *cal, CVesaMonitor *mon,bool overrideTimeCheck, bool useLinearLuts=false, bool commitProfile=true);

	CMonitorWorld *GetMonitorWorld() {return m_MonitorWorld;}

	bool PrimaryDisplayIsCalibrated();

	//enable and disable ambient functionality
	bool enableAmbientForDisplays(bool enable, bool doLUTs = true);
	bool enableAmbientForDisplay(CVesaMonitor *mon, bool enable, bool doLUTs = true);

	bool GetProfileNameForDisplay(CVesaMonitor *mon, char* buf, int bufSize);
	bool GetProfileDescriptionForDisplay(CVesaMonitor *mon, char* buf, int bufSize, bool linear=false);
	bool CheckForCalibrator();

#ifdef HIDE_INTERNAL_DISPLAY_MANUFACTURER
	void SetProfileNameOverride(CVesaMonitor *mon);
#endif

protected:

	bool MeasureAmbientLight(dYxy *meas, bool flashLEDs=true);
	virtual void I1DisplayPlatformSetup();
	virtual void SequelPlatformSetup();

	bool CorrectDisplays(dYxy *meas); //!< correct them all
	bool CorrectDisplay(dYxy *meas, CVesaMonitor *mon, bool overrideTimeCheck=false,bool useLinearLuts=false, bool commitProfile=true); //!< correct one


	CMonitorWorld   *m_MonitorWorld;
	bool			m_ownsMonWorld; //< whether or not we should have our own monitor world
	//these are filled by a third party
	static char profileNamePrefix[255]; //monitor name & sn will be appended
	static char profileDesc[1024];
};

extern char *trimStringFront(char *str, int maxlen);

#endif
