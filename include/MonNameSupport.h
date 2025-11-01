#ifndef MONNAME_SUPPORT_H_INCLUDED
#define MONNAME_SUPPORT_H_INCLUDED

typedef struct 
{
	POINT pt;
	char name[256];
	char serialNumberStr[256];
	int mfg;
	int model;
	RECT rect;
	char deviceID[256];
} MON_INFO_STRUCT;

bool GetMonitorInfoFromPoint(MON_INFO_STRUCT *info);

#endif