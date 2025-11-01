// MarantzSensorInterface.h: interface for the CMarantzSensorInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MarantzSensorInterface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_)
#define AFX_MarantzSensorInterface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LenscapSensorInterfaceBase.h"
#include "cieColor.h"
#include "matrix.h"



class CMarantzSensorInterface : public CLenscapSensorInterfaceBase
{
public:

#define XSCP_MAX_BUFFER  1024
#define XSCP_N_MAX_RETRIES 10000

#define MSG_SIZE_SHORT 13
#define MSG_SIZE_LONG 31
#define MSG_SHORT_ETX 9

	bool DecodeIntTimeMessage(char *buf, RECEIVED_BLOCK *msg);
	bool FormatAndSendIntTimeMessage(char cReq, double dIntTime);
	long GetIntTime(double *dIntTime);
	long SetIntTime(char cRequest, double dIntTime);

	virtual bool xscp_Init();

	bool FormatAndSendShortMessage(int cmd, int head, char d4_1 = ' ', char d4_2 = ' ', char d4_3 = ' ', char d4_4 = ' ');

	bool FormatAndSendLongMessage(int cmd, int head, char d4_1 = ' ', char d4_2 = ' ', char d4_3 = ' ', char d4_4 = ' ',
		double d3 = 0.0, double d2 = 0.0, double d1 = 0.0);

	void ComputeAndInsertBCC (char *start, int numBytes, char *hi, char *lo);

	bool ReceiveAndDecodeMessage (char *buf, RECEIVED_BLOCK *msg);
	bool DecodeShortMessage (char *buf, RECEIVED_BLOCK *msg);
	bool DecodeLongMessage (char *buf, RECEIVED_BLOCK *msg);
	long MeasureYxy();

	bool GetCorrelatedTemp(double *,double *,double *);
};
#endif
