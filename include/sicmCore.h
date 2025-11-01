// sicmCore.h: interface for the CsicmProcesses class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SICMPROCESSES_H__DFB4874E_234A_11D5_A856_0010B508B447__INCLUDED_)
#define AFX_SICMPROCESSES_H__DFB4874E_234A_11D5_A856_0010B508B447__INCLUDED_

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#ifdef WIN32
#ifndef millisecondSleep
#define millisecondSleep Sleep
#endif
#include "resource.h"
#include "winsock2.h"
#else
#define SICM_USE_INTERNAL_STRINGS
#include <unistd.h>

#ifdef LINUX
#include "linuxTypes.h"
#include <sys/time.h>
#else
#include "FakeMacTypes.h"
#endif

#endif

#include "sicmThreadProcs.h"
#include "sicmReporting.h"

#ifdef USE_STRINGENT_TOLERANCES
#define H_RATIO_FINE 1.007
#define L_RATIO_FINE 0.993

#define H_RATIO_COARSE 1.05
#define L_RATIO_COARSE 0.95

#else

#define H_RATIO_FINE 1.02
#define L_RATIO_FINE 0.98

#define H_RATIO_COARSE 1.02
#define L_RATIO_COARSE 0.98

#endif

#define CAL_NOISE_LEVEL 0.025

#define DARK_SET_POINT 15

#define RGBMEASDATA_LOG "RGBMeasData.txt"

#define MINIMUM_BIAS_SETTING 1
#define MINIMUM_BRIGHTNESS_SETTING 3

#ifdef COLOR_DEBUG
#include <stdio.h>
extern FILE *gColorDebugFP;
#endif

#ifndef DONURBSSTUFF
#define DEFAULT_BLACKPOINT_NON_NURBS 0.15
#define DEFAULT_WHITEPOINT_NON_NURBS 90.0
#endif

#define CAL_OFFSCREEN_THRESHOLD 5

#ifdef SICM_USE_INTERNAL_STRINGS
enum {
	IDS_INIT_IN_PROGRESS,
	IDS_LUM_TOO_HIGH,
	IDS_MOUNT_CALIBRATOR,
	IDS_HOLD_CALIBRATOR_AWAY,
	IDS_HOLD_CALIBRATOR_TO_SCREEN,
	IDS_MEASUREMENT_IN_PROGRESS,
	IDS_AMBIENT_COMPLETE,
	IDS_CHARACTERIZING,
	IDS_SETTING_WHITE,
	IDS_SETTING_GREY,
	IDS_SETTING_MAX_LUM,
	IDS_SETTING_ABSOLUTE_BLACK,
	IDS_PROGRESS_START,
	IDS_PROGRESS_MEASUREDARK,
	IDS_PROGRESS_MEASUREFREQUENCY,
	IDS_PROGRESS_INIT_MONITOR,
	IDS_PROGRESS_FIND,
	IDS_PROGRESS_COMPUTE_GAMMA,
	IDS_PROGRESS_VERIFY,
	//IDS_PROGRESS_SAVE_SETTINGS,
	//IDS_PROGRESS_BUILD_PROFILE,
	IDS_ALL_COMPONENTS_FOUND,
	IDS_A_PROBLEM_HAS_OCCURRED,
	IDS_ADJUST_CONTRAST_HIGH,
	IDS_ADJUST_BRIGHTNESS_MIDDLE,
	IDS_ADJUST_COLOR_TEMP_CLOSEST,
	IDS_MEASURING ,
	IDS_ADJUSTING_CONTRAST,
	IDS_SETTING_NOMINAL_BLACK,
	IDS_CANCEL_IN_PROGRESS,
	IDS_PROBING_BIASES,
	IDS_PROGRESS_CALIBRATE_VIDEO_OVERLAY,
	IDS_PROGRESS_VERIFY_VIDEO_OVERLAY,
	IDS_DESATURATING_DISPLAY
};
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

#define CORRECTION_CURVE_SIZE 18

