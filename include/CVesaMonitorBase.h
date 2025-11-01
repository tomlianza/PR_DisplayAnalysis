// CVesaMonitorBase.h: Base interface for the CVesaMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CVESAMONITORBASE_H__E914AD20_613E_11D4_A856_0010B508B447__INCLUDED_)
#define AFX_CVESAMONITORBASE_H__E914AD20_613E_11D4_A856_0010B508B447__INCLUDED_

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "dmc.h"
#include "ab_i2c.h"
#include "cieColor.h"
#include "sony_dmc.h"
#ifdef WIN32
#ifndef SUCCESS
#define SUCCESS 0
#endif
#else
#ifdef LINUX
#include "linuxTypes.h"
#else
#include "FakeMacTypes.h"
#endif
#endif
#include "GammaRamp.h"
#include "MonitorControls.h"
#include "CDSDB.h"
#include "CPresetList.h"
#include "CPreset.h"
#include "CDigitalController.h"
#include "CEnableCableController.h"
#include "CDisplayAdapter.h"
#include <vector>

#ifdef HT1000_SUPPORT
#include "CHT1000Controller.h"
#endif

#define DEFAULT_BLACKPOINT	0.15
#define DEFAULT_WHITEPOINT	80

typedef enum
{
    snyG500 = 0x03B0,
    snyG520 = 0x07B0,
    snyF520 = 0x06B0,
    snyG520P= 0x00b1,
    snyC520 = 0x01b1
}SONYPRODUCTID;

typedef enum
{
	ibm6652 = 0x19fc
} IBMPRODUCTID;


typedef pair<char*, char*> ALIASPAIR;
typedef list<ALIASPAIR*> ALIASLIST;

typedef enum
{ // vendor ID in comment
     lacie_19b2 = 0x19b2 // 0x3061
    ,lacie_22b2 = 0x22b2 // 0x3061
    ,lacie_19b3 = 0x19b3 // 0x3023
    ,lacie_22b3 = 0x22b3 // 0x3023
    ,lacie_22b4 = 0x22b4 // 0x3061
}LACIEPRODUCTID;

typedef enum
{ // vendor ID in comment
     necmits_2060u = 0x4511 // 0x34ac
    ,necmits_dpro2070sb = 0x4632 // 0x34ac
    ,necmits_fp1375x = 0x61be // 0x38a3
    ,necmits_fp2141sb = 0x61db // 0x38a3
    ,necmits_fp955 = 0x61b5 // 0x38a3
}NECMITSUPRODUCTID;

typedef enum
{
	// Type of command. Could be used to determine which
	// panel of a multi-panel OSD the command appears on.
	VCPEX_COLOR = 1,
	VCPEX_GEOMETRY = 2,
	VCPEX_IMAGE = 3 ,
	VCPEX_OTHER = 4
} VCPEX_TYPE;

typedef struct
{
	short code;			// VCP code to be sent to access function
	char name[128];		// Displayable string for the command
	VCPEX_TYPE type;
} EXTENDED_VCP_DATA;

typedef struct
{
	short maxGain;		// Max Physical value
	short maxBias;		// Max Physical value
	short limitGain;	// Max Logical value (range of gain goes to this limit)
	short limitBias;	// Max Logical value (range of bias goes to this limit)
} MAX_GAIN_BIAS_ENTRY;

typedef struct
{
	short presetNumber;
	MAX_GAIN_BIAS_ENTRY red;
	MAX_GAIN_BIAS_ENTRY green;
	MAX_GAIN_BIAS_ENTRY blue;
	MAX_GAIN_BIAS_ENTRY all;
} MAX_GAIN_BIAS_DATA;

#define MAX_NUM_VCPEX_COMMANDS 20
#define DSDB_DUMP_FILE "dsdbdump.txt"

#ifdef HT1000_SUPPORT
#include "NECProjectorInterface.h"
#endif

#define DEFAULT_DARK_GREY_POINT 60

