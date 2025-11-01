#pragma once
//#include "stdafx.h"
#include "CMeasurementData.h"

#define RESPONSE_LENGTH			4096
#define SHORT_TIMEOUT		1000
#define LONG_TIMEOUT		240000L
#define LONG_LONG_TIMEOUT   600000L

#ifndef SUCCESS
#define SUCCESS	0
#endif

#ifndef FAILURE
#define FAILURE	-1
#endif

#define ERR_PR650_INVALID_COMPORT		-100
#define ERR_PR650_ALREADY_OPEN			-101
#define ERR_PR650_COMM_TIMEOUT			-102
#define ERR_PR650_INVALID_ARGUMENT		-103
#define ERR_PR650_QUALITY_CODE_ERROR	-104

typedef enum PriCommands
{

	PRI_GET_NAME = 0,
	PRI_GET_SERIAL_NUMBER,
	PRI_GET_FIRMWARE_VERSION,
	PRI_GET_N_APERTURES_ACCESSORIES,
	PRI_GET_CURRENT_APERTURE_ACCESSORY,
	PRI_GET_APERTURE_INFO,
	PRI_GET_BANDWIDTH_LIST,
	PRI_GET_SENSOR_INFO,
	PRI_MEASURE_Yxy,
	PRI_MEASURE_SPECTRUM,
	PRI_GET_LIGHT,
	PRI_GET_DARK,
	PRI_GET_INTEGRATION_TIME,
	PRI_SET_SINGLE_MEASUREMENT,
	PRI_SET_NO_SYNC,
	PRI_SET_AUTO_SYNC,
	PRI_SET_ENGLISH,
	PRI_SET_METRIC,
	PRI_GET_Yxy,
	PRI_GET_AbsoluteSpectralInfo,
	PRI_SET_ADAPTIVE_MODE,
	PRI_MEASURE_XYZ,
	PRI_GET_PHOTOMETRICDATA,
	PRI_TRIGGER,				//Added July 16, 2017
	PRI_MONITOR_PROCESS,		//Added July 16, 2017
	PRI_ABORT,					//Added July 16, 2017
	// pri 180 commands all require some concatention with the data 
	PRI810_SetAperture,
	PRI810_SetGain,
	PRI810_SetFrequency,
	PRI810_MaxExposure,
	PRI810_EnableAnalog,
	PRI810_NumToAverage,
	PRI810_AnalogFilter,
	PRI810_SyncMode,
	PRI810_PhotometricUnits,
	PRI810_MeasureShutter

}PRICOMMAND;
// Strings are aligned with PRICOMMAND enumeration
static char *csPRI_COMMAND[] =
{
	"D111",//PRI_GET_NAME
	"D110",//PRI_GET_SERIAL_NUMBER
	"D114",//PRI_GET_FIRMWARE_VERSION
	"D112",//PRI_GET_N_APERTURES_ACCESSORIES
	"D116",//PRI_GET_CURRENT_APERTURE_ACCESSORY
	"D117",//PRI_GET_APERTURE_INFO
	"D118",//PRI_GET_BANDWIDTH_LIST,
	"D120",//PRI_GET_SENSOR_INFO,
	"M1",//PRI_MEASURE_Yxy,
	"M5",//	PRI_MEASURE_SPECTRUM,
	"D8",//PRI_GET_LIGHT
	"D9",//PRI_GET_DARK,
	"D13",//PRI_GET_INTEGRATION_TIME,
	"SN1",//PRI_SET_SINGLE_MEASUREMENT,
	"SS0",//PRI_SET_NO_SYNC
	"SS1",//PRI_SET_AUTO_SYNC
	"SU0",//PRI_SET_ENGLISH
	"SU1",//PRI_SET_METRIC
	"D1",  //PRI_GET_Yxy
	"D5" , // PRI_GET_AbsoluteSpectralInfo
	"SE0",//PRI_SET_ADAPTIVE_MODE
	"M2",//PRI_MEASURE_XYZ
	"D4", //Get PhotoMetric Units 
	"T",  
	"P",
	"A",
	"SF",//PRI810_SetAperture
	"SG",//PRI810_SetGain
	"SEO",//PRI810_MaxExposure
	"SL",//PRI810_EnableAnalog
	"SN",//PRI810_NumToAverage
	"SQ",//PRI810_AnalogFilter
	"SS",//PRI810_SyncMode
	"SU",//PRI810_PhotometricUnits
	"SZ"//PRI810_MeasureShutter
};


