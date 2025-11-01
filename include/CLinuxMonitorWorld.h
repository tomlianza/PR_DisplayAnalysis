#ifndef __CLINUXMONITORWORLD_H__
#define __CLINUXMONITORWORLD_H__

#include "CMonitorWorldBase.h"
#include "CDisplayAdapter.h"
#include "CVesaMonitor.h"

class CMonitorWorld : public CMonitorWorldBase
{
public:
	CMonitorWorld();
	virtual ~CMonitorWorld();

	bool Init();
	void InventoryMonitors();


		// for now, assume we only have 1, we'll need to search the code base
		// for myDisplays and fix the index in all occurances.
	//CGDirectDisplayID myDisplays[kMaxMacDisplays];
};

#endif