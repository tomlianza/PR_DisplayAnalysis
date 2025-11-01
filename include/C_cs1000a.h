/* C_cs1000a.h */

#ifndef _C_cs1000a_h_
#define _C_cs1000a_h_

#include "cieColor.h"



#define MAXLEN	4096
#define SHORT_TIMEOUT	1000
#define LONG_TIMEOUT		20000L

#define  INQUE_SIZE            1024
#define  OUTQUE_SIZE           1024

#ifndef SUCCESS
#define SUCCESS	0
#endif

#ifndef FAILURE
#define FAILURE	-1
#endif

typedef enum ErrorCodes
{
	OK = 0


}cs1000Error;

typedef struct SerialPortInfo
{
	BOOL				bSerialPortOpen;
	short				sComPort; 
	DCB					CommDCB;					// DCB for comm port
	HANDLE				PortID;					// The comm port id
	COMSTAT				CommStat;				// COMSTAT info buffer for comm port
	char				comPortString[8];
	COMMTIMEOUTS		TimeOutData;
}SERIAL_PORT_INFO;

typedef struct cs1000Header
{
	char    ErrorString[8];
	short	MeasurementMode;
	double  IntegrationTimeSecs;
	short   LensType;
	short   ExposureFlag;


}CS1000HEADER;

class C_cs1000a 
{

public:

	SERIAL_PORT_INFO	m_PortInfo;
	CS1000HEADER		m_Header;

	long				m_lError;
	char				m_szInBuffer[MAXLEN];
	double              m_dMeasurementTimeSecs;
	double				m_dMeasurementCompletePercent;
	dYxy				m_dYxy;
	dXYZ				m_dXYZ;
	LuvColor			m_dLuv;
	double              m_dLuminance;
	double              m_dIntegratedEnergy;
	double              m_dColorTemperature;
	double				m_dSpectra[401];

	long Open(int ComPort);
	long Close();
	bool ReadStatusString(char *cBuf, short *sLength);
	bool ReadSpectralDataText();
	bool ReadSpectralDataBinary();
	bool ReadYxyData2DegreeText();
	bool ReadYxyData10DegreeText();
	bool ReadYxyData2Degree(dYxy *dYxyData);
	bool ReadYxyData10Degree(dYxy *dYxyData);
	bool MeasureData();               // single routine which waits for completion 
	bool LaunchMeasurementVerbose();  // routine starts measurement determines time to wait you must follow with WaitWhile routine or you will hang. 
	bool WaitWhileMeasuringVerbose(); // routine actively waits and updates completion percentage. 

	cs1000Error GetErrorReturn();

private:
	float	mp_fSpectra[401];
	long BuildCommStruct();
	long SendGetCommand ( char *szOut, char *szIn, DWORD nTimeOutms );
	long Write(char *outbuf, DWORD outcount, DWORD *byteswritten);
	long Write(char *outbuf, DWORD *byteswritten);
	long Read(char *inbuf, DWORD nbytestoread, DWORD *incount);
	long GetResponse(char *szResponse, short smaxlen, DWORD nTimeOutms);
	long GetResponse(char *szResponse, short smaxlen, DWORD nTimeOutms,DWORD *len);
	bool GetStatus();
	void WaitMS(long millisecs);
	bool ParseHeader();
	bool ParseMeasurementTime();
	bool ParseYxyText();


};

#endif  /* _C_cs1000a_h_ */
