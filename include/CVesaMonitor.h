#ifndef CVESAMONITOR_H_INCLUDED
#define CVESAMONITOR_H_INCLUDED

#include "CVesaMonitorBase.h"

#ifdef WIN32
#include "CWinVesaMonitor.h"
#else
#ifdef LINUX
#include "CLinuxVesaMonitor.h"
#else
#include "CMacVesaMonitor.h"
#endif
#endif

#endif
