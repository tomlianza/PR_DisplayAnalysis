// CMonitorWorld class

#ifndef CMONITORWORLD_H_INCLUDED
#define CMONITORWORLD_H_INCLUDED

#include "CMonitorWorldBase.h"
#include "CDisplayAdapter.h"
#include "CVesaMonitor.h"

#ifdef WIN32
  #include "CWinMonitorWorld.h"
#else
  #ifdef LINUX
  #include "CLinuxMonitorWorld.h"
  #else
  #include "CMacMonitorWorld.h"
  #endif
#endif

#endif