class CVesaMonitorBase
{
public:
	inline bool GetIsHT1000() {return m_VESAMonitorContext.type == DDC_TYPE_HT1000;}
	virtual bool PreCalibrationSetup();
	virtual bool GetFileName(char *, char *);
	virtual bool ResetColorPreset();
	virtual bool ResetMonitorFromDSDB();
	virtual bool PostCalibrationSetup();
	virtual bool LockControlPanel(bool lock);
	virtual void ReturnAliasedName (char **name);
	virtual char *GetSerialNumberFromEDID();
	virtual void RestoreSettingSnapshot();
	virtual void SaveSettingSnapshot();
	virtual short CloseMonitor();

	virtual char *GetMonitorDirectory() { return "";}
	char m_monitorDirectory[256];
	virtual bool WriteSecondaryDSDB() {return true;}
	char m_lastDSDBFileWritten[256];
	virtual bool FindSecondaryDSDBFiles() {return false;}
	vector<char *> m_DSDBFiles;
	virtual void EmptySecondaryDSDBFileList();
	vector<char *> *GetSecondaryFileList() { return &m_DSDBFiles;}
	virtual bool MakeDefaultDSDBFile(char *name) {return false;}
	virtual bool SetPrimaryDSDB(char *sourceName) {return false;}

	virtual inline void SetCDSDB(CDSDB *cdsdb) {m_CDSDB = cdsdb;}
	inline CDSDB *GetCDSDB() {return m_CDSDB;}
	virtual bool SyncWithPreset(CPreset *p);
	CVesaMonitorBase();
	virtual ~CVesaMonitorBase();
	// values to be initialized prior to calling functions
	short m_thisMonitor;

	virtual void SetReminderPeriods (UINT expirationTimeInSecs, UINT notificationPeriodInSecs);
	virtual bool IsCalibrationCurrent();
	virtual bool IsCalibrationExpirationWarningPending();

#ifdef SUPPORT_STATIC_ALIASLIST // Disabled since it doesn't work on the Mac.
	static int refCount;
	static ALIASLIST m_aliasList;
#else
	int refCount;
	ALIASLIST m_aliasList;
#endif
	virtual bool LoadMonitorAliasList();
	virtual bool ClearMonitorAliasList();
	virtual void DumpMonitorAliasList();
	bool GetNextAliasEntry (FILE *fp, char *name1, char *name2);
	void AddAliasPairToList(char *s1, char *s2);
	char *LookupMonitorAlias(char *name);
	
	long m_l, m_r, m_t, m_b;

	// These values are set by the open monitor call to false and modified in the GetConfigurationCaps() call
	bool m_bEDIDvalid;
	bool m_bCAPSvalid;
	bool m_bPhotometryValid;
	bool m_bGeometryValid;
	bool m_bImageValid;
	bool m_bLutValid;
	bool m_OnDesktop;

	// Track whether we've successfully read a monitor descriptor file
	bool m_bMDFValid;
	bool MDFValid();

	// Do we support soft DDC operations?
	bool m_bSoftDDCAllowed; // Not whether it is possible, but if MDF allows it
	inline bool SoftDDCAllowed() {return m_bSoftDDCAllowed;}
	inline void SetSoftDDCAllowed(bool allow) {m_bSoftDDCAllowed = allow;}

	
	inline void SetOnDesktop(bool flag) { m_OnDesktop = flag;}
	inline bool GetOnDesktop() {return m_OnDesktop;}

	VESAMonitorContext m_VESAMonitorContext;
	
	CDSDB _CDSDB;
	CDSDB *m_CDSDB;
	DSDB *m_DSDB;

	CDisplayAdapter *m_DisplayAdapter;

	virtual void SetController(CDigitalController *c) {m_VESAMonitorContext.controller = c;}
	virtual CDigitalController *GetController() {return m_VESAMonitorContext.controller;}

	virtual CDisplayAdapter *GetDisplayAdapter() {return m_DisplayAdapter;}
	virtual void SetDisplayAdapter(CDisplayAdapter *a) {m_DisplayAdapter = a;}

	CSIGammaRamp *m_Lut;

	MonitorDefaults *m_monitorDefaults;
	MonitorControls *m_monitorControls;
	
	MonitorControls m_SavedMonitorControls;

	EDIDV13 m_EDID; // parsed edid structure for this monitor
	BYTE *m_bEDID;
	
	CAPABILITIES m_CAPS;
	
	DM_MCCS *m_vcpControls;

