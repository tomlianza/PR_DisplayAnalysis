#if !defined(AFX_PR650_H__97D3C451_F5B5_11D3_B6C3_00104B8FD93D__INCLUDED_)
#define AFX_PR650_H__97D3C451_F5B5_11D3_B6C3_00104B8FD93D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PR650.h : header file
//

//#include "sipcal.h"
#include "cieColor.h"

#ifdef REQUIRE_PR65X_FACTORS
#include "PR650Adjuster.h"
#endif

#define MAXLEN				4096
#define SHORT_TIMEOUT		1000
#define LONG_TIMEOUT		20000L

#define INQUE_SIZE            1024
#define OUTQUE_SIZE           1024

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

#define NSPECTRALPOINTS     101

#ifndef SERIAL_PORT_INFO_DEFINED
typedef struct SerialPortInfo
{
	BOOL			bSerialPortOpen;
	short			sComPort; 
	DCB				CommDCB;				// DCB for comm port
	HANDLE			PortID;					// The comm port id
	COMSTAT			CommStat;				// COMSTAT info buffer for comm port
	char			comPortString[8];
	COMMTIMEOUTS	TimeOutData;
}SERIAL_PORT_INFO;
#define SERIAL_PORT_INFO_DEFINED
#endif


typedef enum command_codes {
	SetUpMeasurement = 0,   /*S*/
	MeasureLight,           /*M*/
	SendMiscellaneousData,  /*D*/
	MeasureFrequency,       /*F*/
	EchoCommand,            /*E*/
	BackLightCommand        /*B*/
}PR650_COMMANDS;

typedef struct PR650_data
{
	dYxy		dYxyMeas;
	dXYZ		dXYZMeas;
	double		dFrequency;
	short		sQualityCode;
	short		sLuminanceUnits;
	short		sLastMeasMode;
}PR650_DATA;

typedef struct PR650_header
{
	unsigned long		ulSerialNumber;
	long				lResponseCode;

}PR650_HEADER;

typedef enum unit_type
{
	UnitEnglish = 0,
	UnitMetric,
}PR650Units;

typedef enum meas_mode
{
	ModeDC = 0,
	ModeLastFreq
}PR650_MEASMODE;

typedef enum freq_mode
{
	FreqNoAuto = 0,
	FreqAuto
}FREQ_MODE;

typedef enum reference_src {
	Illuminant_A = 1,
	Illuminant_B,
	Illuminant_C,
	Illuminant_D55,
	Illuminant_D65,
	Illuminant_D75,
	Illuminant_E
}PR650RefLum;

typedef struct pr650_setup
{
	/* setup data */
	short acc1;
	short acc2;
	short acc3;
	short acc4;
	short sync_frequency;
	PR650RefLum ref_lum;
	PR650Units units;

	/* Configuration Data recieved from the unit */
	long SerialNum;
	char ModelNum[20];
	short NumAccesories;
	char * AccersoryNames[12];
	short NumSpectralPoints;
	double BandWidthNm;
	double StartLamda;
	double EndLamda;
	double WidthLamda;
	double IntegrationTime;
	double Temperature;
}PR650_SetUp;

typedef enum pr650_datatype {
	pr650Yxy = 1,
	pr650XYZ,
	pr650Luv,
	pr650LumColorTemp,
	pr650SpectralData,
	pr650Yxyuv,
	pr650Labuv,
	pr650Unknown = 99,
	pr650SyncFrequency = 101,
	pr650SerialNumber = 110,
	pr650ModelNumber ,
	pr650NumAddOns,
	pr650AddOnList,
	pr650SpectralRange = 120,
	pr650TimeTemperture = 130,
	pr650CheckSCommand = 201
}PR650DataType;

