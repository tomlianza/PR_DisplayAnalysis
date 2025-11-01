//sicmConfigurationMgr.H
#ifndef _SICMCM_
#define _SICMCM_
#include <time.h>

#include "stdafx.h"
#include "CPreset.h"
#include "CVesaMonitor.h"

#error OBSOLETE, USE CVesaMonitor Functions instead as follows: sicmGetStartUpData -> CVM::LoadDSDB(), sicmSetStartUpData -> CVM::SaveDSDB()

bool  sicmGetStartUpData(char * cTempRegistryKeyName, DSDB *data);
bool  sicmSetStartUpData(char * cTempRegistryKeyName, DSDB *data);
#endif