	short m_DarkGreyPoint; // level at which to calibrate darks
	inline short GetDarkGreyPoint() { return m_DarkGreyPoint;}
	inline void SetDarkGreyPoint(short level) {m_DarkGreyPoint = level;}

	inline void GetDimensions (long *l, long *r, long *t, long *b)
		{*l = m_l; *r = m_r, *t = m_t; *b = m_b;}
	inline void SetDimensions (long l, long r, long t, long b) {m_l=l; m_r=r; m_t=t; m_b=b;}
	
#ifdef USES_LOWER_LEFT_AS_ORIGIN
	// LLO = lower left origin. Cocoa UI calls have the origin in the lower left of the 
	// main monitor, not the upper left.  We need to preserve BOTH dimeniosn.  SequelClass
	// use ULO, Cocoa UI uses LLO.  PITA...
protected:
	long m_lLLO, m_rLLO, m_tLLO, m_bLLO;
	
public:
	inline void GetLLODimensions (long *l, long *r, long *t, long *b)
	{*l = m_lLLO; *r = m_rLLO, *t = m_tLLO; *b = m_bLLO;}
	inline void SetLLODimensions (long l, long r, long t, long b) {m_lLLO=l; m_rLLO=r; m_tLLO=t; m_bLLO=b;}
#endif
	
	
	// dc_related functions;
	virtual bool GetLUT();
	virtual bool SetLUT();
	virtual bool LUTIsValid(CSIGammaRamp *gr);
	virtual bool SetLinearLUT();
	// Cable related functions
	virtual bool OpenMonitor(int sWhichMonitor = 0); // opens a monitor with the enable cable ignores whichMonitor variable
	virtual bool GetNameFromEDID(char *name);
    virtual bool GetOSDControls();	// initializes the internal structurs for OSD, talk to the montor to get the values.
    virtual bool GetCapabilitiesString(); // Gets the capabilities string if present
	virtual bool GetCapabilitiesStringTheHardWay(); // Creates a capabilities string by polling for VCP commands.

	virtual bool GetPhotometry(); // Gets the photometry control values;
	virtual bool GetGeometryControls(); // Gets the Geometry controls as enumerated in the geometry structure
	virtual bool GetImageControls();
	virtual bool GetEDIDString(); // Gets all the EDID data;
	virtual void GetChromaticities();
	virtual unsigned short GetManufacturerID();
	virtual bool SetColorTempEDIDbased(double dCT);
	virtual bool SetGammaAbsolute(double dGamma); // Set the display gamma to this value using look up tables. 
	virtual bool SaveCurrentSettings(void);
	virtual bool RestoreGeometry();
	virtual bool RestorePhotometry();

	virtual bool GetMaximumGains();
	virtual bool GetGainAndBiasValues(MAX_GAIN_BIAS_DATA *data);
	// Control functions
	virtual bool SetGeometryControl(DMC_CONTROL_INDEX whichIndex, short value);
	virtual bool SetPhotometryControl(DMC_CONTROL_INDEX whichIndex, short value);
	virtual bool GetGeometryControl(DMC_CONTROL_INDEX whichIndex, short *value,short *max);
	virtual bool GetPhotometryControl(DMC_CONTROL_INDEX whichIndex, short *value,short *max);
	virtual bool SetImageControl(DMC_CONTROL_INDEX whichIndex, short value);
	virtual bool GetImageControl(DMC_CONTROL_INDEX whichIndex, short *value,short *max);

	
	// this is a list and is used to modify the control via the Increment and Set functions
	virtual bool GetControlVal(DMC_CONTROL whichControl, short *value, short *max);
	virtual bool SetControlVal(DMC_CONTROL whichControl, short value);
	virtual bool IsValid(DMC_CONTROL whichControl);// validates a control, should be called after GetCapabilitesString();
	
	virtual bool SetEDIDExternally(char*edidData);
	virtual inline unsigned char *GetEDIDPointer() { return (unsigned char*)m_bEDID;}
	
	virtual bool SetDeviceLUTs(CSIGammaRamp *gr);
	virtual bool GetDeviceLUTs(CSIGammaRamp *gr);
	
	virtual void Cleanup(); // Assume we need to do something to free data

	virtual bool BuildMDFFileNameFromEDID(char *name);
	virtual bool ProcessMonitorProfileFile();