#define MAX_ITERATIONS 20
//was 0.5 WAS .8 //WAS .3
// went back to 0.3 with 20 iterations per Tom 11/20/2002 to solve the 
// non-converging 1375 and 19b4 monitors.  Slower, but it should get there.
#define BRIGHTNESS_EXPONENT 0.3

#define NAVG 5//average the black point measurement 11/13/02

#define NUM_LUM_SAMPLES 16

#define DAC_INCREMENT 15
#define MIN_GREYPOINT_LUM 1.0

#ifdef USES_EXTENDED_DARK

#define EXTENDED_DARK_HIGH 45
#define EXTENDED_DARK_INCREMENT 1
#endif

int CalcBrightnessIncrement(double ratio);

// Measurement Related Thread routines
bool CheckRatioCoarse(dRGB ratio) ;
bool CheckRatioCoarse(double ratio);
bool CheckRatioFine(dRGB ratio);


extern char * g_SWRevString;  

typedef enum {
	sicmNotInitialzed = 32768,
	sicmNoProblems = 0,
	sicmNoCalibrator = 2,
	sicmNoVesaMonitor=4,
	sicmNoLUTs = 8,
	sicmNeedsCalibration = 16,
	sicmInvalidControlMatch = 32,
	sicmCanNotReachMaxLuminance = 64
	
}sicmProblems; // these are intended to be "or-ed" 




typedef enum {
	sicmCancelIdle = -2,
	sicmProcessInProgress = -1,
	sicmPleaseCancel = 0,
	sicmCancelInProgress,
	sicmCancelComplete,
	sicmNCancelStates
}sicmCancelState;

typedef enum {
	
	sicmErrorOK = 0,
	sicmEConfigError,
	sicmECommError,
	sicmNErrorStates
}sicmErrorStatus;

typedef enum {
	sicmThreadCanceledByUser = 0,
	sicmDoCalibrationThreadComplete = 1,
	sicmDoVerifyThreadCompleteGood = 2,
	sicmDoVerifyThreadCompleteBad = 3,
#ifndef electron22b22HACK
	sicmThreadCompleteLosti2C = 4,
#endif //electron22b22HACK
	sicmThreadCompleteUnknownError = 5,		// bad lut or bad measurement
	sicmDoAmbientMeasurementThreadComplete,
	sicmThreadCompletePreCalSetupError,
	sicmCalibratorNotOnScreenThreadComplete,

#ifdef REPORT_SICM_CANCEL_DETAIL // Extra detail provided in high part of message
	sicmThreadCanceledByUser1 = 0x10000,
	sicmThreadCanceledByUser2 = 0x20000,
	sicmThreadCanceledByUser3 = 0x30000,
	sicmThreadCanceledByUser4 = 0x40000,
	sicmThreadCanceledByUser5 = 0x50000,
	sicmThreadCanceledByUser6 = 0x60000,
	sicmThreadCanceledByUser7 = 0x70000,
	sicmThreadCanceledByUser8 = 0x80000,
#endif

	sicmThreadCanceledBySystem
	
}sicmThreadCompletionMsg;

typedef enum{
	sicmRED=0,
	sicmGREEN=1,
	sicmBLUE=2
}sicmColor;


#define UP_DOWN_MEAS_COUNT 5

#ifdef OS9_DRIVER
#define WDOpenFile(x,y) FSOpenInSpec(x,getWorkingDir(),y)
#else
#define WDOpenFile(x,y) fopen(x,y)
#endif

#ifdef SET_BLACK_BY_CONTRAST_RATIO
double GetGlobalContrastRatio();
void   SetGlobalContrastRatio(double d);
#endif

class CsicmProcesses 
{
private:
	bool m_NeedsCalibration;
	
