// SIM2Projector.h: interface for the CSIM2Projector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIM2PROJECTOR_H__2507DB05_B089_414D_83ED_BA285967797E__INCLUDED_)
#define AFX_SIM2PROJECTOR_H__2507DB05_B089_414D_83ED_BA285967797E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "Sip2Utils.h"
#include "ColorStructs.h"

typedef struct {
//DATA FROM win32io.c
	DCB		CommDCB;               // DCB for comm port
	HANDLE	PortID;              // The comm port id
	COMSTAT	CommStat;              // COMSTAT info buffer for comm port
	char	comPortString[8];

/*******************************************************
 * static variables 
 *******************************************************/
	unsigned long	DiffTime;
	time_t			StartTime;
	time_t			CurrentTime;
	COMMTIMEOUTS	TimeOutData;
	HANDLE			hDev;
	FILE			*fout;
} SIM2_WIN32IODATA;

/*
typedef enum {
  USERDEF_TYPE_EVENT = 2,
  USERDEF_TYPE_PARAM = 25,
  USERDEF_TYPE_USEROP = 26,
} teUserDefTypes;
*/

//
// Define Photon EEPROM Map
//
#define EE_SIZE					256

#define EE_SERIAL_NUMBER		0	// 0 - 3, 4 bytes
#define EE_MATRIX_1				4	// 4 - 39, 9 floats x 4 bytes
#define EE_BLACK_OFFSETS		120	// 120 - 136


typedef struct {
	BYTE	Status;
	double	dIntTime;
	dYxy	dYxyMeas;
	dXYZ	dXYZMeas;
	dRGB	dRGBMeas;
	BYTE	eeprom[256];
	ULONG	ulSerNo;
	double	dMatrix[9];
	double	dFlare[3];
} PhotonHdr;




#define SIM2_SUCCESS			0
#define SIM2_FAILURE			-1
#define SIM2_ERR_ALREADY_OPEN	-100
#define SIM2_ERR_NO_COMM		-101
#define SIM2_NOT_OPEN			-102

class CSIM2Projector  
{
public:
	long photonReadFromEEPROM(unsigned char eeaddr, unsigned long *ulvalue);
	long photonReadFromEEPROM(unsigned char eeaddr, float *fvalue);
	long photonLoadParameters();
	long photonStoreCalibration(short index, double *dmtx, CString name, unsigned long datetime);
	long photonCalculateMeasData(dRGB dRGBMeas);
	long photonSetIntTime(double dIntTime);
	long photonMeasureYxy(dYxy *dYxyMeas, bool bMeas);
	long photonMeasureXYZ(dXYZ *dXYZMeas, bool bMeas);
	long photonMeasureRGB(dRGB *dRGBMeas, bool bMeas);
	long photonWriteToEEPROM(unsigned short eeaddr, float fvalue);
	long photonCmdWriteEEByte(unsigned short usAddress, unsigned char ucByte);
	long photonCmdReadEEByte(unsigned short usAddress, unsigned char *ucByte);
	long photonWriteToEEPROM(unsigned short eeaddr, double dvalue);
	long photonGetVersion(char *szVersion);
	PhotonHdr	m_photon;
	long m_err;
	long photonGetIntTime(double *dIntTime);
	short m_sInCount;
	short m_sOutCount;
	BYTE m_bInBuffer[1024];
	BYTE m_bOutBuffer[1024];
	BYTE m_bCommand[64];
	long SendCommand(unsigned char *ucOutBuf, short sOutCnt);
	unsigned int m_uiCheckSum;
	unsigned short int CalculateCRC16(BYTE *pcData, int nCount);
	long SendGetCommand(unsigned char *ucOutBuf, short sOutCnt, unsigned char *ucInBuf, short *sInCnt, unsigned long ulDelaymSec=50);
	long StandBy();
	long On();
	long ReadData(unsigned char *ucInBuf, short *sInCnt);
	long SetMediumSpokeOff();
	long SetMediumSpokeOn();
	long SetLowSpokeOff();
	long SetLowSpokeOn();
	long SetHighSpokeOn();
	long SetHighSpokeOff();
	long SetClear();
	long SetYellow();
	long SetBlack();
	long SetMagenta();
	long SetCyan();
	long SetBlue();
	long SetGreen();
	long SetRed();
	long SetWhite();
	long SendData(unsigned char *ucOutBuf, short sOutCnt);
	SIM2_WIN32IODATA	win32IOData;
	long setup_dcb ( short port, short settings, short lineflag );
	long Open(short sComPort);
	long Close();
	bool m_bIsOpen;
	CSIM2Projector();
	virtual ~CSIM2Projector();

};

#endif // !defined(AFX_SIM2PROJECTOR_H__2507DB05_B089_414D_83ED_BA285967797E__INCLUDED_)
