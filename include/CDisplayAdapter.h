#ifndef CDISPLAYADAPTER_H_INCLUDED
#define CDISPLAYADAPTER_H_INCLUDED
#include "CDisplayAdapterBase.h"

#ifdef WIN32
#include "CWinDisplayAdapter.h"
#else
#ifdef LINUX
#include "CLinuxDisplayAdapter.h"
#else
#include "CMacDisplayAdapter.h"
#endif
#endif

#endif