	//indexes should be normalized 0-1.0
	void ComputeCorrectionCurve(sicmColor,dRGB *, dRGB *, double *indexes, int nPoints);
public:
	dYxy m_PreLutWhite;
	dYxy m_PreLutGrey;
	bool sicmCalibrationWhitePointCalculate(dYxy *WhiteYxy, bool bSetMaximumWhite);
	bool sicmCalibrationWhitePointMeasure(dYxy *Yxy);
	bool sicmCalibrationWhitePointMeasureAndAdjust();
	bool sicmCalibrationDarkPointMeasureAndAdjust();
	bool sicmCalibrationDarkPointCalculate(dYxy *WhiteYxy, bool incrementDarkGreyPointOK=true);
	
	bool sicmCheckRGBRatioTolerance(dRGB *ratio, double tolerance);
	double dRatio;
	double dContrastRatio;
	
	bool sicmCalibrationBlackPointAdjust();
	
	//no values necessary for initial call
	bool sicmCalibrationSetOptimumContrast(short lowControlLimit=-1, short highControlLimit=-1, short depth=0, short increment=-1);
	
	// sicmCalibrationSearchForMaxContrast
	// this method will assume that we are out of saturation
	// on the low end coming in, and in saturation at the high end
	// the goal is to find the max point at which we are out of
	// saturation at this color temp
	bool sicmCalibrationSearchForMaxContrast(short lowControlLimit, short highControlLimit, short depth=0);
	bool sicmCalibrationIsSaturated();
	
	
	
	bool sicmCalibrationWhitePointByColorCurveNecessary();
	bool sicmCalibrationWhitePointAdjustByColorCurve();
	bool sicmCalibrationWhitePointProbeColorCurve();
	
	void sicmCalibrationAdjustBiasForDarkerBlackPoint(double trim);
	bool sicmCalibrationApproveBlackPoint(dYxy *Black, double tolerance);
	bool sicmCalibrationBlackPointCalculate(dYxy *Black, double tolerance);	
	bool sicmCalibrationSetSpecificBlackPoint(double bp, double tolerance, THREAD_OBJECT );
	bool sicmCalibrationSetBlackPointByContrastRatio(double cratio, double tolerance, THREAD_OBJECT);
	
	short sContrast, sContrastOld, sContrastSaturationPoint;
	short sBrightness, sBrightnessOld;
	bool sicmCalibrationTrimLuminanceAdjust();
	bool sicmCalibrationTrimLuminanceCompute(double lum);
	bool sicmCalibrationSetSpecificWhitePoint(double lum, THREAD_OBJECT);
	
	bool sicmScaleRGBBiases(dRGB *scaleRatio);
	int sicmProbeOptimalInitialBiasSettings(short lowBiasVal, short highBiasVal,
											short lowBrightnessVal, short highBrightnessVal,
											short depth, char* wfn, char* bfn, THREAD_OBJECT);
	
	int FindClosestAbsoluteIndexToDesiredY(double *Yvals, short nindices, double targetValue );
	int FindClosestPositiveIndexToDesiredY(double *Yvals, short nindices, double targetValue );
	
	double lumBlack;
	dYxy m_BlackPoint;		// save for later so we can see if our black point was good enough
							// see m_Black, not sure if that is used anymore...
	
#ifdef SMART_BLACK
	double dPrevLum;		// coarse way of measuring slope
	double dPrevPrevLum;	// make sure last TWO points are both on a horizotal (Within limits of error) slope
	
#endif
	
	inline bool sicmDigitalMonitorFound ();
	bool m_DigitalMonitorFound;
	void sicmSendStringMessageVerbose (int stringID);
	void sicmSendStringMessage (int stringID);
	bool m_DSDBCopySaved;
	DSDB m_DSDBCopy;
	bool RestoreDSDBCopy();
	bool SaveDSDBCopy();
	bool CanContinueRunning ();
	void SetIsCancelling (bool state);
	void SetIsSystemCancel (bool state);
	bool IsSystemCancel();
	bool IsCancelling();
	bool m_Cancelling;
	CProgressList* m_ProgressList;
	void InitializeProgressList (CProgressList *progList, bool verifyOnly = false);
	bool CalibratorDoesDarkCurrent();
	bool CalibratorRequiresFrequencyBeforeDarkCurrent();
	unsigned long GetCalibratorSerialNumber();
	int GetDarkCurrentValues(unsigned long *red, unsigned long *green, unsigned long *blue);
	int MeasureDarkCurrent (int numSamples);
	int GetCalibratorType();
	CsicmProcesses();
	virtual ~CsicmProcesses();
	void SendProgressUpdate();
	void sicmSetProgressPercent(int pct);
	bool PreCalNeeded();
	void DoPreCalSteps();
	void sicmUpdateProgressIndicator(int id, PROGRESSLIST_STATE state);
	void LoadStringFromID(char *, int);
	bool sicmSetCallback (SICM_CALLBACK_TYPE type, void *(*fct)(void*));
	