typedef enum pr650_errors{
	PR650_OK =0,
	PR650_NO_EOS,
	PR650_NO_START = 3,
	PR650_NO_EOS_INTEGRATION,
	PR650_DMA_FAILED,
	PR650_NO_EOS_POST_SYNC,
	PR650_NO_SYNC_TO_LIGHT,
	PR650_SYNC_LOST,
	PR650_WEAK_SIGNAL=10,
	PR650_UNKNOWN = 12,
	PR650_SOFTWARE,
	PR650_NO_LAB_SAMPLE,
	PR650_INT_TIME_NOT_FOUND = 16,
	PR650_BATTERY_LOW,
	PR650_LIGHT_LOW,
	PR650_OVERLOAD,
	PR650_NO_SYNC,
	PR650_RAM_ERROR,
	PR650_CORRUPT_DATA = 29,
	PR650_NOISY_SIGNAL
}PR650ErrorCodes;

typedef struct PR650_SpectralData
{
	short  sNpts;
	double dLambda;
	double dLamda[NSPECTRALPOINTS];
	double dSpecData[NSPECTRALPOINTS];

}PR650_SPECTRALDATA;
/////////////////////////////////////////////////////////////////////////////
// CPR650 window

class CPR650 
{
// Construction
public:
	CPR650();

// Implementation
public:
	PR650_MEASMODE m_ACDCmode;
	long CmdMeasure(PR650DataType datatype);
	long CmdSetup(short sFreq, short sNumAvg, short sUnits);
	long AutoMeasureYxy(short sFreq, short sAutoFreq, short sNumAvg, PR650Units Units, dYxy *data);
	long AutoMeasure(short sFreq, short sAutoFreq, short sNumAvg, PR650Units Units, PR650DataType datatype);
	long SendGetCommand(char *outbuf, DWORD *byteswritten, char *inbuf, short smaxlen, DWORD nTimeoutms, DWORD *bytesread);
	long SetUnits(PR650Units units);
	long SetACMode();
	long SetDCMode();
	long SelectLens(int lensIndex); // Currently only 1 or 2 for the PR-650.
	char m_cOutBuf[128];
	char m_cResponseBuf[128];
	char m_cBuf[128];
	long MeasureFrequency ( void );
	PR650_HEADER			m_PR650_Header;
	PR650_DATA				m_MeasData;
	PR650_SPECTRALDATA		m_SpectralData;
	PR650_SetUp				m_SetUpInfo;
	long MeasureYxy(dYxy *data);
	long MeasureYxy(void); //Fill data in class header 
	long MeasureSpectralData ( PR650_SPECTRALDATA *SpectralData ); 
	long MeasureSpectralData(); // use class storage only;
	long SendGetCommand ( char *szOut, char *szIn, DWORD nTimeOutms );
	long SendGetCommand ( char *szOut, char *szIn, DWORD nTimeOutms , DWORD *len);
	long GetSerialNumber ( void );
	char m_szInBuffer[MAXLEN];
	char m_szOutBuffer[128];
	char m_szTemp[128];
	long GetResponse ( char *szResponse, short smaxlen, DWORD nTimeOutms,DWORD *lLength );
	long GetResponse ( char *szResponse, short smaxlen, DWORD nTimeOutms );
	long Read ( char *inbuf, DWORD nbytestoread, DWORD *incount );
	long Write ( char *outbuf, DWORD outcount, DWORD *byteswritten );
	long Write(char *outbuf, DWORD *byteswritten);
	long pr650_4to5(double *in4, short npts, double *out5);
	DWORD m_nNumBytesWritten;
	DWORD m_nNumBytesIn;
	DWORD m_nNumBytesOut;
	void ClosePR650();
	SERIAL_PORT_INFO m_PortInfo;
	long m_lError;
	long OpenPR650 ( void );
	virtual ~CPR650();
	dRGB CalRGB;
	bool GetRGBfromYxy(dYxy*);

	bool m_is655; // Can be set to true to use PR-655 commands.
	void SetIsPR655 (bool iz) { m_is655 = iz;} // Do right after instantiation.
	long WriteByteByByte(char *outbuf, DWORD *byteswritten); // Writes single byte at a time.

	int m_lensIndex;

	char m_logFileName[MAX_PATH];
	bool SetLogFileName(char *logFileName);
	bool Log(char *txt);

	double m_lumFactor[2]; // Multiplier for luminance adjustment - default is 1.0

protected:

private:
	long BuildCommStruct();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PR650_H__97D3C451_F5B5_11D3_B6C3_00104B8FD93D__INCLUDED_)
