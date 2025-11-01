// sicmProcessesApplication.h: interface for the CsicmProcessesApplication class.
//
//////////////////////////////////////////////////////////////////////
#ifndef __CSICMPROCESSESAPPL__
#define __CSICMPROCESSESAPPL__

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#ifndef WIN32
#ifdef LINUX
#include "linuxTypes.h"
#else
#include "FakeMacTypes.h"
#endif
#endif


#include "CCalTargetDisplay.h"

#include "CGenericCalibrator.h"
#include "CCalibrationCombo.h"
#include "SmartBiasCtrl.h"
#include "cieColor.h"
#include "ColorStats.h"
#include "CProgressList.h"
#include "sicmCallbacks.h"
#include "MeasurementSet.h"
#include "CVesaMonitor.h"
#include "CMonitorWorld.h"
#include <list>
#include "CCalibratorList.h"

#ifdef USE_PRESET_GROUPS
	#include "CGroupedFileBasedPresetList.h"
#else
	#include "CPresetList.h"
#endif

typedef enum {
     sicmApplicationUnknown
    ,sicmApplicationSuccess
    ,sicmApplicationTechnologyMismatch
    ,sicmApplicationNoCalibrator
    ,sicmApplicationNoECable
    ,sicmApplicationNoMonitor
    ,sicmApplicationFailBrightnessContrastCheck
    ,sicmApplicationFailColorPresetCheck
    ,sicmApplicationExit
    ,sicmApplicationUnknownMonitorTechnology
	
} sicmApplicationReturn;

typedef enum {
     sicmApplicationUnknownProgress
    ,sicmApplicationOpenCalibrators
    ,sicmApplicationInitializeCalibrators
    ,sicmApplicationLoadPresets
    ,sicmApplicationOpenECables
    ,sicmApplicationOpenMonitors
    ,sicmApplicationSelectMonitor
    ,sicmApplicationOpenDSDB
    ,sicmApplicationMisc
    ,sicmApplicationTechnologyCheck
    ,sicmApplicationInitialize
} sicmApplicationProgressReport;


class CsicmProcessesApplication 
{
public:

    CsicmProcessesApplication();
    virtual ~CsicmProcessesApplication();
    
protected:


    CVesaMonitor *thisMonitor;			// Monitor for calibration
    CGenericCalibrator *thisCalibrator;		// Calibrator to use
	
	CCalibratorList *g_calWorld;
	
    CMonitorWorld *g_monWorld;			// Encapsulation of system monitors
    list <CVesaMonitor*> monList;		// List of monitors available to use.
    CCalibrationCombo *thisCombo;		// Encapsulation of all information
				   // needed for sicmProcesses to run.
    
#ifdef USE_PRESET_GROUPS
	CGroupedFileBasedPresetList * presetList;			// Stored/retrieved list of predefined
#else
	CPresetList * presetList;			// Stored/retrieved list of predefined
#endif
	
				// calibration settings.
    CsicmProcesses *sicmProcesses;			// SicmProcesses object for calibration.
    CDSDB *dsdb;					// Pointer to the CDSDB which defines the
		     // monitor's settings and characteristics.
    CProgressList *thisProgressList;

public:

	// Methods related to initializing an Application Using Sequel Classes and
	// SICM
	virtual sicmApplicationReturn sicmApplicationInit(bool doMonitorToo = true,
		int xPt = 1, int yPt = 1);

	virtual sicmApplicationReturn sicmMonitorInit(CVesaMonitor *inMon = NULL);

	
	// Virtual methods, your application may override these or accept these defaults.

	virtual void RaiseSplashScreen() {};
	virtual void LowerSplashScreen() {};

	// NULL is an ok response, it means that 
	// either the user didn't choose or the application
	// didn't give them a chance to choose.
	// A return value of -1 means time to exit program.
	virtual CVesaMonitor * PresentMonitorChoice(CMonitorWorld*){return NULL;}
	
	virtual void CalibratorPlatformSetup(){};
	#ifdef SUPPORT_I1_DISPLAY
	virtual void I1DisplayPlatformSetup(){};
	#endif
	virtual void ECablePlatformSetup(){};
	virtual bool ApplicationWantsToDisableDigitalOperationsOnThisMonitor(){return false;}
	virtual bool ApplicationShouldLockOSD() { return false;}
	virtual bool CalSupportsMonitorTechnology();
	virtual bool WantsToDelayMonitorOperations(){return false;}
	virtual bool RequiresCalibrator(){return true;}
	virtual bool RequiresECable(){return false;}
	virtual bool IsParanoidAboutMonitorCapabilities(){return false;}
	virtual void ProgressReport(sicmApplicationProgressReport) {};
	virtual void DetermineMonitorTechnology() {};
        virtual void FindOrCreateMDF() {return;}
        virtual void CreateSubFolder() {return;}
		virtual void MonitorPrologue() {}
	virtual bool ReinitCalibrator();
	
	//For logo compatibility
	virtual bool InitCalWorld() { return g_calWorld->Init(); }



	// accessor methods
	CVesaMonitor * GetVesaMonitor() { return thisMonitor;};
	CGenericCalibrator * GetCalibrator() { return thisCalibrator;};
	CMonitorWorld * GetMonitorWorld() { return g_monWorld;};
	list <CVesaMonitor*> GetMonitorList() { return monList;};
	CCalibrationCombo * GetCombo() { return thisCombo;};
	CPresetList * GetPresetList() { return presetList;};
	CsicmProcesses * GetSicmProcesses() { return sicmProcesses;};
	CDSDB * GetCDSDB() { return dsdb;};
	CProgressList * GetProgressList() { return thisProgressList;};
	bool MonitorHasBeenCalibrated() {return monitorHasBeenCalibrated;}
	void CalibratorHasDisappeared() {thisCombo->SetCalibrator(NULL); thisCalibrator = NULL; };
private:
	bool monitorHasBeenCalibrated;
};

#endif
