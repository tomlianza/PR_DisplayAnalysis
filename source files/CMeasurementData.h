#pragma once\
//#include "stdafx.h"
#include "interpolator.h"
//#include "CPRISpectro.h"

#define MAX_SPECTRAL_POINTS  1024 
// existing type definitions...

typedef enum DeviceType
{
	PR7x0 = 0,
	PR7x5 = 1,
	PR6XX = 2
}DEVICETYPE;
typedef enum FilterWheelLocs
{
	FW_Open = 0,// These correspond to the entries in the m_DataSet  variable.  
	FW_Didymium,
	FW_ND1,
	FW_ND3,
	FW_RED,
	FW_BLUE
}FILTERWHEELPOS;

typedef struct DeviceDataDescriptor
{

	double dStartLamda;
	double dEndLamda;
	double dLamdaIncrement;
	WORD   wNRawDataPoints; 
	WORD   sStartPixel;
	WORD   sEndPixel;

}DEVICE_DATA_DESCRIPTOR;

typedef struct XYZ
{
	double X;
	double Y;
	double Z;
}XYZDATA;

typedef struct Yxy
{
	double Y;
	double x;
	double y;
}YxyDATA;

typedef struct FilterWheelData
{
	long lSize;
	bool b_CalibrationDataSet;
	char PRI_Name[128];
	char PRI_SerialNumber[128];
	char PRI_FirmwareVersion[128];
	double dBandWidth;
	double dResponsivity;
	double dStartLamda;
	double dEndLamda; 
	YxyDATA  YxyOpen;
	YxyDATA  YxyRed;
	YxyDATA  YxyGreen;
	YxyDATA  YxyBlue;
	YxyDATA  YxyND3;
	double   OpenSpectrum[1024];
	double   BG20Spectrum[1024];

}FILTERWHEELDATA;

typedef struct MeasurementData
{
	long		lSize;//the size of this structure
	long		iStructs; // the number of structures that are stored in a binary file.  
	double		dTargetLuminance;
	bool		bDataConfigured; 
	DEVICETYPE	whichDevice;
	char PRI_Name[128];
	char PRI_SerialNumber[128];
	char PRI_FirmwareVersion[128];
	 
	int			iReplicates; //used to calculate measn and standard deviations. 
	// Native Data in instrument units;
	double		dNativeSpectrum[1024];
	double		dWavelength[1024];
	DEVICE_DATA_DESCRIPTOR DeviceDescriptor;
	//data interpolated to 1 nm 
	double		InterpolatedSpectrum[1024];
	// Responsivity Data 
	WORD		LightRaw[1024]; 
	WORD		DarkRaw[1024];
	double		dIntegratedLightMinusDarkData;
	double		dIntegrationTime;
	double		dIntegratedEnergy;
	

	//Radiometry and Photometry Data; 
	double		CCT;
	
	
	XYZDATA		XYZdata;
	YxyDATA		YxyData; 

	// Mean data; 
	double Xavg;
	double Yavg;
	double Zavg; 
	double xavg;
	double yavg;
	double		dRadiance;
	double		dTargetLuminanceEnglish;
	double		dMeasuredLuminanceEnglish;
	double      dLuminanceRatio;
	
	
	// Standard deviation Data
	double		Xstdev;
	double		Ystdev;
	double		Zstdev;
	double      xstdev; 
	double      ystdev; 
	double		dMeasuredLuminanceEnglishStdev;
	double		dTargetLuminanceEnglishStdev;
	double		dRadianceStandardDeviation;

	//data for summary report 
	FILTERWHEELPOS  whichFilter;// Filter wheel position 
	double			dResponsivity; // Integral of Light-Dark Data divided by int. time and 
	double			dStandardDeviationResponsivity;
	double			dFigureOfMerit;
	
	
	double			dRadianceRatio; //DUT/Standard
	double			dTargetLuminanceMetric;
	double			dStandardDeviationLuminanceMetric;
	double			dMinimumProjectedLuminance;
	double			DeltaELab;
	double			dPeakWavelength;
	
	
}MEASUREMENTDATA;


typedef struct simple_measurement
{
	DEVICE_DATA_DESCRIPTOR DeviceDescriptor;
	
	XYZDATA		XYZdatadouble;
	double		dIntegrationTime;
	double		dIntegratedEnergy;
	double		dIntegratedLightMinusDarkData;
	double		dNativeSpectrum[1024];
	double		dWavelength[1024];
	double		InterpolatedSpectrum[1024];

}SIMPLE_MEASUREMENT;

typedef struct SimpleStats {
	long    lSize;
	short   nSamples;
	char    csDescription[1024]; 
	double		dTargetLuminanceEnglish; // this is the target luminance for this data set 
	XYZDATA     dTargetXYZdata; // This is the target XYZ data for this data set . this is metric.
	double Xmean;
	double Xstd;
	double Ymean;
	double Ystd;
	double Zmean;
	double Zstd;
	double IntTimeMean;
	double IntTimeStd;
	double IntegratedEnergyMean;
	double IntegratedEnergyStdev;
	double dIntegratedLightMinusDarkData;
	// summary data after comparison of averages betwwn the dut and the calibration device 
	double LuminanceErrorPercent;
	double deltax;
	double deltay;
	double deltaEstar;  // used for device under test.
	double dResponsivity;
	double dRawResponsivity;
	double dLumThreshold; //projected luminance for 10:1 signal to noise ratio 

}SIMPLESTATS;

class CMeasurementData
{
public:
	CMeasurementData();
	~CMeasurementData();
	int	m_Reps;
	CString ReferenceDataPathName ;
	CString DeviceDataPathName;
	SIMPLE_MEASUREMENT m_simple_measurement;
	MEASUREMENTDATA m_currentMeasurement;
	MEASUREMENTDATA m_DeviceDataSet[6];
	MEASUREMENTDATA m_ReferenceDataSet[6];
	DEVICETYPE		m_currentDevice;
	SIMPLESTATS		m_simpleStats;
	SIMPLESTATS     m_simpleStatsReference[2];// 100 and 10 ft lamberts;
	SIMPLESTATS     m_simpleStatsDUT[2];
	CInterpolator	m_Interp;
	bool			m_DeviceDataConfigured; // set this when either of the two routines below are run 
	bool  InterpolateTo1nmData();
	bool ConfigureDeviceData(); // use m_currentDevice;
	bool ConfigureDeviceData(DEVICETYPE whichDevice, MEASUREMENTDATA *whichDataArray);
	bool ConfigureDeviceData(DEVICETYPE whichDevice, SIMPLE_MEASUREMENT simple_measurement);
	void SetMeasurementToReferenceDataSet(FILTERWHEELPOS whichPos,MEASUREMENTDATA *whichData);
	void SetMeasurementToDeviceDataSet(FILTERWHEELPOS whichPos, MEASUREMENTDATA *whichData);
	void ComputeStatistics(MEASUREMENTDATA *whichDataArray, int iMeasurements, MEASUREMENTDATA *whichDataSummary);
	void ComputeSimpleStats(SIMPLESTATS		*m_simpleStats,SIMPLE_MEASUREMENT *smArray, int sReps);
	double ComputeStandardDeviation(double *DataArray, int nPoints);
	double ComputeMean(double *DataArray, int nPoints);
	bool SaveSimpleStatisticsFile(CString FilePath,SIMPLESTATS *stats);
	bool SaveBinarySimpleStatistics(CString FilePath, SIMPLESTATS *stats);


};