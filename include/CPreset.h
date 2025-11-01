#ifndef CPRESET_H_INCLUDED
#define CPRESET_H_INCLUDED

#ifdef DONT_INCLUDE_LIST
#else
	#include <list>
#endif


#ifdef USE_NEW_CPRESET_ARCH

#else
    #define USE_ORIGINAL_PRESET_ARCH
#endif


using namespace std;
#include "CPresetBase.h"




//this file also works with linux
#ifdef LINUX
    #include <stdio.h>
#endif

class CPreset : public CPresetBase
{
public:
	CPreset();
	virtual ~CPreset();
};

typedef list<CPreset*> CPRESETLIST;


#endif