	void*(*callback[NUM_SICM_CALLBACK_TYPES])(void*);
	
	inline void SetNeedsCalibration(bool needsIt)
	{
		m_NeedsCalibration = needsIt;
	}
	
	inline bool GetNeedsCalibration()
	{
		return m_NeedsCalibration;
	}
	
	bool WriteProfileToFile(char* cProfileName, unsigned char* cICM, int lProfileSize);
	
	void ShowMonitorName();
	
	void sicmOverlayOperation (SICM_OVERLAYOP_TYPE op);
	
#ifndef WIN32
	inline void SoundWarningTone() {};
	inline void SoundOKTone() {};
#else
	inline void SoundWarningTone() {MessageBeep(MB_ICONEXCLAMATION);}
	inline void SoundOKTone() {MessageBeep(MB_OK);}
#endif
	
	double sicmMeasureColorTemp();
	bool sicmComputeWhitePoint(double *red, double *green, double *blue);
	
	dYxy sicmGetNativeWhitepoint() { return m_PreLutWhite; }
	
	//***************************Fundamental API functions and Variables ************************/
	
	//******************************************************************************************** 
	// Variables that must be initialized before calling sicm functions 
	//********************************************************************************************/
	
	HWND m_patchWindowHandle;
	
	HWND m_OSDHandle;
	UINT m_SendStringMessage; // application defined message value;
	
	char * m_StringMessage; // this pointer is set and this is the message that is sent
	FILE *g_fpTrace;
	char m_StringMessageContents[256];
	
	
	//some bit maps that should be stored as named resources in the calling app resource structure
	/******************************************************************************************** 
	end of absolutely reqired variables
	******************************************************************************************** 
	******************************************************************************************** 
	Status Variables
	********************************************************************************************/
	UINT m_ProblemCode;
	
	bool m_bCalibratorReady; // calibrator initialized;
	/********************************************************************************************
	end of absolutely reqired variables
	******************************************************************************************** 
	******************************************************************************************** 
	Functions related to the WorkSpace Interface and otheer stored data in The DSDB 
	
	These methods should be used by the calling application to set the user defined work space
	elements. The application should not adjust values in the DSDB directly. 
	********************************************************************************************/
	
	bool sicmWorkSpaceSetGamma(double dGamma);
	bool sicmWorkSpaceSetColorTemp(double dColorTemp);
	bool sicmWorkSpaceSetCustomColorTemp(double dx, double dy);
	bool sicmWorkSpaceSetWhiteLuminance(double dWhite);
	bool sicmWorkSpaceSetBlackLuminance(double dWhite);
	bool sicmWorkSpaceSetCustomGamma(CSIGammaRamp gr_LUT);
	bool sicmWorkSpaceCalcDesiredMeasurements();
	bool sicmWorkSpaceSetName(char * cName);
	bool sicmWorkSpaceSetUseAbsoluteLumFlag(bool bAbLumFlag);
	
	bool sicmSetCreatorAndTimeStamp(WHICH_APP appDescriptor);
	bool sicmSetDSDB(DSDB *thisData); // used to restore the DSDB data back into the monitor ;
	
	bool sicmGetMeasuredWhiteLuminance(double *dWhite);
	bool sicmGetMeasuredBlackLuminance(double *dBlack);
	bool sicmGetMeasuredAmbient(double *dAmbient);
	
