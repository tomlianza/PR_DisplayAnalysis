#pragma once

#include "ArrayTypes.h"		
#include "Wrapper.h"
#include "cieColor.h"
#include "ShutterController.h"

class CUSB2000 
{
// Construction
public:
	CUSB2000(CShutterController *s = NULL);
	~CUSB2000();
	int Open();
	int Close();
	bool GetSpectralDataInfo( double *nmRangeLow, double *nmRangeHigh, double *nmIncrement);

	bool MeasureYxyAndSpectralData1 (double *spectralDataArray,
		dYxy *outYxyData, short sNumAverage=1);
	bool MeasureYxyAndSpectralData2 (double *spectralDataArray,
		dYxy *outYxyData, short sNumAverage=1);
	bool MeasureYxyAndSpectralData (double *spectralDataArray,
		dYxy *outYxyData, short sNumAverage=1);

	bool MeasurePatch();
	bool MeasureDark();
	bool CorrectData();
	bool InterpolateTo1nmData();

	bool GetSerialNumber(char *snString);

	int GetIntegrationTimeInMsecs();

	bool MeasureAndLog(bool shutterClosed, int numMeasurements,
		int numToAverageUSB2000, int numToAverageSW,
		int intTimeMsecs, bool adjustNonLinearity, bool correctElectricalDark, 
		char *logFileName, double *peakSeen);

	void SetShutterController(CShutterController *s);

	bool LoadPixelCorrectionData(char *file);

	bool ComputeTSV();
	dYxy m_Yxy;

	double m_patchSpectrum[2048];
	double m_darkSpectrum[2048];

	bool AccumulateSpectra(double *spectrum, int numHW, int numSW);
	void SetNumbersToAverage (int patchHW, int patchSW, int darkHW, int darkSW);

// Implementation
public:
protected:
	CShutterController *m_shutter;

	char m_snString[64];

	int m_integrationTime;			// the number of milliseconds for the integration time
	int m_numToAvgDarkUSB2000;
	int m_numToAvgUSB2000;
	int m_numToAvgSW;
	int m_numToAvgDarkSW;
#define NUM_PIXELS 2048
	double m_pixelCorrection[NUM_PIXELS];		// multipliers on a per-pixel basis

#define NUM_SPECTRAL_LEVELS (730-380+1)
	double m_1nmData[NUM_SPECTRAL_LEVELS];

#define INITIAL_INTEGRATION_TIME 10000 // 10 millisecs
#define MAX_PIXEL_PCT .88
#define MID_PIXEL_PCT .85
#define MIN_PIXEL_PCT .80
#define MAX_PIXEL_VALUE 65535.0

	DoubleArray m_spectrumArray;	// pixel values from the CCD elements
	DoubleArray m_wavelengthArray;	// wavelengths (in nanometers) corresponding to each CCD element
	Wrapper m_wrapper;				// this is the object through which we will access all of Omnidriver's capabilities

private:
};

