// CL200Interface.h: interface for the CCL200Interface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CL200Interface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_)
#define AFX_CL200Interface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cieColor.h"
#include "matrix.h"



class CCL200Interface  
{
public:

	#define MAX_RECEIVE_SIZE 20480

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

#define CL200MSG_SIZE_SHORT 14
#define CL200MSG_SIZE_LONG 32
#define MSG_SHORT_ETX 9

	typedef enum {XSCP_NOTOPEN, XSCP_TIMEOUT, XSCP_SEND_ERROR, XSCP_RECEIVE_ERROR, XSCP_BUFFER_FULL, XSCP_OK} XSCP_STATUS;

	typedef struct
	{
		char *sendBuffer;
		int sendSize;
		char *receiveBuffer;
		int receiveMax;
		int receiveSize;
		int timeout;
		XSCP_STATUS status;
	} XSCP_COMMAND_RESULT_BLOCK;

	typedef struct {
		unsigned char sign;
		unsigned char mantissa[4];
		unsigned char exponent;
	} ENCODED_FLOAT_VALUE;

	typedef struct {
		unsigned char cmd;
		bool isShort;
		unsigned char d4[4];
		double d3;
		double d2;
		double d1;
	} RECEIVED_BLOCK;

	CCL200Interface();
	virtual ~CCL200Interface();

	HANDLE					m_hComPort;
	DCB						m_DCB ;
	COMMTIMEOUTS            m_TimeOuts;
	BYTE					*m_ubBuffer; 
	xscp_Signal				m_ComSignal;
	short					m_ComNpts; 
	xscp_TerminationType		m_whichTermination;
	short                   m_InComPoints;
	short                   m_MaxInComPoints;		// defaulted to XSCP_MAX_BUFFER 
	short                   m_RetryCount;			//defaulted to XSCP_N_MAX_RETRIES
	
	bool xscp_OpenComPort(short sID, bool bInit=TRUE); // 1 based number
	void xscp_CloseComPort();

	bool xscp_Init();

	bool xscp_SetBaud(short sBaud);

	bool xscp_SetRTS(bool bVal);
	bool xscp_SetDTR(bool bVal);

	bool xscp_SetMaxBufferSize(short nPts);
	bool xscp_SendBuffer(BYTE *bBuf,short nPts);

	bool SendCommandGetData(XSCP_COMMAND_RESULT_BLOCK *op,
							char *cmd, char *result);

	char tmpBuf[4000];

	char m_rcvBuffer[MAX_RECEIVE_SIZE];

	bool xscp_WaitAndGetBuffer(xscp_TerminationType  whichTermination);
	bool xscp_WaitAndGetBuffer();// uses m_whichTermination

	bool xscp_WaitAndGetThisBuffer(xscp_TerminationType  whichTermination,BYTE * buf);
	bool xscp_WaitAndGetThisBuffer(BYTE * buf);// uses m_whichTermination

	bool xscp_SendCommandGetResult (XSCP_COMMAND_RESULT_BLOCK *op, int numLines = 1 );
	bool xscp_SendBlock (XSCP_COMMAND_RESULT_BLOCK *op);
	bool xscp_ReceiveBlock (XSCP_COMMAND_RESULT_BLOCK *op, int numLines = 1);
	bool xscp_ReceiveBuffer(unsigned char *buf);
	int m_port;

	bool FormatAndSendShortMessage(int cmd, int head, char d4_1 = ' ', char d4_2 = ' ', char d4_3 = ' ', char d4_4 = ' ');

	bool FormatAndSendLongMessage(int cmd, int head, char d4_1 = ' ', char d4_2 = ' ', char d4_3 = ' ', char d4_4 = ' ',
		double d3 = 0.0, double d2 = 0.0, double d1 = 0.0);

	void ComputeCommand (int cmd, char *tens, char *units);
	void ComputeAndInsertBCC (char *start, int numBytes, char *hi, char *lo);

	void ConvertFloat(double fVal, ENCODED_FLOAT_VALUE *efv);
	bool ReceiveAndDecodeMessage (char *buf, RECEIVED_BLOCK *msg);
	bool DecodeShortMessage (char *buf, RECEIVED_BLOCK *msg);
	bool DecodeLongMessage (char *buf, RECEIVED_BLOCK *msg);
	double DecodeFloatValue (char *fv);
	long MeasureYxyEx();
	bool GetRGBfromYxy();

	dYxy CalYxy;
	dRGB CalRGB;
	double correlatedTemp[3];
	bool GetCorrelatedTemp(double *,double *,double *);
};
#endif