typedef struct PRI_PRODUCT_INFO
{
	CString PRI_Name;
	CString PRI_SerialNumber;
	CString PRI_FirmwareVersion;

}PRIPRODUCTINFO;



typedef struct PRI_SENSOR_INFO
{
	short	PRI_Sensor_nSpectralPoints;
	double  PRI_BandWidth;
	short   PRI_StartingWavelength;
	short   PRI_EndingWavelength;
	short   PRI_WavelengthIncrement;
	short   PRI_Number_Sensor_Elements;
	short   PRI_First_Useable_Pixel;
	short   PRI_Last_Useable_Pixel;

}PRISENSORINFO;

typedef struct PRI_PHOTOMETRIC_DATA
{
	double dLuminance;
	double dCCT;
	double dLocusDeviation;

}PRIPHOTOMETRICDATA;

typedef struct PRI810_ApertureList
{
	CString csApertureList[5];
	int		iIndex[5];
	int ApertureListCount;

}PRI810APERTURELIST;

class CPRISpectro 
{
public:
	char m_cResponse[RESPONSE_LENGTH];
	char m_ErrorMessage[2048];
	bool m_bSpectroConfigured; 
	bool m_bUsingPR810; 
	PRIPRODUCTINFO     m_ProductInfo;
	PRIPHOTOMETRICDATA m_PhotoMetricData;
	PRISENSORINFO	   m_SensorInfo;
	HANDLE			   m_ComPort;
	MEASUREMENTDATA    m_MeasurementData;
	MEASUREMENTDATA    m_ReferenceStatisticsData;
	MEASUREMENTDATA    m_TestDeviceStatisticsData;
	SIMPLE_MEASUREMENT m_SimpleMeasurementData;
	CMeasurementData   m_MeasureDataClass; 
	PRI810APERTURELIST m_PRI810ApertureList;
	HWND			   m_HWND;  // the window of the calling function ....used for time out purposes 

	CPRISpectro();
	~CPRISpectro();
	// Public routines all put data into m_MeasuementData ;
	bool  GetDeviceName(); //added 5/4/2017
	void  FullMeasurementProcess();
	void  CalculateReferenceStatistics();
	void  CaptureSimpleMeasurement(SIMPLE_MEASUREMENT *sm_data);
	void  CaptureSimpleMeasurement();  // uses member structure.  
	bool InitSpectroConfiguration();
	bool SetRemoteMode(char * ComPortName);
	void QuitRemoteMode();
	bool TakeSpectralMeasurement();
	bool GetYxyData();
	bool MeasureYxyData();
	bool GetPhotoMetricData();
	bool MeasureXYZData(XYZDATA *XYZdata);
	bool MeasureYxyData(YxyDATA * dYxyData);
	bool GetSpectralMeasurementData();
	double  GetIntegrationTime();
	bool  GetLightDarkData();
	bool  SetAdaptiveMode();
	bool  SetIntegrationTime(double dIntTimeMS);
	void  CalculateResponsivity();
	bool  TriggerMeasurement();
	bool  IsMeasurementComplete();
	bool  AbortMeasurement();
	// PRI 810 specific commands 
	int  PRI810_GetApertureList();
	int  PRI810_SetAperture(int whichone);
	int  PRI810_SetGain(int whichone);
	int  PRI810_SetFrequency(double dFreq);
	int  PRI810_MaxExposure(double  dMillisecs);
	int  PRI810_EnableAnalog(bool On_OFF);
	int  PRI810_NumToAverage(int iSamples);
	int  PRI810_AnalogFilter(int whichone);
	int  PRI810_SyncMode(int whichone);
	int  PRI810_PhotometricUnits(bool English_Metric );
	int  PRI810_MeasureShutter(int whichone);
	
private:

	char mp_cBuffer[RESPONSE_LENGTH];
	bool SendGetCommand(PRICOMMAND whichCMD, void *Buffer, DWORD nTimeOutms);
	void CommErrorDisplay(char *theError);
	
	
	
	int ParseToComma(char *cBufin, char*cBufOut);
	int ParseToCR_LF(char *cBufin, char*cBufOut);


	void FormatResponse(char * inBuffer, CString * csResponse);
	void BuildSensorInfoStruct();
	void Clear_m_cResponse();
	void ParseXYZData(XYZDATA *dXYZdata);
	void ParseYxyData( YxyDATA * dYxyData);
	bool PollMeasurementCompleteStatus();
	int GetResponse(char *szResponse, short smaxlen, DWORD nTimeOutms, DWORD *len);
	bool ParsePhotometricData();


};