

//MonitorEnumeration.h
/******************************************************************************
**
**  Project Name: Enable Cable
**     File Name: MonitorEnumeration.h
**
**   Description: Routines to aid in detection of monitor types 
**
*******************************************************************************
**                         C O P Y R I G H T
*******************************************************************************
**
**     Copyright (c) 1989-2000 Sequel Imaging, Inc., Londonderry NH
**            THIS INFORMATION IS COMPANY CONFIDENTIAL
**
** NOTICE:  This material is a confidential trade secret and proprietary 
** information of Sequel Imaging, Inc. which may not be reproduced, used, 
** sold, or transferred to any third party without the prior written consent 
** of Sequel Imaging.  This material is also copyrighted as an unpublished work 
** under sections 104 and 408 of Title 17 of the United States Code.  
** Unauthorized use, copying, or other unauthorized reproduction of any form
** is prohibited.
**
*******************************************************************************
**                   R E V I S I O N   H I S T O R Y
*******************************************************************************
**
**
********************************************************************************/

#ifndef _MONITORENUM_
#define _MONITORENUM_
#define MAX_BUFSIZE      1024
#include "ab_i2c.h"
#include "osType.h"

typedef struct _ME_MonitorInfo
{
	char cName[MAX_BUFSIZE];
	char cID[MAX_BUFSIZE];
	char cEDID[128];
	char cModel[16];
	bool bIsValid;
	EDIDV13 edid;

}ME_MonitorInfo;

typedef struct _ME_MonitorInfoList
{
		short nItems;
		ME_MonitorInfo  *miList[256];


} ME_MonitorInfoList;

bool  ME_GetMonitorList(ME_MonitorInfoList *theList); 
bool  ME_DisposeOfMonitorList(ME_MonitorInfoList *theList);
short ME_FindMonitor(unsigned char *edid, ME_MonitorInfoList *theList);// matches a monitor edid to the edid in the registry list

#ifdef WIN32
HKEY  GetNMonitors(short *nMonitors);
DWORD GetMonitorRegistryInfo(HKEY hKey, DWORD index, char *cName, char*cID, char *edid, bool *isValid);
bool ME_GetCurrentMonitorInfo (DISPLAY_DEVICE *dd);
BOOL CALLBACK MonitorInfoEnumCallback(HMONITOR hm, HDC , RECT* , LPARAM hInfo);
DWORD GetEDIDForCurrentMonitor(char* regKey, char *edid, bool *isValid);
#endif

#endif