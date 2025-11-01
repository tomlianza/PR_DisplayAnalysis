// NECProjectorInterface.h: interface for the CNECProjectorInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NECProjectorInterface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_)
#define AFX_NECProjectorInterface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_RECEIVE_SIZE 128*1024

typedef enum xscp_TerminationType
{
	xscp_TerminateOnLF = 0,
	xscp_TerminateOnCR,
	xscp_TerminateOnNpts,
	xscp_TerminateOnNull,
	xscp_nTerminateOptions
};

typedef enum xscp_Signal
{
	xscp_SignalIdle = 0,
	xscp_SignalCollectionInProcess,
	xscp_SignalDataCollectionComplete,
	xscp_SignalDataCollectionError,
	xscp_SignalDataCollectionError_Retries,
	xscp_SignalDataCollectionError_TooManyPoints,
	xscp_SignalDataCollectionCancel,
	xscp_NSignals
};

#define XSCP_MAX_BUFFER  1024
#define XSCP_N_MAX_RETRIES 10000

	typedef enum {XSCP_NOTOPEN, XSCP_TIMEOUT, XSCP_SEND_ERROR, XSCP_RECEIVE_ERROR, XSCP_BUFFER_FULL, XSCP_OK} XSCP_STATUS;

	typedef struct
	{
		char *displayString;
		unsigned char *sendBuffer;
		int sendSize;
		unsigned char *receiveBuffer;
		int receiveMax;
		unsigned char receiveDataOKValue;
		int receiveSize;
		int receiveSizeExpectedGood;
		int receiveSizeExpectedBad;
		unsigned char checkSum;
		XSCP_STATUS status;
	} XSCP_COMMAND_RESULT_BLOCK;

	typedef struct
	{
		unsigned char patCmd;
		char *patName;
	} PATTERN_DESCRIPTOR;

	typedef enum {NUM_PATTERNS = 11};

#ifdef DEFINE_GLOBAL_STUFF
	PATTERN_DESCRIPTOR Pattern[NUM_PATTERNS] =
	{
		{2, "Cross Hatch"}, 
		{3, "Gray Bars"},
		{4, "Raster 0%"},
		{5, "Raster 25%"},
		{6, "Raster 50%"},
		{7, "Raster 100%"},
		{8, "Focus"},
		{0xa, "Gray 30%"},
		{0x17, "Gray 10%"},
		{0x18, "Ramp WBGR"},
		{0x19, "Blue 60%"}
	};
#else
	extern PATTERN_DESCRIPTOR Pattern[NUM_PATTERNS];
#endif

typedef enum 
{
	PPS_UNKNOWN,
	PPS_READY,
	PPS_IDLE,
	PPS_TRANSITIONING
} PROJECTOR_POWER_STATE;

class CNECProjectorInterface  
{
public:
	bool xscp_SetPattern (PATTERN_DESCRIPTOR *pat, unsigned char color);
	unsigned char xscp_ComputeChecksum (unsigned char *, int length);
	char xscp_ReadByte ();
	bool xscp_getCommonData();
	bool xscp_SetPowerOn(bool on);
	bool xscp_getProjectorName(char *buf);
	bool xscp_SetWallColor(unsigned char color);
	bool xscp_SetColorTemp(unsigned char mode, int color);
	bool xscp_SetWhiteBalance(unsigned char mode, int setting, int val);
	bool xscp_SetBrightness(int val);
	bool xscp_SetContrast(int val);
	bool xscp_SelectRGBInput();
	bool xscp_SetGamma(int level);
	bool xscp_GetGains(unsigned char setting, unsigned char subSetting, short *minVal, short *maxVal, short *defVal, short *curVal);
	bool xscp_GetBrightness(short *minVal, short *maxVal, short *defVal, short *curVal);
	bool xscp_GetContrast(short *minVal, short *maxVal, short *defVal, short *curVal);

	bool xscp_SendArbitraryCommand (unsigned char *buf, int xmitLength, int ackLength, int nakLength);
	bool IsOpen() {return m_isOpen;}

	CNECProjectorInterface();
	virtual ~CNECProjectorInterface();

	HANDLE					m_hComPort;
	DCB						m_DCB ;
	COMMTIMEOUTS            m_TimeOuts;
	xscp_Signal				m_ComSignal;
	short					m_ComNpts; 
	xscp_TerminationType	m_whichTermination;
	short                   m_InComPoints;
	short                   m_MaxInComPoints;		// defaulted to XSCP_MAX_BUFFER 
	short                   m_RetryCount;			//defaulted to XSCP_N_MAX_RETRIES
	bool					m_isOpen;

	PROJECTOR_POWER_STATE m_projectorPowerState;
	bool IsProjectorReady();
	void SetProjectorPowerState(PROJECTOR_POWER_STATE state);
	PROJECTOR_POWER_STATE GetProjectorPowerState() {return m_projectorPowerState;}
	
	bool xscp_OpenComPort(short sID, bool bInit=TRUE); // 1 based number
	void xscp_CloseComPort();

	bool xscp_Init();
	bool xscp_SetBaud(short sBaud);
	bool xscp_SetRTS(bool bVal);
	bool xscp_SetDTR(bool bVal);

	bool xscp_SetMaxBufferSize(short nPts);
	bool xscp_SendBuffer(BYTE *bBuf,short nPts);
	void xscp_DumpCommand(XSCP_COMMAND_RESULT_BLOCK *op);
	void xscp_DumpStatus(XSCP_COMMAND_RESULT_BLOCK *op);

	bool xscp_ProcessCommand(XSCP_COMMAND_RESULT_BLOCK *op);

	int m_port;
};
#endif