	/********************************************************************************************
	end of WorkSpace Methods 
	********************************************************************************************/
	
	/******************************************************************************************** 
	Functions related to the Measurement and Control of a display system using an enable 
	Cable, and Calibrator ( Sequel Imaging Caibration Method) class: sicm 
	********************************************************************************************/
	bool sicmInit();
	
	bool sicmPromptAmbient();
	bool sicmMeasureAmbient(); // measure and set ambient effect.
	
	bool sicmPromptCalibration();
	// Note Thread definition at top of this page 
	
	bool sicmPromptVisibilityTarget();
	
	bool sicmDoCalibration(); // simple call to do the whole enchilada modally.
	bool sicmDoVerify();
	bool sicmDoAmbientMeasurement();
	
	//set bCancel = true to initiate a cancel operation,false returns the current cancel 
	//isSystemCancel sets the system to return a System cancel, instead of a user cancel
	sicmCancelState sicmCancelCurrentProcess(bool bCancel, bool isSystemCancel=false); 
	
	sicmCancelState sicmCheckCancelState(); // returns the m_CancelState member variable.
	
	
	bool sicmSetPatchColor(short R, short G, short B); // set the patch on the calling screen to a color
	bool sicmSetPatchColor_dRGB(dRGB data);
	
	bool puckOnScreen();
	bool doPuckCheckAndContinue();
	
	/******************************************************************************************** 
	end of sicm measurement methods. 
	********************************************************************************************/
	
	
	/************************************end of API for sicm ********************************************
	********************************************************************************************
	Thread operational boolean flags: Set true at the start of the thread and false at the end
	********************************************************************************************/
	bool bSetWhiteInProgress;
	bool bSetDarkInProgress;
	bool bMeasureGreyPatchesInProgress;
	bool bSettingBlackInProgress;
	bool bSettingMaxLuminanceInProgress;
	bool bMeasureAmbientInProgress;
	
	void SetAllProgressFlagsFalse();
	/******************************************************************************************** 
	The functions and variables that follow are used by the sicmClass internally. They may be
	broken out into a standalone class later. Application developers should not venture down 
	here. 
	********************************************************************************************/
	
	// Verbose functions used to send data back to the UI 
	void sicmSetStringMessageValue(UINT StringMessage);
	//This is an application defined message that sicm uses to post a status string to the calling application
	void sicmSendThreadCompleteMessage(sicmThreadCompletionMsg theMessage);
	char* sicmReadStringMessage();
	bool sicmTakeVerboseYxyMeasurement(dYxy *YxyMeasurement); //Sends formatted string data
	bool sicmTakeVerboseYxyMeasurement(dYxy *YxyMeasurement, dRGB RGBmeasurement);
	
	void sicmMeasureCurrentWhitePoint();
	void sicmMeasureCurrentBlackPoint();
	void sicmMeasureEverything();
	
	bool sicmPromptCalibratorMount();
	bool sicmPromptAmbientMeasure();
	// displays an image of the calibrator in the measurement field
	bool sicmSendFormattedRatioString(char * prefix,dRGB theRatio);
	bool sicmSendFormattedRatioString(char * prefix, double theRatio);
	void sicmSendStringMessage();
	void sicmSendStringMessageVerbose();
	void sicmSendExceptionMessage(SICM_EXCEPTION_TYPE type);
	void sicmReportFileError(SICM_EXCEPTION_TYPE theException, char *fileName);
	// Cancel function 
	sicmCancelState m_CancelState;// a mailbox to check cancel status between threads
	bool m_isSystemCancel;
	
	short m_Status; // status is defined by "or-ing" enumerations defined by sicmProblems
	
	
	
	// Measurement Functions and threads
	bool sicmGetGrayScaleData();
		
#ifdef CHARACTERIZE_DISPLAY
	bool sicmCharacterizeDisplay();
#endif
		
