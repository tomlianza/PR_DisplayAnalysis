#if !defined(AFX_CONFIGURATIONMANAGER_H__D088FEC2_3FE7_11D2_865F_2C1F06C10000__INCLUDED_)
#define AFX_CONFIGURATIONMANAGER_H__D088FEC2_3FE7_11D2_865F_2C1F06C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfigurationManager.h : header file
//
#include "MonitorWorld.h"
#include "MonitorMeasurements.h"
#define   nMaxSetUps				32
#define   NumInterCalDefaults		4
#define   NumInterCalMeasurements   32
#define   INTERCALVERSION			1000
#define   CONFIG_VERSION		    2000


typedef struct InterCalSetup
{
	DWORD   dwVersion;
	char    csSetUpName[1024];
	double  dColorTemp;
	double	dGamma;
	double  WhiteLuminance;
	double  BlackLuminance;
	bool    bAbsoluteMatch;
	bool    bUseAbsoluteWhite;
	dYxy	AbsoluteWhite;
	long    lMeasurements;
	dYxy	AbsoluteMeasurements[NumInterCalMeasurements];

}InterCalSetup;

typedef struct SimpleCalConfig 
{
	short   sVersion;
	bool	b_ValidConfiguration;
	bool    b_GammaSupported;
	bool    b_CalibrationComplete;
	char	sCurrentDisplayName[1024];
	char	sCurrentConfigName[1024];
	char	sMatchingFileName[1024];
	short   sUnitsAbsoluteLuminance;
	double	dColorTemp;
	double	dGamma;
	double  WhiteLuminance;
	double  BlackLuminance;
	bool    b_UseReferenceForMatching;  // used for matching two monitors exactly
	MONITORMEASUREMENTS   ImageForStorage;
	bool    b_UseAbsoluteCoordinatesForWhite;
	dYxy    YxyWhite;
}SIMPLECALCONFIG;


/////////////////////////////////////////////////////////////////////////////
// CConfigurationManager window

class CConfigurationManager
{
// Construction
public:
	CConfigurationManager();


	CMonitorWorld *MonitorWorld; // points to the monitor world used by the app.
	MONITORMEASUREMENTS *pCurrentMeasurements, *pDesiredMeasurements;
	SIMPLECALCONFIG CalConfig;
	CMonitorMeasurements *Measurements;
	InterCalSetup	m_InterCalDefaults[nMaxSetUps];
	CStringList m_InterCalList;
	short		m_sNumInList;
	

	bool GetCurrentConfiguration();
	bool SaveCurrentConfiguration();
	bool BuildDefaultConfiguration();
	bool BuildConfigurationFromInterCal(short index);
	short BuildAndSaveInterCalFromConfiguration(LPCSTR name);
	short UpdateInterCalFromConfiguration(LPCSTR name);
	bool BuildDesiredMeasurements();
	AddFileByNameToList(CString csName); //assumes no path info or extension 
	AddFileByPathToList(CString csName); //assumes full path and name
	bool ThisNameIsInList(char *cBuf);
	bool ThisNameIsInList(CString csName);
	bool ThisNameIsReserved(CString csName);
	bool ThisNameIsReserved(char *cBuf);

	bool DeleteThisNameFromList(char *cBuf);
	bool DeleteThisNameFromList(CString csName);

	void DeleteCurrentConfiguration();
	void DisplayConfigParams(char *cGamBuf, char *cCTBuf);
	// used during real time changes of configuration
	bool BuildDesiredMeasurementsFromPending(); 
	void SetGammaPending(double dGamma);
	bool InGammaRange(double dGamma);
	void SetCTPending(double dCT);
	bool InCTRange(double dCT);
	double GetGammaPending();
	double GetCTPending();
	void DisplayPendingConfigParams(char *cGamBuf, char *cCTBuf);
	void CancelPendingChange();
	void SetPendingChange();
	GetInterCalDirectory(char *SysDir);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigurationManager)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfigurationManager();


private:

// these are values that are temporary place holders when adjusting gamma and CT
	bool        m_bChangesPending;
	double      m_dGammaPending;
	double      m_dCTPending;	

	char path[1024],drive[4],fname[256],ext[10];
	
	void AddDefaultToList(CString name,double gamma,double ct,double lmax,double lmin,bool abs,short index);
	void ChangeConfigInfo(short sWhichIndex);
	short Kelvin2xy(double CT, double *x, double *y);
	short find_yd(double x,double *yd);
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURATIONMANAGER_H__D088FEC2_3FE7_11D2_865F_2C1F06C10000__INCLUDED_)
