// LenscapSensorInterfaceBase.h: interface for the CLenscapSensorInterfaceBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LenscapSensorInterfaceBase_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_)
#define AFX_LenscapSensorInterfaceBase_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cieColor.h"
#include "matrix.h"



class CLenscapSensorInterfaceBase  
{
public:

#define MAX_RECEIVE_SIZE 20480
#define MAX_TRANSMIT_SIZE 128

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

#define MSG_SIZE_SHORT 13
#define MSG_SIZE_LONG 31
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
	virtual bool DecodeIntTimeMessage(char *buf, RECEIVED_BLOCK *msg);
	virtual bool FormatAndSendIntTimeMessage(char cReq, double dIntTime);
	virtual long GetIntTime(double *dIntTime);
	virtual long SetIntTime(char cRequest, double dIntTime);
	virtual char GetEncodedExponent (int expVal);

	CLenscapSensorInterfaceBase();
	virtual ~CLenscapSensorInterfaceBase();

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
	
	virtual bool xscp_OpenComPort(short sID, bool bInit=TRUE); // 1 based number
	virtual void xscp_CloseComPort();

	virtual bool xscp_Init();

	virtual bool xscp_SetBaud(short sBaud);

	virtual bool xscp_SetRTS(bool bVal);
	virtual bool xscp_SetDTR(bool bVal);

	virtual bool xscp_SetMaxBufferSize(short nPts);
	virtual bool xscp_SendBuffer(BYTE *bBuf,short nPts);

	virtual bool SendCommandGetData(XSCP_COMMAND_RESULT_BLOCK *op,
							char *cmd, char *result);

	char tmpBuf[4000];

	char m_rcvBuffer[MAX_RECEIVE_SIZE];

	virtual bool xscp_WaitAndGetBuffer(xscp_TerminationType  whichTermination);
	virtual bool xscp_WaitAndGetBuffer();// uses m_whichTermination

	virtual bool xscp_SendCommandGetResult (XSCP_COMMAND_RESULT_BLOCK *op, int numLines = 1 );
	virtual bool xscp_SendBlock (XSCP_COMMAND_RESULT_BLOCK *op);
	virtual bool xscp_ReceiveBlock (XSCP_COMMAND_RESULT_BLOCK *op, int numLines = 1);
	virtual bool xscp_ReceiveBuffer(unsigned char *buf);
	int m_port;

	virtual bool FormatAndSendShortMessage(int cmd, int head, char d4_1 = ' ', char d4_2 = ' ', char d4_3 = ' ', char d4_4 = ' ');

	virtual bool FormatAndSendLongMessage(int cmd, int head, char d4_1 = ' ', char d4_2 = ' ', char d4_3 = ' ', char d4_4 = ' ',
		double d3 = 0.0, double d2 = 0.0, double d1 = 0.0);

	virtual void ComputeCommand (int cmd, char *tens, char *units);
	virtual void ComputeAndInsertBCC (char *start, int numBytes, char *hi, char *lo);

	virtual void ConvertFloat(double fVal, ENCODED_FLOAT_VALUE *efv);
	virtual bool ReceiveAndDecodeMessage (char *buf, RECEIVED_BLOCK *msg);
	virtual bool DecodeShortMessage (char *buf, RECEIVED_BLOCK *msg);
	virtual bool DecodeLongMessage (char *buf, RECEIVED_BLOCK *msg);
	virtual double DecodeFloatValue (char *fv);
	virtual long MeasureYxy();
	virtual bool GetRGBfromYxy();

	dYxy CalYxy;
	dRGB CalRGB;
	double correlatedTemp[3];
	virtual bool GetCorrelatedTemp(double *,double *,double *);

	XSCP_COMMAND_RESULT_BLOCK m_op;
	char m_buf[MAX_RECEIVE_SIZE];
	char m_msg[MAX_TRANSMIT_SIZE];

	static char *m_expMap[10];
	static char m_cMap[16];
};
#endif