	virtual double GetDefaultBlackPoint() {return m_dDefaultBlackPoint;}
	virtual void SetDefaultBlackPoint(double arg) {m_dDefaultBlackPoint = arg;}
	
	virtual double GetDefaultWhitePoint() {return m_dDefaultWhitePoint;}
	virtual void SetDefaultWhitePoint(double arg) {m_dDefaultWhitePoint = arg;}

	short m_numVCPExCommands;
	EXTENDED_VCP_DATA vcpExData[MAX_NUM_VCPEX_COMMANDS];

	enum {MAX_MONITOR_PRESETS = 10};
	short m_numDefinedMonitorPresets;
	short m_definedMonitorPreset[MAX_MONITOR_PRESETS];

	MAX_GAIN_BIAS_DATA m_gainBiasData[MAX_MONITOR_PRESETS];

	bool IsPointOnMonitor(long x, long y);
	bool IsRectOnMonitor(long top, long bottom, long left, long right);
	bool IsRectInsideMonitor(long top, long bottom, long left, long right);
	bool IsRectOutsideMonitor(long top, long bottom, long left, long right);

	short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);

	short m_bitsPerPixel;
	virtual short GetBitsPerPixel() {return m_bitsPerPixel;}
	virtual void SetBitsPerPixel(short bpp) {m_bitsPerPixel = bpp;}

	virtual short GetPreferredMonitorPreset(){ return m_CDSDB->GetPreferredMonitorPreset(); }
	virtual void SetPreferredMonitorPreset(short arg){ m_CDSDB->SetPreferredMonitorPreset(arg); }

	virtual char* GetCapabilitiesStringBuffer(){ return &m_CapString[0]; }
	virtual short GetCapabilitiesStringLength(){ return m_sCapStringLength; }

	virtual float GetMCCSVersion() {return m_CAPS.fVersion;}
protected:
	char m_CapString[32768];
	short m_sCapStringLength;
	bool SonySetExpertMode();
	bool SonySetExpertModeEx(short sIndex);
	bool SonySetCID6500(); 

	short m_EnableCableIndex; // -1 ---> no cable attached yet, otherwise 0-based index
	bool m_bBrightnessEnabled;
	bool m_bContrastEnabled;
	bool m_bRedVideoGainEnabled;
	bool m_bGreenVideoGainEnabled;
	bool m_bBlueVideoGainEnabled;
	bool m_bColorPresetEnabled;

	double m_dDefaultBlackPoint;
	double m_dDefaultWhitePoint;
	bool m_bFirstTimeSeen;
	
	char *m_sForcedNonDigitalReason;
	bool m_bForcedNonDigital;

	bool m_bDesaturationEnabled;

public:
#ifdef DEBUG_DSDB_OPS
	virtual DSDB_STATUS LoadDSDB(char *name, DSDB*, char *file, int line);
	virtual DSDB_STATUS SaveDSDB(char *name, DSDB*, char *file, int line);
	virtual DSDB_STATUS SaveDSDB(char *name, DSDB*, bool newOne, char *file, int line);
	virtual DSDB_STATUS UpdateDSDB(char *file, int line);
#else
	virtual DSDB_STATUS LoadDSDB(char *name, DSDB*);
	virtual DSDB_STATUS SaveDSDB(char *name, DSDB*, bool newOne=false);
	virtual DSDB_STATUS UpdateDSDB();
#endif
	virtual bool VerifyDSDB(DSDB *dsdb, bool dumpit=false);
	
	virtual bool UpdateCalibrationTime(time_t time);

	virtual bool SelectMonitor(CPresetList *pList);

	inline bool GetForceNonDigitalMode() {return m_bForceNonDigitalMode;}
	inline void SetForceNonDigitalMode(bool ignore) {m_bForceNonDigitalMode = ignore;}
	virtual bool RunningDigital() {return (!m_bForceNonDigitalMode  && DigitallyEnabled());}
	virtual bool DigitallyEnabled();

	bool m_bForceNonDigitalMode;		// Treat as non-digital monitor even if cable is connected

	bool m_bPresetAddedToList;
	bool m_bPresetConflict;
	bool m_bDigitallyEnabledStateChanged;
	DSDB_STATUS m_DSDBSaveStatus;

	virtual bool GetKeyNameFromEDID(char *keyName);
	char m_DSDBFileName[512];
	CPresetList *m_PresetList;
	
