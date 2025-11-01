#ifndef EDID_SUPPORT_H_INCLUDED
#define EDID_SUPPORT_H_INCLUDED

DWORD XGetEDIDForCurrentMonitor(char* regKey, char *edid, bool *isValid);
void InventoryMonitors();
BOOL CALLBACK XMonitorInfoEnumCallback(HMONITOR hm, HDC hDC , RECT* , LPARAM hInfo);
double DecodeChromaticity(short sVal);
short EDIDFillShort(char *cBuf, short sOffset);
BYTE EDIDFillByte(char *cBuf, short sOffset);
long EDIDFillLong(char *cBuf, short sOffset);
double DecodeChromaticity(short sVal);

typedef enum {
	MEM_ORIENTATION_UNKNOWN,
	MEM_ORIENTATION_LITTLE_ENDIAN,
	MEM_ORIENTATION_BIG_ENDIAN
} MEM_ORIENTATION;

MEM_ORIENTATION GetMemOrientation();


/***********************************************************************************\

	the edid 1.3 data is stored in a byte aligned array.  The routine Parse EdidV13
	extracts the data and puts it into the structure that follows.

\***********************************************************************************/
typedef struct _DetailedTiming{
	WORD PixelClock;
	BYTE HorizontalActive;
	BYTE HorizontalBlacking;
	BYTE PackedUpperHorBits;
	BYTE VerticalActive;
	BYTE VerticalBlanking;
	BYTE PackedUpperVertBits;
	BYTE HorizontalSyncOffset;
	BYTE HorizontalSyncPulseWidth;
	BYTE PackedVerticalBits;
	BYTE PackedUpperSyncBits;
	BYTE HorizontalImageSize;
	BYTE VerticalImageSize;
	BYTE HorVertPackedUpperBits;
	BYTE HorizontalBorder;
	BYTE VerticalBorder;
	BYTE Flags;

	}DetailedTiming;

typedef struct _MonitorDescriptorBlock{
	
	WORD wFlag; // 00 when used as block Desriptor;
	BYTE bFlag; // 0 when used as block Descriptor;
	BYTE bDataType; 
	BYTE bFlag2; // 0 when used as block Descriptor;
	BYTE bData[14]; 

	}MonitorDescriptorBlock;

typedef struct _edid13{
	unsigned short sIDManName;
	unsigned short sIDProductCode;
	unsigned long  LIDSerialNumber;
	short sWOM;
	short sYOM;
	unsigned short sVersion;
	unsigned short sRevsision;
	unsigned short sVID;
	short sMaxHorizontalSize;
	short sMaxVerticalSize;
	short sGamma;
	short sFeatureSuport;
	double dRedx;
	double dRedy;
	double dGreenx;
	double dGreeny;
	double dBluex;
	double dBluey;
	double dWhitex;
	double dWhitey;
	short  sET1;
	short  sET2;
	short  sMRT;
	short  sSTI1;
	short  sSTI2;
	short  sSTI3;
	short  sSTI4;
	short  sSTI5;
	short  sSTI6;
	short  sSTI7;
	short  sSTI8;
	DetailedTiming dDTD1;
	MonitorDescriptorBlock  dDTD2;
	MonitorDescriptorBlock  dDTD3;
	MonitorDescriptorBlock  dDTD4;
	char strSerialNumber[32];
	bool bIsDigital;
}EDIDV13;

typedef enum _EDIDV13ERROR
{
	EDIDV13_ERROR_OK = 0,
	EDIDV13_ERROR_BAD_VER,
	EDIDV13_ERROR_BAD_REV

}EDIDV13ERROR;

bool GetNameFromEDID(EDIDV13 *edid, char *name);
bool GetSerialNumberFromEDID (EDIDV13 *edid, char *serialNumber);
bool GetModelFromEDID (EDIDV13 *edid, int *model);
bool GetMfgFromEDID (EDIDV13 *edid, int *mfg);
EDIDV13ERROR  ParseEDIDV13(char *cBuf ,EDIDV13 *edidV13);

#endif
