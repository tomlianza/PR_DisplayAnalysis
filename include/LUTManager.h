// LutManager.h: interface for the CLutManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LUTMANAGER_H__E2D70980_6415_11D2_B9F6_004033E05B37__INCLUDED_)
#define AFX_LUTMANAGER_H__E2D70980_6415_11D2_B9F6_004033E05B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MonitorMeasurements.h"
#include "DirecDac.h"




// Matrox definitions 
#define MTX_MAKEBOARDCURRENT        0x4D54586C
typedef struct _BOARD_OPERATION 
{ 
    ULONG   ulBoardId; 
    ULONG   ulOperation; 
} BOARD_OPERATION, *PBOARD_OPERATION;


// Definitions for ulOperation 
#define SET_GAMMA_RAMP     0x00000001 
#define GET_GAMMA_RAMP     0x00000002
#define MTX_GETGAMMARAMP            0x4D54586E 
#define MTX_SETGAMMARAMP            0x4D54586F

/************************************************************\
ExtEscape(hDC, 
              MTX_MAKEBOARDCURRENT,             // iEsc 
              sizeof(BOARD_OPERATION),          // cjIn 
              &BoardOperation,                  // pvIn 
              0,                                // cjOut 
              NULL;                             // pvOut




    USHORT  Array[3*256];


    ExtEscape(hDC, 
              MTX_GETGAMMARAMP,             // iEsc 
              0,                            // cjIn 
              NULL,                         // pvIn 
              3*256*sizeof(USHORT),         // cjOut 
              &Array[0]);                   // pvOut


    ExtEscape(hDC, 
              MTX_SETGAMMARAMP,             // iEsc 
              3*256*sizeof(USHORT),         // cjIn 
              &Array[0],                    // pvIn 
              0,                            // cjOut 
              NULL);                        // pvOut


\********************************************************************/



typedef enum _WhichLutFormat
{
	LutFormatNotSupported = - 1,
	LutFormatPlanarByte = 0, //standard Win98 default on construction
	LutFormatChunkyByte,
	LutFormatMatrox,
	LutFormatATI,
	LutFormatPlanarWordIntel, // Word tables in Intel format RGB order;
	LutFormatPlanarWordMot,   // Little Endian word tables
	
}LutFormat;

typedef enum _WhichLutAPI
{

	LutAPIWin98 = 0,
	LutAPIWinNTCustom,
	LutAPIWinNTMatrox,
	LutAPISGINTPlatform,
	LutAPIWinNTEntechDll


}LutAPI;


typedef struct _Lut8 
{

	unsigned char Red[256];
	unsigned char Green[256];
	unsigned char Blue[256];

}Lut8;

class CLutManager  
{
public:
	CLutManager();
	virtual ~CLutManager();
	bool OpenLutManager();
	void SetLinearLut();
	bool SetCurrentLut(); // assumes format and api are correct and m_pCurrentLuts is initialized 
//	bool GetCurrentLut(); // as above and it saves it to the pointed location.....
	bool GetCurrentLutLocal(); // as above, saves to the local formatted copy.

	// Use these routine to save without formatting.  
	bool GetCurrentLutPhysical(); // used to make physical copy only for later restoration
	bool RestoreCurrentLutPhysical(); // restore the lut using copy from GetCurrentLut....
// some low level routines for simple applications
	bool GetLut8();
	bool SetLut8();


	// public variables  must be set prior to calling 
	CWnd	  *m_CWnd;
	HDC        m_hDC;
	LutFormat m_whichFormat;
	LutAPI    m_whichAPI;
	Lut8      m_Lut8;
	// public elements of the the class for inspection
	OSVERSIONINFO   m_osVersionInfo;
	bool m_bIsWin98orLater;
	bool m_bIsWinNT;

	MonitorLuts *m_pCurrentLuts, m_CurrentCopy;
	
	unsigned short usPlut[768]; // storage for physical lut. 


private:

	
	BOARD_OPERATION  BoardOperation; // used for matrox board stuf....
	bool bCurrentLutCached; // Set and reset by public get/restore pair
	bool SaveCurrentLutToCopy();
	bool pLoadLutPhysical(unsigned char *lut);// formatting assumed
	bool pGetLutPhysical(unsigned char *lut); // no formatting use inconjuction with pSetLutPhysical
	bool pSetLutPhysical(unsigned char *lut); // no formatting assumed

	LutFormat pCheckLutFormat();
};

#endif // !defined(AFX_LUTMANAGER_H__E2D70980_6415_11D2_B9F6_004033E05B37__INCLUDED_)