public:
#ifdef DEBUG_DUMP 
	FILE *m_dumpFP;
	bool InitDumpFile (char *fname);
	bool Dump();
	bool Dump(FILE *fp);
	bool Dump(char *fname);
	void CloseDumpFile();
	virtual bool DumpPlatformSpecificData() {return true;}
#endif

	// Track whether this monitor is connected via an enable cable.
	inline short GetEnableCableIndex() {return m_EnableCableIndex;}
	inline void SetEnableCableIndex(short idx) {m_EnableCableIndex = idx;}
	inline bool ECEnabled() { return m_EnableCableIndex != -1;}

	virtual bool DiscoverDMCControl(DMC_CONTROL control);

	inline bool BrightnessEnabled() { return m_bBrightnessEnabled;}
	inline void SetBrightnessEnabled(bool val) {m_bBrightnessEnabled = val;}

	inline bool ContrastEnabled() { return m_bContrastEnabled;}
	inline void SetContrastEnabled(bool val) {m_bContrastEnabled = val;}
	virtual void DiscoverContrastAndBrightness();
	
	inline bool RedVideoGainEnabled() { return m_bRedVideoGainEnabled;}
	inline void SetRedVideoGainEnabled(bool val) {m_bRedVideoGainEnabled = val;}
	inline bool GreenVideoGainEnabled() { return m_bGreenVideoGainEnabled;}
	inline void SetGreenVideoGainEnabled(bool val) {m_bGreenVideoGainEnabled = val;}
	inline bool BlueVideoGainEnabled() { return m_bBlueVideoGainEnabled;}
	inline void SetBlueVideoGainEnabled(bool val) {m_bBlueVideoGainEnabled = val;}
	virtual void DiscoverRGBGains();

	inline bool DigitalColorTempEnabled() { return m_CDSDB->GetCanAdjustDigitalColorTemp(); }
	inline void SetDigitalColorTempEnabled(bool val) { m_CDSDB->SetCanAdjustDigitalColorTemp(val); }
	virtual void DiscoverDigitalColorTemp();
	
	inline bool ColorPresetEnabled() { return m_bColorPresetEnabled;}
	inline void SetColorPresetEnabled(bool val) {m_bColorPresetEnabled = val;}
	virtual void DiscoverColorPresetLock();

	// Allow DSDB to be used to initialize the monitor's data structures.
	virtual void SetValidityFlags ();
	
	bool m_bGotMonitorData;

	inline DISPLAY_TECHNOLOGY GetTechnology() {return m_CDSDB->GetTechnology();}
	inline void SetTechnology(DISPLAY_TECHNOLOGY tech) { m_CDSDB->SetTechnology(tech);}

	inline bool GetBiasReverseFlag() {return m_CDSDB->GetBiasReverseFlag();}
	inline void SetBiasReverseFlag(bool flag) {m_CDSDB->SetBiasReverseFlag(flag);}

	inline void SetCanAdjustBrightness(bool can) {m_CDSDB->SetCanAdjustBrightness(can);}
	inline bool GetCanAdjustBrightness() {return m_CDSDB->GetCanAdjustBrightness();}
	
	inline void SetCanAdjustContrast(bool can) {m_CDSDB->SetCanAdjustContrast(can);}
	inline bool GetCanAdjustContrast() {return m_CDSDB->GetCanAdjustContrast();}
	
	inline void SetCanAdjustManualColorTemp(bool can) {m_CDSDB->SetCanAdjustManualColorTemp(can);}
	inline bool GetCanAdjustManualColorTemp() {return m_CDSDB->GetCanAdjustManualColorTemp();}
	
	inline void SetCanAdjustGains(bool can) {m_CDSDB->SetCanAdjustGains(can);}
	inline bool GetCanAdjustGains() {return m_CDSDB->GetCanAdjustGains();}

	inline void SetCanAdjustDigitalColorTemp(bool can) {m_CDSDB->SetCanAdjustDigitalColorTemp(can);}
	inline bool GetCanAdjustDigitalColorTemp() {return m_CDSDB->GetCanAdjustDigitalColorTemp();}

	inline void SetMDFDefinitionVersion(long ver) {m_CDSDB->SetMDFDefinitionVersion(ver);}
	inline long GetMDFDefinitionVersion() {return m_CDSDB->GetMDFDefinitionVersion();}

	inline void SetMDFFileVersion(long ver) {m_CDSDB->SetMDFFileVersion(ver);}
	inline long GetMDFFileVersion() {return m_CDSDB->GetMDFFileVersion();}

	inline void SetMDFSource(char *src) {m_CDSDB->SetMDFSource(src);}
	inline char *GetMDFSource() {return m_CDSDB->GetMDFSource();}

	inline void SetMDFNonDigital(bool nd) {m_CDSDB->SetMDFNonDigital(nd);}
	inline bool GetMDFNonDigital() {return m_CDSDB->GetMDFNonDigital();}

	inline void SetDisplayableName(char *src) {m_CDSDB->SetDisplayableName(src);}
	char *GetDisplayableName();

	inline void SetInternalLUTDepth(int val) {m_CDSDB->SetInternalLUTDepth(val);}
	inline int GetInternalLUTDepth() { return m_CDSDB->GetInternalLUTDepth();}

	inline void SetInternalLUTChannels(int val) {m_CDSDB->SetInternalLUTChannels(val);}
	inline int GetInternalLUTChannels() { return m_CDSDB->GetInternalLUTChannels();}