	bool sicmTakeYxyMeasurement(dYxy *YxyMeasurement);
	bool sicmTakeYxyMeasurement(dYxy *YxyMeasurement, short red, short green, short blue);
	bool sicmTakeYxyMeasurement(dYxy *YxyMeasurement, dRGB RGBmeasurement);
	bool sicmMeasurePeakLuminance();
	bool sicmGetRGBfromYxyMeasurement(dYxy *YxyMeasurement,dRGB * RGBmeasurement); 
	
	bool sicmSaveICCProfile(char * cProfileName, char * cProfileDescription);
	
	bool sicmSetDarkPoint(dYxy *Yxy);
	//bool sicmSetBlackPoint(dYxy *BlackYxy, bool bSetMaxWhiteBased);
	bool sicmSetBlackPoint();
	bool sicmSetDarkAmbientLuminance(THREAD_OBJECT);
	//bool simcSetAbsouteDarkLuminance();
	bool sicmSetAbsoluteLuminance();
	
	
	
	bool sicmMeasureAndSetGreyScale(sicmWorkSpaceDescriptor *WS);
	bool sicmMeasureAndSetGreyScale(); // uses class variable; 
	
	
	// Functions and variables relating to the patch to be calibrated 
	
	
	
	
	
	
	// Functions and variables relating to the measurement Data se
	
	bool FillMeasurementSetVerbose(); // measure the patch as specified by the data in the measurement set;
	bool FillMeasurementSetVerbose(sicmMeasurementSet *data);
	double GetGamma();
	bool ComputeCalibrationLUT();
	bool ComputeCalibrationLUTEx(sicmMeasurementSet mesurements, dYxy desiredWhite, double desiredGamma);
	void TrimLUTToDesiredLuminance(dYxy *dYxyMeasurements, double *indices, int nMeasurements, CSIGammaRamp *gr);	
	
	//smooth the derivative of the LUT
	bool SmoothLUT(CSIGammaRamp *gr);
	double WeightedAverage(double *data, double *weights, int nPoints);
	
	// Functions to manage the display controls 
	
	bool sicmGetDisplayRGBgains(short *sRed,short *sGreen,short *sBlue);
	bool sicmSetDisplayRGBgains(short *sRed,short *sGreen,short *sBlue);
	
	bool sicmGetDisplayRGBbias(short *sRed,short *sGreen,short *sBlue);
	bool sicmSetDisplayRGBbias(short *sRed,short *sGreen,short *sBlue);
	
	bool sicmGetDisplayContrast(short *sContrast);
	bool sicmGetDisplayBrightness(short *sBrightness);
	
	bool sicmSetDisplayContrast(short sContrast);
	bool sicmSetDisplayBrightness(short sBrightness);
	
	bool sicmSaveDisplayData();
	
	bool sicmGetPhotometryValue(DMC_CONTROL_INDEX whichIndex, short *value);
	bool sicmSetPhotometryValue(DMC_CONTROL_INDEX whichIndex, short value);
	
	
	bool sicmGetGeometryValue(DMC_CONTROL_INDEX whichIndex, short *value);
	bool sicmSetGeometryValue(DMC_CONTROL_INDEX whichIndex, short value);
	// Public variables 
	
	
	DSDB* m_dsdbDisplayData; // data structure stored for all applications
	char m_cTempRegistryKeyName[4096];//
	sicmMeasurementSet m_MeasurementSet;
	sicmMeasurementSet m_PreCalibrationSet;
	
	dYxy m_White; // used by threads;
	dYxy m_Black; // used by threads;
	double m_dLmax;
	
	double m_dGammaCorrectionFactor;
	double m_dVeilingGlareLuminance;
	double m_dCurrentDarkLuminance;
	
	void sicmBuildTargetValues();
	
	// The classes that encompass a sicm system
	CCalibrationCombo *m_sicmCalCombo;
	CVesaMonitor *m_sicmVesaMonitor; // Vesa Monitor
	CGenericCalibrator *m_sicmCalibrator; // Sequel Calibrator
										  // Statistical Analysis
	CColorStats m_sicmColorStats; //ColorStats.cpp....
	
