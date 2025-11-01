/* CalMANv6.h
 *
 * Copyright (c) 2005 - 2015 SpectraCal, LLC www.SpectraCal.com
 * Copyright (c) 2016 SpectraCal, Inc
 *
 * $History: CalMANv6.h $
 *
 */

#pragma once

#ifndef AFX_CALMANV6_H__CC6F3BD1_E436_48FD_91C0_F5A783CA438A__INCLUDED_
#define AFX_CALMANV6_H__CC6F3BD1_E436_48FD_91C0_F5A783CA438A__INCLUDED_

#ifdef _WIN32
#define CMEXPORT __declspec(dllexport)
#else
#define EXPORT
#define __cdecl
#define __stdcall
#endif

#include "CalMAN.h"  //changed from dll program 


BOOL SetError(ERRORS error);

#ifdef __cplusplus
extern "C" {
#endif

    CMEXPORT BOOL   __cdecl CM_SDK_Initialize(INITIALIZE_CALMAN *Initialize, WriteLogCallback  WriteLog, DecryptToCallback DecryptTo);
    CMEXPORT void   __cdecl CM_SDK_Cleanup();
    CMEXPORT ERRORS __cdecl CM_SDK_GetError(void);

    typedef BOOL(__stdcall *WriteLogCallback) (char *, int);
    typedef BOOL(__stdcall *DecryptToCallback)(char *, char *);

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_CALMANV6__CC6F3BD1_E436_48FD_91C0_F5A783CA438A__INCLUDED_)