#ifdef SUPPORT_DSDB_SUFFIX
	virtual bool FormatDSDBFileName(char *name, char *serNo, char *resultString, char *suffix = NULL);
#else
	virtual bool FormatDSDBFileName(char *name, char *serNo, char *resultString);
#endif

	inline bool GetOverriddenGains(short *red, short *green, short *blue)
		{ return m_CDSDB->GetOverriddenGains(red, green, blue);}

	inline void SetOverriddenGains(short red, short green, short blue)
		{ m_CDSDB->SetOverriddenGains(red, green, blue);}

	inline bool GetOverriddenBiases(short *red, short *green, short *blue)
		{ return m_CDSDB->GetOverriddenBiases(red, green, blue);}

	inline void SetOverriddenBiases(short red, short green, short blue)
		{ m_CDSDB->SetOverriddenBiases(red, green, blue);}
	
	bool CanSetBias(); 
	
	inline bool GetFirstTimeSeen() { return m_bFirstTimeSeen;}
	inline void SetFirstTimeSeen(bool fts) { m_bFirstTimeSeen = fts;}
	
	inline bool ForcedNonDigital() { return m_bForcedNonDigital;}
	inline void SetForcedNonDigital(bool fnd) { m_bForcedNonDigital = fnd; }
	inline char *ForcedNonDigitalReason(){ return m_sForcedNonDigitalReason; }
	void SetForcedNonDigitalReason(char *inreason);

	int m_monitorPrologueType;
	int m_monitorEpilogueType;

	bool MonitorPrologue();
	bool MonitorEpilogue();

#define MAX_CONTROLS_TO_CHECK 5
#define NUM_CONTROLS_TO_CHECK 5

	int m_numControlsToCheck;
	DMC_CONTROL m_controlToCheck[MAX_CONTROLS_TO_CHECK];

	typedef struct
	{
		short presetNumber;
		bool presetIsValid;
		short RedVideoGain;
		short GreenVideoGain;
		short BlueVideoGain;
		bool canBeSet[MAX_CONTROLS_TO_CHECK];
	} CONTROL_SET_ENTRY;

	CONTROL_SET_ENTRY m_csEntry[NUM_COLOR_PRESET_TYPES];

	int SelectBestPreset(CONTROL_SET_ENTRY **);
	bool CanChangeControl (DMC_CONTROL control);
	bool ControlIsInCapString (DMC_CONTROL control);

	void SetDesaturationEnabled(bool flag) {m_bDesaturationEnabled = flag;}
	bool GetDesaturationEnabled() {return m_bDesaturationEnabled;}

	// checks the digital controller for 
	// hardware LUT support
	bool SupportsDisplayHardwareLUT();
};

#endif // !defined(AFX_CVESAMONITORBASE_H__E914AD20_613E_11D4_A856_0010B508B447__INCLUDED_)
