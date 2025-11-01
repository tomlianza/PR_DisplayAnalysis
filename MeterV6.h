/* MeterV6.h
*
* Copyright (c) 2005 - 2015 SpectraCal, LLC www.SpectraCal.com
* Copyright (c) 2016 SpectraCal, Inc
*
* $History: MeterV6.h $
*
*/

#pragma once

#ifndef AFX_METERV6_H__C814A817_0433_4DB1_B789_56D9E30D937E__INCLUDED_
#define AFX_METERV6_H__C814A817_0433_4DB1_B789_56D9E30D937E__INCLUDED_

#ifdef _WIN32
#define CMEXPORT __declspec(dllexport)
#else
#define CMEXPORT
#define __cdecl
#define __stdcall
#endif

#include "./libCommon/CalMAN.h"

#ifdef __cplusplus
extern "C" {
#endif

	CMEXPORT BOOL __cdecl CM_SDK_Meter_ListSerialPort(char *list, int *length, int meter, UINT32 manufacturer, UINT32 port);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_CreateWithSerialNumber(LPVOID &handle, int meter, int serialNumber);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_Destroy(LPVOID &handle);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetSerialNumber(LPVOID handle, char *serialnumber);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetDeviceSerialNumber(LPVOID handle, char *serialnumber);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetName(LPVOID handle, char *name);
	CMEXPORT BOOL __cdecl CM_SDK_Meter_IsConnected(LPVOID handle, BOOL *enable);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsTristimulus(LPVOID handle, BOOL *tristimulus);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsSpectrometer(LPVOID handle, BOOL *spectrometer);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetSpectrumBase(LPVOID handle, UINT32 *spectrumbase);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetSpectrumSize(LPVOID handle, UINT32 *spectrumsize);
	CMEXPORT BOOL __cdecl CM_SDK_Meter_GetSpectrumIncrement(LPVOID handle, UINT32 *increment);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetSpectrum(LPVOID handle, double *spectrum, UINT32 index);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetLowLightHandler(LPVOID handle, BOOL enable);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetLowLightHandler(LPVOID handle, BOOL *enable);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetLowExposure(LPVOID handle, double exposure);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetLowExposure(LPVOID handle, double *exposure);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetLowTrigger(LPVOID handle, double trigger);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetLowTrigger(LPVOID handle, double *trigger);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetHighExposure(LPVOID handle, double exposure);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetHighExposure(LPVOID handle, double *exposure);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetUnit(LPVOID handle, UINT32 unit);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetUnit(LPVOID handle, METER_UNITS *unit);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetButton(LPVOID handle, UINT32 button);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_HasButton(LPVOID handle, BOOL *hasbutton);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsButtonPressed(LPVOID handle, BOOL *buttonpressed);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetIsPointer(LPVOID handle, BOOL *ispointer);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetPointer(LPVOID handle, BOOL pointer);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetPointer(LPVOID handle, BOOL *pointer);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetIsIndicator(LPVOID handle, BOOL *indicator);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetIndicator(LPVOID handle, BOOL indicator);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetIndicator(LPVOID handle, BOOL *indicator);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsProjector(LPVOID handle, BOOL *projector);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsScreen(LPVOID handle, BOOL *screen);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsCRT(LPVOID handle, BOOL *crt);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetVersion(LPVOID handle, char *version);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetVersion2(LPVOID handle, char *version2);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetVersion3(LPVOID handle, char *version3);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_DarkCalibrate(LPVOID handle, BOOL *darkcalibrate);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsInit(LPVOID handle, BOOL *init);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_MaxCalibration(LPVOID handle, UINT32 *maxcalibration);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_NextCalibration(LPVOID handle, UINT32 *nextcalibration);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsDarkCalibrated(LPVOID handle, BOOL *darkcalibrated);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetDarkMessage(LPVOID handle, char *darkmessage);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_CRTSync(LPVOID handle, BOOL *crtsync);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsSync(LPVOID handle, BOOL *sync);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsCRTSynced(LPVOID handle, BOOL *crtsynced);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_IsUserSync(LPVOID handle, BOOL *usersync);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetRefreshRate(LPVOID handle, double refreshrate);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetRefreshRate(LPVOID handle, double *refreshrate);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetCRTMessage(LPVOID handle, char *crtmessage);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_Mode(LPVOID handle, MODES mode);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_CalibrationName(LPVOID handle, char *calibrationname, MODES mode);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetMatrix(LPVOID handle, double X[], double Y[], double Z[], MATRIX_TYPES type);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_SetSyncType(LPVOID handle, METER_SYNC synctype);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetSyncType(LPVOID handle, METER_SYNC *synctype);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_ReadSpectrum(LPVOID handle, UINT32 seconds);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_ReadXYZ(LPVOID handle, UINT32 seconds);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_TriggerXYZ(LPVOID handle, UINT32 seconds, UINT32 wait, double Y);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetMinY(LPVOID handle, double *miny);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetMaxY(LPVOID handle, double *maxy);

    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetX(LPVOID handle, double *x);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetY(LPVOID handle, double *y);
    CMEXPORT BOOL __cdecl CM_SDK_Meter_GetZ(LPVOID handle, double *z);

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_METERV6_H__C814A817_0433_4DB1_B789_56D9E30D937E__INCLUDED_)