	// data used by threads for storage and analysis 
	short m_psRedVideoGain,m_psGreenVideoGain,m_psBlueVideoGain;
	short m_psRedOffset,m_psGreenOffset,m_psBlueOffset;
	short m_sRed, m_sGreen, m_sBlue ;
	dYxy m_YxyMeasured, m_YxyDesired;
	dRGB m_pRatioTest1, m_pRatioTest2, m_pRatioTest3;
	dRGB m_MeasuredRGBWhite, m_DesiredRGBWhite;
	dRGB m_MeasuredRGBDark, m_DesiredRGBDark;
	dRGB m_MeasuredRGBBlack, m_DesiredRGBBlack;
	
	bool sicmCalcAbsoluteRatio(dRGB* data1, dRGB* data2, dRGB* dRatio);
	bool sicmCalcRelativeRatio(dRGB * data);
	bool sicmRootScaleRatio(dRGB *data);
	
	bool m_frequencyHasBeenMeasured;
	inline void SetFrequencyHasBeenMeasured(bool flag) {m_frequencyHasBeenMeasured = flag;}
	bool NeedsFrequencyMeasurement();
	
	bool sicmUpDateDSDB();
	bool sicmSetDSDB();
	bool sicmGetDSDB();
	int BeginThread (void*, void*);
	void EndThread(
#ifdef USES_PP_THREADS
				   LThread& inThread,
#endif
				   int);
	
#if 0 // was 1 CHECK LATER AND REMOVE OTHER STUFF THEN
	  //this should be derived from the dsdb in the monitor, but isn't correct for some reason.
	
	inline bool CanSetContrast() {return m_dsdbDisplayData->mcData.MCCS.Contrast.bIsValid;}
	inline bool CanSetBrightness() {return m_dsdbDisplayData->mcData.MCCS.Brightness.bIsValid;}
	inline bool CanSetGain() {return m_dsdbDisplayData->mcData.MCCS.RedVideoGain.bIsValid;}
	
	inline bool CanSetBias() {return 
		(m_dsdbDisplayData->mcData.MCCS.RedVideoBlackLevel.bIsValid && m_dsdbDisplayData->mdData.sBiasLimit);}
	inline bool CanSetDigitalColorTemp() { return m_dsdbDisplayData->mcData.MCCS.DigitalColorTemp.bIsValid;}
	
#else
	bool CanSetContrast();
	bool CanSetBrightness();
	bool CanSetGain();
	bool CanSetBias();	
	bool CanSetDigitalColorTemp();
#endif
	
	bool ContrastEnabled();
	bool BrightnessEnabled();
	bool GainEnabled();
	bool DigitalColorTempEnabled();
	bool BiasEnabled();
	
	
	void QualityReport(char *s);
	
	bool ShowWarning(int id);
	bool ShowError(int id);
	
	bool ShowStringAndWait(int id);
	bool ShowStringAndWait(char *msg);
	
	
	short m_darkGreyPoint;
	
private:
		char m_pcBuf[2048];
	void NormalizeMeasurementData(dYxy *data, int npoints=18); //Pointer to an array of dYxy structures
	
	void Yxy2XYZ(dYxy *in, dXYZ *out);
	
	void Normalize_dRGBArray(dRGB *dat, int npoints=18);
	void ScaleDataByMinWhite(dRGB *data, int npoints=18);
	void ScaleDataByMaxWhitePerChannel(dRGB *data, int npoints=18);
	void LoadVesaMonitorFromDSDB();
#ifdef WIN32
	CString lastKeyLoaded;
#endif
	
#ifdef RECORD_PUCKONSCREEN_GAMMA
public:
		dYxy m_measCheckWhite, m_measCheckGrey;
	double m_calcGamma;
#endif
};

#endif // !defined(AFX_SICMPROCESSES_H__DFB4874E_234A_11D5_A856_0010B508B447__INCLUDED_)
