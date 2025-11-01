// SerialComProcesses.h: interface for the CSerialComProcesses class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALCOMPROCESSES_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_)
#define AFX_SERIALCOMPROCESSES_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef enum scp_TerminationType
{

	scp_TerminateOnLF = 0,
	scp_TerminateOnCR,
	scp_TerminateOnNpts,
	scp_TerminateOnNull,
	scp_nTerminateOptions

};

typedef enum scp_Signal
{

	scp_SignalIdle = 0,
	scp_SignalCollectionInProcess,
	scp_SignalDataCollectionComplete,
	scp_SignalDataCollectionError,
	scp_SignalDataCollectionError_Retries,
	scp_SignalDataCollectionError_TooManyPoints,
	scp_SignalDataCollectionCancel,
	scp_NSignals

};

#define SCP_MAX_BUFFER  1024
#define SCP_N_MAX_RETRIES 10000

UINT WaitForDataThreadProc(LPVOID pParam );

UINT WaitForDataThreadProcChild(LPVOID pParam );
class CSerialComProcesses  
{
public:
	CSerialComProcesses();
	virtual ~CSerialComProcesses();

	HANDLE					m_hComPort;
	DCB						m_DCB ;
	COMMTIMEOUTS            m_TimeOuts;
	BYTE					*m_ubBuffer; 
	scp_Signal				m_ComSignal;
	short					m_ComNpts; 
	scp_TerminationType		m_whichTermination;
	short                   m_InComPoints;
	short                   m_MaxInComPoints;		// defaulted to SCP_MAX_BUFFER 
	short                   m_RetryCount;			//defaulted to SCP_N_MAX_RETRIES
	
	bool scp_OpenComPort(short sID); // 1 based number
	bool scp_SetBaud(short sBaud);

	bool scp_SetRTS(bool bVal);
	bool scp_SetDTR(bool bVal);

	bool scp_SetMaxBufferSize(short nPts);
	bool scp_SetComNpts(short nPts);

	bool scp_SendBuffer(BYTE *bBuf,short nPts);

	bool scp_WaitAndGetBuffer(scp_TerminationType  whichTermination);
	bool scp_WaitAndGetBuffer();// uses m_whichTermination

	bool scp_WaitAndGetThisBuffer(scp_TerminationType  whichTermination,BYTE * buf);
	bool scp_WaitAndGetThisBuffer(BYTE * buf);// uses m_whichTermination
};

#endif // !defined(AFX_SERIALCOMPROCESSES_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_)
