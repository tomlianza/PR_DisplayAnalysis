/* CM_Defines.h
*
* Copyright (c) 2005 - 2015 SpectraCal, LLC www.SpectraCal.com
* Copyright (c) 2016 SpectraCal, Inc
*
* $History: CM_Defines.h $
*
*/

#pragma once

#ifndef AFX_CM_DEFINES_H__CA128181_9366_4A17_B2CE_65CB116A3DDA__INCLUDED_
#define AFX_CM_DEFINES_H__CA128181_9366_4A17_B2CE_65CB116A3DDA__INCLUDED_

#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef _WIN32
#define _gcvt gcvt
#define INVALID_HANDLE_VALUE -1 //((void *)(long long)-1)
#define LPVOID void*
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;
typedef int BOOL;
typedef unsigned int UINT32;
typedef long unsigned int UINT64;
typedef unsigned char UINT8;
typedef unsigned char BYTE;
typedef unsigned short WORD;
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef VK_F1 
#define VK_F1             0x70
#endif

#ifndef VK_F5
#define VK_F5             0x74
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef NULL
#define NULL 0
#endif

#endif
