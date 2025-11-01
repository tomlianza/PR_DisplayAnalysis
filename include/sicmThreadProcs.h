#ifndef __SICMTHREADPROCS_H__
#define __SICMTHREADPROCS_H__

#ifdef USES_PP_THREADS
	using namespace std;
	#include <vector.h>
	#include <LApplication.h>
	#undef Sleep
	#include "LSimpleThread.h"
	#include "LThread.h"
	#include "UThread.h"
	#define THREAD_OBJECT LThread& inThread
	#define THREAD_OBJECT_PASS inThread
	#define THREAD_YIELD  inThread.Yield();
	#define THREAD_END_SUCCESS Process->EndThread(inThread, 0);
	#define THREAD_END_FAILURE Process->EndThread(inThread, 1);
	#define PP_THREAD_ARG LThread& inThread,
	#define PP_THREAD_PASS inThread,
#else	
	#define THREAD_OBJECT void*
	#define THREAD_OBJECT_PASS NULL
	#define THREAD_YIELD 
	#define THREAD_END_SUCCESS Process->EndThread(0);
	#define THREAD_END_FAILURE Process->EndThread(1);
	#define PP_THREAD_ARG
	#define PP_THREAD_PASS
#endif

#ifdef WIN32
#ifndef STALL
#define STALL Sleep(10)
#endif
#endif

#ifndef WIN32
#ifdef MWERKS_8
	//Metroworks defns go here
	#define STALL millisecondSleep(0)
	#include "DataPersistance.h"
#else
	//OS X
	//#define Sleep(x) usleep(x*1000)
	#define STALL sleep(0)
	#include <pthread.h>
	#ifndef LINUX
		#include "FakeMacTypes.h"
	#endif
#endif
#endif

#ifdef LINUX
	#include "linuxTypes.h"
#endif

#define BAILONCANCEL {if (Process->IsCancelling()) goto BailOnCancel;}


UINT VerboseMeasurementThreadProc( 
#ifdef USES_PP_THREADS
LThread& inThread,
#endif
LPVOID pParam );

UINT SetDarkLuminanceThreadProc(
PP_THREAD_ARG
LPVOID pParam );

UINT VerboseSetDarkPointThreadProc( 
PP_THREAD_ARG
LPVOID pParam );

UINT sicmDoCalibrationThreadProc(
PP_THREAD_ARG
void* pParam); // simple call to do the whole enchilada as thread

UINT sicmDoVerifyThreadProc(
PP_THREAD_ARG
void* pParam); // simple call to do only a verification run

UINT sicmDoAmbientThreadProc(
PP_THREAD_ARG
void * pParam);

UINT SetBlackPointThreadProc(
PP_THREAD_ARG
LPVOID pParam); 

UINT VerboseSetMaxLumThreadProc(
PP_THREAD_ARG
LPVOID pParam);

UINT SetAbsouteDarkLuminanceThreadProc(
PP_THREAD_ARG
LPVOID pParam);


#ifdef CHARACTERIZE_DISPLAY
UINT CharacterizeDisplayThreadProc( 
PP_THREAD_ARG
LPVOID pParam );
#endif

#ifdef INTERNAL_LUT_VERIFY
UINT sicmDoInternalLUTVerifyThreadProc(
									   PP_THREAD_ARG
									   void* pParam); // simple call to do the whole enchilada as thread
#endif



#endif
